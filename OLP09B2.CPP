#include <stdio.h>
#include <conio.h>
const M=4,N=5;
int main()
{
 clrscr();
 int m=M,n=N;
 int n1=n-1,m1=m-1;
 int a[M][N]={{10,11,12,13,14},{15,0,16,17,11},{4,5,6,7,8},{2,10,6,7,5}},i,j;
 int tmp1[3],tmp2[3],tmp3[3],bound=2,count[3],i1,j1,dem,upper,arrnum,k1;
 int *tmp,*p[3],tg,median,min,vitri;
 FILE *tep;
 //tmp1 den 3 la 3 mang trung gian
 //p[0..2] tro vao 3 mang tren de tien xu ly, day se the hien o vuong 3x3
 p[0]=tmp1;
 p[1]=tmp2;
 p[2]=tmp3;
 //Mo tep de bai
 tep=fopen("ADJUST.INT","r");
 fscanf(tep,"%d%d",&m,&n);
 m1=m-1,n1=n-1;
 for (i=0;i<=m1;i++)
  for (j=0;j<=n1;j++)
   fscanf(tep,"%d",a[i][j]);
 fclose(tep);
 //Tao tep moi, bat dau lam
 tep=fopen("ADJUST.OUT","w");
 for (i=0;i<m;i++)
 {
  for (j=0;j<n;j++)
  {
   if ((i>=0)&&(i<=m1)&&(j>=1)&&(j<n1))
   {
    //Khoi tao sang vi tri tiep theo
    tmp=p[0];
    p[0]=p[1];
    p[1]=p[2];
    p[2]=tmp;
    //Them du lieu vao
    if ((i>0)&&(i<m1))
    {
     bound=2;
     upper=i+1;
     median=5;
    }
    else
    if (i==0)
    {
     bound=1;
     upper=i+1;
     median=3;
    }
    else
    if (i==m1)
    {
     bound=1;
     upper=i;
     median=3;
    }
    for (i1=0;i1<=bound;i1++)
     p[2][i1]=a[upper-i1][j+1];
    //p[2][0]=a[i+1][j+1];
    //p[2][1]=a[i][j+1];
    //p[2][2]=a[i-1][j+1];
    //Sap xep cac mang trung gian
    for (i1=0;i1<bound;i1++)
     for (j1=i1+1;j1<=bound;j1++)
      if (p[2][i1]>p[2][j1])
      {
       tg=p[2][i1];
       p[2][i1]=p[2][j1];
       p[2][j1]=tg;
      }
    //Tim kiem trung vi tren 3 mang
    dem=0,count[0]=0,count[1]=0,count[2]=0;
    while (dem<median)
    {
     dem++;
     vitri=0;            //p[vitri][count[vitri]]???
     for (i1=1;i1<=2;i1++)
     {
      //if (p[1][count[1]]<p[vitri][count[vitri]])
      // vitri=1;
      //if (p[2][count[2]]<p[vitri][count[vitri]])
      // vitri=2;
      if (p[i1][count[i1]]<p[vitri][count[vitri]])
       vitri=i1;
     }
     if (dem==median)
      break;
     count[vitri]++;
    }
    //Dua ket qua vao
    printf("%3d ",p[vitri][count[vitri]]);
    fprintf(tep,"%3d ",p[vitri][count[vitri]]);
   }
   else
   if (j==0)
   {
    //Khoi tao
    if ((i>0)&&(i<m1))
    {
     bound=2;
     upper=i+1;
     median=3;
    }
    else
    if (i==0)
    {
     bound=1;
     upper=i+1;
     median=2;
    }
    else
    if (i==m1)
    {
     bound=1;
     upper=i;
     median=2;
    }
    //Cho gia tri vao cac mang trung gian
    for (i1=0;i1<=bound;i1++)
    {
     p[1][i1]=a[upper-i1][j];
     p[2][i1]=a[upper-i1][j+1];
    }
    //Sap xep
    for (i1=0;i1<bound;i1++)
     for (j1=i1+1;j1<=bound;j1++)
     {
      if (p[1][i1]>p[1][j1])
      {
       tg=p[1][i1];
       p[1][i1]=p[1][j1];
       p[1][j1]=tg;
      }
      if (p[2][i1]>p[2][j1])
      {
       tg=p[2][i1];
       p[2][i1]=p[2][j1];
       p[2][j1]=tg;
      }
     }
    //Tim trung vi
    dem=0,count[0]=0,count[1]=0,count[2]=0;
    while (dem<median)
    {
     dem++;
     vitri=1;            //p[vitri][count[vitri]]???
     if (p[2][count[2]]<p[vitri][count[vitri]])
      vitri=2;
     if (dem==median)
      break;
     count[vitri]++;
    }
    //Dua ket qua vao
    printf("%3d ",p[vitri][count[vitri]]);
    fprintf(tep,"%3d ",p[vitri][count[vitri]]);
   }
   else
   //if (j==n1)                       //Phia ben phai
   {
    //Khoi tao
    if ((i>0)&&(i<m1))
    {
     bound=2;
     upper=i+1;
     median=3;
    }
    else
    if (i==0)
    {
     bound=1;
     upper=i+1;
     median=2;
    }
    else
    if (i==m1)
    {
     bound=1;
     upper=i;
     median=2;
    }
    //Tim trung vi
    dem=0,count[0]=0,count[1]=0,count[2]=0;
    while (dem<median)
    {
     dem++;
     vitri=1;            //p[vitri][count[vitri]]???
     if (p[2][count[2]]<p[vitri][count[vitri]])
      vitri=2;
     if (dem==median)
      break;
     count[vitri]++;
    }
    //Dua ket qua vao
    printf("%3d ",p[vitri][count[vitri]]);
    fprintf(tep,"%3d ",p[vitri][count[vitri]]);
   }
  }
  printf("\n");
  fprintf(tep,"\n");
 }
 fclose(tep);
 getch();
 return 0;
}