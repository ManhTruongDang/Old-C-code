#include <stdio.h>
#include <conio.h>
#include <math.h>
const int MAX=100,MA=1,BLOCK=2,DICH=3,GOOD=0,YES=1,NO=0;
int knight(int *data,int *marked,int N,int x1,int y1,int x2,int y2,
  int num,int *min,int *savex,int *savey,
   int *savexlast,int *saveylast,int *nummin,int *ok);
int main()
{
 FILE *fpt;
 int i,j,N,data[MAX][MAX],marked[MAX][MAX],x1,y1,x2,y2;
 int min=0,savex[MAX],savey[MAX],savexlast[MAX],saveylast[MAX],nummin=0;
 int ok=YES;
 fpt=fopen("KNIGHT.TXT","r");
 fscanf(fpt,"%d",&N);
 for (i=0;i<N;i++)
  for (j=0;j<N;j++)
  {
   fscanf(fpt,"%d",&data[i][j]);
   if (data[i][j]==MA)
   {
    marked[i][j]=YES;
    x1=i,y1=j;
   }
   else
   if (data[i][j]==BLOCK)
    marked[i][j]=YES;
   else
   if (data[i][j]==DICH)
   {
    marked[i][j]=NO;
    x2=i,y2=j;
   }
   else
   if (data[i][j]==GOOD)
    marked[i][j]=NO;
 }
 fclose(fpt);
 savex[0]=x1,savey[0]=y1;
 knight((int*)data,(int*)marked,N,x1,y1,x2,y2,1,&min,savex,savey,
   savexlast,saveylast,&nummin,&ok);
 fpt=fopen("KNIGHT.OUT","w+");
 fprintf(fpt,"%d\n",nummin+1);
 for (i=0;i<=nummin;i++)
  fprintf(fpt,"%2d",savexlast[i]);
 fprintf(fpt,"\n");
 for (i=0;i<=nummin;i++)
  fprintf(fpt,"%2d",saveylast[i]);
 fprintf(fpt,"\n");
 fclose(fpt);
 return 0;
}
int knight(int *data,int *marked,int N,int x1,int y1,int x2,int y2,
  int num,int *min,int *savex,int *savey,
   int *savexlast,int *saveylast,int *nummin,int *ok)
//Luc dau ok=1
{
 int dx,dy,tmpx,tmpy,toado,dem;
 for (dx=-2;dx<=2;dx++)
  {
   if (dx==0) continue;
   for (dy=-2;dy<=2;dy++)
    {
     if (dy==0) continue;
     if (abs(dx)==abs(dy))
      continue;
     tmpx=x1+dx,tmpy=y1+dy;
     if ((tmpx<0)||(tmpx>=N)||(tmpy<0)||(tmpy>=N))
      continue;
     toado=tmpx*MAX+tmpy;
     if ((data[toado]==BLOCK)||(data[toado]==MA))
      continue;
     if (marked[toado]==YES)
      continue;
     if (data[toado]==GOOD)
      {
       marked[toado]=YES;
       savex[num]=tmpx,savey[num]=tmpy;
       knight(data,marked,N,tmpx,tmpy,x2,y2,num+1,min,savex,savey,
	 savexlast,saveylast,nummin,ok);
       marked[toado]=NO;
      }
     else               //Ve dich
      {
       if ((*ok)==YES)
	{
	 (*ok)=NO;
	 (*nummin)=num;
	 for (dem=0;dem<=num;dem++)
	  {
	   savexlast[dem]=savex[dem];
	   saveylast[dem]=savey[dem];
	  }
	}
       else
	{
	 if ((*nummin)>num)
	  {
	   (*nummin)=num;
	   for (dem=0;dem<=num;dem++)
	    {
	     savexlast[dem]=savex[dem];
	     saveylast[dem]=savey[dem];
	    }
	  }
	}
       return 0;
      }
    }
  }

 return 0;

}