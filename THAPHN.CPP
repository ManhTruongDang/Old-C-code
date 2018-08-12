#include <stdio.h>  // Solution to the Tower of Hanoi problem without using recursion
// #include <conio.h>
int save[20],disk,C1=1,C2=2,C3=3;
int GoUp();
int GoDown();
int KeepGoing();
int Swap(int *a,int *b);
int main()
{
 int N=3,i; 
 printf("Tower of Hanoi with 3 rods and N disks, the job is to move all disks from the 1st to the 2nd rod\n");
 printf("Input N: ");scanf("%d",&N);
 disk=N;
 for (i=1;i<=N;i++)
  save[i]=1;

 while (save[N]==1)
 {
  if (disk==1)
   if (save[disk]==3)
    GoUp();
   else
    KeepGoing();
  else
  if (save[disk]==3)
  {
   if (save[disk-1]==1)
    GoDown();
   else
    GoUp();
   save[disk-2]=1;
   Swap(&disk,&disk);
  }
  else
  if (save[disk]==2)
  {
   KeepGoing();
   save[disk-1]=1;
  }
  else
  if (save[disk-1]<3)
   GoDown();
  else
  {
   KeepGoing();
   save[disk-1]=1;
  }
 if ((disk<N)&((disk==1)||(save[disk]==2)))
 {
  printf("%d->%d\n",C1,C2);  
 }
 Swap(&disk,&disk);
 } 
 getchar(); // https://stackoverflow.com/questions/7469139/what-is-equivalent-to-getch-getche-in-linux
 return 0;
}

int GoUp()
{
 if (save[disk]==3)
 {
  Swap(&C3,&C1);
  disk++;
 }
 return(0);
}

int GoDown()
{
 Swap(&C2,&C3);
 disk--;
 return 0;
}

int KeepGoing()
{
 switch (save[disk])
 {
  case 1: Swap(&C2,&C3),save[disk]++;
	  break;
  case 2: Swap(&C1,&C3),save[disk]++;
	  break;
 }
 return 0;
}

int Swap(int *a,int *b)
{
 int t;
 t=*a;
 *a=*b;
 *b=t;
 return 0;
}
