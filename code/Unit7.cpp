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
	wang.MergeSort(A,sizeof(A)/sizeof(int)); // �����������������ķ���
	for(int j = 0;j < sizeof(A)/sizeof(int);j++)
		cout << A[j] << " ";
	cout << endl;
}
void Unit_7::test_function()
{
	test_();
}
void Unit_7::Bubble_Sort(int A[],int N)//�Ѵ��Ԫ�ط�������
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
		if(flag == 0) break;//ȫ���޽���
	}
}
void Unit_7::Insertion_Sort(int A[],int N)
{ /* �������� */
     int P,i,temp;
     for ( P=1; P<N; P++ ) {
         temp = A[P]; /* ȡ��δ���������еĵ�һ��Ԫ��*/
         for ( i=P; i>0 && A[i-1]>temp; i-- )
             A[i] = A[i-1]; /*������������������Ԫ�رȽϲ�����*/
         A[i] = temp; /* �Ž����ʵ�λ�� */
     }
}
void Unit_7::Shell_Sort(int A[],int N)//������ȥ����ԣ�Ҫ��ÿ�μ��Ԫ�ػ��ʣ�������ܴ��ʺ���ϣ������
{
	/* ϣ������ - ��Sedgewick�������� */
     int Si, D, P, i;
     ElementType Tmp;
     /* ����ֻ�г�һС�������� */
     int Sedgewick[] = {929, 505, 209, 109, 41, 19, 5, 1, 0};
      
     for ( Si=0; Sedgewick[Si]>=N; Si++ ) 
         ; /* ��ʼ������Sedgewick[Si]���ܳ����������г��� */
 
     for ( D=Sedgewick[Si]; D>0; D=Sedgewick[++Si] )
         for ( P=D; P<N; P++ ) { /* ��������*/
             Tmp = A[P];
             for ( i=P; i>=D && A[i-D]>Tmp; i-=D )
                 A[i] = A[i-D];
             A[i] = Tmp;
         }
}
void Unit_7::HeapSort(int A[],int N)
{ /* ������ */
	int i;
       
	for ( i=N/2-1; i>=0; i-- )/* �������� */
		PercDown( A, i, N );
      
	for ( i=N-1; i>N - 1 - 3; i-- ) {//���������ʺϽ��ֻѡǰ����Ԫ�ص�����
		/* ɾ�����Ѷ� */
		Swap( &A[0], &A[i] ); /* ������7.1 */
		PercDown( A, 0, i );
	}
}
void Unit_7::MergeSort( ElementType A[], int N )
{ /* �鲢���� */
     ElementType *TmpA;
     TmpA = (ElementType *)malloc(N*sizeof(ElementType));
      
     if ( TmpA != NULL ) {
          Msort( A, TmpA, 0, N-1 );
          free( TmpA );
     }
     else printf( "�ռ䲻��" );
}