#include <stdio.h>
#include <conio.h>
#include <math.h>

#define MAX 50
#define ACCEPTABLE 10000000
#define YES 1
#define NO  0
int Nhap(double* A,int* N,double* B,int* coNghia);
int Xuat(double* X,int N,int coNghia);
int SSOR(const double* A,int N,const double* B,double* X,double w,int coNghia);  //Gauss-Seidel thuc chat cung la SSOR khi w = 1
double HesoLamda(const double *A,int N);
double VongLap(const double*A, int N, const double*B, double* X,
   double w,int ok);
//Thuc hien 1 vong lap. Ok=YES, tra ve maxerror, OK=0, tra ve 0

int main()
{
  double A[MAX][MAX],B[MAX],X[MAX];
  int N,w=1,coNghia;



  Nhap( (double*) A ,&N,B,&coNghia);
  X[0]=2,X[1]=3,X[2]=5;
  SSOR( (const double*) A ,N,(const double*) B,X,w,coNghia);
  Xuat(X,N,coNghia);
  return 0;
}

int Nhap(double* A,int* N,double* B,int* coNghia)
{
  //Dinh dang nhap file SEIDEL.TXT:
  //Dong 1: so hang va cot N cua ma tran A,B
  //Dpmg 2: so chu so co nghia can thiet
  //N dong tiep theo: Nhap ma tran A va B

  FILE *SEIDEL;
  int i,j;
  SEIDEL = fopen("SEIDEL.TXT","rt");
  fscanf(SEIDEL, "%d" , N);
  fscanf(SEIDEL, "%d " , coNghia);
  for (i=0; i < (*N) ; i++)
  {
   for (j=0; j <  (*N) ; j++)
     fscanf(SEIDEL, "%lf",  A + i*MAX + j);
   fscanf(SEIDEL, "%lf", &B[i]  );
  }
  fclose(SEIDEL);
  return 0;
}

int Xuat(double* X,int N,int coNghia)
{
    int i;
    FILE *SEIDEL;
    SEIDEL=fopen("SEIDEl.OUT","w+");
    //fprintf(SEIDEL, "%d", N );
    for (i=0; i< N ; i++)
	fprintf(SEIDEL, "%.*f\n",coNghia,  X[i]);
    return 0;
}

double HesoLamda(const double *A,int N)
{
 double s1=0,s2=0, tmp;
 int i,j;
 double lamda;
 //Tim sai so lamda
 i=0,s1=0,s2=0;
 for (j=i+1; j<N ; j++)
   s2+= fabs ( *(A + i*MAX + j) );
 lamda = fabs ( s2 /  ( (* (A + i*MAX + i)) -s1)  ) ;         //O hang dau tien s1=0 theo dinh nghia
 for (i=0; i<N ; i++ )
 {
   s1=0,s2=0;
   for (j=0; j<i; j++)
     s1+= fabs( *(A + i*MAX + j) );
   if (i==N-1)
     s2=0;
   else
     {
      for (j=i+1; j<N; j++)
	s2+= fabs( *(A + i*MAX + j) );
     }
   tmp= fabs ( s2 / ( (* (A + i*MAX + i))  -s1)  ) ;
   if (tmp> lamda)
     lamda = tmp;
 }
 return lamda;
}

double VongLap(const double*A, int N, const double*B, double* X,
   double w,int ok)
{
 int i,j;
 double tmp,Xtruoc,error,maxerror;
 maxerror=0;

 for (i=0; i<N; i++ )
 {
   tmp=0;
   for (j=0; j<N; j++)
   {
     if (j==i) continue;
     tmp += ( (*(A +i*MAX + j))  * X[j] );
   }
   Xtruoc=X[i];
   X[i]= (1-w)* X[i] + ( w* (B[i]-tmp)  / (*(A + i*MAX + i))  );
	    //X[i] =  (B[i] - tmp)  / (*(A + i*MAX + i))  ;
   if (ok==YES)
   {
     error= fabs( X[i] - Xtruoc );
     if (i==0) maxerror=error;
       else
     if (maxerror<error)
       maxerror=error;
   }
 }
 return maxerror;   //Neu OK==NO, maxerror se bang 0 => gop luon 2 truong hop
}


int SSOR(const double *A,int N,const double* B,double* X,double w,int coNghia)
{      // DK: 0 < w < 2
    int dem=0;
    double error,maxerror;
    long num;
    int i,j;
    double Xtruoc,sumerr,lamda,epsi;
    double tmp1,tmp;

    lamda = HesoLamda(A,N);

    //Tinh toan lan thu nhat nham biet truoc so lan lap
    dem=0;

    maxerror = VongLap(A,N,B,X,w,YES);

    //Tinh toan sai so thuc su
    num=  log (0.5 * pow(10, coNghia) * (1 - lamda) / maxerror)    /   ( log(lamda) )     ;
    num =   abs(floorl(num));
    if ( num > ACCEPTABLE)
	return 0;


    dem=1;
    //Tiep tuc tinh toan nhung lan sau, bay gio da biet truoc so lan lap
    do
    {
	 dem++;
	 VongLap(A,N,B,X,w,NO);
    }
    while ( dem < num );


    return 1;
}
