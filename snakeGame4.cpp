#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<cmath>
#include<conio.h>
#include<fstream>
#define row 50
#define col 50

using namespace std;

int Score=0;
int pCount=0;
struct food
{
	int x;
	int y;
	char value;
}f[3];
struct snake
{
	int x;
	int y;
	char value;
	struct snake* next;
};
struct poison
{
	int x;
	int y;
	char value;
}p[3];
//insertingElements
void insert(struct snake** head,struct snake** tail,int x,int y)
{
	struct snake *n,*ptr;
	char ch;
		n= new snake;
	    n->x=x;
	    n->y=y;
	    n->next=NULL;
	    if((*head)==NULL)
	    {
	    	n->value='#';
		    (*head)=n;
		    (*tail)=n;
	    }
	    else
	    {
	    	n->value='*';
	    	(*tail)->next=n;
	    	(*tail)=(*tail)->next;
		}
}

//Printing Snake
void printMaze(char board[100][100])
{
	for(int i=0;i<row;i++)
    {
		for(int j=0;j<col;j++)
		{
			cout<<board[i][j];
		}
		cout<<endl;
	}
	for(int m=0;m<10000;m++);	
}
void printBorder(char board[100][100])
{
	int i=0,j=0;
	for(i=0;i<row;i++)
	{
		for(j=0;j<col;j++)
		{
			board[i][j]=' ';
		}
	}
	for(i=0;i<row;i++)
	{
		board[i][0]='.';
		board[i][col-1]='.';
	}
	for(i=0;i<col;i++)
	{
		board[0][i]='.';
		board[row-1][i]='.';
	}
}
void genPoison(char board[100][100])
{
	p[pCount].x=(rand()%100)/2+1;
	p[pCount].y=(rand()%100)/2+1;
	while(board[p[pCount].x][p[pCount].y]!=' ')
	{
		p[pCount].x=(rand()%100)/2+1;
	    p[pCount].y=(rand()%100)/2+1;
	}
	p[pCount].value='P';
	board[p[pCount].x][p[pCount].y]=p[pCount].value;
	pCount++;
}
void genRand(char board[100][100])
{
	int m=0;
	while(m!=3)
	{
		f[m].x=(rand()%100)/2+1;
     	f[m].y=(rand()%100)/2+1;
    	while(board[f[m].x][f[m].y]!=' ')
	    {
		    f[m].x=(rand()%100)/2+1;
     	    f[m].y=(rand()%100)/2+1;
	    }
	    f[m].value='O';
	    board[f[m].x][f[m].y]=f[m].value;
	    m++;
	}
}
void addNode(struct snake **tail,char board[100][100],int index,int x,int y)
{
	struct snake *n;
	n=new snake;
	n->x=x;
	n->y=y;
	n->value='*';
	n->next=NULL;
	(*tail)->next=n;
	(*tail)=(*tail)->next;
	f[index].x=(rand()%100)/2+1;
	f[index].y=(rand()%100)/2+1;
	while(board[f[index].x][f[index].y]!=' ')
	{
	    f[index].x=(rand()%100)/2+1;
	    f[index].y=(rand()%100)/2+1;
	}
	board[f[index].x][f[index].y]=f[index].value;
}
void deleteNode(struct snake** head,struct snake** tail,char board[100][100])
{
	struct snake* h=(*head),*temp;
	if(h->next==NULL)
	{
		board[h->x][h->y]=' ';
		delete(h);
		cout<<"Game Over";
		exit(0);
	}
	while(h->next!=(*tail))
	{
	 	h=h->next;
	} 
    (*tail)=h;
	temp=h->next;
	board[temp->x][temp->y]=' '; 
	h->next=NULL;
	delete(temp);
}
//Moving Snake
void moveSnake(struct snake **head,struct snake** tail,int x,int y,char board[100][100])
{
	struct snake *h=(*head),*n,*t=(*tail);
	int a,b;
	if((board[x][y]=='*'))
	{
		if(t->x==x&&t->y==y)
		{
			//Donthing;
		}
		else
		{
			cout<<"Game Over";
		    exit(0);
		}
	}
	while(h!=NULL)
	{
		a=h->x;
		b=h->y;
		h->x=x;
		h->y=y;
		x=a;
		y=b;
		h=h->next;
	}
	h=(*head);
	int m=0;
	while(m+1!=3)
	{
		if(f[m].x==h->x&&f[m].y==h->y)
		   break;
		if(m<pCount&&p[m].x==h->x&&p[m].y==h->y)
		   break;
	    m++;
	}
	if(h->x==f[m].x&&h->y==f[m].y)
	{
		Score++;
		addNode(&(*tail),board,m,x,y);		
	}
	if(h->x==p[m].x&&h->y==p[m].y)
	{
		Score--;
		deleteNode(&(*head),&(*tail),board);
		genPoison(board);
		board[x][y]=' ';
	}
	else
	{
		board[x][y]=' ';
	}
	
}

