#include"Unit1.h"

#define FENZHI 1//SIMPLE NORMAL FENZHI ONLINE
#define	FIND 1//FIND MAX_SUM 测试函数实现的功能

Unit_1::Unit_1(int temp_List[],int N)
{
	this->N = N;
	for(int i = 0;i < N;i++)
		this->List[i] = temp_List[i];
	
}
Unit_1::~Unit_1()
{
	;
}
#ifdef SIMPLE
int Unit_1::MaxSubseqSum()
{
	int i,j,k,ThisSum,MaxSum = 0;
	for(i=0;i<this->N;i++)
		for(j=0;j<this->N;j++)
		{
			ThisSum = 0;
			for(k=i;k<=j;k++)
				ThisSum+=this->List[k];
			if(ThisSum > MaxSum)
				MaxSum = ThisSum;
		}
	return MaxSum;
}
#elif NORMAL
int Unit_1::MaxSubseqSum()
{
	int i,j,ThisSum,MaxSum=0;
	for(i=0;i<this->N;i++)
	{
		ThisSum=0;
		for(j=i;j<this->N;j++)
		{
			ThisSum+=this->List[j];
			if(ThisSum>MaxSum)
				MaxSum = ThisSum;
		}
	}
	return MaxSum;
}
#elif FENZHI
int Max3(int A,int B,int C)
{
	return A > B ? A > C ? A : C : B > C ? B : C;
}
int DivideAndConquer(int List[],int left,int right)
{
	//求List[Left]到List[Right]的最大子列和
	int MaxLeftSum,MaxRightSum,MaxLeftBorderSum,MaxRightBorderSum,LeftBorderSum,RightBorderSum,center,i;
	if(left == right)
		if(List[left]>0)
			return List[left];
		else
			return 0;
	//分的过程
	center = (left+right)/2;
	//递归球的两边子列的最大和
	MaxLeftSum=DivideAndConquer(List,left,center);
	MaxRightSum=DivideAndConquer(List,center+1,right);
	//求分界线的最大子列和
	MaxLeftBorderSum=0;LeftBorderSum=0;
	for(i=center;i>=left;i--)//从中间向左扫描
	{
		LeftBorderSum += List[i];
		if(LeftBorderSum>MaxLeftBorderSum)
			MaxLeftBorderSum = LeftBorderSum;
	}
	MaxRightBorderSum=0;RightBorderSum=0;
	for(i=center+1;i<=right;i++)//从中间向左扫描
	{
		RightBorderSum += List[i];
		if(RightBorderSum>MaxRightBorderSum)
			MaxRightBorderSum = RightBorderSum;
	}
	Max3(MaxLeftSum,MaxRightSum,MaxLeftBorderSum+MaxRightBorderSum);
}
int Unit_1::MaxSubseqSum()
{
	return DivideAndConquer(this->List,0,this->N-1);
}
#elif ONLINE
int Unit_1::MaxSubseqSum(int List[],int N)
{
	int i,ThisSum=0,MaxSum=0;
	for(i=0;i<N;i++)
	{
		ThisSum+=List[i];
		if(ThisSum>MaxSum)
			MaxSum=ThisSum;
		else if(ThisSum < 0)
			ThisSum = 0;
	}
	return MaxSum;
}
#endif
int Unit_1::find_member(int temp_List[],int begin,int end,int object)
{
	if ((begin == end) && (List[begin] != object))
		return -1;
	if (temp_List[(begin+end)/2]>object)
		return find_member(temp_List,begin,(begin+end)/2-1,object);
	else if(temp_List[(begin+end)/2]<object)
		return find_member(temp_List,(begin+end)/2+1,end,object);
	else
		return (begin+end)/2;
}

//测试函数 放这里就行
void Unit_1::test_function()
{
#ifdef MAX_SUM
	int MaxSum;
	MaxSum = MaxSubseqSum();
	assert(MaxSum);
	cout << "The MaxSum of the List is " << MaxSum << endl;
#elif FIND
	int temp,object,i;
	for(i=0;i<this->N;i++)
	{
		object=this->List[i];
		temp = find_member(this->List,0,this->N-1,object);
		if(temp != -1)
			cout << "We find the object "<<object<<" is at the "<< temp + 1<<endl;
		else
			cout<<"We didn't find anything"<<endl;
	}
#endif
}