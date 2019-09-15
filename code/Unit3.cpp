#include "Unit3.h"
#define STACK 0

Unit_3::Unit_3()
{
	
}
Unit_3::~Unit_3()
{

}
#if STACK
void Unit_3::test_function()
{
	stack<int> temp;
	for(int i = 0;i < 10;i++)
	{
		cout << "ÊäÈë" << i << endl;
		temp.push(i);
	}
	for(int i = 0;i < 10;i++)
	{
		cout << temp.top() << endl;
		temp.pop();
	}
}
#else
void Unit_3::test_function()
{
	queue<int> temp;
	for(int i = 0;i < 10;i++)
	{
		cout << "ÊäÈë" << i << endl;
		temp.push(i);
	}
	for(int i = 0;i < 10;i++)
	{
		cout << temp.front() << endl;
		temp.pop();
	}
}
#endif