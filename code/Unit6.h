#include "include.h"
using namespace std;
/* ͼ���ڽӾ����ʾ�� */
#define MaxVertexNum 100    /* ��󶥵�����Ϊ100 */
#define MaxSize_Q 100
#define INFINITY 65535        /* ����Ϊ˫�ֽ��޷������������ֵ65535*/
#define ADJ_MATRIX 0
typedef int Vertex;         /* �ö����±��ʾ����,Ϊ���� */
typedef int WeightType;        /* �ߵ�Ȩֵ��Ϊ���� */
typedef char DataType;        /* ����洢������������Ϊ�ַ��� */
typedef int ElementType;



/* �ߵĶ��� */
typedef struct ENode *PtrToENode;
struct ENode{
    Vertex V1, V2;      /* �����<V1, V2> */
    WeightType Weight;  /* Ȩ�� */
};
typedef PtrToENode Edge;

#if ADJ_MATRIX
/* ͼ���Ķ��� */
typedef struct GNode *PtrToGNode;
struct GNode{
    int Nv;  /* ������ */
    int Ne;  /* ����   */
    WeightType G[MaxVertexNum][MaxVertexNum]; /* �ڽӾ��� */
    DataType Data[MaxVertexNum];      /* �涥������� */
    /* ע�⣺�ܶ�����£����������ݣ���ʱData[]���Բ��ó��� */
};
typedef PtrToGNode MGraph; /* ���ڽӾ���洢��ͼ���� */
#else
/* �ڽӵ�Ķ��� */
typedef struct AdjVNode *PtrToAdjVNode; 
struct AdjVNode{
    Vertex AdjV;        /* �ڽӵ��±� */
    WeightType Weight;  /* ��Ȩ�� */
    PtrToAdjVNode Next;    /* ָ����һ���ڽӵ��ָ�� */
};
 
/* �����ͷ���Ķ��� */
typedef struct Vnode{
    PtrToAdjVNode FirstEdge;/* �߱�ͷָ�� */
    DataType Data;            /* �涥������� */
    /* ע�⣺�ܶ�����£����������ݣ���ʱData���Բ��ó��� */
} AdjList[MaxVertexNum];    /* AdjList���ڽӱ����� */
 
/* ͼ���Ķ��� */
typedef struct GNode *PtrToGNode;
struct GNode{  
    int Nv;     /* ������ */
    int Ne;     /* ����   */
    AdjList G;  /* �ڽӱ� */
};
typedef PtrToGNode LGraph; /* ���ڽӱ�ʽ�洢��ͼ���� */


#endif

