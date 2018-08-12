#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
const int N=10000;
int main()
{
 clrscr();
 char str[20],ch='0';
 int dem1=0,dem=0,n=N,a[20000],maxright[N],maxleft,j,max,f;
 FILE *fptr;
 a[0]=-1;
 a[1]=2;
 a[2]=-2;
 a[3]=-3;
 a[4]=5;
 n=5;
 /*
 fptr=fopen("C:\\TC\\SEQUENCE.TXT","r");
 if (fptr==NULL)
  printf("LOI!");
 fgets(str,20,fptr);
 if (feof(fptr))
  return 0;
 if (str[strlen(str)-1]=='\n')
  str[strlen(str)-1]='\0';
 n=atoi(str);
 ch=getc(fptr);
 for (dem1=0;dem1<n;dem1++)
 {
  dem=0;
  str[dem++]=ch;
  ch=getc(fptr);
  while ((ch!='\n')&&(((ch>='0')&&(ch<='9'))||(ch=='-')))
  {
   str[dem++]=ch;
   ch=getc(fptr);
  }
  str[dem]='\0';
  a[dem1]=atoi(str);
  ch=getc(fptr);
 }
 fclose(fptr);
 */
 for (j=0;j<n;j++)
 {
  a[j]=random(100);
  printf("%d  ",a[j]);
 }
 printf("\n");
 if (n==3)
 {
  max=a[0]+2*a[1]+3*a[2];
  printf("Lon nhat:%d\n",max);
  //goto ak47;
 }
 /*
 maxright[n-1]=a[n-1];
 max=a[n-1];
 for (j=n-2;j>=2;j--)      //Tim cac gia tri max ben phai tu i toi n-1
 {
  if (a[j]>max)
  {
   maxright[j]=a[j];
   max=a[j];
  }
  else
   maxright[j]=max;
 }
 maxleft=a[0];
 max=maxleft+2*a[1]+3*maxright[2];
 for (j=2;j<n-1;j++)
 {
  f=maxleft+2*a[j]+3*maxright[j+1];
  if (f>max)
   max=f;
  if (a[j]>maxleft)
   maxleft=a[j];
 }
 */
 int maxleft1,maxleft2,maxright1,maxright2,maxtrue,tmp;
 int center,left,right;
 int isleft,isright;   //2 bien nay de xem maxtrue co trung vao hai ben k?
 //maxleft2->maxleft1->maxtrue<-maxright1<-maxleft1
 double start=clock();
 maxtrue=0;
 for (j=0;j<n;j++)
  if (a[j]>a[maxtrue])
   maxtrue=j;                //Tim phan tu lon nhat cua toan mang
 maxleft1=0;
 for (j=0;j<=maxtrue;j++)    //maxleft1: max o phia ben trai cua maxtrue
 {
  if (j==maxtrue)
   continue;
  if (a[j]>a[maxleft1])
   maxleft1=j;
 }
 maxright1=n-1;
 for (j=n-1;j>=maxtrue;j--)     //maxright1:max o phia ben phai cua maxtrue
 {
  if (j==maxtrue)
   continue;
  if (a[j]>a[maxright1])
   maxright1=j;
 }
 isleft=0,isright=0;
 if (maxleft1!=maxtrue)                 //maxleft2,maxleft1,tmp,maxtrue...
 {
  isleft=1;
  maxleft2=0;
  for (j=0;j<maxleft1;j++)
   if (a[j]>a[maxleft2])
    maxleft2=j;
  tmp=maxleft1+1;
  for (j=tmp;j<maxtrue;j++)
   if (a[j]>a[tmp])
    tmp=j;
  left=a[maxleft2]+2*a[maxleft1]+3*a[maxtrue];
  tmp=a[maxleft1]+2*a[tmp]+3*a[maxtrue];
  if (tmp>left)
   left=tmp;
 }
 if (maxright1!=maxtrue)                 //maxtrue,maxright2,maxright1,tmp
 {
  isright=1;
  maxright2=maxtrue+1;
  for (j=maxtrue+1;j<maxright1;j++)
   if (a[j]>a[maxright2])
    maxleft2=j;
  tmp=maxright1+1;
  for (j=tmp;j<n;j++)
   if (a[j]>a[tmp])
    tmp=j;
  right=a[maxtrue]+2*a[maxright2]+3*a[maxright1];
  tmp=a[maxtrue]+2*a[maxright1]+3*a[tmp];
  if (tmp>right)
   right=tmp;
 }
 if ((isleft==1)&&(isright==1))
 {
  center=a[maxleft1]+2*a[maxtrue]+3*a[maxright1];
  max=center;
  if (max<left)
   max=left;
  if (max<right)
   max=right;
 }
 else
 if (isleft==0)
  max=right;
 else   //isleft va isright khong the dong thoi =1
  max=left;
 double finish=clock();
 printf("Lon nhat:%d\n",max);
 printf("Time:%f",(finish-start)/CLOCKS_PER_SEC);
 ak47:fptr=fopen("SEQUENCE.OUT","w");
 dem=0;
 while (max!=0)
 {
  ch='0'+max%10;
  max=max/10;
  str[dem++]=ch;
 }
 str[dem]='\0';
 for (j=strlen(str)-1;j>=0;j--)
  putc(str[j],fptr);
 putc('\n',fptr);
 fclose(fptr);
 getch();
 return 0;
}
