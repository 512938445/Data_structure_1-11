#include"Unit2.h"
using namespace std;
#define KTHLAR 1 //AVERAGE & KTHLAR
Unit_2::Unit_2(int temp_List[],int temp_N,int k)
{
	this->N = temp_N;
	this->k = k;
	for(int i = 0;i < N;i++)
		this->List[i] = temp_List[i];
}
Unit_2::~Unit_2()
{
;
}
int Unit_2::Average()
{
	int Sum = 0;
	for(int i=0;i<this->N;i++)
		Sum += this->List[i];
	return Sum/this->N;
}
int Unit_2::FindKthLagest(int temp_List[],int temp_N,int _N)
{
	int temp_List_1[100]={},temp_List_2[100]={};
	int k=0,j=0;
	for(int i=1;i<temp_N;i++)
	{
		if(temp_List[0] <= temp_List[i])
			temp_List_1[k++]=temp_List[i];
		else
			temp_List_2[j++]=temp_List[i];
	} 
	if(k>=_N)
		return FindKthLagest(temp_List_1,k,_N);
	else if(k == _N - 1)
		return temp_List[0];
	else 
		return FindKthLagest(temp_List_2,j,_N-k-1);
}
void Unit_2::test_function()
{
#ifdef AVERAGE
	cout<<"数组的平均值是"<< this->Average() <<endl;
#elif KTHLAR
	cout << "数组的第"<<k<<"个最大数是"<<this->FindKthLagest(this->List,this->N,this->k)<<endl;
#endif
}