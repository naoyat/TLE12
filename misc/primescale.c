#include <stdio.h>

#define M 10000
main(){
  int prime[M], i, j;
  for (i=0; i<M; ++i) prime[i] = 1;
  prime[0] = prime[1] = 0;
  for (i=2; i<M; ++i) {
    if (!prime[i]) continue;
    for (j=i*2; j<M; j+=i) prime[j] = 0;
  }
  for (i=0; i<M; ++i) {
    putchar( prime[i] ? '-' : '*' );
  }
  printf("\n");
}
