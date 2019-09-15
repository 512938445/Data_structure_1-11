#include "Unit4.h"
#define HEAP 1

Unit_4::Unit_4()
{
}
Unit_4::~Unit_4()
{}
void test_binary_search_tree();
void test_balance_tree();
void test_heap();
void Unit_4::test_function()
{
#if BINARY
	int temp[10] = {1,3,4,5,6,7,9,10,23,43};
	cout << BinarySearch(temp,sizeof(temp)/sizeof(temp[0]),43) << endl;
#elif BINARY_TREE
	test_binary_tree();
#elif BINARY_SEARCH_TREE
	test_binary_search_tree();
#elif BALANCE_TREE
	test_balance_tree();
#elif HEAP
	test_heap();
#endif
}
void test_heap()
{
	bool MINHEAP = true;
	//MINHEAP = false;
	if(MINHEAP)
	{
		binary_tree<int> wang;
		MinHeap temp;
		temp = wang._CreateHeap(10);
		for(int i = 9;i > -1;i--)
			temp->Data[10 - i] = i * 2;
		for(int i = 1;i <= 10;i++)
			cout << temp->Data[i] << endl;
		temp->Size = 10;
		wang._BuildHeap(temp);
		for(int i = 1;i <= 10;i++)
			cout << temp->Data[i] << endl;
	}
	else
	{
		binary_tree<int> wang;
		MaxHeap temp;
		temp = wang.CreateHeap(10);
		for(int i = 1;i <= 10;i++)
			temp->Data[i] = i * 2;
		for(int i = 1;i <= 10;i++)
			cout << temp->Data[i] << endl;
		temp->Size = 10;
		wang.BuildHeap(temp);
		for(int i = 1;i <= 10;i++)
			cout << temp->Data[i] << endl;
	}
}

void test_balance_tree()
{
	int f[7] = {6,5,3,1,2,4,7};
	bool taller;
	binary_tree<int> t;
	for(int i=0; i<7; i++) 
	{
		t.InsertAVL(t._root, f[i], taller);
	}
	t.in_order_no_r();	
}
void test_binary_search_tree()
{
	int array_temp[] = { 1, 2, 3, 40, 5, 6};
	binary_tree<int> t(4);
	t.prev_order();
	cout << endl;
	cout << t.Search(4) << endl;
	for(int i = 0;i < sizeof(array_temp)/sizeof(int);i++)
		cout << t.Insert(array_temp[i]) << endl;
	t.prev_order_no_r();
	cout << endl;
	cout << t.Remove(40) << endl;
	cout << t.Remove(5) << endl;
	t.prev_order_no_r();
	cout << endl;
	cout << t.height() << endl;
}
void test_binary_tree()
{
	int array[] = { 1, 2, 3, '#', '#', 4, 40, '#', '#', '#', 5, 6, '#', '#', '#' };
	binary_tree<int> t(array, sizeof(array) / sizeof(int), '#');
	t.prev_order();
	t.prev_order_no_r();
	t.in_order();
	t.in_order_no_r();
	t.post_order_no_r();
	t.level_order();

	cout << "size:" << t.size() << endl;
	cout << "leaf_size:" << t.leaf_size() << endl;
	cout << "height:" << t.height() << endl;
	cout << "is_complete_tree:" << t.is_complete_tree() << endl;
	cout << "k_level_size:" << t.get_k_level(4) << endl;

	binary_tree<int> t1(t);
	t1.prev_order_no_r();
}
int Unit_4::BinarySearch(int *temp,int length,int key)
{
	int mid,left,right;
	left = 0;
	right = length - 1;
	mid = left + (right - left) / 2;
	while(left <= right)
	{
		mid = left + (right - left) / 2;
		if(key < *(temp + mid)) right = mid - 1;
		else if (key > *(temp + mid)) left = mid + 1;
		else return mid;
	}
	return -1;
}