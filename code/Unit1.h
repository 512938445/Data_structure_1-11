#include "include.h"
using namespace std;

class Unit_1
{
public:
	Unit_1(int temp_List[],int N);
	~Unit_1();
	int MaxSubseqSum();
	int find_member(int temp_List[],int begin,int end,int object);
	void test_function();

	int N;
	int List[];
};