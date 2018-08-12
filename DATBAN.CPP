#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <alloc.h>
#include <time.h>
typedef struct data
{
 long int value;
 struct data huge *next;
};
const long N=5000;
// int a[n],b[n],tmp[n];
long int a[N],b[N],tmp[N];
//long a[N]={84,78,94,87,50,63,91,64,41,73},b[N]={87,16,36,93,22,28,60,27,27,37},tmp[N];
int Datban(long int k,long int n,struct data huge **last,FILE **fptr );
int mergesort(int p,int r);
int merge(int p,int q,int r);
int main()
{
 struct data huge *last=NULL,huge *ptr=NULL,huge *last2=NULL;
 long int dem,k,n=N,tmp1;
 char ch,st[20];
 FILE *fptr;
 fptr=fopen("POPUST.INP","r");
 fgets(st,20,fptr);
 if (feof(fptr))
  return 0; //Loi
 n=atoi(st);
 for (k=0;k<n;k++)
 {
  tmp[k]=k;
  ch=getc(fptr);
  dem=0;
  while (ch!=' ')
  {
   st[dem++]=ch;
   ch=getc(fptr);
  }
  st[dem]='\0';
  a[k]=atoi(st);
  while (ch==' ')
   ch=getc(fptr);
  dem=0;
  st[dem++]=ch;
  ch=getc(fptr);
  while (ch!='\n')
  {
   st[dem++]=ch;
   ch=getc(fptr);
  }
  st[dem]='\0';
  b[k]=atoi(st);
 }
 fclose(fptr);
 mergesort(0,n-1);
 clrscr();
 //double start=clock();
 for (k=n;k>0;k--)
  Datban(k,n,&last,&fptr);
 //double finish=clock();
 //printf("Time:",(finish-start)/CLOCKS_PER_SEC);
 //printf("
 fptr=fopen("POPUST.OUT","w");         	 //Luu ra file ben ngoai
 while (last!=NULL)
 {
  dem=last->value;
  ptr=last;
  last=last->next;
  farfree(ptr);
  fprintf(fptr,"%ld\n",dem);
 }
 /*
 tmp1=(last==NULL);
 while (last!=NULL)                   //Lay ket qua tu stack
 {
  dem=last->value;
  ptr=last;
  last=last->next;
  farfree(ptr);
  //Luon duong, khong can xet truong hop am
  while (dem>0)    //Bat dau luu tru vao file
  {
   ptr=(data*) farcalloc(1,sizeof(struct data));
   ptr->value=dem%10;                  //Chuyen so sang xau=>Nguoc lai
   dem/=10;
   ptr->next=last2;
   last2=ptr;
  }
  while (last2!=NULL)
  {
   ptr=last2;
   putc('0'+ptr->value,fptr);
   last2=last2->next;
   farfree(ptr);
  }
  putc('\n',fptr);
 }
 */
 fclose(fptr);
 //double finish=clock();
 printf("\n\n\n\n\n\n");
 //printf("Time:%f",(finish-start)/CLOCKS_PER_SEC);
 getch();
 return 0;
}
int mergesort(int p,int r)
{
 int q;
 if (p<r)
 {
  q=(p+r)/2;
  mergesort(p,q);
  mergesort(q+1,r);
  merge(p,q,r);
 }
 return 0;
}
int merge(int p,int q,int r)
{
 long tg[N],i,j,dem=p;
 for (i=p;i<=r;i++)
  tg[i]=tmp[i];
 i=p,j=q+1,dem=p;
 while ((i<=q)&&(j<=r))
 {
  if (b[tg[i]]<=b[tg[j]])
   tmp[dem++]=tg[i++];
  else
   tmp[dem++]=tg[j++];
 }
 if (i==q+1)
  while (j<=r)
   tmp[dem++]=tg[j++];
 else
  while (i<=q)
   tmp[dem++]=tg[i++];
 return 0;
}
int Datban(long int k,long int n,struct data huge **last,FILE **fptr)
{
 long int q=0,i,j,tmp1;
 long int min,dem;
 struct data huge *ptr=NULL,huge *last2;
 static long int min2;
 static long int sum1;
 if (k==1)                     //Xu ly truong hop dac biet
 {
  if (a[tmp[0]]<min2) min2=a[tmp[0]];          //Chi dat 1 ban-> a[i]min
  printf("Dat 1 ban mat it nhat:%ld",min2);
  ptr=(data*) farcalloc(1,sizeof(struct data));
  ptr->value=min2;
  ptr->next=*last;
  *last=ptr;
  return 0;
 }
 for (i=0;i<k-1;i++)              //xet cac b nho nhat -> nho thu k-1
 {
  if (i==0)
  {
   if (k==n)
   {
    for (j=1;j<k;j++)
     sum1+=b[tmp[j]];
    sum1+=a[tmp[0]];
    min=sum1;
   }
   else
   {
    sum1=sum1-b[tmp[0]]+a[tmp[0]];      //Tinh toan hieu qua hon
    min=sum1;
   }
  }
  else
  {
   sum1=sum1+a[tmp[i]]-b[tmp[i]]-a[tmp[i-1]]+b[tmp[i-1]];//Tiet kiem tinh tong
   if (sum1<min)
    min=sum1;
  }
 }
 //Voi cac TH dat truoc ma a[i] khong thuoc thanh phan nho nhat-> nho thu k-1
 //Ta chi can tim thanh phan nho nhat a[i1] trong do thoi, cong voi tong b
 //o phan truoc, roi so voi min
 sum1=sum1-a[tmp[k-2]]+b[tmp[k-2]]-b[tmp[k-1]];
 if (k==n)
  min2=a[tmp[n-1]];
 else
 if (a[tmp[k-1]]<min2)
  min2=a[tmp[k-1]];
 q=min2+sum1;
 if (q<min) min=q;
 tmp1=(*last==NULL);
 printf("Dat %d ban mat it nhat:%d \n",k,min);
 ptr=(data*) farcalloc(1,sizeof(struct data));
 ptr->value=min;
 ptr->next=*last;
 *last=ptr;
 return 0;
}