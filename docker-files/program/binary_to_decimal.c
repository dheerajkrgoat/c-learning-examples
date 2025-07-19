
#include<stdio.h>
void main()
 {
    int a,n,k,l=0,i,j;
    printf("\nEnter the number of digits in the binary input:\n");
    scanf("%d",&n);
    printf("\nEnter the binary digits one by one:\n");
    for(i=0;i<n;i++)
     {
        scanf("%d",&a);
        if(a==0)
         {
            continue;
         }
        else
         {
            k=1;
            for(j=0;j<n-i-1;j++)
             {
                k=k*2;
             }
           l=l+k;
         }
     }
     printf("\nThe corresponding decimal number is %d\n",l);
 }
