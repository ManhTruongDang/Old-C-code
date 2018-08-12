#include <stdio.h>        Chuong trinh nhan 2 so voi nhau
#include <conio.h>        Da khac phuc hien tuong tran so
#include <string.h>       Ve co ban khong co loi
int Daoxau(char a[]);
char tmp;
int main()
{
 char a1[10],b1[10],d[10],d1[10],a[10],b[10],nhan[10];
 int c[10],i,j,m,nho=0,N=20,dem=0,max=0;
 for (i=0;i<10;i++) c[i]=0;                            //Khoi tao
 for (i=0;i<10;i++) nhan[i]=0;
 clrscr();
 printf("Nhap so a:");scanf("%s",&a1);
 printf("Nhap so b:");scanf("%s",&b1);
 printf("%*s\n",N,a1);
 printf("%*s\n",N,b1);
 printf("---------------------------------------------------\n");
 for (i=0;i<strlen(a1);i++) a[i]=a1[strlen(a1)-1-i];//Dao xau
 for (i=0;i<strlen(b1);i++) b[i]=b1[strlen(b1)-1-i];
 a[strlen(a1)]='\0';
 b[strlen(b1)]='\0';

 //Nhan 2 so voi nhau theo tung dong
 for (j=0;j<strlen(b);j++)
 {
  if (b[j]=='0') continue;
  for (i=0;i<strlen(a);i++)
  {
   m=(a[i]-'0')*(b[j]-'0');
   if (nho!=0) {m+=nho;nho=0;}
   if (m>=10) {nho=m/10;m=m%10;}      //Lay chu so da tinh ra va tach phan nho
   c[i+j]=c[i+j]+m;
   //if (i+j>max) max=i+j;              //c: mang chua ket qua cuoi cung, van co phan nho
   d[i]=m+'0';
   d[i+1]='\0';     			  //Lenh nay rat can thiet
  }			  //d: xau chua ket qua nhan o moi dong
  //Bay gio i=strlen(a), ta phai xet chu so cuoi cung xem no co phan nho k
  max=i+j;
  if (nho!=0)
  {
   d[i]=nho+'0';
   c[i+j]+=m;
   nho=0;
   d[i+1]='\0';
   max++;
  }    //Chu so cuoi cung phai nho
  for (i=0;i<=strlen(d);i++) d1[i]=d[strlen(d)-1-i];
  printf("%*s\n",N-j,d1);
  dem++;
 }

 //Dua ra ket qua cuoi cung
 nho=0;
 for (m=0;m<max;m++)
 {
  c[m]=c[m]+nho;
  nho=0;
  if (c[m]>=10)
  {
   nho=c[m]/10;            //Tuong tu nhu phan tren
   c[m]=c[m]%10;
   //nhan[m]=c[m]+'0';
   i=0;
  }
 }
 i=0;
 if (nho!=0)
 {
  max++;
  c[m]=c[m]+nho;
 }
 printf("___________________________________________________\n\n");
 printf("%*d",N-max+1,c[max-1]);
 if (max>=2) for (m=max-2;m>=0;m--) printf("%d",c[m]);
 /*for (m=0;m<=strlen(nhan);m++)
 {
  a1[m]=a1[strlen(nhan)-1-m];
 }*/
 getch();
 return(0);
}

