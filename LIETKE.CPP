#include <stdio.h>   //Liet ke tat ca cach sap xep m vien bi cho n nguoi
#include <conio.h>   //Khong liet ke lap lai cac cach
#include <math.h>
int n1;
int Lietke(int,int);
int main()
{
 int m,n;
 clrscr();
 printf("\n So vien bi:"); scanf("%d",&m);
 printf("\n So nguoi:"); scanf("%d",&n);
 n1=n;
 Lietke(m,n);
 getch();
 return(0);
}

int Lietke(int m, int n)
{
 if (n==1)                                        //TH dac biet
 {
  int j;
  for (j=0;j<=n1-n;j++) printf("  ");             //Lui dau dong
  printf("1 nguoi co %d vien.\n",m);
  return(0);
 }
 int i=m/n;
 for (;i<=m;i++)                                  //TH de quy
 {
  int j;
  for (j=0;j<=n1-n;j++) printf("  ");             //Lui dau dong
  printf("1 nguoi co %dvien,\n",i);
  Lietke(m-i,n-1);
 }
 return(0);
}