class Unit_6
{
public:
	Unit_6();
	~Unit_6();
	void test_function();
	bool Visited[MaxVertexNum];

	
	/* ���� */
	typedef int Position;
	struct _QNode {
		ElementType *Data;     /* �洢Ԫ�ص����� */
		Position Front, Rear;  /* ���е�ͷ��βָ�� */
		int MaxSize;           /* ����������� */
	};
	typedef struct _QNode *_Queue;
	_Queue _CreateQueue( int MaxSize )
	{
		_Queue Q = (_Queue)malloc(sizeof(struct _QNode));
		Q->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
		Q->Front = Q->Rear = 0;
		Q->MaxSize = MaxSize;
		return Q;
	}
	bool _IsFull( _Queue Q )
	{
		return ((Q->Rear+1)%Q->MaxSize == Q->Front);
	}
	bool _AddQ( _Queue Q, ElementType X )
	{
		if ( _IsFull(Q) ) {
			printf("������");
			return false;
		}
		else {
			Q->Rear = (Q->Rear+1)%Q->MaxSize;
			Q->Data[Q->Rear] = X;
			return true;
		}
	}
	bool _IsEmpty( _Queue Q )
	{
		return (Q->Front == Q->Rear);
	}
	ElementType _DeleteQ( _Queue Q )
	{
		if ( _IsEmpty(Q) ) { 
			printf("���п�");
			return ERROR;
		}
		else  {
			Q->Front =(Q->Front+1)%Q->MaxSize;
			return  Q->Data[Q->Front];
		}
	}
	/* ���� */

#if ADJ_MATRIX
	MGraph CreateGraph( int VertexNum )
	{ /* ��ʼ��һ����VertexNum�����㵫û�бߵ�ͼ */
		Vertex V, W;
		MGraph Graph;
     
		Graph = (MGraph)malloc(sizeof(struct GNode)); /* ����ͼ */
		Graph->Nv = VertexNum;
		Graph->Ne = 0;
		/* ��ʼ���ڽӾ��� */
		/* ע�⣺����Ĭ�϶����Ŵ�0��ʼ����(Graph->Nv - 1) */
		for (V=0; V<Graph->Nv; V++)
			for (W=0; W<Graph->Nv; W++)  
				Graph->G[V][W] = INFINITY;
             
		return Graph; 
	}
	void InsertEdge( MGraph Graph, Edge E )
	{
		 /* ����� <V1, V2> */
		 Graph->G[E->V1][E->V2] = E->Weight;    
		 /* ��������ͼ����Ҫ�����<V2, V1> */
		 Graph->G[E->V2][E->V1] = E->Weight;
	}
	MGraph BuildGraph()
	{
		MGraph Graph;
		Edge E;
		Vertex V;
		int Nv, i;
		cout << "���붥�����" << endl;
		scanf("%d", &Nv);   /* ���붥����� */
		Graph = CreateGraph(Nv); /* ��ʼ����Nv�����㵫û�бߵ�ͼ */ 
		
		cout << "�������" << endl;
		scanf("%d", &(Graph->Ne));   /* ������� */
		if ( Graph->Ne != 0 ) { /* ����б� */ 
			E = (Edge)malloc(sizeof(struct ENode)); /* �����߽�� */ 
			/* ����ߣ���ʽΪ"��� �յ� Ȩ��"�������ڽӾ��� */
			for (i=0; i<Graph->Ne; i++) {
				cout << "����ߣ���ʽΪ ��� �յ� Ȩ��" << endl;
				scanf("%d %d %d", &E->V1, &E->V2, &E->Weight); 
				/* ע�⣺���Ȩ�ز������ͣ�Weight�Ķ����ʽҪ�� */
				InsertEdge( Graph, E );
			}
		} 
 
		/* ������������ݵĻ����������� */
		/*cout << "��������" << endl;
		for (V=0; V<Graph->Nv; V++) 
			scanf(" %c", &(Graph->Data[V]));*/
 
		return Graph;
	}
	/* �ڽӾ���洢��ͼ - BFS */
 
	/* IsEdge(Graph, V, W)���<V, W>�Ƿ�ͼGraph�е�һ���ߣ���W�Ƿ�V���ڽӵ㡣  */
	/* �˺�������ͼ�Ĳ�ͬ����Ҫ����ͬ��ʵ�֣��ؼ�ȡ���ڶԲ����ڵıߵı�ʾ������*/
	/* �������Ȩͼ, ��������ڵı߱���ʼ��ΪINFINITY, ����ʵ������:         */
	bool IsEdge( MGraph Graph, Vertex V, Vertex W )
	{
		return Graph->G[V][W]<INFINITY ? true : false;
	}
 
	/* Visited[]Ϊȫ�ֱ������Ѿ���ʼ��Ϊfalse */
	void BFS ( MGraph Graph, Vertex S, void (*Visit)(Vertex) )
	{   /* ��SΪ��������ڽӾ���洢��ͼGraph����BFS���� */
		_Queue Q;     
		Vertex V, W;
 
		Q = _CreateQueue( MaxSize_Q ); /* �����ն���, MaxSizeΪ�ⲿ����ĳ��� */
		/* ���ʶ���S���˴��ɸ��ݾ��������Ҫ��д */
		if(this->Visited[S])
			return;
		Visit( S );
		this->Visited[S] = true; /* ���S�ѷ��� */
		_AddQ(Q, S); /* S����� */
     
		while ( !_IsEmpty(Q) ) {
			V = _DeleteQ(Q);  /* ����V */
			for( W=0; W<Graph->Nv; W++ ) /* ��ͼ�е�ÿ������W */
				/* ��W��V���ڽӵ㲢��δ���ʹ� */
				if ( !this->Visited[W] && IsEdge(Graph, V, W) ) {
					/* ���ʶ���W */
					Visit( W );
					this->Visited[W] = true; /* ���W�ѷ��� */
					_AddQ(Q, W); /* W����� */
				}
		} /* while����*/
	}

