#include <stdio.h>
#include <conio.h>
#include <math.h>
const int MAX=100,MA=1,BLOCK=2,DICH=3,GOOD=0,YES=1,NO=0;
int knight2(int *data,int *marked,int x1,int y1,int x2,int y2,int N,int *min,
  int *savex,int *savey);
int main()
{
 FILE *fpt;
 int data[MAX][MAX],marked[MAX][MAX],x1,y1,x2,y2,N,min,savex[MAX],savey[MAX];
 int i,j;
 fpt=fopen("KNIGHT2.TXT","r");
 fscanf(fpt,"%d",&N);

 for ( i=0 ; i<N ; i++ )
  for ( j=0 ; j<N ; j++)
  {
   fscanf(fpt,"%d",&data[i][j]);
   if ( data[i][j]==BLOCK )
    marked[i][j]=YES;
   else
   if ( data[i][j]==MA )
   {
    marked[i][j]=YES;
    x1=i,y1=j;
   }
   else
   if ( data[i][j]==DICH )
   {
    marked[i][j]=NO;
    x2=i,y2=j;
   }
   else
   if ( data[i][j]==GOOD )
    marked[i][j]=NO;
  }
 fclose(fpt);

 knight2((int*)data,(int*)marked,x1,y1,x2,y2,N,&min,savex,savey);

 fpt=fopen("KNIGHT2.OUT","w+");

 fprintf(fpt,"%d\n",min+1);
 for (i=min;i>=0;i++)
  fprintf(fpt,"%2d",savex[i]);
 fprintf(fpt,"\n");
 for (i=min;i>=0;i--)
  fprintf(fpt,"%2d",savey[i]);
 fclose(fpt);
 return 0;
}
int knight2(int *data,int *marked,int x1,int y1,int x2,int y2,int N,int *min,
  int *savex,int *savey)
{
 int xdau,ydau,dx,dy,tmpx,tmpy,toado,dem[MAX],x[MAX],y[MAX],last[MAX];
 int i,dau,cuoi,dautmp,cuoitmp,i1;
 int ok=YES;
 dau=0,cuoi=0;
 dem[0]=0,x[0]=x1,y[0]=y1;
 (*min)=-1;
 while (1)
  {
   ok=NO;
   for (  i=dau  ; i <= cuoi  ; i++ )
    {
     (*min)++;
     xdau=x[i],  ydau=y[i];
     dautmp=cuoi+1, cuoitmp=dautmp;
     for ( dx=-2 ; dx<=2 ; dx++)
      {
       if ( dx==0 ) continue;
       for ( dy=-2 ; dy<=2 ; dy++)
	{
	 if (dy==0) continue;
	 if (abs(dx)==abs(dy))
	  continue;
	 tmpx= xdau+dx , tmpy= ydau+dy ;
	 if ( (tmpx<0) || (tmpx>=N) || (tmpy<0) || (tmpy>=N) )
	  continue;
	 toado = tmpx * MAX + tmpy ;
	 if ( (data[toado]==BLOCK) || (data[toado]==MA) )
	  continue;
	 if ( marked[toado]==YES )
	  continue;
	 if ( data[toado]==GOOD )
	  {
	   ok=YES;
	   marked[toado]=YES;
	   x[cuoitmp]=tmpx;
	   y[cuoitmp]=tmpy;
	   last[cuoitmp]=i;
	   cuoitmp++;
	  }
	 else
	  {
	   //Ket thuc
	   ok=YES;
	   x[cuoitmp]=x2 , y[cuoitmp] = y2 , last[cuoitmp]=i;
	   for ( i1=0 ; i1<=(*min) ; i1++ )
	    {
	     savex[i1]=x[cuoitmp], savey[i1]=y[cuoitmp];
	     cuoitmp=last[cuoitmp];
	    }
	   return 0;
	  }
	}
      }
     //dau=dautmp,cuoi=cuoitmp;
    }
   dau=dautmp,cuoi=cuoitmp;
   if (ok==NO)
    return 0;
  }
}