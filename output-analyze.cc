#include <stdio.h>
#include <ctype.h>
#include <string.h>
inline void swap(int &a, int &b) { int t=a; a=b; b=t; }

int f(int a,int b,int m){
  if (m<0) swap(a,b);
  if (a<='9') {
    return (b-a+100)%10;
  } else if (a<='Z') {
    return (b-a+260)%26;
  } else {
    return (b-a+260)%26;
  }
}
int g(int a, int d) {
  if (a <= '9') {
    int x = (a - '0') + d;
    if (x >= 80) x += 4;
    return '0' + (x+1000) % 10;
  } else if (a <= 'Z') {
    int x = (a - 'A') + d;
    if (x >= 63) x += 4;
    return 'A' + (x+2600) % 26;
  } else {
    int x = (a - 'a') + d;
    if (x >= 31) x += 4;
    return 'a' + (x+2600) % 26;
  }
}
int main() {
  FILE *fp1=fopen("data/OUTPUT-in.txt","r");
  FILE *fp2=fopen("data/OUTPUT-out.txt","r");

  char buf1[200], buf2[200];
  for (int i=0; i<100; i++) {
    fgets(buf1, 200, fp1);
    fgets(buf2, 200, fp2);
    int len = strlen(buf1), len2 = strlen(buf2);
    for (int j=1,pm=-1; j<len-1; j++,pm=-pm) {
      if (pm < 0) continue;
      int c1 = buf1[j], c2 = buf2[j];
      int d = f(c1,c2,pm);
      int e = g(c1,j*pm);
      printf("%c",c1);
      printf(", pos %3d (%+4d)", j, j*pm);
      printf(" -> estim %c,", e);
      printf(" %s", e==c2 ? "   ":"but");
      printf(" actually %c (%2d)", c2, d);
      printf(", line %2d ", i);
      printf("\n");
    }
  }
  
  fclose(fp1);
  fclose(fp2);
}

