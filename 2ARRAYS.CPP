#include <stdio.h>
#include <conio.h>

#define MAX 34000

//const int MAX = 34000;
const int YES  = 1;
const int NO  = 0;
int mergesort(long *A1,long *tmp,long p,long r);
int merge(long *B1,long *B2,long *out,long p1,long q1,long p2,long q2,long first);
int findK(long *A,long *B,long M,long N,long K,long *out);
    //Gia su A,B da duoc sap xep :(
int findK2(long *A,long *B,long M,long N,long K,long *limit);
int findK3(long *A,long *B,long M,long N,long K,long *out);
int makeheapK(long *value,long *x,long*y,long num,long index);
int main()
{
 FILE *fpt;
 long dem,M,N,K,A[MAX],B[MAX],out[MAX],max;
 long limit[MAX],tmpA[MAX],tmpB[MAX],i,j,optimal;
 //long sample[MAX]={14,2,7,4,6,10,11,5,13,8,9,12,20,21};
 fpt=fopen("2ARRAYS.INP","r");
 fscanf(fpt,"%ld%ld%ld",&M,&N,&K);
 for (dem=0;dem<M;dem++)
  fscanf(fpt,"%ld",&A[dem]);
 for (dem=0;dem<N;dem++)
 fscanf(fpt,"%ld",&B[dem]);
 max=A[0];
 for (dem=0;dem<M;dem++)
  if (A[dem]>max) max=A[dem];
 fclose(fpt);
 mergesort(A,out,0,M-1);
 mergesort(B,out,0,N-1);
 //findK(A,B,M,N,K,out);
 //findK2(A,B,M,N,K,limit);
 //makeheapK(sample,tmpA,tmpB,13,0);
 findK3(A,B,M,N,K,out);
 fpt=fopen("2ARRAYS.OUT","w+");
 /*
 for (i=0;i<M;i++)
  tmpA[i]=B[0]+A[i];
 if (M>K) optimal=M;
 else optimal=K;
 for (j=1;j<N;j++)
 {
  if (limit[j]<0) continue;
  for (i=0;i<=limit[j];i++)
   tmpB[i]=B[j]+A[i];
  merge(tmpA, tmpB, out, 0, optimal-1, 0, limit[j], 0);
  //if (M>K) optimal=M;
  //else optimal=K;
  for (dem=0;dem<optimal;dem++)
   tmpA[dem]=out[dem];
 }
 */

 for (dem = 0; dem < K; dem ++)
  fprintf(fpt,"%ld\n",out[dem]);
 fclose(fpt);
 return 0;
}


