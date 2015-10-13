//To use different word selection algorithm based on different data structures.
#include<iostream>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "gst.h"
#include "2D_mat.h"
#include "3D_mat.h"
#include <sys/time.h>
#include "display.h"
using namespace std;
class element
{
	int size;
	int prev_pos;
	int next_pos;
	public:
	void alot();
	int return_size()
	{	
		return size;
	}
	int return_prev_pos()
	{	
		return prev_pos;
	}
	int return_next_pos()
	{	
		return next_pos; 
	}
	void assign(int a, int b, int c);
};
class block  : public element
{
	int dic_pos;
	int ptr_letter;
	public:
	char word[7];
	void copy(element info)
	{	  
		assign(info.return_size(),info.return_prev_pos(),info.return_next_pos());
	}
	int word_selection();
	int first_word_selection();
	int check_with_prev();
	block()
	{	
		dic_pos=0;
		ptr_letter=0;
	}
	block* link;
}*top,*prev,*ptr;
vector<element> blank_crossword;
block crossword_first;
FILE* dic_file[5];
int Num_of_block,choice=1;
char word[6];
char grid[30][30];
int check=0;
int first_algnment;
timeval start_time,stop_time;
char time_taken[100];
void alot_features();
void gen_blank_crossword(int number);
int solving(element* list_of_elements);
block* add_next_crossword(element info);
void pop();
void add_verticle(int i,int* x,int* y);
char* linear_search(char a,int b,int c,int* d);
void open_dic();
void reset_dic();
void close_dic();
void add_horizontal(int i,int* x,int* y);
void display_blank();
void add_verticle_filled(int i,int* x,int* y);
void display_filled();
void add_horizontal_filled(int i, int* x,int* y);	
void element::alot()                                  // to randomly alot features to the elements of blank crossword
{
	size = (rand() % 4)+3;
	prev_pos = (rand() % (size-2));
	next_pos = (rand() % (size-2-prev_pos))+prev_pos+2;
}
void element::assign(int a , int b, int c)    //copy function
{
	size=a;
	prev_pos=b;
	next_pos=c;
}
int block::word_selection()                          //word selection algorithm
{
	char key_letter=prev->word[prev->return_next_pos()];
	switch(choice)
	{
		case 1:	strcpy(word,linear_search(key_letter, return_prev_pos(),return_size(),&dic_pos));
		 		break;
		case 2:	dic_pos=search_gst(key_letter,return_prev_pos(),return_size(),dic_pos);
				break;
		case 3:	dic_pos=search_2D(key_letter,return_prev_pos(),return_size(),dic_pos);
				break;
		case 4:	dic_pos=search_3D(key_letter,return_prev_pos(),return_size());
				break;
	}
	fseek(dic_file[return_size()-2],dic_pos*(return_size()+1),SEEK_SET);
	if(choice!=1)
	{
		return fscanf(dic_file[return_size()-2],"%s",word);
	}
	if(feof(dic_file[return_size()-2]))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
char* linear_search(char key_letter,int key_position,int size, int * dic_pos) //linear search algorithm
{
	fseek(dic_file[size-2],*dic_pos,SEEK_SET);
	while(!feof(dic_file[size-2]))
	{
		fscanf(dic_file[size-2],"%s",word);
		if(word[key_position]==key_letter)
		{
			*dic_pos=ftell(dic_file[size-2]);
			break;
		}
	}
	return word;
}
int block::check_with_prev()
{
		return (word[return_prev_pos()]==prev->word[prev->return_next_pos()]);
}
int block::first_word_selection()              //selecting the first word
{
	reset_dic();
	int a=fscanf(dic_file[return_size()-2],"%s",word);
	return a;
}	
void pop()                              //to pop the block
{
	ptr=top;
 	top=top->link;
 	prev=prev->link;
 	delete ptr;
 	ptr=top;
}
void alot_features()                        //randomly getting all features of crossword
{
	Num_of_block=(rand()%5)+3;
	first_algnment=rand()%2;
	blank_crossword.reserve(Num_of_block);
	gen_blank_crossword(Num_of_block);
}
void gen_blank_crossword(int Number)                     //generating blank crossword
{
	for(int indicator=0;indicator<Number;indicator++)                      
 	{
  		blank_crossword[indicator].alot();
 	}
}
int solving(element* list_of_elements)
{
	open_dic();
	/*cout<<"Enter choice:\n1.linear search\n2.generalized suffix tree\n3.2D matrix\n4.3D matrix";
	cin>>choice;
	cout<<"\nTime taken by:";*/
	switch(choice)
	{
		case 2:	build_gst(); 
				break;
		case 3:	build_2D();
				break;
		case 4:	build_3D();
				break;
	}			
	int indicator,check=0;
	crossword_first.copy(*list_of_elements); //pushing first block
	top=&crossword_first;
	gettimeofday(&start_time,NULL);             //timing starts
	while(crossword_first.first_word_selection()) //continue till all words of firsts dictionaries are not filled
	{                                        
          for(indicator=1;(indicator<Num_of_block)&&(indicator);indicator++) //either push till end or if all poped exit          
          {
          	ptr=add_next_crossword(list_of_elements[indicator]);//push next block
               check=ptr->word_selection();                        //select appropriate word
               while(!check)                                     
               {
               	pop();                                          //if no match found at this level pop
               	indicator--;
    				if(!indicator)
    				{
    					break;
    				}
    				check=ptr->word_selection(); 
    			}
    			if(!indicator)
    			{
    				indicator--;
    			}
    		}
  		if(indicator==Num_of_block)
  		{
  			return 1;
  			break;
  		}
  	}	   
  	return 0;
}
block* add_next_crossword(element info)     //pushing block into stack
{
	block* ptr=new block;
	ptr->copy(info);
 	ptr->link=top;
 	prev=top;
 	top=ptr;
 	return ptr;
}
void open_dic()              //opening dictionary files 
{
	for(int i=0;i<5;i++)
	{
	     char name[16]="dictionary_";
		char a[2];
		a[0]=50+i;
	     a[1]='\0';
	     strcat(name,a);
		strcat(name,".txt");
		dic_file[i]=fopen(name,"r");
	}
}
void reset_dic()                          //reseting dictionaries for new blank filling
{
	for(int i=0;i<5;i++)
	{
		fseek(dic_file[i],0,SEEK_SET);
	}
}
void close_dic()                 //closing dictionaries at end
{
	for(int i=0;i<5;i++)
	{
		fclose(dic_file[i]);
	}
}
void display_blank()                      //displaying blank crossword
{
	int algnment=first_algnment;
	int *current_x;
	int *current_y;
	int x=8;
	int y=10;
	current_x=&x;
	current_y=&y;
	for(int i=Num_of_block-1;i>=0;i--,algnment++)
	{
		if(algnment%2)
		{
			add_horizontal(i,current_x,current_y);
		}
		else
		{
			add_verticle(i,current_x,current_y);
		}
	}
	disply();
	/*for(int i=0;i<20;i++)
	{
		for(int j=0;j<20;j++)
		{
			if(grid[i][j]=='*')
			{
				cout<<"*";
			}
			else
			{
				cout<<" ";
			}
		}
		cout<<"\n";
	} */
}
void add_horizontal(int i,int* x,int* y)       //adding blanks to grid
{
	for(int k=0;k<blank_crossword[i].return_size();k++)
	{
		grid[*x+k][*y]='*';
	}
	if(i==0)
	{
		return;
	}
	*x+=blank_crossword[i].return_prev_pos();
	*y-=blank_crossword[i-1].return_next_pos();
}
void add_verticle(int i,int* x,int* y)                 //adding blanks to grid
{
	for(int k=0;k<blank_crossword[i].return_size();k++)
	{
		grid[*x][*y+k]='*';
	}
	if(i==0)
	{
		return;
	}
	*x-=blank_crossword[i-1].return_next_pos();
	*y+=blank_crossword[i].return_prev_pos();
}
void display_filled()                        //displaying filled crossword
{
	int algnment=first_algnment;
	int *current_x;
	int *current_y;
	int x=8;
	int y=10;
	current_x=&x;
	current_y=&y;
	ptr=top;
	for(int i=Num_of_block-1;i>=0;i--,algnment++)
	{
		if(algnment%2)
		{
			add_horizontal_filled(i,current_x,current_y);
		}
		else
		{
			add_verticle_filled(i,current_x,current_y);
		}
		if(i>0)
		{
			ptr=ptr->link;
		}
	}
	disply();
	/*for(int i=0;i<30;i++)
	{
		for(int j=0;j<30;j++)
		{
			if(grid[i][j])
			{
				cout<<grid[i][j];
			}
			else
			{
				cout<<" ";
			}
		}
		cout<<"\n";
	}*/
}
void add_horizontal_filled(int i, int* x,int* y)      //adding filled elements to grid
{
	for(int k=0;k<blank_crossword[i].return_size();k++)
	{
		grid[*x+k][*y]=ptr->word[k];
	}
	if(i==0)
	{
		return;
	}
	*x+=blank_crossword[i].return_prev_pos();
	*y-=blank_crossword[i-1].return_next_pos();
}
void add_verticle_filled(int i,int* x,int* y)      //adding filled elemnts to the grid
{
	for(int k=0;k<blank_crossword[i].return_size();k++)
	{
		grid[*x][*y+k]=ptr->word[k];
	}
	if(i==0)
	{
		return;
	}
	*x-=blank_crossword[i-1].return_next_pos();
	*y+=blank_crossword[i].return_prev_pos();
}			
int main()
{
	unsigned int seed;
 	time_t t;
 	seed=(unsigned) time (&t);
 	srand(seed);
	alot_features();                    //generating blank crossword
	display_blank();                    //displaying blank crossword
	check=solving(&blank_crossword[0]); //solving crossword
	gettimeofday(&stop_time,NULL);
	long diff= (stop_time.tv_usec - start_time.tv_usec);//checking time required
	sprintf(time_taken,"%ld",diff);
	display_filled();
	/*switch(choice)                                   //To display on terminal
  	{
  		case 1: 	cout<<"linear search";
  				break;
  		case 2:	cout<<"generalised suffix tree";
  				break;
  		case 3:	cout<<"2D matrix";
  				break;
  		case 4:	cout<<"3D matrix";
  				break;
  	}*/
	//cout<<"microseconds\n";
	if(!check)
	{
		cout<<"No solution";
	}
	close_dic();
	return 0;
}