	/* �ڽӾ���洢 - ��Ȩͼ�ĵ�Դ���·�㷨 */
	Vertex FindMinDist( MGraph Graph, int dist[], int collected[] )
	{ /* ����δ����¼������dist��С�� */
		Vertex MinV, V;
		int MinDist = INFINITY;
 
		for (V=0; V<Graph->Nv; V++) {
			if ( collected[V]==false && dist[V]<MinDist) {
				/* ��Vδ����¼����dist[V]��С */
				MinDist = dist[V]; /* ������С���� */
				MinV = V; /* ���¶�Ӧ���� */
			}
		}
		if (MinDist < INFINITY) /* ���ҵ���Сdist */
			return MinV; /* ���ض�Ӧ�Ķ����±� */
		else return ERROR;  /* �������Ķ��㲻���ڣ����ش����� */
	}
	bool Dijkstra( MGraph Graph, int dist[], int path[], Vertex S )
	{
		int collected[MaxVertexNum];
		Vertex V, W;
 
		/* ��ʼ�����˴�Ĭ���ڽӾ����в����ڵı���INFINITY��ʾ */
		for ( V=0; V<Graph->Nv; V++ ) {
			dist[V] = Graph->G[S][V];
			if ( dist[V]<INFINITY )
				path[V] = S;
			else
				path[V] = -1;
			collected[V] = false;
		}
		/* �Ƚ�������뼯�� */
		dist[S] = 0;
		collected[S] = true;
 
		while (1) {
			/* V = δ����¼������dist��С�� */
			V = FindMinDist( Graph, dist, collected );
			if ( V == ERROR ) /* ��������V������ */
				break;      /* �㷨���� */
			collected[V] = true;  /* ��¼V */
			for( W = 0; W < Graph->Nv; W++ ) /* ��ͼ�е�ÿ������W */
				/* ��W��V���ڽӵ㲢��δ����¼ */
				if ( collected[W]==false && Graph->G[V][W]<INFINITY ) {
					if ( Graph->G[V][W]<0 ) /* ���и��� */
						return false; /* ������ȷ��������ش����� */
					/* ����¼Vʹ��dist[W]��С */
					if ( dist[V]+Graph->G[V][W] < dist[W] ) {
						dist[W] = dist[V]+Graph->G[V][W]; /* ����dist[W] */
						path[W] = V; /* ����S��W��·�� */
					}
				}
		} /* while����*/
		return true; /* �㷨ִ����ϣ�������ȷ��� */
	}
	/* �ڽӾ���洢 - ��Դ���·�㷨 */
	bool Floyd( MGraph Graph, WeightType D[][MaxVertexNum], Vertex path[][MaxVertexNum] )
	{
		Vertex i, j, k;
 
		/* ��ʼ�� */
		for ( i=0; i<Graph->Nv; i++ )
			for( j=0; j<Graph->Nv; j++ ) {
				D[i][j] = Graph->G[i][j];
				path[i][j] = -1;
			}
 
		for( k=0; k<Graph->Nv; k++ )
			for( i=0; i<Graph->Nv; i++ )
				for( j=0; j<Graph->Nv; j++ )
					if( D[i][k] + D[k][j] < D[i][j] ) {
						D[i][j] = D[i][k] + D[k][j];
						if ( i==j && D[i][j]<0 ) /* �����ָ�ֵȦ */
							return false; /* ������ȷ��������ش����� */
						path[i][j] = k;
					}
		return true; /* �㷨ִ����ϣ�������ȷ��� */
	}
	/* �ڽӾ���洢 - Prim��С�������㷨 */
	Vertex FindMinDist( MGraph Graph, WeightType dist[] )
	{ /* ����δ����¼������dist��С�� */
		Vertex MinV, V;
		WeightType MinDist = INFINITY;
 
		for (V=0; V<Graph->Nv; V++) {
			if ( dist[V]!=0 && dist[V]<MinDist) {
				/* ��Vδ����¼����dist[V]��С */
				MinDist = dist[V]; /* ������С���� */
				MinV = V; /* ���¶�Ӧ���� */
			}
		}
		if (MinDist < INFINITY) /* ���ҵ���Сdist */
			return MinV; /* ���ض�Ӧ�Ķ����±� */
		else return -1;  /* �������Ķ��㲻���ڣ�����-1��Ϊ��� */
	}
	int Prim( MGraph Graph, MGraph MST )
	{ /* ����С����������Ϊ�ڽӾ���洢��ͼMST��������СȨ�غ� */
		WeightType dist[MaxVertexNum], TotalWeight;
		Vertex parent[MaxVertexNum], V, W;
		int VCount;
		Edge E;

		/* ��ʼ����Ĭ�ϳ�ʼ���±���0 */
		   for (V=0; V<Graph->Nv; V++) {
			/* ���������V��Wû��ֱ�ӵıߣ���Graph->G[V][W]����ΪINFINITY */
			   dist[V] = Graph->G[0][V];
			   parent[V] = 0; /* ���Ҷ������ж���ĸ���㶼�ǳ�ʼ��0 */ 
		}
		TotalWeight = 0; /* ��ʼ��Ȩ�غ�     */
		VCount = 0;      /* ��ʼ����¼�Ķ����� */
		/* �����������ж��㵫û�бߵ�ͼ��ע�����ڽӾ���汾 */
		
		E = (Edge)malloc( sizeof(struct ENode) ); /* �����յı߽�� */
            
		/* ����ʼ��0��¼��MST */
		dist[0] = 0;
		VCount ++;
		parent[0] = -1; /* ��ǰ������0 */
 
		while (1) {
			V = FindMinDist( Graph, dist );
			/* V = δ����¼������dist��С�� */
			if ( V==-1 ) /* ��������V������ */
				break;   /* �㷨���� */
             

			/* ��V����Ӧ�ı�<parent[V], V>��¼��MST */
			E->V1 = parent[V];
			E->V2 = V;
			E->Weight = dist[V];
			InsertEdge( MST, E );
			TotalWeight += dist[V];
			dist[V] = 0;//V�����뵽MST�У������ľ������0
			VCount++;
         
			for( W=0; W<Graph->Nv; W++ ) /* ��ͼ�е�ÿ������W */
				if ( dist[W]!=0 && Graph->G[V][W]<INFINITY ) {//dist[W]!=0 ��仰������ �������ǻ�·�������
				/* ��W��V���ڽӵ㲢��δ����¼ */
					if ( Graph->G[V][W] < dist[W] ) {
					/* ����¼Vʹ��dist[W]��С */
						dist[W] = Graph->G[V][W]; /* ����dist[W] */
						parent[W] = V; /* ������ */
					}
				}
		} /* while����*/
		if ( VCount < Graph->Nv ) /* MST���յĶ��㲻��|V|�� */
		   TotalWeight = -1;
		return TotalWeight;   /* �㷨ִ����ϣ�������СȨ�غͻ������ */
	}

#else
	LGraph CreateGraph(int VertexNum )
	{ /* ��ʼ��һ����VertexNum�����㵫û�бߵ�ͼ */
		Vertex V;
		LGraph Graph;
     
		Graph = (LGraph)malloc( sizeof(struct GNode) ); /* ����ͼ */
		Graph->Nv = VertexNum;
		Graph->Ne = 0;
		/* ��ʼ���ڽӱ�ͷָ�� */
		/* ע�⣺����Ĭ�϶����Ŵ�0��ʼ����(Graph->Nv - 1) */
		for (V=0; V<Graph->Nv; V++)
			Graph->G[V].FirstEdge = NULL;
             
		return Graph; 
	}      
	void InsertEdge( LGraph Graph, Edge E )
	{
		PtrToAdjVNode NewNode;
     
		/* ����� <V1, V2> */
		/* ΪV2�����µ��ڽӵ� */
		NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
		NewNode->AdjV = E->V2;
		NewNode->Weight = E->Weight;
		/* ��V2����V1�ı�ͷ */
		NewNode->Next = Graph->G[E->V1].FirstEdge;
		Graph->G[E->V1].FirstEdge = NewNode;
         
		/* ��������ͼ����Ҫ����� <V2, V1> */
		/* ΪV1�����µ��ڽӵ� */
		//NewNode = (PtrToAdjVNode)malloc(sizeof(struct AdjVNode));
		//NewNode->AdjV = E->V1;
		//NewNode->Weight = E->Weight;
		///* ��V1����V2�ı�ͷ */
		//NewNode->Next = Graph->G[E->V2].FirstEdge;
		//Graph->G[E->V2].FirstEdge = NewNode;
	}
	LGraph BuildGraph()
	{
		LGraph Graph;
		Edge E;
		Vertex V;
		int Nv, i;
		cout << "���붥�����" << endl;
		scanf("%d", &Nv);   /* ���붥����� */
		Graph = CreateGraph(Nv); /* ��ʼ����Nv�����㵫û�бߵ�ͼ */ 
		cout << "����ߵĸ���" << endl;
		scanf("%d", &(Graph->Ne));   /* ������� */
		if ( Graph->Ne != 0 ) { /* ����б� */ 
			E = (Edge)malloc( sizeof(struct ENode) ); /* �����߽�� */ 
			/* ����ߣ���ʽΪ"��� �յ� Ȩ��"�������ڽӾ��� */
			for (i=0; i<Graph->Ne; i++) {
				cout << "����ߣ���ʽΪ��� �յ� Ȩ��" << endl;
				scanf("%d %d %d", &E->V1, &E->V2, &E->Weight); 
				/* ע�⣺���Ȩ�ز������ͣ�Weight�Ķ����ʽҪ�� */
				InsertEdge( Graph, E );
			}
		} 
 
		/* ������������ݵĻ����������� */
		/*for (V=0; V<Graph->Nv; V++) 
			scanf(" %c", &(Graph->G[V].Data));*/
 
		return Graph;
	}
	/* �ڽӱ�洢��ͼ - DFS */
	/* Visited[]Ϊȫ�ֱ������Ѿ���ʼ��Ϊfalse */
	void DFS( LGraph Graph, Vertex V, void (*Visit)(Vertex) )
	{   /* ��VΪ��������ڽӱ�洢��ͼGraph����DFS���� */
		PtrToAdjVNode W;
		if(Visited[V])
			return;
		Visit( V ); /* ���ʵ�V������ */
		Visited[V] = true; /* ���V�ѷ��� */
 
		for( W=Graph->G[V].FirstEdge; W; W=W->Next ) /* ��V��ÿ���ڽӵ�W->AdjV */
			if ( !Visited[W->AdjV] )    /* ��W->AdjVδ������ */
				DFS( Graph, W->AdjV, Visit );    /* ��ݹ����֮ */
	}