int xtract(char str[],int *i)
{
	int k=0,res;
	char num[10];
	while(str[*i]!=','&&str[*i]!='\0')
	{
		num[k]=str[*i];
		
		(*i)++;
		k++;
	}
	num[k]='\0';
	res=atoi(num);
	return res;
}

void loadFromFile(struct snake** head,struct snake** tail,char *file,char board[100][100])
{
	char str[20],num[10];
	int i=0,x,y,k,m=0;
	ifstream fin;
	fin.open(file);
	while(fin)
	{
		fin>>str;
		
		i=0;
		k=0;
		while(str[i]!=',')
		{
			num[k]=str[i];
			k++;
			i++;
		}
		num[k]='\0';
		i++;
		x=xtract(str,&i);
		i++;
		y=xtract(str,&i);
		if(!(strcmp(num,"snake")))
		{
			insert(&(*head),&(*tail),x,y);
		}
		else if(!(strcmp(num,"food")))
		{
			f[m].x=x;
			f[m].y=y;
			f[m].value='O';
			board[f[m].x][f[m].y]=f[m].value;
			m++;
		}
		else if((!strcmp(num,"poison")))
		{
			p[pCount].x=x;
			p[pCount].y=y;
			p[pCount].value='P';
			board[p[pCount].x][p[pCount].y]=p[pCount].value;
			pCount++;
		}
		else if((!strcmp(num,"score")))
		{
			Score=x;
		}
	}
	
}

