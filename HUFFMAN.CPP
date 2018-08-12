#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

//#include <cstdlib>
//#include <cstdio>

#define MAX 600
#define MAXCHAR 256


const int YES=1;
const int NO =0;
const int INVALID=0;

int nhap(int *tansuat,char *input);

int check_extension(char *name, char *extension, size_t length);

int makehuff(int *tansuat, int *huff, int *left, int *right, int *root);

int add_heap(const int *tansuat, int *heap, int input, int *N);

int extract_heap(const int *tansuat, int *heap, int *N);

int readhuff(char ch, int *huff, char *st ); //max of huff: MAXCHAR

int compress_huff(char *input, char *output, int *huff);

char Huff_to_char(char *st);             //8 bit char

int char_to_string(char ch, char *st);   //8 bit char

int decompress_huff(char *compressed, char *decompressed,
	int *left, int *right, int root);



int main()
{
 int i,tansuat[MAX], huff[MAX],left[MAX],right[MAX], root;
 char st[100], *input="HUFFMAN.txt", *output="HUFFMAN.huf";
 char *decompressed= "HUFFMAN2.txt";
 //int N=-1;
 for (i=0; i<MAX; i++)
 {
	tansuat[i]=0;
 }
 if ( nhap(tansuat,input)==INVALID )
	return 0;

 makehuff(tansuat, huff,left,right, &root);
 readhuff('d',huff,st);
 compress_huff(input,output,huff);
 decompress_huff(output,decompressed,left,right,root);

 getch();
 return 0;
}

int add_heap(const int *tansuat, int *heap, int input, int *N)
{
 (*N)++, heap[(*N)-1]= input;
 if ( (*N)==1 )
	return 0;
 int i,j,tmp;
 i= (*N)/2;
 for (i= (*N)/2; i>0; i--)
 {
	j=2*i,tmp=heap[i-1];
	while (j<= (*N) )
	{
		if (j< (*N) )
			if (tansuat[heap[j-1]]> tansuat[heap[j]])
				j++;
		if (tansuat[tmp] < tansuat[heap[j-1]])
		{
			heap[j/2-1]=tmp;
			break;
		}
		heap[j/2-1]=heap[j-1];
		j*=2;
	}
	heap[j/2-1]=tmp;
 }
 return 0;
}

int extract_heap(const int *tansuat, int *heap, int *N)
{
 int value,i,j,tmp,heap1[MAX];

 value=heap[0];
 heap[0]=heap[(*N)-1];
 heap[(*N)-1]= INVALID;
 (*N)--;
 if ((*N)==0)
	return value;

 j=2,tmp=heap[0];
 while (j<= (*N))
 {
	if (j< (*N) )
		if (tansuat[heap[j-1]] > tansuat[heap[j]] )
			j++;
	if (tansuat[tmp]< tansuat[heap[j-1] ])
	{
		heap[j/2-1] = tmp;
		break;
	}
	heap[j/2-1]=heap[j-1];

	j*=2;
 }
 heap[j/2-1]= tmp;

 tmp=0;
 return value;
}

int makehuff(int *tansuat, int *huff, int *left, int *right,int *root)
{
 int p,q,i,heap[MAX]={0},N=0,max,tong,huff1[MAX];
 for (i=0; i<MAXCHAR; i++)
 {
	left[i]=INVALID;
	right[i]=INVALID;
	if (tansuat[i]!=0)
	{
		add_heap( (const int*) tansuat,heap,i,&N);

	}
 }
 max = MAXCHAR;

 for (i=0; i<MAXCHAR; i++)
 {
	huff[i]= INVALID;
 }
 while (N>0)
 {
	p=extract_heap( (const int *) tansuat, heap, &N);
	if (N==0)
		break;
	q=extract_heap( (const int *) tansuat, heap, &N);
	tong = tansuat[p]+tansuat[q];
	max++;
	tansuat[max] = tong;
	huff[p]= -(max+1) , huff[q]=max+1;
	left[max]= p, right[max]=q;
	add_heap( (const int *) tansuat, heap, max, &N);
	tong++;
 }
 huff[max]=-(max+1);  //phan tu goc tro vao chinh no
 (*root)=max;
 return 0;
}

int readhuff(char ch, int *huff, char *st)
{
 int dem=0,i= (int)ch;
 char tmp;
 dem=0;
 do
 {
	if (huff[i]<0)
		st[dem]='0';
	else
	if (huff[i]>0)
		st[dem]='1';
	i= abs(huff[i])-1;
	dem++;
 }
 while (i!= (abs(huff[i])-1) );
 st[dem]='\0';


 for (i=0; i<dem/2; i++)
 {
	tmp = st[i];
	st[i]= st[dem- 1-i];
	st[dem-1-i]=tmp;
	tmp++;
 }
 return 0;
}