	/* �ڽӱ�洢 - ��Ȩͼ�ĵ�Դ���·�㷨 */
 
	/* dist[]��path[]ȫ����ʼ��Ϊ-1 */
	void Unweighted ( LGraph Graph, int dist[], int path[], Vertex S )
	{
		_Queue Q;
		Vertex V;
		PtrToAdjVNode W;
     
		Q = _CreateQueue( Graph->Nv ); /* �����ն���, MaxSizeΪ�ⲿ����ĳ��� */
		dist[S] = 0; /* ��ʼ��Դ�� */
		_AddQ (Q, S);
 
		while( !_IsEmpty(Q) ){
			V = _DeleteQ(Q);
			for ( W=Graph->G[V].FirstEdge; W; W=W->Next ) /* ��V��ÿ���ڽӵ�W->AdjV */
				if ( dist[W->AdjV]==-1 ) { /* ��W->AdjVδ�����ʹ� */
					dist[W->AdjV] = dist[V]+1; /* W->AdjV��S�ľ������ */
					path[W->AdjV] = V; /* ��V��¼��S��W->AdjV��·���� */
					_AddQ(Q, W->AdjV);
				}
		} /* while����*/
	}

	/* �ڽӱ�洢 - Kruskal��С�������㷨 */
 
	/*-------------------- ���㲢�鼯���� --------------------*/
	typedef Vertex ElementType; /* Ĭ��Ԫ�ؿ����÷Ǹ�������ʾ */
	typedef Vertex SetName;     /* Ĭ���ø������±���Ϊ�������� */
	typedef ElementType SetType[MaxVertexNum]; /* ���輯��Ԫ���±��0��ʼ */
 
