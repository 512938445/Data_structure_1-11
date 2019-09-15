#include "Unit6.h"
#define LGRAPH_TOPOLOGY 1
Unit_6::Unit_6()
{

}
Unit_6::~Unit_6()
{

}
void Visit( Vertex V );
void test();
void Unit_6::test_function()
{
	test();
}
#ifdef ADJ_BFS
	void test()
	{
		MGraph temp;
		Unit_6 wang;
		for(int i = 0;i < MaxVertexNum;i++)
			wang.Visited[i] = false;
		temp = wang.BuildGraph();
		for(int i = 0;i < temp->Nv;i++)
			wang.BFS(temp,i,Visit);
	}
#elif LGRAPH_DFS
	void test()
	{
		LGraph temp;
		Unit_6 wang;
		for(int i = 0;i < MaxVertexNum;i++)
			wang.Visited[i] = false;
		temp = wang.BuildGraph();
		for(int i = 0;i < temp->Nv;i++)
			wang.DFS(temp,i,Visit);
	}
#elif LGRAPH_UNWEIGHTED
	void test()
	{
		LGraph temp;
		Unit_6 wang;
		for(int i = 0;i < MaxVertexNum;i++)
			wang.Visited[i] = false;
		temp = wang.BuildGraph();
		int begin_ = 0;
		int* dist;
		int* path;
		dist = (int*)malloc(temp->Nv*sizeof(int));
		path = (int*)malloc(temp->Nv*sizeof(int));
		for(int i = 0;i < temp->Nv;i++)
		{
			dist[i] = -1;
			path[i] = -1;
		}
		wang.Unweighted(temp,dist,path,begin_);
		for(int i = 0;i < temp->Nv;i++)
			cout << dist[i] << endl;
		cout << endl;
		for(int i = 0;i < temp->Nv;i++)
			cout << path[i] << endl;
	}
#elif ADJ_DIJKSTRA
	void test()
	{
		MGraph temp;
		Unit_6 wang;
		for(int i = 0;i < MaxVertexNum;i++)
			wang.Visited[i] = false;
		temp = wang.BuildGraph();
		int begin_ = 0;
		int* dist;
		int* path;
		dist = (int*)malloc(temp->Nv*sizeof(int));
		path = (int*)malloc(temp->Nv*sizeof(int));
		for(int i = 0;i < temp->Nv;i++)
		{
			dist[i] = INFINITY;
			path[i] = -1;
		}

		wang.Dijkstra(temp,dist,path,begin_);
		for(int i = 0;i < temp->Nv;i++)
			cout << dist[i] << endl;
		cout << endl;
		for(int i = 0;i < temp->Nv;i++)
			cout << path[i] << endl;
	}
#elif ADJ_FLOYD
	void test()
	{
		MGraph temp;
		Unit_6 wang;
		temp = wang.BuildGraph();
		int D[MaxVertexNum][MaxVertexNum];
		int path[MaxVertexNum][MaxVertexNum];

		wang.Floyd(temp,D,path);
		for(int i = 0;i < temp->Nv;i++)
		{
			for(int j = 0;j < temp->Nv;j++)
				cout << D[i][j] << " ";
			cout << endl;
		}
		for(int i = 0;i < temp->Nv;i++)
		{
			for(int j = 0;j < temp->Nv;j++)
				cout << path[i][j] << " ";
			cout << endl;
		}
	}
#elif ADJ_PRIM
	void test()
	{
		Unit_6 wang;
		MGraph temp_in,temp_out;
		temp_in = wang.BuildGraph();
		temp_out = wang.CreateGraph(temp_in->Nv);
		cout << " Prim方法得到最小生成树的最小权值和 " << wang.Prim(temp_in,temp_out) << endl;
		for(int i = 0;i < temp_out->Nv;i++)
		{
			for(int j = 0;j < temp_out->Nv;j++)
				cout << temp_out->G[i][j] << " ";
			cout << endl;
		}
	}
#elif LGRAPH_KRUSKAL
	void test()
	{
		LGraph temp_in,temp_out;
		Unit_6 wang;
		temp_in = wang.BuildGraph();
		temp_out = wang.CreateGraph(temp_in->Nv);
		cout << " Prim方法得到最小生成树的最小权值和 " << wang.Kruskal(temp_in,temp_out) << endl;
	}
#elif LGRAPH_TOPOLOGY
	void test()
	{
		LGraph temp_in;
		Vertex temp_out[MaxVertexNum];
		Unit_6 wang;
		temp_in = wang.BuildGraph();
		cout << wang.TopSort(temp_in,temp_out) << endl;
		for(int i = 0;i < temp_in->Nv;i++)
			cout << temp_out[i] << " " << endl;
	}
#endif