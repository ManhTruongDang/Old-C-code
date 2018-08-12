#include <stdio.h>
#include <conio.h>

#define MAX 100
#define YES 1
#define NO 0
#define INVALID -1

int Nhap(int *path, int *N, int *dau,int *dich, int *thutuong,
	int *thoigian, int *thutuong2);
int city(const int *path, int  N, int  dau,int  dich, int *thutuong,
	int *thoigian, int *thutuong2);
int Xuat(int mincost);
int add_heap(int *marked, int *num,int location, int *index, int *chiphi);
int extract_heap(int *marked, int *num, int *index, int *chiphi);

int main()
{
    int mincost,path[MAX][MAX],N,dau, dich, thutuong[MAX]
	,thoigian[MAX], thutuong2[MAX];
    Nhap( (int*) path, &N , &dau, &dich, thutuong, thoigian , thutuong2 );
    mincost = city( (const int*)path, N, dau, dich, thutuong,
	thoigian, thutuong2);
    Xuat(mincost);
    return 0;
}

int add_heap(int *marked, int *num,int location, int *index, int *chiphi)
{
    int N,j,i,key;
    (*num)++, index[*num] = location;
    marked[location] = YES;
    if ((*num) ==0 )
	return 0;
    N = (*num)+1;

    for (i=N/2; i>= 1; i--)
    {
	j = 2*i;
	key = index[i-1];
	while (j<=N)
	{
	    if (j<N)
		if (chiphi[index[j-1] ] > chiphi[ index[j] ] )
		    j=j+1;
	    if (chiphi[key]< chiphi[index[j-1] ])
	    {
		break;
	    }
	    index[j/2-1] =index[j-1];
	    j*=2;
	}
	index[j/2-1] = key;
    }
    return 0;
}
int extract_heap(int *marked, int *num, int *index, int *chiphi)
{
    int key,value = index[0], i, j,N;
    marked[value] = NO;
    index[0] = index[(*num)], index[(*num)] = -1;
    (*num)--;
    if ( (*num)==-1 )
	return value;

    i =1, j= 2*i, N=(*num)+1;
    key = index[0];
    while (j<=N)
    {
	if (j<N)
	    if (chiphi[  index[j-1] ] > chiphi[ index[j] ])
		j=j+1;
	if (chiphi[key]< chiphi[index[j-1] ])
	{
	    break;
	}
	index[j/2-1] =index[j-1];
	j*=2;
    }
    index[j/2-1] = key;
    return value;
}


int city(const int *path, int  N, int  dau,int  dich, int *thutuong,
	int *thoigian, int *thutuong2)
{
    int alt,i,next,current,passed[MAX],index[MAX], chiphi[MAX],marked[MAX], num=-1,previous[MAX];
    for (i=0; i< MAX; i++)
    {
	index[i] = INVALID;
	marked[i] = NO;
	passed[i] = NO;
	previous[i] = INVALID;
    }
    num= -1;
    add_heap(marked,&num, dau, index, chiphi);
    chiphi[dau ] = 0;
    do
    {
	   current = extract_heap(marked, &num, index, chiphi);
	   i=0;
	   for (next=0; next < N; next++)
	   {
	       if (passed[next] == YES) continue;
	       if ( (*(path + current*MAX + next)) ==INVALID ) continue;
	       if (next == current) continue;
	       alt = chiphi[current] + ( *(path + current*MAX + next) );
	       if (thutuong[current] == next )
	       {
		    if (chiphi[current]< thoigian[ next ] )
		    {
		     if (chiphi[current] > thoigian[ current ])
		      {
			alt = thoigian[next] +
			 ( *(path + current*MAX + next) );
			//Doi cho den khi thu tuong di qua
		      }
		    }
	       }
	       else
	       if (thutuong2[current] == next)
	       {
		    if (chiphi[current] < thoigian[ current ])
		    {
		     if (chiphi[current] > thoigian[thutuong2 [next] ])
		      {
			alt = thoigian[ current ] +
			  ( *(path + current*MAX + next) );
			//Doi cho den khi thu tuong di qua
		      }
		    }
	       }
	       if (marked[next] == NO)
	       {
		   add_heap(marked,&num, next, index, chiphi);
		   chiphi[next] = alt;
		   previous[next] = current;
	       }
	       else
		if (alt < chiphi[next] )
		    {
			chiphi[next] = alt;
			previous[next] = current;
		    }
	   }
	   passed[current] = YES;
    }
    while (current != dich);
    return chiphi[current];

}

int Xuat(int mincost)
{
    FILE *f;
    f = fopen("CITY.OUT","w+");
    fprintf(f,"%d",mincost);
    fclose(f);
    return 0;
}

int Nhap(int *path, int *N, int *dau,int *dich,
	int *thutuong, int *thoigian, int *thutuong2)
{
    FILE *f;
    int tmp,dem,cost,truoc,u,v,m,sonutM,sau,duongdi[MAX],chenhlech;
    f = fopen("city.inp","r");

    fscanf(f,"%d %d",N, &m);
    fscanf(f,"%d %d %d %d", dau, dich, &chenhlech, &sonutM);
    (*dau)--,(*dich)--;
    dem=0;
    for (u=0; u< (*N); u++)
     for (v=0; v< (*N); v++)
      (*(path + u*MAX +v)) = INVALID;

    for (dem=0; dem< (*N); dem++)
    {
	thoigian[dem] = INVALID;
	thutuong[dem] = INVALID;
	thutuong2[dem] = INVALID;
    }

    dem=0;
    for (dem=0; dem< sonutM; dem++ )
    {
	fscanf(f,"%d", &tmp);
	duongdi[dem]=tmp-1;
    }
    dem=0;
    for (dem = 1; dem <= m; dem++   )
    {
	fscanf(f,"%d %d",&u,&v);
	u--,v--;
	fscanf(f,"%d", &tmp);
	(*(path + u*MAX + v)) = tmp;
	(*(path + v*MAX +u)) = (*(path + u*MAX + v));
    }

    truoc = duongdi[0];
    cost = 0 - chenhlech;
    thoigian[truoc] = cost;

    for (dem=1; dem < sonutM ; dem++)
    {
	sau = duongdi[dem];
	thutuong[truoc] = sau;
	thutuong2[sau] = truoc;
	tmp = (*(path +truoc*MAX + sau));
	truoc = sau;
	cost += tmp;

	thoigian[sau] = cost;
    }
    truoc = duongdi[sonutM-1];

    fclose(f);
    return 0;
}
