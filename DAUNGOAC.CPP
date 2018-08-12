/* Bai 1 chuong Ky thuat nhanh can, Giai thuat va lap trinh - Le Minh Hoang */
#include <stdio.h>
#include <conio.h>
#include <string.h>
int calculate();
int Try(int i,int max,int open,int close,int depth);
int result();
char str[40];
int n=23,k=6;
int main()
{
 clrscr();
 str[n+1]='\0';
 str[1]='(';
 str[0]=' ';
 printf("\a");
 Try(2,1,1,0,1);
 printf("\a\a\a\a\a\a\a\a");
 getch();
 return 0;
}
int calculate(int i,int depth)
{
 if (str[i]!=str[i-1])
  return depth;
 else
 if (str[i]=='(')
  return depth+1;
 else
  return depth-1;
}
int Try(int i,int max,int open,int close,int depth)
{
 int depth1=depth,left=n-i+1;
 if ((open<close)||((str[i-1]==')')&&(depth==1)))
 {
  str[i]='(';
  depth1=calculate(i,depth);
  if (i==n) result();
  else
   Try(i+1,max>depth1?max:depth1,open+1,close,depth1);
 }
 else
 if ((open==n/2)||(open-close==left))
 {
  if (max==k)
  {
   str[i]=')';
   depth1=calculate(i,depth);
   if (i==n) result();
   else
    Try(i+1,max>depth1?max:depth1,open,close+1,depth1);
   str[i]=' ';
  }
 }
 /*
 else
 if ((max<k)&&(str[i-1]=='(')&&((left-(open-close))/(k-depth+1)==2))
 {
  str[i]='(';
  depth1=depth+1;
  int m=i+1;
  while (depth1<k)
  {
   str[m++]='(';
   depth1++;
  }
  Try(m,k,open+depth1-depth,close,k);
 }
 */
 else
 {
  str[i]='(';
  depth1=calculate(i,depth);
  if (i==n)
   result();
  else
   Try(i+1,max>depth1?max:depth1,open+1,close,depth1);
  str[i]=' ';
  str[i]=')';
  depth1=calculate(i,depth);

 if ((max==k)||((n/2-open)>=(k-depth1+1)))          //Is this line useless???
  {
   if (i==n)
    result();
   else
    Try(i+1,max>depth1?max:depth1,open,close+1,depth1);
  }
  str[i]=' ';
 }
 return 0;
}
int result()
{
 puts(str);
 return 0;
}
