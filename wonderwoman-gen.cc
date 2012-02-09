#include <iostream>
#include <vector>
#include <utility>
#include <string>
#include <queue>

using namespace std;
#include <stdio.h>
#include <string.h>

#include "cout.h"

#define sz(a)  int((a).size())
#define pb  push_back
#define all(c)  (c).begin(),(c).end()
#define tr(c,i)  for(typeof((c).begin()) i=(c).begin(); i!=(c).end(); i++)
#define rep(var,n)  for(int var=0;var<(n);++var)
#define found(s,e)  ((s).find(e)!=(s).end())

typedef pair<int,int> ii;

vector<string> huffman_table;

class Node {
 public:
  Node(int val, int c) { sum = val; ch = c; left = right = NULL; }
  Node(Node *a, Node *b) { // a > b
    sum = a->sum + b->sum; ch = -1; left = a; right = b; }
  ~Node() { if (left) delete left; if (right) delete right; }
  int sum;
  int ch;
  Node *left, *right;
  void dump(string code) {
    if (ch >=0) {
      huffman_table[ch] = code;
    }
    if (left) left->dump(code + "1");
    if (right) right->dump(code + "0");
  }
};

int main(){
//FILE *fp = fopen("data/wonder-woman.txt", "r");
  FILE *fp = fopen("data/wonder-flip.txt", "r");
  
  int c, lastc=EOF, len=0;
  map<ii,int> token_count;
  map<ii,int> token_ids; int token_id_ser = 0;
  vector<ii> tokens;
  vector<int> str;

  while (c = fgetc(fp)) {
    if (c == lastc) {
      len++;
    } else {
      if (lastc != EOF) {
        int bx = (lastc == ' ') ? 2 : 10000;
        for (int unit=1, l=len; l; unit*=bx, l/=bx) {
          int cnt = l % bx;
          if (!cnt) continue;
          for (int j=0; j<cnt; ++j) {
            pair<int,int> token(lastc, unit);
            if (found(token_count,token)) {
              // known token
              int token_id = token_ids[token];
              token_count[token]++;
              str.push_back(token_id);
            } else {
              // new token
              int token_id = token_id_ser++;
              token_ids[token] = token_id;
              tokens.push_back(token);
              token_count[token]=1;
              str.push_back(token_id);
            }
          }
        }
      }
      
      len = 1;
      if (c == EOF) break;
      lastc = c;
    }
  }

  int T = token_count.size();
  huffman_table.resize(T);

  priority_queue<pair<int,Node*> > pq;
  tr(token_count,it){
    ii token = it->first; int count = it->second;
    int token_id = token_ids[token];
    pq.push(make_pair(-count,new Node(count, token_id)));
  }

  Node *root = NULL;
  while (true) {
    pair<int,Node*> u = pq.top(); pq.pop(); // more
    if (pq.empty()) { root = u.second; break; }
    pair<int,Node*> v = pq.top(); pq.pop(); // less
    pq.push(make_pair(u.first+v.first, new Node(u.second,v.second)));
  }
  if (root) {
    root->dump("");
  }

  int S = str.size();
  stringstream ss;
  rep(i,S){
    ss << huffman_table[str[i]];
  }

  string bitstr = ss.str();
  len = bitstr.size();

  printf("unsigned char*D=\"");
  for (int i=0; i<len; i+=8) {
    int ch = 0;
    for (int j=0; j<8; ++j) {
      if (i+j < len)
        ch = ch*2 + bitstr[i+j] - '0';
      else
        ch = ch*2;
    }
    switch(ch) {
      case '\r':
        putchar('\\'); putchar('r'); break;
      case '\n':
        putchar('\\'); putchar('n'); break;
      case '\\':
        putchar('\\'); putchar('\\'); break;
      case '"':
        putchar('\\'); putchar(ch); break;
      default:
        putchar(ch); break;
    }
  }
  printf("\";");
//printf("typedef unsigned int I;int q[]={");
  printf("typedef long long I;int q[]={");
  rep(token_id,T) {
    ii token = tokens[token_id];
    int ch = token.first, rep = token.second;
    const char *bit = huffman_table[token_id].c_str();
    int bl = strlen(bit);
    int val = 0;
    rep(i,bl) {
      val = val*2 + (bit[i] - '0');
    }
    printf("%d,%d",bl,val);
    if (ch == ' ') printf(",%d",-rep);
    else           printf(",%d",ch);
    if (token_id < T-1) putchar(',');
  }
  printf("};I b=0,r=0,i=0,c,m,o,e,B,M;main(Z){for(;i<%d;){if(r<16){b<<=16;b|=*(D++)<<8;b|=*(D++);r+=16;}for(c=0;c<%d;){B=q[c++],M=q[c++],Z=q[c++],o=r-B,m=(1<<B)-1;if((b>>o&m)==M){e=1;if(Z<0)e=-Z,Z=32;while(e--)putchar(Z);b&=(1<<o)-1;r-=B;i+=B;break;}}}return 0;}", len,T*3);
  fclose(fp);
  return 0;
}
