#include <stdio.h>	//Problem: Off-line minimum
#include <conio.h>

#define MAX 100
#define YES 1
#define NO 0
#define INVALID -1

int input(int *N, int *M, int *list);
int Offline(int N, int M, int *list, int *extract);
int make_disjoint(int x, int *parent, int *rank);
int union_disjoint(int x, int y, int *parent, int *rank);
int link_disjoint(int x, int y, int *parent, int *rank);
int find_disjoint(int x, int *parent, int *rank);

int main()
{
 int N=9 ,M=6;
 int list[MAX]={3,7,-1,2,-1,8,1,5,-1,-1,-1,0,6,-1,4};
 int extract[MAX]={-1},i;
 for (i=0; i<MAX; i++)
	extract[i]=-1;
 Offline(N,M,list,extract);
 getch();
 return 0;
}

int input(int *N, int *M, int *list)
{
 FILE *f;
 int i;
 f=fopen("OFFLINE.txt","r");
 fscanf(f,"%d %d",N,M);
 for (i=0; i< (M+N); i++)
	fscanf(f,"%d",&list[i]);
 fclose(f);
 return 0;
}

int make_disjoint(int x, int *parent, int *rank)
{
 parent[x]=x;
 rank[x]=0;
 return 0;
}

int union_disjoint(int x, int y, int *parent, int *rank)
{
 link_disjoint(find_disjoint(x,parent,rank), find_disjoint(y,parent,rank),parent,rank );
 return 0;
}

int link_disjoint(int x, int y, int *parent, int *rank)
{
 int rootx, rooty;
 if (y==INVALID)
	return 0;
 rootx= find_disjoint(x,parent,rank);
 rooty= find_disjoint(y,parent,rank);
 parent[rootx]=parent[rooty];
 if (rank[rootx]== rank[rooty])
	rank[rooty]++;
 return 0;
}


int find_disjoint(int x, int *parent, int *rank)
{                                                //Path compression heuristic
 if (parent[x]!=x)
	x = find_disjoint(parent[x], parent, rank);
 return x;
}



int Offline(int N, int M, int *list, int *extract)
{
 int position,dem,i,j,rank[MAX]={0},parent[MAX],pos[MAX];
 int dump[MAX]={-1},cdump;
 int count,exist[MAX]={YES},q,l;
 int list1[MAX],extract1[MAX];
 int root[MAX];
 for (i=0; i<MAX; i++)
 {
	list1[i]= list[i];
	pos[i]=INVALID;
	extract1[i]=extract[i];
	exist[i]=INVALID;
	root[i]=INVALID;
	parent[i]=INVALID;
 }
 position=0;
 cdump=-1;
 for (dem=1; dem <= M+N ; dem++)
 {
	if (list[dem-1]==INVALID)
	{
		position++;
		if (cdump> -1)
		{
			exist[position-1]=YES;
			make_disjoint(dump[0],parent,rank);
			for (i=1; i<=cdump; i++)
			{
				make_disjoint(dump[i],parent,rank);
				union_disjoint(dump[i], dump[0],parent,rank);
				//root[position-1]= find_disjoint(dump[0],parent,rank);
			}
			root[position-1]= find_disjoint(dump[0],parent,rank);
			cdump = -1;
		}
	}
	else
	{
		pos[ list[dem-1] ] =position;
		cdump++;
		dump[cdump] = list[dem-1];
	}
 }
 if (cdump> -1)
 {
	make_disjoint(dump[0],parent,rank);
	for (i=1; i<=cdump; i++)
	{
		make_disjoint(dump[i],parent,rank);
		union_disjoint(dump[i], dump[0],parent,rank);
		//root[position-1]= find_disjoint(dump[0],parent,rank);
	}
	exist[position]=YES;
	root[position]= find_disjoint(dump[0],parent,rank);
	cdump = -1;
 }

 count = M;
 for (i=0; i<N; i++)
 {
	j= pos[ find_disjoint(i,parent,rank)  ];
	if (j!= M)
	{
		extract[j]= i;
		extract1[j]=i;
		q=NO;
		for (l=j+1; l<=M; l++)
		{
			if ((exist[l]==YES)||(exist[l]==INVALID))
			{
				q=YES;
				break;
			}
		}
		if (q==YES)
		{
			union_disjoint(root[j],root[l],parent,rank);
			if (root[l]==INVALID)
			{
				exist[l]=YES;
				root[l]=root[j];
				pos[root[l]]=l;
			}
			else
			{
				pos[root[l]]=l;
			}
			exist[j]=NO;
			q++;
		}
	}
 }
 return 0;
}