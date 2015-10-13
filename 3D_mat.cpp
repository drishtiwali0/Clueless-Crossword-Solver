#include <iostream>
#include <vector>
#include<string.h>
#include<stdio.h>
#include "3D_mat.h"
using namespace std;
char word_3d[8];
matrix_3d matrix_3d_head[5];
void first_element_3d::put_char(int letter_position,int word_position)
{
	next_gen[label_pos[letter_position]].label[letter_position]=word_position+1;//insert word position in next_gen wherever last 
	label_pos[letter_position]++;  //was placed under coloumn of given letter position and iterate inserted position in that
}                                                                           //coloumn
int first_element_3d::search(int letter_position)
{
	if(!label_pos[letter_position]) //if no word inserted in that coloumn return -1
	{
		return -1;
	}
	while(search_flag[letter_position]<label_pos[letter_position])//searching allowed till last insertion in coloumn
	{
 		
 		return next_gen[search_flag[letter_position]].label[letter_position]-1;
		search_flag[letter_position]++;//keeping track of words read from this list
	}
	return -1;//when run out of words return -1
}
void matrix_3d::create_mat(int size)//create matrix of given size
{
	int r=1;
	while(!feof(dic_file[size-2]))
	{
		fscanf(dic_file[size-2],"%s",word_3d);
		for(int i=0;i<size;i++)
		{	
			first_level[(int)word_3d[i]-97].put_char(i,r);//putting correct word positions in respective letter position places
		}
		r++;
	}
}
void build_3D()//creating matrices for different sized dictionaries
{
	for(int i=0;i<5;i++)
	{
		matrix_3d_head[i].create_mat(i+2);
	}
}
int search_3D(char key_letter,int key_position,int size)//go to matrix head of given size, under given letter, search letter 
{                                                                         //position required
	return matrix_3d_head[size-2].first_level[(int)key_letter-97].search(key_position)-1;
}
