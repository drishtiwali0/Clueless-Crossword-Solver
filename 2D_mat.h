#include <vector>
#ifndef TWO_D_H_GUARD
#define TWO_D_H_GUARD
extern FILE* dic_file[5];
struct label_2d
{
	int word_pos;
	int letter_pos;
};
class first_element_2d
{
	std::vector<label_2d> next_gen;
	int label_pos;
	int mid;
	public:
	void put_letter(int a,int b);
	int search(int a);
	int binary_search(int a,int b);
	void push(label_2d* temp,int a);
	int rest_search(int a);
	first_element_2d()
	{
		label_pos=0;
		next_gen.resize(10000);
	}
};
class matrix_2d
{
	public:
	first_element_2d first_level[26];
	void create_mat(int size);
};
void build_2D();
int search_2D(char key_letter,int key_position,int size,int dic_pos);
#endif
