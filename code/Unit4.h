#include "include.h" 
#define heap 1
using namespace std;
#define LH +1
#define EH 0
#define RH -1
typedef int ElementType;

typedef struct HNode *Heap; /* 堆的类型定义 */
struct HNode {
    ElementType *Data; /* 存储元素的数组 */
    int Size;          /* 堆中当前元素个数 */
    int Capacity;      /* 堆的最大容量 */
};
typedef Heap MaxHeap; /* 最大堆 */
typedef Heap MinHeap; /* 最小堆 */
 
#define MAXDATA 1000  /* 该值应根据具体情况定义为大于堆中所有可能元素的值 */


template<class T>
struct binary_tree_node
{
	T _data;
	int bf;
	binary_tree_node<T>* _left;
	binary_tree_node<T>* _right;

	binary_tree_node(const T& x)
		:_data(x),_left(NULL),_right(NULL),bf(0){}
};
template<class T> 
class binary_tree
{
	typedef binary_tree_node<T> node;
public:

	binary_tree(T* a,size_t n,const T& invalid)
	{
		size_t index = 0;
		_root = _create_tree(a,n,invalid,index);
	}
	node *copy_tree(node *root)
	{
		if(root == NULL)
			return NULL;
		node* new_root = new node(root->_data);
		new_root->_left = copy_tree(root->_left);
		new_root->_right = copy_tree(root->_right);

		return new_root;
	}
	//二叉搜索树，插入一个元素
	bool Insert(T x)
	{
		return _Insert(x,&_root);
	}
	bool Remove(T x)
	{
		return _Remove(x,&_root);
	}
	bool Search(T x)
	{
		return (_Search(x,_root) != NULL)?true:false;
	}
	bool _Insert(const T e1,node** ptr)
	{
		if(*ptr == NULL)
		{
			*ptr = new binary_tree_node<T>(e1);
			if(*ptr == NULL)
			{
				cout << "Memory allocation failed!" << endl;
				return false;
			}
			return true;
		}
		if(e1 < (*ptr)->_data)
		{
			_Insert(e1,&((*ptr)->_left));
		}
		else if(e1 > (*ptr)->_data)
		{
			_Insert(e1,&((*ptr)->_right));
		}
		else
		{
			return false;
		}
	}
	bool _Remove(T x,node** ptr)
	{
		node* temp;
		if(*ptr != NULL)
		{
			if(x < (*ptr)->_data)
			{
				return _Remove(x,&((*ptr)->_left));
			}
			else if(x > (*ptr)->_data)
				return _Remove(x,&((*ptr)->_right));
			else if((*ptr)->_left != NULL && (*ptr)->_right != NULL)
			{
				temp = (*ptr)->_right;    //在右子树中搜索中序下的第一个结点
				while (temp->_left != NULL)
				{
					temp = temp->_left;
				}
				//用右子树中序下的第一个结点的值填充要删除的结点
				(*ptr)->_data = temp->_data;
				//然后再新填充值ptr的右子树中删除temp的data值
				return _Remove((*ptr)->_data, &((*ptr)->_right));
			}
			else//只有一个子节点
			{
				temp = *ptr;
				if((*ptr)->_left == NULL)
					*ptr = (*ptr)->_right;
				else
					*ptr = (*ptr)->_left;
				delete temp;
				temp = NULL;
				return true;
			}
		}
		else 
			return false;
	}
	node* _Search(T x,node *ptr)
	{
		if(ptr == NULL)
			return NULL;
		else if(x < ptr->_data)
			return _Search(x,ptr->_left);
		else if(x > ptr->_data)
			return _Search(x,ptr->_right);
		else
			return ptr;
	}
	/*****以上为二叉搜索树*****/
	binary_tree(const binary_tree<T>& t)
	{
		_root = copy_tree(t._root);
	}
	binary_tree(T a):_root(NULL)
	{
		_Insert(a, &_root);
	}
	binary_tree():_root(NULL)
	{
		;
	}
	binary_tree<T>& operator =(binary_tree<T> t)
	{
		swap(_root,t._root);
		return *this;
	}
	~binary_tree()
	{
		destory(_root);
		_root = NULL;
	}
	void destory(node* root)
	{
		if(root == NULL)
			return;
		destory(root->_left);
		destory(root->_right);

		delete root;
	}
	//创建二叉树
	node *_create_tree(T *a,size_t n,const T& invalid,size_t& index)
	{
		node *root = NULL;
		if(a[index]!=invalid)
		{
			root = new node(a[index]);
			root->_left = _create_tree(a,n,invalid,++index);
			root->_right = _create_tree(a,n,invalid,++index);
		}
		return root;
	}
	//前序遍历
	void prev_order()
	{
		_prev_order(_root);
		cout << endl;
	}
	void _prev_order(node *root)
	{
		if(root == NULL)
			return;
		cout << root->_data << " ";
		_prev_order(root->_left);
		_prev_order(root->_right);
	}
	//非递归的前序遍历
	void prev_order_no_r()
	{
		node* cur = _root;
		stack<node*> s;
		while(cur||!s.empty())
		{
			while(cur)
			{
				cout << cur->_data << " ";
				s.push(cur);
				cur = cur->_left;
			}
			node* top = s.top();
			s.pop();
			cur = top->_right;
		}
		cout << endl;
	}
	//中序遍历
	void in_order()
	{
		_in_order(_root);
		cout << endl;
	}
	void _in_order(node* root)
	{
		//left->root->right
		if(root != NULL)
			return;
		_in_order(root->_left);
		cout << root->_data << " ";
		_in_order(root->_right);
	}
	//非递归的中序遍历
	void in_order_no_r()
	{
		node *cur = _root;
		stack<node*> s;
		while(cur||!s.empty())
		{
			while(cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			node* top = s.top();
			cout << top->_data << " ";
			s.pop();
			cur = top->_right;
		}
		cout << endl;
	}
	//非递归的后序遍历 看的不是太懂
	void post_order_no_r()
	{
		node* cur = _root;
		node* prev = NULL;
		stack<node*> s;
		while(cur || !s.empty())
		{
			while(cur)
			{
				s.push(cur);
				cur = cur->_left;
			}
			node *top = s.top();
			if(top->_right == NULL || top->_right == prev)
			{
				cout << top->_data << " ";
				s.pop();
				prev = top;
			} 
			else
			{
				cur = top->_right;
			}
		}
		cout << endl;
	}
	//计算节点个数
	int size()
	{
		size_t size = 0;
		_size(_root,size);
		return size;
	}
	void _size(node *root,size_t&size)
	{
		if(root == NULL) 
			return;
		++size;
		_size(root->_left,size);
		_size(root->_right,size);
	}
	//求叶子节点的个数
	size_t leaf_size()
	{
		return _leaf_size(_root);
	}
	size_t _leaf_size(node *root)
	{
		if(root == NULL) 
			return 0;
		if(root->_left == NULL && root->_right == NULL)
			return 1;
		return _leaf_size(root->_left) + _leaf_size(root->_right);
	}
	//二叉树的高度
	size_t height()
	{
		return _height(_root);
	}
	size_t _height(node *root)
	{
		if(root == NULL)
			return 0;
		size_t left_height = _height(root->_left);
		size_t right_height = _height(root->_right);
		return left_height > right_height ? left_height+1 : right_height+1;
    }
	//求第k层节点个数
	size_t get_k_level(size_t k)
    {
        return _get_k_level(_root, k);
    }
	size_t _get_k_level(node* root, size_t k)
    {
        //空树返回0
        if (root == NULL)return 0;
        //第一层只有一个节点
        if (k == 1)return 1;
        //注意这里为什么是k-1?  如果你需要求第二层的节点个数，则需要用第一层的根节点访问他的左子树和右子树的第一层的个数
        return _get_k_level(root->_left, k - 1) + _get_k_level(root->_right, k - 1);
    }
	void level_order()
    {
        queue<node *>q;
        if (_root)
            q.push(_root);
        while (!q.empty())
        {
            node* front = q.front();
            cout << front->_data << "  ";
            q.pop();
            if (front->_left)
                q.push(front->_left);
            if (front->_right)
                q.push(front->_right);
        }
        cout << endl;
    }
	//判断二叉树是否为完全二叉树
    bool is_complete_tree()
    {
        queue<node*>q;
        if (_root)
            q.push(_root);
        bool flag = true;
        while (!q.empty())
        {
            node* front = q.front();
            q.pop();
            if (front->_left)
            {
                if (flag == false)
                    return false;
                q.push(front->_left);
            }
            else
            {
                flag = false;
            }
            if (front->_right)
            {
                if (flag == false)
                    return false;
                q.push(front->_right);
            }
            else
                flag = false;
        }
        return true;
    }
	//查找一个节点是否在一棵二叉树中
    node* find(const T&x)
    {
        return _find(_root, x);
    }
    node* _find(node*root, const T& x)
    {
        if (root == NULL)return NULL;
        if (root->_data == x)return root;

        node* ret1 = _find(root->_left, x);
        if (ret1)return ret1;

        node* ret2 = _find(root->_data, x);
        if (ret2)return ret2;

        return NULL;
    }
	void R_Roate(node** p)
	{
		node* temp = (*p)->_left;
		(*p)->_left = temp->_right;
		temp->_right = *p;
		*p = temp;
	}
	void L_Roate(node** p)
	{
		node* temp = (*p)->_right;
		(*p)->_right = temp->_left;
		temp->_left = *p;
		*p = temp;
	}
	void LeftBalance(node** p)
	{
		node* temp = (*p)->_left;
		switch(temp->bf)
		{
			case LH:
			{
				(*p)->bf = temp->bf = EH;
				R_Roate(p); 
				break;
			}
			case RH:
			{
				node* t = temp->_right;
				switch(t->bf)
				{
					case LH:{temp->bf = EH; (*p)->bf = RH; break;}
					case EH:{temp->bf = EH; (*p)->bf = EH; break;}
					case RH:{temp->bf = LH; (*p)->bf = EH; break;}
				}
				t->bf = EH;
				L_Roate(&((*p)->_left));
				R_Roate(p);
			}
		}
	}
	void RightBalance(node** p){
		node* temp = (*p)->_right;
		switch(temp->bf){
		case LH:{
					node* t = temp->_left;
					switch(t->bf){
					case LH:{(*p)->bf = EH; temp->bf = RH; break;}
					case EH:{(*p)->bf = EH; temp->bf = EH; break;}
					case RH:{(*p)->bf = LH; temp->bf = EH; break;}
					}
					t->bf = EH;
					R_Roate(&((*p)->_right));
					L_Roate(p);
				}
		case RH:{(*p)->bf = temp->bf = EH; L_Roate(p); break;}
		}
	}
	bool InsertAVL(node* &p, int val, bool& taller){
    if(!p)
	{//插入新结点，树变高
		p = new binary_tree_node<T>(val);
        //p->_data = val; p->bf = EH; p->_left = p->_right = NULL;
        taller = true;
    }
	else{
        if(val==p->_data){taller = false; return false;} //如果val存在于二叉树中， 则插入失败
        if(val<p->_data){ //若果val比当前结点的值小，则把新结点插入到当前结点的左子树中
            if(!InsertAVL(p->_left, val, taller)) return false;
            if(taller){
            switch(p->bf){    //插入新结点后要对当前结点的平衡因子做出相应的修改
            case LH:{LeftBalance(&p); taller=false; break;}
            case EH:{taller = true; p->bf = LH; break;}
            case RH:{taller = false; p->bf = EH; break;}
            }}
        }else{
            if(!InsertAVL(p->_right, val, taller)) return false;
            if(taller){
            switch(p->bf){
            case LH:{p->bf = EH; taller = false; break;}
            case EH:{p->bf = RH; taller = true; break;}
            case RH:{RightBalance(&p); taller = false; break;}
            }}
        }
    }
    return true;
}
	
	/* 最大堆的应用 */
		MaxHeap CreateHeap( int MaxSize)
		{ /* 创建容量为MaxSize的空的最大堆 */
 
			MaxHeap H = (MaxHeap)malloc(sizeof(struct HNode));
			H->Data = (ElementType *)malloc((MaxSize+1)*sizeof(ElementType));
			H->Size = 0;
			H->Capacity = MaxSize;
			H->Data[0] = MAXDATA; /* 定义"哨兵"为大于堆中所有可能元素的值*/
 
			return H;
		}
		bool IsFull( MaxHeap H )
		{
			return (H->Size == H->Capacity);
		}
		bool Insert( MaxHeap H, ElementType X )
		{ /* 将元素X插入最大堆H，其中H->Data[0]已经定义为哨兵 */
			int i;
  
			if ( IsFull(H) ) { 
				printf("最大堆已满");
				return false;
			}
			i = ++H->Size; /* i指向插入后堆中的最后一个元素的位置 */
			for ( ; H->Data[i/2] < X; i/=2 )/* 2/i是父节点 */
				H->Data[i] = H->Data[i/2]; /* 上滤X */
			H->Data[i] = X; /* 将X插入 */
			return true;
		}
		bool IsEmpty(MaxHeap H)
		{
			return (H->Size == 0);
		}
		ElementType DeleteMax( MaxHeap H )
		{ /* 从最大堆H中取出键值为最大的元素，并删除一个结点 */
			int Parent, Child;
			ElementType MaxItem, X;
 
			if ( IsEmpty(H) ) {
				printf("最大堆已为空");
				return ERROR;
			}
 
			MaxItem = H->Data[1]; /* 取出根结点存放的最大值 把要删除的最大值先保存起来*/
			/* 用最大堆中最后一个元素从根结点开始向上过滤下层结点 */
			X = H->Data[H->Size--]; /* 注意当前堆的规模要减小 下面这个for循环的目的就是给X找位置*/
			for( Parent=1; Parent*2<=H->Size; Parent=Child ) {  /* for的判断条件是看看是否有左子树，没有左子树一定没有柚子树 */
				Child = Parent * 2;
				if( (Child!=H->Size) && (H->Data[Child]<H->Data[Child+1]) )
					Child++;  /* Child指向左右子结点的较大者 */
				if( X >= H->Data[Child] ) break; /* 找到了合适位置 */
				else  /* 下滤X */
					H->Data[Parent] = H->Data[Child];
			}
			H->Data[Parent] = X;
 
			return MaxItem;
		}
		/*----------- 建造最大堆 -----------*/
		void PercDown( MaxHeap H, int p )
		{ /* 下滤：将H中以H->Data[p]为根的子堆调整为最大堆 */
			int Parent, Child;
			ElementType X;
 
			X = H->Data[p]; /* 取出根结点存放的值 */
			for( Parent=p; Parent*2<=H->Size; Parent=Child ) {
				Child = Parent * 2;
				if( (Child!=H->Size) && (H->Data[Child]<H->Data[Child+1]) )
					Child++;  /* Child指向左右子结点的较大者 */
				if( X >= H->Data[Child] ) break; /* 找到了合适位置 */
				else  /* 下滤X */
					H->Data[Parent] = H->Data[Child];
			}
			H->Data[Parent] = X;
		}
		void BuildHeap( MaxHeap H )
		{ /* 调整H->Data[]中的元素，使满足最大堆的有序性  */
		  /* 这里假设所有H->Size个元素已经存在H->Data[]中 */
 
			int i;
 
			/* 从最后一个结点的父节点开始，到根结点1 */
			for( i = H->Size/2; i>0; i-- )
				PercDown( H, i );
		}
	/* 最大堆的应用 */
	
	/* 最小堆的应用 */
		MinHeap _CreateHeap( int MaxSize)
		{ /* 创建容量为MaxSize的空的最小堆 */
 
			MinHeap H = (MinHeap)malloc(sizeof(struct HNode));
			H->Data = (ElementType *)malloc((MaxSize+1)*sizeof(ElementType));
			H->Size = 0;
			H->Capacity = MaxSize;
			H->Data[0] = -MAXDATA; /* 定义"哨兵"为小于堆中所有可能元素的值*/
 
			return H;
		}
		bool _IsFull( MinHeap H )
		{
			return (H->Size == H->Capacity);
		}
		bool _Insert( MinHeap H, ElementType X )
		{ /* 将元素X插入最大堆H，其中H->Data[0]已经定义为哨兵 */
			int i;
  
			if ( _IsFull(H) ) { 
				printf("最小堆已满");
				return false;
			}
			i = ++H->Size; /* i指向插入后堆中的最后一个元素的位置 */
			for ( ; H->Data[i/2] > X; i/=2 )/* 2/i是父节点 */
				H->Data[i] = H->Data[i/2]; /* 上滤X */
			H->Data[i] = X; /* 将X插入 */
			return true;
		}
		bool _IsEmpty(MinHeap H)
		{
			return (H->Size == 0);
		}
		ElementType _DeleteMax( MinHeap H )
		{ /* 从最小堆H中取出键值为最小的元素，并删除一个结点 */
			int Parent, Child;
			ElementType MinItem, X;
 
			if ( _IsEmpty(H) ) {
				printf("最小堆已为空");
				return ERROR;
			}
 
			MinItem = H->Data[1]; /* 取出根结点存放的最小值 把要删除的最小值先保存起来*/
			/* 用最小堆中最后一个元素从根结点开始向上过滤下层结点 */
			X = H->Data[H->Size--]; /* 注意当前堆的规模要减小 下面这个for循环的目的就是给X找位置*/
			for( Parent=1; Parent*2<=H->Size; Parent=Child ) {  /* for的判断条件是看看是否有左子树，没有左子树一定没有柚子树 */
				Child = Parent * 2;
				if( (Child!=H->Size) && (H->Data[Child]>H->Data[Child+1]) )
					Child++;  /* Child指向左右子结点的较小者 */
				if( X <= H->Data[Child] ) break; /* 找到了合适位置 */
				else  /* 下滤X */
					H->Data[Parent] = H->Data[Child];
			}
			H->Data[Parent] = X;
 
			return MinItem;
		}
		/*----------- 建造最小堆 -----------*/
		void _PercDown( MinHeap H, int p )
		{ /* 下滤：将H中以H->Data[p]为根的子堆调整为最小堆 */
			int Parent, Child;
			ElementType X;
 
			X = H->Data[p]; /* 取出根结点存放的值 */
			for( Parent=p; Parent*2<=H->Size; Parent=Child ) {
				Child = Parent * 2;
				if( (Child!=H->Size) && (H->Data[Child]>H->Data[Child+1]) )
					Child++;  /* Child指向左右子结点的较小者 */
				if( X <= H->Data[Child] ) break; /* 找到了合适位置 */
				else  /* 下滤X */
					H->Data[Parent] = H->Data[Child];
			}
			H->Data[Parent] = X;
		}
 
		void _BuildHeap( MinHeap H )
		{ /* 调整H->Data[]中的元素，使满足最大堆的有序性  */
		  /* 这里假设所有H->Size个元素已经存在H->Data[]中 */
 
			int i;
 
			/* 从最后一个结点的父节点开始，到根结点1 */
			for( i = H->Size/2; i>0; i-- )
				_PercDown( H, i );
		}

	/* 最小堆的应用 */

	node *_root;	
};
void test_binary_tree();
class Unit_4
{
public:
	Unit_4();
	~Unit_4();
	//二叉树

	int BinarySearch(int *temp,int length,int key);
	void test_function();
};