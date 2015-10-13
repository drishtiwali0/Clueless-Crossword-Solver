#include<vector>
#ifndef GST_H_GUARD
#define GST_H_GUARD
extern FILE* dic_file[5];
void build_gst();
int search_gst(char a,int b,int c,int d);
class node
{
	public:
	char letter;
	int value;
	node* link_depth_wise;
	node* link_width_wise;
	node()
	{
		link_depth_wise=NULL;
		link_width_wise=NULL;
	}
};
struct label_gst
{
	int pos_of_letter;
	int pos_of_word;
};
class first_element_gst
{
	public:
	int last_level_pos_srch_func;
	node* link;
	std::vector<label_gst> last_level;
	char letter;
	first_element_gst()
	{
		link=NULL;
		last_level.resize(100000);
		last_level_pos_srch_func=0;
	}
};
class root
{
	first_element_gst* first_level[28];
	int first_level_pos;
	int last_level_pos;
	public:
	void put_substring(int i,int j);
	int check_first_level(int i);
	void insert_childnode(int ptr,int i, int j,int k);
	node* push_letter(int i,int j,int k, int h);
	void search(node* ptr, int i, int j,int k, int h);
	int find_location(char key_letter, int key_position,int a);
	int get(char key);
	void create_st(int size);
	int search_position(int ptr,int key);
	int get_current_pos(first_element_gst* ptr);
	root()
	{
		first_level_pos=0;
		last_level_pos=0;
	}
};
#endif
