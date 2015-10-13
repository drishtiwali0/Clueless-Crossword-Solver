//word selection via generalised suffix tree
#include<iostream>
#include<vector>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include "gst.h"
using namespace std;
char word_gst[20];
int ptr_letter;
root suffix_tree[5];
void root::put_substring(int i, int word_num)
{
	int temp=check_first_level(i);            //to check if the first letter of substring matches with first level letters
	if(!temp)                                   //no match
	{	

		first_level_pos++;                     //keeping track of letters in first level present
		first_level[first_level_pos]=new first_element_gst;
		first_level[first_level_pos]->letter=word_gst[i];//insert new letter
		first_level[first_level_pos+1]=NULL;             
		insert_childnode(first_level_pos,i+1,i,word_num);//inserting rest of substring
	}
	else
	{
		search(first_level[temp]->link,i+1,i,word_num,temp);//searching for posiible match of next letter at next gen nodes
	}
}
int root::check_first_level(int i)
{
	int first_level_pos_func=1;                         // to keep track of letters in first level read
	while(first_level[first_level_pos_func]!=NULL)
	{
		if(first_level[first_level_pos_func]->letter==word_gst[i])//if match found with first letterof the substrings first
		{                                                         //letter, tell position in first level
			return first_level_pos_func;
		}
		first_level_pos_func++;
	}
	return 0;                                          //if no match return 0
}
void root::insert_childnode(int start_point,int i,int suffix_pt,int word_num)//i is second letter in substrong position
{                                  //suffix_pt is position of letter of first level on actual word 
	first_level[start_point]->link=push_letter(i,suffix_pt,word_num,start_point);//word num is word position on dictionary
}
int root::get_current_pos(first_element_gst* ptr)
{
	int last_level_pos_func=0;
	while(ptr->last_level[last_level_pos_func].pos_of_letter)//to check which labels have been accessed
	{
		last_level_pos_func++;
	}
	return last_level_pos_func;
}	
node* root::push_letter(int i, int suffix_pt,int word_num,int first_level_pos)
{
	node* ptr=new node;
	if(word_gst[i]=='\0')//if substring ended
	{
		ptr->value=suffix_pt;//label of the substring
		last_level_pos=get_current_pos(first_level[first_level_pos]);//getting position to add next label in last level vector
		first_level[first_level_pos]->last_level[last_level_pos].pos_of_letter=suffix_pt+1;//adding 1 to identify unaccessed 
		                                                                 //label position
		first_level[first_level_pos]->last_level[last_level_pos].pos_of_word=word_num;//adding label
		return ptr;
	}
	else//if substring not ended
	{	
		ptr->letter=word_gst[i];// new child for substring letter
		ptr->link_depth_wise=push_letter(i+1,suffix_pt,word_num,first_level_pos);//addition of left over substring length wise 
		return ptr;
	}
}
void root::search(node* ptr,int i,int suffix_pt,int word_num, int first_level_pos)
{
	if(ptr==NULL)//if no added next gen to node matched OR no match found at a level 
	{
		ptr=new node;
		//ptr->letter=word_gst[i];
		ptr=push_letter(i,suffix_pt,word_num,first_level_pos);
		return;
	}
	else if(ptr->letter==word_gst[i])//found match for next letter at next gen 
	{
		search(ptr->link_depth_wise,i+1,suffix_pt,word_num,first_level_pos);
	}
	else
	{
		search(ptr->link_width_wise,i,suffix_pt,word_num,first_level_pos);//check different letters at same level for match 
	}                                                                      //with letter
}
int root::find_location(char key_letter,int key_position,int restart)
{
	if(!restart)
	{	
		ptr_letter=get(key_letter);
		first_level[ptr_letter]->last_level_pos_srch_func=0;
	}
	return search_position(ptr_letter,key_position);
}
int root::get(char key)
{
	int first_level_pos_func=1;
	while(first_level[first_level_pos_func]!=NULL)
	{
		if(first_level[first_level_pos_func]->letter==key)
		{
			return first_level_pos_func;
		}
		first_level_pos_func++;
		
	}
	return 0;
}
int root::search_position(int ptr,int key)
{
	if(ptr==0)
	{
		return -1;
	}
	while(first_level[ptr]->last_level[first_level[ptr]->last_level_pos_srch_func].pos_of_letter)
	{
		if(first_level[ptr]->last_level[first_level[ptr]->last_level_pos_srch_func].pos_of_letter==key+1)
		{
			return first_level[ptr]->last_level[first_level[ptr]->last_level_pos_srch_func].pos_of_word-1;
		}
		first_level[ptr]->last_level_pos_srch_func++;
	}
	return -1;
}
void root::create_st(int size)
{
	int r=1;
	while(!feof(dic_file[size-2]))            //loop to read all words to put in suffix tree 
	{
		fscanf(dic_file[size-2],"%s",word_gst);
		for(int i=0;i<size;i++)                 //loop to put all substrings of 1 word of the file into suffix tree
		{
			put_substring(i,r);                //word position starts with 1
		}
		r++;
	}
}
void build_gst()
{
	for(int i=0;i<5;i++)                            //building 5 generalised suffix trees based on word size
	{
		suffix_tree[i].create_st(i+2);
	}
}
int search_gst(char key_letter, int key_position,int size,int restart)
{
	return suffix_tree[size-2].find_location(key_letter,key_position,restart);//searching suffix tree for key letter at given
}	                                                                          //position