void saveFile(struct snake* head,char *file)
{
	ofstream fout;
	char str[10];
	fout.open(file);
	int i=0,temp,len,m;
	while(head!=NULL)
	{
		fout<<"snake,";
		itoa(head->x,str,10);
	    fout<<str;
     	fout<<',';
	    itoa(head->y,str,10);
    	fout<<str;
    	fout<<'\n';	
		head=head->next;
	}
	m=0;
	while(m!=3)
	{
		fout<<"food,";
		itoa(f[m].x,str,10);
	    fout<<str;
	    fout<<',';
	    itoa(f[m].y,str,10);
	    fout<<str;
	    fout<<'\n';	
		m++;
	}
	m=0;
	while(m!=3)
	{
		fout<<"poison,";
	    itoa(p[m].x,str,10);
	    fout<<str;
	    fout<<',';
	    itoa(p[m].y,str,10);
	    fout<<str;
	    fout<<'\n';
	    m++;
	}
	fout<<"score,";
	itoa(Score,str,10);
	fout<<str<<","<<"0\n";	
}
//snakeGame
void snakeGame(struct snake* head,struct snake* tail,char board[100][100],char *file)
{
	struct snake *h=head,*t;
	int i,j,flag=0,m=0,yes;
	char level[20]="L  E  V  E  L -  1";
	char endingText[100]="";
	int temp;
	char ch='b';
	do
	{
		system("CLS");
		while(h!=NULL)
	    {
		    board[h->x][h->y]=h->value;
	     	h=h->next;
	    }
	    h=head;
		if(Score==12)
	    {
	    	strcpy(endingText,"You Have Completed Level 5.You Won");
	    	break;
		}
		if(Score==3&&flag==0)
		{ 
			strcpy(level,"L  E  V  E  L -  2");
			flag=1;
			genPoison(board);
		}
		if(Score==5)
		{
			strcpy(level,"L  E  V  E  L -  3");
			while(pCount!=3)
			{
				genPoison(board);
			}
		}
		if(Score==8)
		{
			strcpy(level,"L  E  V  E  L -  4");
		}
		cout<<"\t\t"<<level<<endl;
		printMaze(board);
		cout<<"\nScore->"<<Score<<endl;
		cout<<"\nMove Snakes Towards Right(r) Left(l) Top(t) Bottom(b) Or Exit(x)\n";
		if(kbhit())
		{
			ch = getch();
		}
		temp=0;
		switch(ch)
		{
			case 'l' :
			if(head->next!=NULL)
			    temp=head->y-head->next->y;
			if(temp< -1||temp==1)
			{
				cout<<"\nInvalid Move\n";
			}
			else
			{
				if(head->y==1)
				{
					if(Score>=8)
					{
						cout<<"Game Over"<<endl;
						exit(0);
					}
					moveSnake(&head,&tail,head->x,col-2,board);	
				}
				else
					moveSnake(&head,&tail,head->x,head->y-1,board);
			}
			break;
			case 'r' :
			if(head->next!=NULL)
			    temp=head->next->y-head->y;
			if(temp< -1||temp==1)
			{
				cout<<"\nInvalid Move\n";	
			}
			else
			{
				if(head->y==col-2)
				{
					if(Score>=8)
					{
						cout<<"Game Over"<<endl;
						exit(0);
					}
					moveSnake(&head,&tail,head->x,1,board);	
				}
				else
				    moveSnake(&head,&tail,head->x,head->y+1,board);
			}	
			break;
			case 't' :
			if(head->next!=NULL)	
			    temp=head->x-head->next->x;
			if(temp< -1||temp==1)
			{
				cout<<"\nInvalid Move\n";	
			}
			else
			{
				if(head->x==1)
				{
					if(Score>=8)
					{
						cout<<"Game Over"<<endl;
						exit(0);
					}
					moveSnake(&head,&tail,row-2,head->y,board);	
				}
				else
				    moveSnake(&head,&tail,head->x-1,head->y,board);
			}	
			break;
			case 'b' :
			if(head->next!=NULL)
			    temp=head->next->x-head->x;
			if(temp< -1||temp==1)
			{
				cout<<"\nInvalid Move\n";	
			}
			else
			{
				if(head->x==row-2)
				{
					if(Score>=8)
					{
						cout<<"Game Over"<<endl;
						exit(0);
					}
					moveSnake(&head,&tail,1,head->y,board);	
				}
				else
				    moveSnake(&head,&tail,head->x+1,head->y,board);
			}	
			break;
			case 'x' :
				cout<<"Do U Wana Save This File 1 or 0";
				cin>>yes;
				if(yes)
				{
					saveFile(head,file);
				}
				cout<<"Game Over\n";
				
		}
		for(int m=0;m<20000000;m++);  //Loop is used to slow th espeed of snake which became very fast due to kbit 
		cout<<endl;
	}while(ch!='x');
	cout<<endingText<<endl;
}


//LoadPreviousStage*/
int main()
{
	struct snake *sHead=NULL,*sTail=NULL;
	char board[100][100],file[20]="fileSnake.txt",ch;
	int f=0;	
	int i,j,x,y;
	srand(time(0));
	printBorder(board);
	cout<<"Do You Wish To Continue Previous Game 1 or 0\n";
	cin>>f;
	if(f)
	{
		loadFromFile(&sHead,&sTail,file,board);
	}
	else
	{
		x=4;
		y=4;
	    do
		{
			insert(&sHead,&sTail,x,y);
			y++;
		}while(y!=6);
		genRand(board);
	}
	snakeGame(sHead,sTail,board,file);		
}