	void InitializeVSet( SetType S, int N )
	{ /* ��ʼ�����鼯 */
		ElementType X;
 
		for ( X=0; X<N; X++ ) S[X] = -1;//S�Ǵ��沢�鼯�������飬X�Ǻ��ӽڵ���±꣬S[X]�Ǹ��ڵ���±�
	}

	void Union( SetType S, SetName Root1, SetName Root2 )//������
	{ /* ����Ĭ��Root1��Root2�ǲ�ͬ���ϵĸ���� */
		/* ��֤С���ϲ���󼯺� */
		if ( S[Root2] < S[Root1] ) { /* �������2�Ƚϴ� */
			S[Root2] += S[Root1];     /* ����1���뼯��2  */
			S[Root1] = Root2;
		}
		else {                         /* �������1�Ƚϴ� */
			S[Root1] += S[Root2];     /* ����2���뼯��1  */
			S[Root2] = Root1;
		}
	}
 
	SetName Find( SetType S, ElementType X )
	{ /* Ĭ�ϼ���Ԫ��ȫ����ʼ��Ϊ-1 */
		if ( S[X] < 0 ) /* �ҵ����ϵĸ� */
			return X;
		else
			return S[X] = Find( S, S[X] ); /* ·��ѹ�� */
	}
	
	bool CheckCycle( SetType VSet, Vertex V1, Vertex V2 )//������
	{ /* �������V1��V2�ı��Ƿ������е���С�������Ӽ��й��ɻ�· */
		Vertex Root1, Root2;
 
		Root1 = Find( VSet, V1 ); /* �õ�V1��������ͨ������ */
		Root2 = Find( VSet, V2 ); /* �õ�V2��������ͨ������ */
 
		if( Root1==Root2 ) /* ��V1��V2�Ѿ���ͨ����ñ߲���Ҫ */
			return false;
		else { /* ����ñ߿��Ա��ռ���ͬʱ��V1��V2����ͬһ��ͨ�� */
			Union( VSet, Root1, Root2 );
			return true;
		}
	}
	/*-------------------- ���鼯������� --------------------*/
 