int nhap(int *tansuat, char *input)
{
 FILE *f;
 int i;
 char ch;

 if (check_extension(input,".txt",4) == NO)
	return INVALID;
 f = fopen(input,"r");
 if (f==NULL)
	return INVALID;

 while((ch = fgetc(f)) != EOF)
    {
	tansuat[ (int) ch]++;
    }

 fclose(f);
 return YES;
}

int compress_huff(char *input, char *output, int *huff )
{
 FILE *f1,*f2;
 int i;
 char ch,st[8],tmp[8],tg;
 int leftOver;
 int lenst=-1;

 f1 = fopen(input,"r");
 if (f1==NULL)
	return 0;
 f2 = fopen(output,"w");
 fwrite(&leftOver, sizeof(int), 1, f2);

 while((ch = fgetc(f1)) != EOF)
    {
	readhuff(ch,huff,tmp);
	i=0;
	while (tmp[i]!='\0')
	{
		lenst++;
		st[lenst]=tmp[i];
		if (lenst==7)
		{

			st[lenst+1]='\0';
			lenst= -1;
			tg = Huff_to_char(st);
			putc(tg, f2);
		}
		i++;
	}

    }
 //if (lenst!= -1)
 {
	leftOver= lenst;
	//st[lenst+1]='\0';
	for (i=lenst+1; i<8; i++)
		st[i]='0';
	st[8]='\0';
	lenst=-1;
	tg = Huff_to_char(st);
	fputc(tg, f2);
 }

 fclose(f1);
 fclose(f2);

 f2 = fopen(output,"r+b");
 fwrite(&leftOver,sizeof (int), 1, f2);
 fclose(f2);

 return 0;
}

char Huff_to_char(char *st)             //8 bit string (usually)
{
	int i,val=0,tmp,somu;
	somu=1;
	for (i=strlen(st)-1 ; i>=0; i--)
	{
		//if (st[i]=='1')
		//	tmp=1;
		//else
		//if (st[i]=='0')
		//	tmp=0;
		tmp = st[i]-'0';
		val+= tmp*somu ;
		somu*=2;
	}
	return ((char) val);
}

int check_extension(char *name, char *extension, size_t length)
{
	int true1;
	char *pos = strrchr(name, '.');
	true1 = strncmp(pos,extension,length);
	if (true1==0)
		return YES;
	else
		return NO;
}

int char_to_string(char ch, char *st)	//8 bit char
{
	int i,tmp;
	//tmp = ( (unsigned int) ch) ;
	i=7;
	while ( ((int)ch) >0)
	{
		st[i]=(ch%2)+'0';
		ch  = ch/2;
		i--;
	}
	if (i>-1)
	{
		for (; i>=0; i--)
		{
			st[i]='0';
		}
	}
	st[8]='\0';
	return 0;
}

int decompress_huff(char *compressed, char *decompressed,
	int *left, int *right, int root)
{
	FILE *f1,*f2;
	int leftOver,i,j,pos;
	char st[MAX],tmp[MAX];
	char ch1, ch2;
	f1 = fopen(compressed, "r");
	fread(&leftOver, sizeof(int), 1, f1);

	f2 = fopen(decompressed, "w");

	pos = root;
	ch1=getc(f1);
	while ( (ch2=getc(f1)) !=EOF )
	{
		i=0;
		char_to_string(ch1,st);
		do
		{
			if (st[i++]=='0')
				pos=left[pos];
			else
				pos=right[pos];
			if ( (left[pos]==INVALID) && (right[pos]==INVALID) )
			{	//pos is now the dehuffed character
				putc((char) pos,f2);
				pos= root;
			}
		}
		while ( i<8 );
		ch1=ch2;
	}
	//One character left to dehuff; this one's got a leftOver
	i=0;
	if (leftOver!=-1)
	{
		char_to_string(ch1,st);
		do
		{
			if (st[i++]=='0')
				pos=left[pos];
			else
				pos=right[pos];
			if ( (left[pos]==INVALID) && (right[pos]==INVALID) )
			{	//pos is now the dehuffed character
				fputc((char) pos,f2);
				pos= root;
			}
		}
		while ( i<leftOver );
	}
	fclose(f1);
	fclose(f2);
	return 0;
}
