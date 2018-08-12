#include <stdio.h>
#include <conio.h>

#define MAX 100
#define YES 1
#define NO  0

int r,s,N,M;
int r1=0,s1=0;
int ngang[MAX],doc[MAX];           //ngang,doc: 0->r1+1, 0->s1+1
int tong[MAX],vitri_i[MAX],vitri_j[MAX],demtong=-1;	//Heap
long sum_mapping[MAX][MAX];

int nhap(long *dubao);
long entry(long *dubao, int i, int j);
long* address(long *dubao, int i, int j);
//long Grid(long *dubao);
int Divide(long *dubao, int ngang1, int doc1, int ifdoc);

int Sum_max(long *sum_mapping,
	int *ngang1, int *doc1);   //sum_mapping: 0->r1, 0->s1
int update_sum(long *sum_mapping, int vitri, int ifdoc);
int phep_gan(long *sum_mapping, int i, int j, long value);
//int add_heap(long data,int i, int j);
//long extract_heap(int *i, int *j);

int main()
{
 int result;
 long dubao[MAX][MAX],i,j;
 nhap( (long*) dubao);
 ngang[0]=0, ngang[1]=N, doc[0]=0, doc[1]= M;
 sum_mapping[0][0] = 0;
 for (i=0; i<N; i++)
	for (j=0 ; j<M; j++)
		sum_mapping[0][0]+= dubao[i][j];
 result = Divide( (long* ) dubao, 0, 0, NO);
 getch();
 return 0;
}

int nhap(long *dubao)
{
 FILE *f;
 int i,j;
 f = fopen("grid.txt","r");
 fscanf(f,"%d %d %d %d",&N,&M,&r,&s);
 for (i=0; i< N; i++)
	for (j=0; j< M; j++)
		fscanf(f,"%ld",dubao + i*MAX + j);
 fclose(f);
 return 0;
}

long entry(long *dubao, int i, int j)
{
 return (*(dubao + i*MAX + j));
}

long* address(long *dubao, int i, int j)
{
	return (dubao+ i*MAX +j);
}

int phep_gan(long *sum_mapping, int i1, int j1, long value)
{
	(*(sum_mapping +i1*MAX + j1)) = value;
	return 0;
}

/*
long Grid(long *dubao)
{
 int i,j,tmp; 					//Bien dem
 ngang[0]=0,ngang[1]= M, doc[0]=0,doc[1]=N;
 dem= (r1+1) * (s1+1);
 tong[0]=0;
 for (i=0; i< N; i++)
	for (j=0; j< M; j++)
		tmp+= entry(dubao,i,j);
 add_heap(tmp, 0, 0);

 while (r1<r)
 {
  //extract_heap(&i,&j);
  i = vitri_i[0],j = vitri_j[0];
  Divide(dubao,i,j,NO);
  //r1++;
  //Sap xep lai tat ca
 }
}
*/
int Divide(long *dubao, int ngang1, int doc1,int ifdoc)
{
 if (ifdoc==NO)
 {
  int i,j,tongngang[MAX],n,m;
  int tongtmp[MAX]={0};
  int dau,cuoi,giua, key,tmp;
  int result;
  int max1, max2;

  m = doc[doc1+1] - doc[doc1]-1;
  n = ngang[ngang1+1] - ngang[ngang1]-1;
  for (i=0; i<=n; i++)
  {
	tongngang[i]=0;
	for (j=0; j<=m; j++)
	{
		tongngang[i]+= entry(dubao , ngang[ngang1]+i , doc[doc1]+j);
	}
  }
  tmp=0;
  for (i=0; i<=n; i++)
  {
	tmp+=tongngang[i];
	tongtmp[i]=tmp;
  }

  dau=ngang[ngang1], cuoi=ngang[ngang1+1];
  giua = dau+ (cuoi-dau)/2;
  key = tongtmp[n]/2;
  while (dau<=cuoi)
  {
   giua = dau+ (cuoi-dau)/2;
   if (key==tongtmp[giua])
	break;
   if (key> tongtmp[giua])
	dau = giua+1;
   else
	cuoi= giua-1;
  }

  if (dau<=cuoi)
	result = giua;
  else
  {
	max1 = tongtmp[m] - tongtmp[cuoi];
	max2 = tongtmp[dau];
	if (max1 < max2)
		result = cuoi;
	else
		result = dau;
  }
  result++;


  {
   //tmp= ngang[ngang1+1] ;
   //ngang[ngang1+1] = result;
   for (i=r1+2; i>= ngang1+1; i--)            //r1????
   {
    ngang[i]= ngang[i-1];
   }
   ngang[ngang1+1]=result;
   r1++;
   //update_sum
   update_sum( (long*) sum_mapping, ngang1, ifdoc);
  }
  return result;
 }
 else
 {
  int i,j,tongdoc[MAX],n,m;
  int tongtmp[MAX]={0};
  int dau,cuoi,giua, key,tmp;
  int result;
  int max1, max2;

  m = doc[doc1+1] - doc[doc1]-1;
  n = ngang[ngang1+1] - ngang[ngang1]-1;
  for (j=0; j<=m; j++)
  {
	tongdoc[j]=0;
	for (i=0; i<=n; i++)
	{
		tongdoc[j]+= entry(dubao,ngang[ngang1]+i,doc[doc1] + j);
	}
  }
  tmp=0;
  for (j=0; j<=m; j++)
  {
	tmp+=tongdoc[j];
	tongtmp[j]=tmp;
  }

  dau=doc[doc1], cuoi=doc[doc1+1];
  giua = dau+ (cuoi-dau)/2;
  key = tongtmp[n]/2;
  while (dau<=cuoi)
  {
   giua = dau+ (cuoi-dau)/2;
   if (key==tongtmp[giua])
	break;
   if (key> tongtmp[giua])
	dau = giua+1;
   else
	cuoi= giua-1;
  }

  if (dau<=cuoi)
	result = giua;
  else
  {
	max1 = tongtmp[m] - tongtmp[cuoi];
	max2 = tongtmp[dau];
	if (max1 < max2)
		result = cuoi;
	else
		result = dau;
  }
  result++;
  max1=result-2;
  {
   //tmp= doc[doc1-1] ;
   //ngang[ngang1+1] = result;
   for (i=s1+2; i>= doc1+1; i--)            //r1????
   {
    doc[i]= doc[i-1];
   }
   doc[doc1+1]=result;
   s1++;
   //update_sum
  }
  return result;
 }
}

