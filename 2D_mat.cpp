#include <iostream>
#include <vector>
#include<string.h>
#include<stdio.h>
#include "2D_mat.h"
using namespace std;
char word_2d[10];
matrix_2d matrix_2d_head[5];
void first_element_2d::put_letter(int letter_position,int word_position)
{
	int pos=binary_search(letter_position,word_position);//to find correct position to insert the word position value
	label_2d *temp;                                        //according to increasing letter position
	temp=new label_2d;                                      
	temp->letter_pos=letter_position;
	temp->word_pos=word_position+1;
	push(temp,pos);                         //pushing the label after finding correct location
	label_pos++;	                           //keeping track of last value read into a particular next_gen
	delete temp;
}
int first_element_2d::binary_search(int letter_position,int word_position)//search for correct letter position insertion
{
	int start=0;
	int end=label_pos-1;
	int mid=(start+end)/2;
	while(start<=end)
	{
		if(next_gen[mid].letter_pos==letter_position)
		{
			break;
		}
		else if(next_gen[mid].letter_pos<letter_position)
		{
			start=mid+1;
		}
		else
		{
			end=mid-1;
		}
		mid=(start+end)/2;
	}
	return mid;
}
void first_element_2d::push(label_2d* temp,int position)//insertion of label in sorted list
{                                   
	int i;
	for(i=label_pos;i>position;i--)
	{
		next_gen[i].letter_pos=next_gen[i-1].letter_pos;
		next_gen[i].word_pos=next_gen[i-1].word_pos;
	}
	next_gen[i].letter_pos=temp->letter_pos;
	next_gen[i].word_pos=temp->word_pos;
}
int first_element_2d::search(int letter_position)//search of correct letter position
{
	int start=0;
	int end=label_pos-1;
	mid=(start+end)/2;
	while((start<=end)&&(next_gen[mid].word_pos))
	{
		if(next_gen[mid].letter_pos==letter_position)
		{
			while(mid>0)
			{
				if(next_gen[mid-1].letter_pos==letter_position)// earliest word position matching this letter position
				{
					mid--;
				}
				else
				{
					break;
				}
			}
			return next_gen[mid].word_pos;
		}
		else if(next_gen[mid].letter_pos<letter_position)
		{
			start=mid+1;
		}
		else
		{
			end=mid-1;
		}
		mid=(start+end)/2;
	}
	return -1;           //in case no found word with letter position correct
}
void matrix_2d::create_mat(int size)
{
	int r=1;                      //keeping r as word position in file
	while(!feof(dic_file[size-2]))
	{
		fscanf(dic_file[size-2],"%s",word_2d);//reading word from file
		for(int i=0;i<size;i++)
		{	
			first_level[(int)word_2d[i]-97].put_letter(i,r);//adding letters in matrix
		}
		r++;
	}

}
void build_2D()                     //building matrices of different sizes
{
	for(int i=0;i<5;i++)
	{
		matrix_2d_head[i].create_mat(i+2);
	}
}
int search_2D(char key_letter,int key_position,int size,int dic_pos)
{
	
	if(!dic_pos)                                        //first search for a particular letter at particular position
	{
		return matrix_2d_head[size-2].first_level[(int)key_letter-97].search(key_position)-1;
	} //matrix_head tells particular matrix and its first level at given letter - search
	return matrix_2d_head[size-2].first_level[(int)key_letter-97].rest_search(key_position)-1;
}
int first_element_2d::rest_search(int letter_position)
{
	while(next_gen[mid+1].letter_pos==letter_position)//mid is fixed for 1 next_gen, so keeps track of next word position 
	{                                                 //satisfying criteria
		mid++;
		return next_gen[mid].word_pos-1;
	}
	return -1;
}
