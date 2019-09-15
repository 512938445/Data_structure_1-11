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

/**测试出代码需要的变量**/
#ifdef Unit1
int List[]={-2,11,12,13,25,29};
int N=6;
Unit_1 wang(List,N);
#elif Unit2
int List[]={1,2,3,4,5,6,7};
int N = 7;//数组个数
int k = 3;//第几大的数
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
/**测试出代码需要的变量**/


//测试函数运行时间 

void test_time_fuction()
{
	LARGE_INTEGER nFreq;
	LARGE_INTEGER t1;
	LARGE_INTEGER t2;
	double dt;
	QueryPerformanceFrequency(&nFreq);
	QueryPerformanceCounter(&t1);
	/**改这里就行**/
	wang.test_function();
	/**改这里就行**/
	QueryPerformanceCounter(&t2);
	dt = (t2.QuadPart - t1.QuadPart) / (double)nFreq.QuadPart;
	cout<<"Running time :"<<dt*1000000<<"us"<<endl;//dt结果乘以1000,将显示时间调整到ms级别显示，乘以1000000，将显示时间调整到us级别显示
}
//这里面的函数不用动
int main()
{
	test_time_fuction();
	system("pause");
	return 0;
}