#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <ctype.h>
int main()
{
 int i=0;
 char ch,pass[3]="Lol";
 void (*f)(void);
 clrscr();
 printf("Nhap mat khau, nhap sai khoi dong lai may!\n");
 while (i<3)
 {
  ch=getch();
  if (ch!=pass[i])
  {
   f=(void (*)()) MK_FP(0xFFFF,0x0000);
   //f=MK_FP(0xFFFF,0x0000);
   f();
  }
  i++;
 }
 printf("Chuc mung ban da vuot qua thu thach!\n");
 getch();
 return 0;
}