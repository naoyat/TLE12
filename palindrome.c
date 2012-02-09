l,i,q;main(n){char b[1];scanf("%d\n",&n);while(n--){gets(b);q=0,i=l=strlen(b)-1;while(--i)q+=b[i]!=b[l-i];puts(q?"NO":"YES");}}
