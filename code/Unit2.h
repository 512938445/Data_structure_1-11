#include "include.h"
class Unit_2
{
public:
	Unit_2(int temp_List[],int temp_N,int k);
	~Unit_2();
	int Average();
	void test_function();
	int FindKthLagest(int temp_List[],int temp_N,int _N);

	int N;
	int k;	
	int List[];
	
};