int update_sum(long *sum_mapping, int vitri, int ifdoc)
{               //Su dung sau khi r1, s1 da duoc cap nhat
 if (ifdoc==NO)
 {
  int i,j,tong[MAX],dem,value;
  //Khoi tao
  for (dem=0; dem<MAX; dem++)
	tong[dem]=0;
  //Don cac vi tri len truoc
  for (i=r1; i>=vitri+2; i--)
  {
	for (j=0; j<= s1+1; j++)
	{
		value = entry(sum_mapping, ngang[i-1], doc[j]);
		phep_gan(sum_mapping,ngang[i],doc[j] , value);
	}
  }
  //Cap nhat lai
  for (i= ngang[vitri]; i< ngang[vitri+1] ; i++)
  {
	for (dem=1; dem<= s1+1; dem++)
	{
		for (j=doc[dem-1]; j< doc[dem]; j++)
			tong[dem-1]+= entry(sum_mapping,i,j);
	}
  }
  for (j=0; j<= s1; j++)

  {
	value = tong[j];
	phep_gan(sum_mapping, ngang[vitri], j, value);
	//sum[ngang[vitri]] [j] = tong[j];
  }
  for (j=0; j<= s1; j++)
	tong[j]=0;
  for (i = ngang[vitri+1]; i< ngang[vitri+2] ; i++)
  {
	for (dem=1; dem<= s1+1; dem++)
	{
		for (j=doc[dem-1]; j< doc[dem]; j++)
			tong[dem-1]+= entry(sum_mapping,i,j);
	}
  }
  for (j=0; j<= s1; j++)
  {
	value = tong[j];
	phep_gan(sum_mapping, ngang[vitri+1], j, value);
	//sum[ngang[vitri+1]] [j] = tong[j];
  }
 }
 else
 {
 }
}

/*

int add_heap(long data,int i, int j)
{
 int i1,j1,N,key;
 demtong++, tong[demtong] = data, vitri_i[demtong]=i, vitri_j[demtong]=j;
 sum_mapping[i][j]= demtong;
 if (demtong==0)
	return 0;
 N=demtong+1;
 for (i1=N/2; i1>0; i1--)
 {
  j1=2*i1,key= tong[i1-1];
  while (j1<=N)
  {
	 if (j1<N)
		 if (tong[j1-1]< tong[j1])
			 j++;
	 if (key> tong[j1-1])
	  {
		 vitri_i[j1/2-1]=i, vitri_j[j1/2-1]=j;
		 sum_mapping[i][j]=j1/2-1;
		 tong[j1/2-1]= key;
		 break;
		 }
	 tong[j1/2-1] = tong[j1-1];
	 vitri_i[j1/2-1]= vitri_i[j1-1], vitri_j[j1/2-1]= vitri_j[j1-1];
	 sum_mapping[vitri_i[j1-1]] [vitri_j[j1-1]] = j1/2-1;
	 j1*=2;
  }
  tong[j/2-1]=key;
  vitri_i[j1/2-1]=i, vitri_j[j1/2-1]=j;
  sum_mapping[i][j]=j1/2-1;
 }
 return 0;
}

long extract_heap(int *i, int *j)
{
 int value,i1,j1,N, key;
 value = tong[demtong];
 *i = vitri_i[demtong], *j = vitri_j[demtong];
 //sum_mapping[i][j]= demtong;
 demtong--;
 if (demtong==-1)                //TH dac biet
	return value;
 N = demtong+1;
 i1=0;
 j1=2*i1,key= tong[i1-1];
  while (j1<=N)
  {
	 if (j1<N)
		 if (tong[j1-1]< tong[j1])
			 j1++;
	 if (key> tong[j1-1])
	  {
		 vitri_i[j1/2-1]= (*i), vitri_j[j1/2-1]=(*j);
		 sum_mapping[*i][*j]=j1/2-1;
		 tong[j1/2-1]= key;
		 break;
		 }
	 tong[j1/2-1] = tong[j1-1];
	 vitri_i[j1/2-1]= vitri_i[j1-1], vitri_j[j1/2-1]= vitri_j[j1-1];
	 sum_mapping[vitri_i[j1-1]] [vitri_j[j1-1]] = j1/2-1;
	 j1*=2;
  }
  tong[j1/2-1]=key;
  vitri_i[j1/2-1]=(*i), vitri_j[j1/2-1]=(*j);
  sum_mapping[*i][*j]=j1/2-1;
  return value;
}

*/