	/*-------------------- �ߵ���С�Ѷ��� --------------------*/
	void PercDown( Edge ESet, int p, int N )
	{ /* �ı����4.24��PercDown( MaxHeap H, int p )    */
	  /* ��N��Ԫ�صı���������ESet[p]Ϊ�����Ӷѵ���Ϊ����Weight����С�� */
		int Parent, Child;
		struct ENode X;
 
		X = ESet[p]; /* ȡ��������ŵ�ֵ */
		for( Parent=p; (Parent*2+1)<N; Parent=Child ) {
			Child = Parent * 2 + 1;
			if( (Child!=N-1) && (ESet[Child].Weight>ESet[Child+1].Weight) )
				Child++;  /* Childָ�������ӽ��Ľ�С�� */
			if( X.Weight <= ESet[Child].Weight ) break; /* �ҵ��˺���λ�� */
			else  /* ����X */
				ESet[Parent] = ESet[Child];
		}
		ESet[Parent] = X;
	}
 
	void InitializeESet( LGraph Graph, Edge ESet )
	{ /* ��ͼ�ıߴ�������ESet�����ҳ�ʼ��Ϊ��С�� */
		Vertex V;
		PtrToAdjVNode W;
		int ECount;
 
		/* ��ͼ�ıߴ�������ESet */
		ECount = 0;
		for ( V=0; V<Graph->Nv; V++ )
			for ( W=Graph->G[V].FirstEdge; W; W=W->Next )
				if ( V < W->AdjV ) { /* �����ظ�¼������ͼ�ıߣ�ֻ��V1<V2�ı� */
					ESet[ECount].V1 = V;
					ESet[ECount].V2 = W->AdjV;
					ESet[ECount++].Weight = W->Weight;
				}
		/* ��ʼ��Ϊ��С�� */
		for ( ECount=Graph->Ne/2; ECount>=0; ECount-- )
			PercDown( ESet, ECount, Graph->Ne );
	}
 
