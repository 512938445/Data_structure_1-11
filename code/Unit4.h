#include "include.h" 
#define heap 1
using namespace std;
#define LH +1
#define EH 0
#define RH -1
typedef int ElementType;

typedef struct HNode *Heap; /* �ѵ����Ͷ��� */
struct HNode {
    ElementType *Data; /* �洢Ԫ�ص����� */
    int Size;          /* ���е�ǰԪ�ظ��� */
    int Capacity;      /* �ѵ�������� */
};
typedef Heap MaxHeap; /* ���� */
typedef Heap MinHeap; /* ��С�� */
 
#define MAXDATA 1000  /* ��ֵӦ���ݾ����������Ϊ���ڶ������п���Ԫ�ص�ֵ */


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
	//����������������һ��Ԫ��
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
				temp = (*ptr)->_right;    //�������������������µĵ�һ�����
				while (temp->_left != NULL)
				{
					temp = temp->_left;
				}
				//�������������µĵ�һ������ֵ���Ҫɾ���Ľ��
				(*ptr)->_data = temp->_data;
				//Ȼ���������ֵptr����������ɾ��temp��dataֵ
				return _Remove((*ptr)->_data, &((*ptr)->_right));
			}
			else//ֻ��һ���ӽڵ�
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
	/*****����Ϊ����������*****/
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
	//����������
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
	//ǰ�����
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
	//�ǵݹ��ǰ�����
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
	//�������
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
	//�ǵݹ���������
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
	//�ǵݹ�ĺ������ ���Ĳ���̫��
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
	//����ڵ����
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
	//��Ҷ�ӽڵ�ĸ���
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
	//�������ĸ߶�
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
	//���k��ڵ����
	size_t get_k_level(size_t k)
    {
        return _get_k_level(_root, k);
    }
	size_t _get_k_level(node* root, size_t k)
    {
        //��������0
        if (root == NULL)return 0;
        //��һ��ֻ��һ���ڵ�
        if (k == 1)return 1;
        //ע������Ϊʲô��k-1?  �������Ҫ��ڶ���Ľڵ����������Ҫ�õ�һ��ĸ��ڵ�����������������������ĵ�һ��ĸ���
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
	//�ж϶������Ƿ�Ϊ��ȫ������
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
	//����һ���ڵ��Ƿ���һ�ö�������
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
	{//�����½�㣬�����
		p = new binary_tree_node<T>(val);
        //p->_data = val; p->bf = EH; p->_left = p->_right = NULL;
        taller = true;
    }
	else{
        if(val==p->_data){taller = false; return false;} //���val�����ڶ������У� �����ʧ��
        if(val<p->_data){ //����val�ȵ�ǰ����ֵС������½����뵽��ǰ������������
            if(!InsertAVL(p->_left, val, taller)) return false;
            if(taller){
            switch(p->bf){    //�����½���Ҫ�Ե�ǰ����ƽ������������Ӧ���޸�
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
	
	/* ���ѵ�Ӧ�� */
		MaxHeap CreateHeap( int MaxSize)
		{ /* ��������ΪMaxSize�Ŀյ����� */
 
			MaxHeap H = (MaxHeap)malloc(sizeof(struct HNode));
			H->Data = (ElementType *)malloc((MaxSize+1)*sizeof(ElementType));
			H->Size = 0;
			H->Capacity = MaxSize;
			H->Data[0] = MAXDATA; /* ����"�ڱ�"Ϊ���ڶ������п���Ԫ�ص�ֵ*/
 
			return H;
		}
		bool IsFull( MaxHeap H )
		{
			return (H->Size == H->Capacity);
		}
		bool Insert( MaxHeap H, ElementType X )
		{ /* ��Ԫ��X��������H������H->Data[0]�Ѿ�����Ϊ�ڱ� */
			int i;
  
			if ( IsFull(H) ) { 
				printf("��������");
				return false;
			}
			i = ++H->Size; /* iָ��������е����һ��Ԫ�ص�λ�� */
			for ( ; H->Data[i/2] < X; i/=2 )/* 2/i�Ǹ��ڵ� */
				H->Data[i] = H->Data[i/2]; /* ����X */
			H->Data[i] = X; /* ��X���� */
			return true;
		}
		bool IsEmpty(MaxHeap H)
		{
			return (H->Size == 0);
		}
		ElementType DeleteMax( MaxHeap H )
		{ /* ������H��ȡ����ֵΪ����Ԫ�أ���ɾ��һ����� */
			int Parent, Child;
			ElementType MaxItem, X;
 
			if ( IsEmpty(H) ) {
				printf("������Ϊ��");
				return ERROR;
			}
 
			MaxItem = H->Data[1]; /* ȡ��������ŵ����ֵ ��Ҫɾ�������ֵ�ȱ�������*/
			/* �����������һ��Ԫ�شӸ���㿪ʼ���Ϲ����²��� */
			X = H->Data[H->Size--]; /* ע�⵱ǰ�ѵĹ�ģҪ��С �������forѭ����Ŀ�ľ��Ǹ�X��λ��*/
			for( Parent=1; Parent*2<=H->Size; Parent=Child ) {  /* for���ж������ǿ����Ƿ�����������û��������һ��û�������� */
				Child = Parent * 2;
				if( (Child!=H->Size) && (H->Data[Child]<H->Data[Child+1]) )
					Child++;  /* Childָ�������ӽ��Ľϴ��� */
				if( X >= H->Data[Child] ) break; /* �ҵ��˺���λ�� */
				else  /* ����X */
					H->Data[Parent] = H->Data[Child];
			}
			H->Data[Parent] = X;
 
			return MaxItem;
		}
		/*----------- �������� -----------*/
		void PercDown( MaxHeap H, int p )
		{ /* ���ˣ���H����H->Data[p]Ϊ�����Ӷѵ���Ϊ���� */
			int Parent, Child;
			ElementType X;
 
			X = H->Data[p]; /* ȡ��������ŵ�ֵ */
			for( Parent=p; Parent*2<=H->Size; Parent=Child ) {
				Child = Parent * 2;
				if( (Child!=H->Size) && (H->Data[Child]<H->Data[Child+1]) )
					Child++;  /* Childָ�������ӽ��Ľϴ��� */
				if( X >= H->Data[Child] ) break; /* �ҵ��˺���λ�� */
				else  /* ����X */
					H->Data[Parent] = H->Data[Child];
			}
			H->Data[Parent] = X;
		}
		void BuildHeap( MaxHeap H )
		{ /* ����H->Data[]�е�Ԫ�أ�ʹ�������ѵ�������  */
		  /* �����������H->Size��Ԫ���Ѿ�����H->Data[]�� */
 
			int i;
 
			/* �����һ�����ĸ��ڵ㿪ʼ���������1 */
			for( i = H->Size/2; i>0; i-- )
				PercDown( H, i );
		}
	/* ���ѵ�Ӧ�� */
	
	/* ��С�ѵ�Ӧ�� */
		MinHeap _CreateHeap( int MaxSize)
		{ /* ��������ΪMaxSize�Ŀյ���С�� */
 
			MinHeap H = (MinHeap)malloc(sizeof(struct HNode));
			H->Data = (ElementType *)malloc((MaxSize+1)*sizeof(ElementType));
			H->Size = 0;
			H->Capacity = MaxSize;
			H->Data[0] = -MAXDATA; /* ����"�ڱ�"ΪС�ڶ������п���Ԫ�ص�ֵ*/
 
			return H;
		}
		bool _IsFull( MinHeap H )
		{
			return (H->Size == H->Capacity);
		}
		bool _Insert( MinHeap H, ElementType X )
		{ /* ��Ԫ��X��������H������H->Data[0]�Ѿ�����Ϊ�ڱ� */
			int i;
  
			if ( _IsFull(H) ) { 
				printf("��С������");
				return false;
			}
			i = ++H->Size; /* iָ��������е����һ��Ԫ�ص�λ�� */
			for ( ; H->Data[i/2] > X; i/=2 )/* 2/i�Ǹ��ڵ� */
				H->Data[i] = H->Data[i/2]; /* ����X */
			H->Data[i] = X; /* ��X���� */
			return true;
		}
		bool _IsEmpty(MinHeap H)
		{
			return (H->Size == 0);
		}
		ElementType _DeleteMax( MinHeap H )
		{ /* ����С��H��ȡ����ֵΪ��С��Ԫ�أ���ɾ��һ����� */
			int Parent, Child;
			ElementType MinItem, X;
 
			if ( _IsEmpty(H) ) {
				printf("��С����Ϊ��");
				return ERROR;
			}
 
			MinItem = H->Data[1]; /* ȡ��������ŵ���Сֵ ��Ҫɾ������Сֵ�ȱ�������*/
			/* ����С�������һ��Ԫ�شӸ���㿪ʼ���Ϲ����²��� */
			X = H->Data[H->Size--]; /* ע�⵱ǰ�ѵĹ�ģҪ��С �������forѭ����Ŀ�ľ��Ǹ�X��λ��*/
			for( Parent=1; Parent*2<=H->Size; Parent=Child ) {  /* for���ж������ǿ����Ƿ�����������û��������һ��û�������� */
				Child = Parent * 2;
				if( (Child!=H->Size) && (H->Data[Child]>H->Data[Child+1]) )
					Child++;  /* Childָ�������ӽ��Ľ�С�� */
				if( X <= H->Data[Child] ) break; /* �ҵ��˺���λ�� */
				else  /* ����X */
					H->Data[Parent] = H->Data[Child];
			}
			H->Data[Parent] = X;
 
			return MinItem;
		}
		/*----------- ������С�� -----------*/
		void _PercDown( MinHeap H, int p )
		{ /* ���ˣ���H����H->Data[p]Ϊ�����Ӷѵ���Ϊ��С�� */
			int Parent, Child;
			ElementType X;
 
			X = H->Data[p]; /* ȡ��������ŵ�ֵ */
			for( Parent=p; Parent*2<=H->Size; Parent=Child ) {
				Child = Parent * 2;
				if( (Child!=H->Size) && (H->Data[Child]>H->Data[Child+1]) )
					Child++;  /* Childָ�������ӽ��Ľ�С�� */
				if( X <= H->Data[Child] ) break; /* �ҵ��˺���λ�� */
				else  /* ����X */
					H->Data[Parent] = H->Data[Child];
			}
			H->Data[Parent] = X;
		}
 
		void _BuildHeap( MinHeap H )
		{ /* ����H->Data[]�е�Ԫ�أ�ʹ�������ѵ�������  */
		  /* �����������H->Size��Ԫ���Ѿ�����H->Data[]�� */
 
			int i;
 
			/* �����һ�����ĸ��ڵ㿪ʼ���������1 */
			for( i = H->Size/2; i>0; i-- )
				_PercDown( H, i );
		}

	/* ��С�ѵ�Ӧ�� */

	node *_root;	
};
void test_binary_tree();
class Unit_4
{
public:
	Unit_4();
	~Unit_4();
	//������

	int BinarySearch(int *temp,int length,int key);
	void test_function();
};