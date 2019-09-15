#include "Unit5.h"
Unit_5::Unit_5()
{
}
Unit_5::~Unit_5()
{
	
}
void Unit_5::test_function()
{
	HashTable temp = CreateTable(12);
	int test[12] = {24,7,756,36,568,35,5,483,123,48,60,98};
	for(int i = 0;i < 12;i++)
		Insert(temp,test[i]);
	for(int i = 0;i < 12;i++)
		cout << Find(temp,test[i]) << endl;
}