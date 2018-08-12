#include <stdio.h>
#include <conio.h>
const int MAX=100,BLOCKED=-1,YES=1,NO=0;
int cungmau(int N,int *matrix,int *marked,int dau,int now,int cuoi,int *mau,
  int *num,int *way,int *solan,FILE *fpt);
int main()
{
 int N,matrix[MAX][MAX],marked[MAX];
 int dau,cuoi,mau,num=1,way[MAX],solan=0;
 FILE *fpt;
 int i,j;
 fpt=fopen("CUNGMAU.INP","r");
 fscanf(fpt,"%d",&N);
 fscanf(fpt,"%d",&dau);
 fscanf(fpt,"%d",&cuoi);
 dau--,cuoi--;
 for (i=0;i<N;i++)
 {
  for (j=0;j<N;j++)
   fscanf(fpt,"%d",&matrix[i][j]);
  if ((i==dau))
   marked[i]=YES;
  else
   marked[i]=NO;
 }
 way[0]=dau;
 fclose(fpt);
 fpt=fopen("CUNGMAU.OUT","w");
 cungmau(N-1,(int*)matrix,marked,dau,dau,cuoi,&mau,&num,way,&solan,fpt);
 fclose(fpt);
 return 0;
}
int cungmau(int N,int *matrix,int *marked,int dau,int now,int cuoi,int *mau,
  int *num,int *way,int *solan,FILE *fpt)
{
 int dem,diduoc,dich,i,toado;
 for (dem=0;dem<=N;dem++)
 {
  diduoc=0;
  if (dem==now) continue;
  toado=now*MAX+dem;
  if (matrix[toado]!=BLOCKED)
   if (marked[dem]==NO)
   {
    if (now==dau)
    {
     *mau=matrix[toado];
     diduoc=1;
    }
    else
    if (matrix[toado]==(*mau))
     diduoc=1;
    if (diduoc==1)
    {
     if (dem!=cuoi)
     {
      way[*num]=dem;
      (*num)++;
      marked[dem]=YES;
      cungmau(N,matrix,marked,dau,dem,cuoi,mau,num,way,solan,fpt);
      marked[dem]=NO;
      (*num)--;
     }
     else
     {
      way[*num]=dem;
      //(*num)++;
      //marked[dem]=YES;
      (*solan)++;
      //In ket qua ra file
      fprintf(fpt,"%3d, ",*mau);
      for (i=0;i<=(*num);i++)
       fprintf(fpt,"%3d ",way[i]);
      fprintf(fpt,"\n");
     }
    }
   }
 }
 return 0;
}