	int GetEdge( Edge ESet, int CurrentSize )
	{ /* ������ǰ�ѵĴ�СCurrentSize������ǰ��С��λ�õ����������� */

		/* ����С���뵱ǰ�ѵ����һ��λ�õı߽��� */
		//swap( &ESet[0], &ESet[CurrentSize-1]);
		ENode temp;
		temp = ESet[0];
		ESet[0] = ESet[CurrentSize-1];
		ESet[CurrentSize-1] = temp;

		/* ��ʣ�µı߼�����������С�� */
		PercDown( ESet, 0, CurrentSize-1 );
 
		return CurrentSize-1; /* ������С������λ�� */
	}
	/*-------------------- ��С�Ѷ������ --------------------*/
 
	int Kruskal( LGraph Graph, LGraph MST )
	{ /* ����С����������Ϊ�ڽӱ�洢��ͼMST��������СȨ�غ� */
		WeightType TotalWeight;
		int ECount, NextEdge;
		SetType VSet; /* �������� */
		Edge ESet;    /* ������ */
 
		InitializeVSet( VSet, Graph->Nv ); /* ��ʼ�����㲢�鼯 */
		ESet = (Edge)malloc( sizeof(struct ENode)*Graph->Ne );
		InitializeESet( Graph, ESet ); /* ��ʼ���ߵ���С�� */
		/* �����������ж��㵫û�бߵ�ͼ��ע�����ڽӱ�汾 */
		//MST = CreateGraph(Graph->Nv);
		TotalWeight = 0; /* ��ʼ��Ȩ�غ�     */
		ECount = 0;      /* ��ʼ����¼�ı��� */
 
		NextEdge = Graph->Ne; /* ԭʼ�߼��Ĺ�ģ */
		while ( ECount < Graph->Nv-1 ) {  /* ���ռ��ı߲����Թ�����ʱ */
			NextEdge = GetEdge( ESet, NextEdge ); /* �ӱ߼��еõ���С�ߵ�λ�� */
			if (NextEdge < 0) /* �߼��ѿ� */
				break;
			/* ����ñߵļ��벻���ɻ�·�������˽�㲻����ͬһ��ͨ�� */
			if ( CheckCycle( VSet, ESet[NextEdge].V1, ESet[NextEdge].V2 )==true ) {
				/* ���ñ߲���MST */
				InsertEdge( MST, ESet+NextEdge );
				TotalWeight += ESet[NextEdge].Weight; /* �ۼ�Ȩ�� */
				ECount++; /* �������б�����1 */
			}
		}
		if ( ECount < Graph->Nv-1 )
			TotalWeight = -1; /* ���ô����ǣ���ʾ������������ */
 
		return TotalWeight;
	}

	/* �ڽӱ�洢 - ���������㷨 */ 
	bool TopSort( LGraph Graph, Vertex TopOrder[] )
	{ /* ��Graph������������,  TopOrder[]˳��洢�����Ķ����±� */
		int Indegree[MaxVertexNum], cnt;
		Vertex V;
		PtrToAdjVNode W;
		_Queue Q = _CreateQueue( Graph->Nv );
  
		/* ��ʼ��Indegree[] */
		for (V=0; V<Graph->Nv; V++)
			Indegree[V] = 0;
         
		/* ����ͼ���õ�Indegree[] */
		for (V=0; V<Graph->Nv; V++)
			for (W=Graph->G[V].FirstEdge; W; W=W->Next)
				Indegree[W->AdjV]++; /* �������<V, W->AdjV>�ۼ��յ����� */
             
		/* ���������Ϊ0�Ķ������� */
		for (V=0; V<Graph->Nv; V++)
			if ( Indegree[V]==0 )
				_AddQ(Q, V);
             
		/* ��������������� */ 
		cnt = 0; 
		while( !_IsEmpty(Q) ){
			V = _DeleteQ(Q); /* ����һ�����Ϊ0�Ķ��� */
			TopOrder[cnt++] = V; /* ��֮��Ϊ������е���һ��Ԫ�� */
			/* ��V��ÿ���ڽӵ�W->AdjV */
			for ( W=Graph->G[V].FirstEdge; W; W=W->Next )
				if ( --Indegree[W->AdjV] == 0 )/* ��ɾ��Vʹ��W->AdjV���Ϊ0 */
					_AddQ(Q, W->AdjV); /* ��ö������� */ 
		} /* while����*/
     
		if ( cnt != Graph->Nv )
			return false; /* ˵��ͼ���л�·, ���ز��ɹ���־ */ 
		else
			return true;
	}
#endif
};
