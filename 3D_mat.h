#include <vector>
#ifndef THREE_D_H_GUARD
#define THREE_D_H_GUARD
extern FILE* dic_file[5];
struct letter_position
{
	int label[6];
};
class first_element_3d
{
	std::vector<letter_position> next_gen;
	int label_pos[6];
	int search_flag[6];
	public:
	void put_char(int a,int b);
	int search(int a);
	first_element_3d()
	{
		next_gen.resize(10000);
		for(int i=0;i<6;i++)
			label_pos[i]=0;
		for(int i=0;i<6;i++)
			search_flag[i]=0;
	}
};
class matrix_3d
{
	public:
	first_element_3d first_level[26];
	void create_mat(int size);
};
void build_3D();
int search_3D(char key_letter,int key_position,int size);
#endif
