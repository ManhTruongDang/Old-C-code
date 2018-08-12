#include <stdio.h>
#include <conio.h>
#include <math.h>
const int BLOCK=-1,FINISH=-2,YES=1,NO=0,MAX=100;
int robot(int x1,int y1,int x2,int y2,int *data,int *marked,int N1,int N2,
   int *savex,int *savey,int *num,int *value,int *min,
   int *savexlast,int *saveylast,int *nummin,int *q);
int main()
{
 FILE *fpt;
 //Vao du lieu
 fpt=fopen("ROBOT.INP","r");
 int x1,y1,x2,y2,N1,N2,i,j,data[MAX][MAX],marked[MAX][MAX];
 int savex[MAX],savey[MAX],num=0,value=0,min=0,savexlast[MAX],saveylast[MAX];
 int nummin=0;
 int q=1;
 //fread(&N1,sizeof(int),1,fpt);
 //fread(&N2,sizeof(int),1,fpt);
 fscanf(fpt,"%d%d",&N1,&N2);
 for (i=0;i<N1;i++)
  for (j=0;j<N2;j++)
  {
   //fread(&data[i,j],sizeof(int),1,fpt);
   fscanf(fpt,"%d",&data[i][j]);
   if (data[i][j]>0)
    marked[i][j]=NO;
   else if (data[i][j]==BLOCK)
    marked[i][j]=YES;
   else if (data[i][j]==FINISH)
   {
    if (q==1)
    {
     x1=i;
     y1=j;
     q=0;
     marked[i][j]=YES;
    }
    else
    {
     x2=i;
     y2=j;
     marked[i][j]=YES;
    }
   }
  }
 fclose(fpt);
 //Ra du lieu
 q=1;
 robot(x1,y1,x2,y2,(int*)data,(int*)marked,N1-1,N2-1,savex,savey,&num,&value,&min,
   savexlast,saveylast,&nummin,&q);
 fpt=fopen("ROBOT.OUT","w+	");
 fprintf(fpt,"%d\n",min);
 for (i=0;i<=nummin;i++)
  fprintf(fpt,"%3d",savexlast[i]);
 fprintf(fpt,"\n");
 for (i=0;i<=nummin;i++)
  fprintf(fpt,"%3d",saveylast[i]);
 fprintf(fpt,"\n");
 fclose(fpt);
 getch();
 return 0;
}
int robot(int x1,int y1,int x2,int y2,int *data,int *marked,int N1,int N2,
   int *savex,int *savey,int *num,int *value,int *min,
   int *savexlast,int *saveylast,int *nummin,int *q)
{
 int tmpx,tmpy,dx,dy,dem,toado,*tmp,tmp1;
 for (dx=-1;dx<=1;dx++)         //Xet nhung diem co the di tiep duoc
  for (dy=-1;dy<=1;dy++)
  {
   tmpx=x1+dx;                  //Luu tru gia tri trung gian
   tmpy=y1+dy;
   if ((tmpx<0)||(tmpx>N1)||(tmpy<0)||(tmpy>N2)) continue;
   if ((abs(dx)^abs(dy))==0) continue;//Khong phai la 1 trong 4 nuoc di duoc?
   //Xet xem gia tri tai do co thoa man de di tiep khong?
   toado=tmpx*MAX+tmpy;
   if (data[toado]==BLOCK) continue;
   if (data[toado]>0)      //Di tiep TH nay
   {
    if (marked[toado]==NO)
    {
     marked[toado]=YES;
     (*value)+=data[toado];
     savex[*num]=tmpx;
     savey[*num]=tmpy;
     (*num)+=1;
     robot(tmpx,tmpy,x2,y2,data,marked,N1,N2,savex,savey,num,value,min,savexlast,saveylast,nummin,q);
     marked[toado]=NO;
     (*value)-=data[toado];
     (*num)-=1;
    }
   }
   else
   if (data[toado]==FINISH)   //Den dich hoac diem bat dau
    if ((tmpx==x2)&&(tmpy==y2))
    {
     if ((*q)==0)      //Luu gia tri moi vao?
     {
      if ((*value)<(*min))
      {
       *min=*value;
       savex[*num]=x2;
       savey[*num]=y2;
       //Cap nhat ket qua moi
       *nummin=*num;
       for (dem=0;dem<=(*nummin);dem++)
       {
	savexlast[dem]=savex[dem];
	saveylast[dem]=savey[dem];
       }
      }
     }
     else
     {
      *min=*value;//Cap nhat gia tri nho nhat luc dau
      *q=0;
     }
    }
  }
 return 0;
}