int findK(long *A,long *B,long M,long N,long K,long *out)
{ //Gia su A,B da duoc sap xep khong giam tu truoc
 long dem,i,j,tmpB[MAX],tmpA[MAX],optimal;
 //long *tmp,*ptA,*ptB;
 for (i=0;i<M;i++)
  tmpA[i]=B[0]+A[i];
 //ptA=tmpA,ptB=tmpB;
 if (M>K) optimal=M;
 else optimal=K;
 //optimal=M;
 for (j=1;j<N;j++)
 {
  for (i=0;i<M;i++)
   tmpB[i]=B[j]+A[i];
  merge(tmpA,tmpB,out,0,optimal-1,0,M-1,0);
  //if (M>K) optimal=M;
  //else optimal=K;
  for (dem=0;dem<optimal;dem++)
   tmpA[dem]=out[dem];
 }
 return 0;
}
int merge(long *B1,long *B2,long *out,long p1,long q1,long p2,long q2,long first)
{
 long dem=first,i1=p1,i2=p2;
 while ((i1<=q1)&&(i2<=q2))
 {
  while (B1[i1]<=B2[i2])
  {
   out[dem++]=B1[i1++];
   if (i1>q1)
    break;
  }
  //if (i1>q1) break;
  while (B1[i1]>B2[i2])
  {
   out[dem++]=B2[i2++];
   if (i2>q2)
    break;
  }
 }
 if (i1<=q1)
  for (;i1<=q1;i1++)
   out[dem++]=B1[i1];
 else
 if (i2<=q2)
  for (;i2<=q2;i2++)
   out[dem++]=B2[i2];
 return 0;
}
int mergesort(long *A1,long *tmp,long p,long r)
{
 long mid;
 if (p<r)
 {
  mid=(p+r)/2; //O day thi mid la trung diem
  mergesort(A1,tmp,p,mid);
  mergesort(A1,tmp,mid+1,r);
  merge(A1,A1,tmp,p,mid,mid+1,r,p);
  for (mid=p;mid<=r;mid++) //O day thi mid chi la chi so ma thoi
   A1[mid]=tmp[mid];
 }
 return 0;
}
int findK2(long *A,long *B,long M,long N,long K,long *limit)
{
 long j,tmp,moc,first,last,mid,K1,K2,dem;
 long goodK,upper,lower;
 //long optimal,binary
 for (dem=0;dem<N;dem++)
  limit[dem]=M-1;
 //if (M>K) optimal=K;
 //else optimal=M;
 //binary=(M-1+N-1)/2;
 upper=A[M-1]+B[N-1];
 lower=A[0]+B[0];
 moc=(upper+lower)/2;
 goodK=0;
 while (goodK!=K)
 {
  for (j=0;j<N;j++)
  {
   first=0;last=M-1;
   mid=(M-1)/2;
   while (first<=last)
   {
    mid=(first+last)/2;
    tmp=B[j]+A[mid];
    if (tmp<moc) first=mid+1;
    else
    if (tmp>moc) last=mid-1;
    else
     break;
    //if (tmp==moc)
    //{
    // first=mid;
    // last=mid;
    //}
   }
   if (tmp==moc)
    limit[j]=mid;
   else
    limit[j]=last;
  }
  goodK=0;
  for (j=0;j<N;j++)
  {
   goodK+=limit[j];
   goodK+=1;
  }
  if (goodK>K) upper=moc;
  if (goodK<K) lower=moc;
  moc=(upper+lower)/2;
 }
 return 0;
}
int findK3(long *A,long *B,long M,long N,long K,long *out)
{//A,B duoc sap xep tu truoc
 long i,j,dem,ngang[MAX],doc[MAX],cheo,value[MAX],x[MAX],y[MAX],num=0;
 long min,diag,tmp,tmpx,tmpy,ok;
 for (dem=0;dem<M;dem++)
  doc[dem]=dem+1;
 for (dem=0;dem<N;dem++)
  ngang[dem]=dem+1;
 cheo=0;
 value[0]=A[0]+B[0],x[0]=0,y[0]=0;
 value[1]=A[1]+B[0],x[1]=0,y[1]=1;
 value[2]=A[0]+B[1],x[2]=1,y[2]=0;  //3 gia tri nay da thoa man 1 heap
 num=2;
 diag=A[1]+B[1];
 for (dem = 0;dem < K;dem ++)
 {
  min=value[0];   //Lay phan tu nho nhat trong heap

  //if (min<=diag)
  //{

  if (min>diag)                //Da den luc cap nhat them duong cheo moi
  {
   cheo++;
   diag=A[cheo+1]+B[cheo+1];
   //Cap nhat 3 phan tu cua duong cheo moi
   num++;
   value[num]=A[cheo]+B[cheo],x[num]=cheo,y[num]=cheo;
   if (num%2==0) i=num/2-1;   //Tim nut cha cuoi cung
   else i=num/2;
   for (;i>=0;i--)
    makeheapK(value,x,y,num,i);

   num++;
   value[num]=A[cheo+1]+B[cheo],x[num]=cheo,y[num]=cheo+1;
   if (num%2==0) i=num/2-1;   //Tim nut cha cuoi cung
   else i=num/2;
   for (;i>=0;i--)
    makeheapK(value,x,y,num,i);

   num++;
   value[num]=A[cheo]+B[cheo+1],x[num]=cheo+1,y[num]=cheo;
   if (num%2==0) i=num/2-1;   //Tim nut cha cuoi cung
   else i=num/2;
   for (;i>=0;i--)
    makeheapK(value,x,y,num,i);
   dem--;
   continue;
  }
  out[dem]=min;
  ok=NO;
  if (x[0]==y[0])   //Phan tu cheo?
  {
   //Cap nhat heap;
   /*
   value[0]=value[num],x[0]=x[num],y[0]=y[num];
   num--;
   if (num%2==0) i=num/2-1;   //Tim nut cha cuoi cung
   else i=num/2;
   for (;i>=0;i--)
    makeheap(value,x,y,&num,i);
   */
  }
  else
  if (x[0]>y[0])    //Phia doc
  {
   doc[y[0]]++;
   if (doc[y[0]]<N)  //Van con phan tu tren duong doc nay
   {
    tmp=A[y[0]]+B[doc[y[0]]];
    tmpx=doc[y[0]],tmpy=y[0];
    ok=YES;
   }
  }
  else              //Phia ngang
  {
   ngang[x[0]]++;
   if (ngang[x[0]]<M)
   {
    tmp=A[ngang[x[0]]]+B[x[0]];
    tmpx=x[0],tmpy=ngang[x[0]];
    ok=YES;
   }
  }

  value[0]=value[num],x[0]=x[num],y[0]=y[num];
  num--;
  if (num%2==0) i=num/2-1;   //Tim nut cha cuoi cung
  else i=num/2;
  for (;i>=0;i--)
   makeheapK(value,x,y,num,i);
  if (ok==YES)               //Them tiep 1 lan nua
  {
   num++;
   value[num]=tmp,x[num]=tmpx,y[num]=tmpy;
   if (num%2==0) i=num/2-1;   //Tim nut cha cuoi cung
    else i=num/2;
   for (;i>=0;i--)
    makeheapK(value,x,y,num,i);
  }

 }
 return 0;
}
int makeheapK(long *value,long *x,long*y,long num,long index)
{
 int jtmp,j,key,keyx,keyy;
 key=value[index],keyx=x[index],keyy=y[index];
 j=index*2+1;
 while (j<=num)
 {
  if ((j<num)&&(value[j]>value[j+1]))
   j++;
  if (key<value[j])
  {
   if (j%2==0) jtmp=j/2-1;
   else jtmp=j/2;
   value[jtmp]=key;
   x[jtmp]=keyx;
   y[jtmp]=keyy;
   return 0;
  }
  if (j%2==0) jtmp=j/2-1;
  else jtmp=j/2;
  value[jtmp]=value[j];
  x[jtmp]=x[j];
  y[jtmp]=y[j];
  j=j*2+1;
 }
 if (j%2==0) jtmp=j/2-1;
 else jtmp=j/2;
 value[jtmp]=key;
 x[jtmp]=keyx;
 y[jtmp]=keyy;
 return 0;
}