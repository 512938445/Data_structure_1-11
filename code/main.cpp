#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#include "Unit4.h"
#include "Unit5.h"
#include "Unit6.h"
#include "Unit7.h"
#include <stack>
#include <iostream>
#include <vector>
#define Unit7 1
using namespace std;

/**���Գ�������Ҫ�ı���**/
#ifdef Unit1
int List[]={-2,11,12,13,25,29};
int N=6;
Unit_1 wang(List,N);
#elif Unit2
int List[]={1,2,3,4,5,6,7};
int N = 7;//�������
int k = 3;//�ڼ������
Unit_2 wang(List,N,k);
#elif Unit3
Unit_3 wang;
#elif Unit4
Unit_4 wang;
#elif Unit5
Unit_5 wang;
#elif Unit6
Unit_6 wang;
#elif Unit7;
Unit_7 wang;
#endif
/**���Գ�������Ҫ�ı���**/


//���Ժ�������ʱ�� 

void test_time_fuction()
{
	LARGE_INTEGER nFreq;
	LARGE_INTEGER t1;
	LARGE_INTEGER t2;
	double dt;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&t1);
	/**���������**/
	wang.test_function();
	/**���������**/
	QueryPerformanceCounter(&t2);
	dt = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;
	cout<<"Running time :"<<dt*1000000<<"us"<<endl;//dt�������1000,����ʾʱ�������ms������ʾ������1000000������ʾʱ�������us������ʾ
}
//������ĺ������ö�
int main()
{
	test_time_fuction();
	system("pause");
	return 0;
}