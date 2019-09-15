#include "Unit7.h"
Unit_7::Unit_7()
{

}
Unit_7::~Unit_7()
{

}
void test_()
{
	Unit_7 wang;
	int A[] = {9,8,7,6,4,3,2,1};
	for(int j = 0;j < sizeof(A)/sizeof(int);j++)
		cout << A[j] << " ";
	cout << endl;
	wang.MergeSort(A,sizeof(A)/sizeof(int)); // 在这里更改所用排序的方法
	for(int j = 0;j < sizeof(A)/sizeof(int);j++)
		cout << A[j] << " ";
	cout << endl;
}
void Unit_7::test_function()
{
	test_();
}
void Unit_7::Bubble_Sort(int A[],int N)//把大的元素放在下面
{
	for(int i = N-1;i >=0;i--)
	{
		int flag = 0;
		for(int j = 0;j < i;j++)
		{
			if(A[j] > A[j+1])
			{
				swap(A[j],A[j+1]);
				flag = 1;
			}
		}
		if(flag == 0) break;//全程无交换
	}
}
void Unit_7::Insertion_Sort(int A[],int N)
{ /* 插入排序 */
     int P,i,temp;
     for ( P=1; P<N; P++ ) {
         temp = A[P]; /* 取出未排序序列中的第一个元素*/
         for ( i=P; i>0 && A[i-1]>temp; i-- )
             A[i] = A[i-1]; /*依次与已排序序列中元素比较并右移*/
         A[i] = temp; /* 放进合适的位置 */
     }
}
void Unit_7::Shell_Sort(int A[],int N)//快速消去逆序对，要求每次间隔元素互质，如果量很大，适合用希尔排序
{
	/* 希尔排序 - 用Sedgewick增量序列 */
     int Si, D, P, i;
     ElementType Tmp;
     /* 这里只列出一小部分增量 */
     int Sedgewick[] = {929, 505, 209, 109, 41, 19, 5, 1, 0};
      
     for ( Si=0; Sedgewick[Si]>=N; Si++ ) 
         ; /* 初始的增量Sedgewick[Si]不能超过待排序列长度 */
 
     for ( D=Sedgewick[Si]; D>0; D=Sedgewick[++Si] )
         for ( P=D; P<N; P++ ) { /* 插入排序*/
             Tmp = A[P];
             for ( i=P; i>=D && A[i-D]>Tmp; i-=D )
                 A[i] = A[i-D];
             A[i] = Tmp;
         }
}
void Unit_7::HeapSort(int A[],int N)
{ /* 堆排序 */
	int i;
       
	for ( i=N/2-1; i>=0; i-- )/* 建立最大堆 */
		PercDown( A, i, N );
      
	for ( i=N-1; i>N - 1 - 3; i-- ) {//堆排序最适合解决只选前几个元素的问题
		/* 删除最大堆顶 */
		Swap( &A[0], &A[i] ); /* 见代码7.1 */
		PercDown( A, 0, i );
	}
}
void Unit_7::MergeSort( ElementType A[], int N )
{ /* 归并排序 */
     ElementType *TmpA;
     TmpA = (ElementType *)malloc(N*sizeof(ElementType));
      
     if ( TmpA != NULL ) {
          Msort( A, TmpA, 0, N-1 );
          free( TmpA );
     }
     else printf( "空间不足" );
}