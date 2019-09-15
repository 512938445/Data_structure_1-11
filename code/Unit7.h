#include "include.h"
using namespace std;
typedef int ElementType;
class Unit_7
{
public:
	Unit_7();
	~Unit_7();
	void test_function();
	void Bubble_Sort(int A[],int N);
	void Insertion_Sort(int A[],int N);
	void Shell_Sort(int A[],int N);
	void Swap( ElementType *a, ElementType *b )
	{
		 ElementType t = *a; *a = *b; *b = t;
	}  
	void PercDown( ElementType A[], int p, int N )
	{ /* �ı����4.24��PercDown( MaxHeap H, int p )    */
	  /* ��N��Ԫ�ص���������A[p]Ϊ�����Ӷѵ���Ϊ���� */
		int Parent, Child;
		ElementType X;
 
		X = A[p]; /* ȡ��������ŵ�ֵ */
		for( Parent=p; (Parent*2+1)<N; Parent=Child ) {
			Child = Parent * 2 + 1;
			if( (Child!=N-1) && (A[Child]<A[Child+1]) )
				Child++;  /* Childָ�������ӽ��Ľϴ��� */
			if( X >= A[Child] ) break; /* �ҵ��˺���λ�� */
			else  /* ����X */
				A[Parent] = A[Child];
		}
		A[Parent] = X;
	}
	void HeapSort( ElementType A[], int N );
	/* �鲢���� - �ݹ�ʵ�� */
	/* L = �����ʼλ��, R = �ұ���ʼλ��, RightEnd = �ұ��յ�λ��*/
	void Merge( ElementType A[], ElementType TmpA[], int L, int R, int RightEnd )
	{ /* �������A[L]~A[R-1]��A[R]~A[RightEnd]�鲢��һ���������� */
		 int LeftEnd, NumElements, Tmp;
		 int i;
      
		 LeftEnd = R - 1; /* ����յ�λ�� */
		 Tmp = L;         /* �������е���ʼλ�� */
		 NumElements = RightEnd - L + 1;
      
		 while( L <= LeftEnd && R <= RightEnd ) {
			 if ( A[L] <= A[R] )
				 TmpA[Tmp++] = A[L++]; /* �����Ԫ�ظ��Ƶ�TmpA */
			 else
				 TmpA[Tmp++] = A[R++]; /* ���ұ�Ԫ�ظ��Ƶ�TmpA */
		 }
 
		 while( L <= LeftEnd )
			 TmpA[Tmp++] = A[L++]; /* ֱ�Ӹ������ʣ�µ� */
		 while( R <= RightEnd )
			 TmpA[Tmp++] = A[R++]; /* ֱ�Ӹ����ұ�ʣ�µ� */
          
		 for( i = 0; i < NumElements; i++ )
			 A[RightEnd] = TmpA[RightEnd--]; /* �������TmpA[]���ƻ�A[] */
	}
	void Msort( ElementType A[], ElementType TmpA[], int L, int RightEnd )
	{ /* ���ĵݹ������� */ 
		 int Center;
      
		 if ( L < RightEnd ) {
			  Center = (L+RightEnd) / 2;
			  Msort( A, TmpA, L, Center );              /* �ݹ������ */ 
			  Msort( A, TmpA, Center+1, RightEnd );     /* �ݹ����ұ� */  
			  Merge( A, TmpA, L, Center+1, RightEnd );  /* �ϲ������������� */ 
		 }
	}
	void MergeSort( ElementType A[], int N );

	/* �鲢���� - ѭ��ʵ�� */
	/* ����Merge�����ڵݹ�汾�и��� */
	/* length = ��ǰ�������еĳ���*/
	void Merge_pass( ElementType A[], ElementType TmpA[], int N, int length )
	{ /* �����鲢������������ */
		 int i, j;
       
		 for ( i=0; i <= N-2*length; i += 2*length )
			 Merge( A, TmpA, i, i+length, i+2*length-1 );
		 if ( i+length < N ) /* �鲢���2������*/
			 Merge( A, TmpA, i, i+length, N-1);
		 else /* ���ֻʣ1������*/
			 for ( j = i; j < N; j++ ) TmpA[j] = A[j];
	}
	void Merge_Sort( ElementType A[], int N )
	{ 
		 int length; 
		 ElementType *TmpA;
      
		 length = 1; /* ��ʼ�������г���*/
		 TmpA = (ElementType*)malloc( N * sizeof( ElementType ) );
		 if ( TmpA != NULL ) {
			  while( length < N ) {
				  Merge_pass( A, TmpA, N, length );//���ƿռ临�Ӷȣ�TmpA->A  A->TmpA TmpA->A  A->TempA
				  length *= 2;
				  Merge_pass( TmpA, A, N, length );
				  length *= 2;
			  }
			  free( TmpA );
		 }
		 else printf( "�ռ䲻��" );
	}
};