#include <iostream>
using namespace std;int L=1;class N{int m,d;N*l,*r;public:N(int M,int D){m=M;d=D;l=r=0;}int a(int x){return 1+(x<m?l?l->a(x):(l=new N(x,d+1),1):r?r->a(x):(r=new N(x,d+1),1));}int p(){if(r)r->p();if(l)l->p();if(L==d)cout<<m<<' ';}};int main(){int n,x;cin>>n;if(n){cin>>x;N*r=new N(x,1);while(--n){cin>>x;L=max(L,r->a(x));}for(;L;--L)r->p(),cout<<endl;}return 0;}