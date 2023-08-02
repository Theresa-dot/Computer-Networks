#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void main()
{
    int maxp=6;
    int a[50],temp[70],temp2[70];
    int t,i,j,k,nd,n,nh,sum=0,pos=0;

    printf("Enter Length of Data String: ");
    scanf("%d",&nd);
    printf("Enter Data String: ");
    for(i=0;i<nd;i++)
    {
        scanf("%d",&a[i]);
    }
    printf("-----------------------------------\n");
    for(i=0,j=0;i<nd;i++)
    {
        for(k=0;k<maxp;k++)
        {
            t=pow(2,k)-1;
            if(j==t)
            {
                temp[j]=0;
                j++;
            }
        }
        temp[j]=a[i];
        j++;
    }
    nh=j;
    printf("Length of Hamming code: %d bits\n",nh);
    n=nh-nd;
    printf("Number of Parity Bits: %d \n",n);

    int b[n];
    int m=n-1;
    for(k=0;k<n;k++)
    {
        t=pow(2,k)-1;

        for(i=t;i<nh;)
        {
            for(j=0;j<=t;j++)
            {
                sum=sum+temp[i];
                i++;
                if(i>=nh)
                    break;
            }

            if(i>=nh)
                break;

            for(j=0;j<=t;j++)
            {
                i++;
                if(i>=nh)
                    break;
            }

            if(i>=nh)
                break;
        }
        temp[t]=sum%2;
        sum=0;
        printf("P%d: %d\n",t+1,temp[t]);
    }


    printf("\nHamming code: Sender side:   ");
    for(i=0;i<nh;i++)
    {
        printf("%d ",temp[i]);
    }


    printf("\nHamming code: Receiver side: ");
    for(i=0;i<nh;i++)
    {
        scanf("%d",&temp2[i]);
    }
    sum=0;
    for(k=0;k<n;k++)
    {
        t=pow(2,k)-1;

        for(i=t;i<nh;)
        {
            for(j=0;j<=t;j++)
            {
                sum=sum+temp2[i];
                i++;
                if(i>=nh)
                    break;
            }

            if(i>=nh)
                break;

            for(j=0;j<=t;j++)
            {
                i++;
                if(i>=nh)
                    break;
            }

            if(i>=nh)
                break;
        }
        b[m]=sum%2;
        sum=0;
        printf("P%d: %d\n",t+1,b[m]);
        m--;
    }
    for(m=0;m<n;m++)
    {
        pos=pos+b[n-m-1]*pow(2,m);
    }
    printf("Position of Error: %d\n",pos);
    if(temp2[pos-1]==0)
        temp2[pos-1]=1;
    else
        temp2[pos-1]=0;

    printf("\nHamming code: Receiver side: Error Corrected:  ");
    for(i=0;i<nh;i++)
    {
        printf("%d ",temp2[i]);
    }

    printf("\n-----------------------------------\n");
}