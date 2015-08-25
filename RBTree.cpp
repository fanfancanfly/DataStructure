// RBTree.cpp : 定义控制台应用程序的入口点。
/*******************************copyrights****************************************
   This code was programmed by xiefanfan,xi'an university of technology,all rights reserved;
**Function:research on Red-Black Tree
**Time:2015-08-23
********************************************************************************/

/********************************************************
**红黑树5大性质：
**（1）每个结点非红即黑
**（2）根结点是黑色
**（3）叶子结点是黑色的（NULL结点或者NIL结点）
**（4）如果一个结点是红色，那么它的孩子结点为黑色
**（5）对任意节点，从该结点到任意NIL结点路径上，经过的黑节点个数相同
********************************************************/
#include "stdafx.h"
#include "stdio.h"
#include <iostream>
#include <queue>

using namespace std;

//定义颜色类型，使用枚举
typedef enum color_t
{
	RED = 0,
	BLACK
}color_t;

//红黑树结点结构体
template <typename T>
struct RBTreeNode
{
	RBTreeNode():key(T()),lchild(NULL),rchild(NULL),parent(NULL),color(RED){}           //构造函数列表初始化
	RBTreeNode(const T& value):key(value),lchild(NULL),rchild(NULL),parent(NULL),color(RED){}
	T    key;                    //键值
	struct RBTreeNode *lchild;
	struct RBTreeNode *rchild;
	struct RBTreeNode *parent;
	color_t  color;                //颜色
};

//红黑树类
template <typename T>
class RBTree
{
public:
	RBTree():root(NULL){}	                              //构造函数
	void RBTPrint();                                      //打印红黑树
	void RBTSearch(const T &value,RBTreeNode<T> *&ptr);    //红黑树中搜索
	bool RBTInsert(const T &value);                 //插入结点
	void RBTDelete(const T &value);                 //删除结点
	//void Destroy(RBTreeNode<T> *rt);                //销毁红黑树
	void RBTInsertFixUp(RBTreeNode<T> *x);          //插入修复
	void RBTDeleteFixUp(RBTreeNode<T> *p,RBTreeNode<T> *x);        //删除修复
	void RBTLeftRotate(RBTreeNode<T> *x);                          //左旋操作
	void RBTRightRotate(RBTreeNode<T> *x);                         //右旋操作
	RBTreeNode<T> *RBTSuccessor(RBTreeNode<T> *x);                 //返回x结点的后继
	~RBTree()                                                      //析构函数
	{
		if (root)
		{
			//Destroy(root);
		}
	}
private:
	RBTreeNode<T> *root;
};

/*********************************************
**功能：递归打印红黑树,中序遍历
**ptr:红黑树根节点
*********************************************/
template <typename T>
void RBTree<T>::RBTPrint()
{
	RBTreeNode<T> *tem;
	queue<RBTreeNode<T> *> Que;
	Que.push(root);
	while(!Que.empty())
	{
		tem = Que.front();
		Que.pop();
		cout<<"node: "<<tem->key<<" ";
		if (tem->lchild)
		{
			cout<<"left: "<<tem->lchild->key<<" color-"<<(tem->lchild->color==RED?'R':'B')<<" ";
			Que.push(tem->lchild);
		}
		if(tem->rchild)
		{
			cout<<"right: "<<tem->rchild->key<<" color-"<<(tem->rchild->color==RED?'R':'B')<<" ";		
			Que.push(tem->rchild);
		}
		cout<<endl;
	}
}

/*********************************************
**功能：红黑树中搜索一个结点
**value：待搜索结点值
**ptr:指向结点的指针
**warning:如果没有找到结果，返回的ptr指向搜索路径上的最后一个结点。如果存在，ptr指向待搜索的结点
*********************************************/
template <typename T>
void RBTree<T>::RBTSearch(const T& value,RBTreeNode<T> *&ptr)
{
	RBTreeNode<T> *p = root;
	ptr = NULL;
	while (p)
	{
		if (p->key == value)
		{
			ptr = p;
			break;
		}
		else if (value < p->key)         //搜索左子树
		{
			ptr = p;                   //保存当前结点指针
			p = p->lchild;
		}
		else                            //搜索右子树
		{
			ptr = p;
			p = p->rchild;  
		}
	}
}

/*********************************************
**功能：红黑树中插入一个结点
**value：插入的值
**warning：插入一个结点，该结点为红色。有可能破坏红黑树的性质，需要做插入修复，恢复红黑树的性质
*********************************************/
template <typename T>
bool RBTree<T>::RBTInsert(const T &value)
 {
	RBTreeNode<T> *node,*p,*curNode;                 //分别是，带插入结点，带插入结点父结点，当前结点
	p = NULL;
	node = new RBTreeNode<T>;
	if (!node)
	{
		return false;
	}
	node->key = value;               //只需要给key赋值，其它的已经用构造函数初始化
	RBTSearch(value,p);
	if (!p)                           //当前红黑树为空
	{
		root = node;
		root->color = BLACK;       //修改根节点颜色
		return true;
	}
	if (p->key == value)             //结点已经存在，不用插入了
	{
		return false;
	}
	if (value < p->key)
	{
		p->lchild = node;
	}
	else
	{
		p->rchild = node;
	}
	node->parent = p;
	RBTInsertFixUp(node);             //插入修复
	return true;
}

/*********************************************
**功能：红黑树中插入一个元素后，可能破坏了红黑树的性质，需要对红黑树进行插入后的修复工作
**x：从该结点开始修复
**warning：红黑树修复主要考虑三种插入的修复情况即可,插入结点可能破坏性质4和性质2.
*********************************************/
template <typename T>
void RBTree<T>::RBTInsertFixUp(RBTreeNode<T> *x)
{
	RBTreeNode<T> *p,*gparent,*uncle;                //父结点、祖父结点和叔叔结点指针
	//纠正性质2
	while ((p = x->parent) != NULL && p->color == RED)               //父结点为红色，所以祖父结点一定存在
	{
		gparent = p->parent;
		if (p == gparent->lchild)               //父结点是祖父结点的左子树
		{
			uncle = gparent->rchild;
			//情况1，父结点为红色结点，叔叔结点为红色结点；
			//修正方法：父结点和叔叔结点涂黑，祖父结点涂红，然后从祖父结点处继续修复
			if (uncle != NULL && uncle->color == RED)
			{
				gparent->color = RED;
				p->color = BLACK;
				uncle->color = BLACK;
				x = gparent;
			}
			else                              //叔叔结点不存在或者为黑色，通过旋转来保持红黑树性质
			{
				//情况2，当前结点为父结点的右子树,
				//修正方法：指向当前结点的父结点为支点，进行左旋操作，转为情况3
				if (x == p->rchild)         
				{
					x = p;
					RBTLeftRotate(x);
					p = x->parent;               //旋转后进行修复，使p仍为x的父结点
				}
				//情况3，当前结点为父结点的左子树
				//修正方法：父结点变为黑，祖父结点变为红，祖父结点为支点进行右旋操作，
				else                             
				{
					p->color = BLACK;
					gparent->color = RED;
					RBTRightRotate(gparent);
				}
			}
		}
		else                                    //父结点是祖父结点的右子树,跟上边是对称情况
		{
			uncle = gparent->lchild;
			//情况1：父结点和叔叔结点为红色
			if (uncle != NULL && uncle->color == RED)
			{
				p->color = BLACK;
				uncle->color = BLACK;
				gparent->color = RED;
				x = gparent;
			}
			else                              //叔叔结点不存在或者为黑色，通过旋转来保持红黑树性质
			{
				//情况2：x为其父结点左子，通过旋转转换为情况3
				if (x == p->lchild)
				{
					x = p;
					RBTRightRotate(x);
					p = x->parent;
				}
				//情况3：x为其父结点右子树，父结点颜色执黑，祖父结点颜色值红，然后以祖父结点为支点进行左旋
				else
				{
					p->color = BLACK;
					gparent->color = RED;
					RBTLeftRotate(gparent);
				}
			}
		}
	}
	//保持性质2
	root->color = BLACK;
}

/*********************************************
**功能：红黑树左旋处理
**x：当前旋转的指点结点
*********************************************/
template <typename T>
void RBTree<T>::RBTLeftRotate(RBTreeNode<T> *x)
{
	//调整顺序：先调整x结点右子树的左子树的父结点，然后调整R和x的父结点链接关系（左旋后，x父结点不再与x相连，而是与R相连），最后修改R和x的连接。
	RBTreeNode<T> *R;                                   //指向x结点的右子树
	R = x->rchild;
	x->rchild = R->lchild;
	if (R->lchild)
	{
		R->lchild->parent = x;                     //R左子树的父结点修改为x
	}
	R->parent = x->parent;
	if (x->parent == NULL)                           //根节点
	{
		root = R;
	}
	else
	{
		if (x->parent->lchild == x)                //x父结点的左子树上挂载R
		{
			x->parent->lchild = R;
		}
		else
		{
			x->parent->rchild = R;
		}
	}
	R->lchild = x;                                   //修改R和x之间的关系
	x->parent = R;
}

/*********************************************
**功能：红黑树右旋处理
**T:红黑树根结点
**x：当前旋转的指点结点
*********************************************/
template <typename T>
void RBTree<T>::RBTRightRotate(RBTreeNode<T> *x)
{
	//方法与左旋类似
	RBTreeNode<T> *L;
	L = x->lchild;
	x->lchild = L->rchild;
	if (L->rchild)
	{
		L->rchild->parent = x;
	}
	L->parent = x->parent;
	if (x->parent == NULL)                //根结点
	{
		root = L;
	}
	else
	{
		if (x->parent->lchild == x)
		{
			x->parent->lchild = L;
		}
		else
		{
			x->parent->rchild = L;
		}
	}
	L->rchild = x;
	x->parent = L;
}

/*********************************************
**功能：红黑树删除结点
**T：删除结点值
*********************************************/
template <typename T>
void RBTree<T>::RBTDelete(const T &value)
{
	RBTreeNode<T> *target,*realDel,*child;
	target = NULL;
	RBTSearch(value,target);
	if (!target)                       //该节点不存在
	{
		return;
	}
	if (target->lchild == NULL || target->rchild == NULL)        //找到待删除结点的真正结点位置,至少左右子树有一个为空
	{
		realDel = target;
	}
	else                                                         //左右子树都不为空
	{
		realDel = RBTSuccessor(target);                        //找到当前结点的后继结点
	}
	if (realDel->lchild)                             //待删除结点只有一颗子树，重接该子树
	{
		child = realDel->lchild;
	}
	else
	{
		child = realDel->rchild;
	}

	if (child)                                       //孩子结点的父结点指向真正删除结点的父结点
	{
		child->parent = realDel->parent;
	}

	if (realDel->parent == NULL)                    //根结点？
	{
		root = child;
	}
	else
	{
		if (realDel->parent->lchild == realDel)
		{
			realDel->parent->lchild = child;
		}
		else
		{
			realDel->parent->rchild = child;
		}
	}

	if (target != realDel)
	{
		target->key = realDel->key;
	}

	if (realDel->color == BLACK)                             //真正删除的结点是黑色，才进行删除修复，红色结点删除不影响红黑树性质
	{
		RBTDeleteFixUp(realDel->parent ,child);
	}
	free(realDel);
}

/*********************************************
**功能：查找当前结点的后继结点
**x：当前结点
*********************************************/
template <typename T>
RBTreeNode<T> *RBTree<T>::RBTSuccessor(RBTreeNode<T> *x)
{
	RBTreeNode<T> *rp;
	rp = x->rchild;                      //向右，然后向左到尽头
	while(rp->lchild)
	{
		rp = rp->lchild;
	}
	return rp;
}

/*********************************************
**功能：删除修复，保持红黑树的性质
**p：当前结点父结点
**x：当前结点
*********************************************/
template <typename T>
void RBTree<T>::RBTDeleteFixUp(RBTreeNode<T> *p,RBTreeNode<T> *x)
{
	RBTreeNode<T> *brother;                      //兄弟结点指针
	while ((x == NULL || x->color == BLACK) && x != root)        
	{
		if (x == p->lchild)                 //当前结点为父结点左子
		{
			brother = p->rchild;
			//情况1：兄弟结点为红色
			//解决办法：父结点置红，兄弟结点置黑，以父结点为支点进行左旋
			if (brother->color == RED)
			{
				brother->color = BLACK;
				p->color = RED;
				RBTLeftRotate(p);
				brother = p->rchild;
			}
			//情况2：兄弟结点为黑，兄弟节点的两个孩子结点都为黑(NULL也为黑节点)：将x和brother抹除一重黑色
			//解决办法：brother颜色变为红，x结点上移到其父结点
			if ((brother->lchild == NULL || brother->lchild->color == BLACK) && (brother->rchild == NULL || brother->rchild->color == BLACK))
			{
				brother->color = RED;
				x = p;
				p = p->parent;
			}                  
			else
			{
				//情况3：兄弟结点为黑，兄弟结点左子为红，右子为黑
				//解决方法：兄弟结点染红，兄弟结点左子染黑，以兄弟结点为支点进行右旋   
				if (brother->rchild == NULL && brother->color == BLACK)
				{
					brother->lchild->color = BLACK;
					brother->color = RED;
					RBTRightRotate(brother);
					brother = p->rchild;
				}
				//情况4：兄弟结点为黑，兄弟结点右子为红，左子任意
				//解决方法：将兄弟节点染成父结点颜色，父结点染黑，兄弟结点右结点染黑，以父结点为指点进行左旋
				else
				{
					brother->color = p->color;
					p->color = BLACK;
					brother->rchild->color = BLACK;
					RBTLeftRotate(p);
				}

				x = root;                        //当x为树根时，结束循环
			}
		}
		else
		{
			brother = p->lchild;
			//情况1
			if (brother->color == RED)
			{
				brother->color = BLACK;
				p->color = RED;
				RBTRightRotate(p);
				brother = p->lchild;
			}
			//情况2
			if ((brother->lchild == NULL || brother->lchild->color == BLACK) && (brother->rchild == NULL || brother->rchild->color == BLACK))
			{
				brother->color = RED;
				x = p;
				p = p->parent;
			}
			else
			{
				//情况3
				if (brother->lchild == NULL || brother->lchild->color == BLACK)
				{
					brother->rchild->color = BLACK;
					brother->color = RED;
					RBTLeftRotate(brother);
					//重置brother
					brother = p->lchild;
				}
				//情况4
				else
				{
					brother->color = p->color;
					p->color = BLACK;
					brother->lchild->color = BLACK;
					RBTRightRotate(p);
				}

				x = root;
			}
		}
	}
	if (x != NULL)
	{
		x->color = BLACK;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	//RBTree<int>  irbtree;
	//int a[]={3,2,1,4,5,6,7,10,9,8};
	//for (int i=0;i<10;++i)
	//{
	//	irbtree.RBTInsert(a[i]);
	//}
	//irbtree.RBTPrint();
	//irbtree.RBTDelete(8);
	//irbtree.RBTPrint();

	RBTree<char>  crbtree;
	char b[]={'c','b','a','d','e','f','g','j','i','h'};
	for (int i=0;i<10;++i)
	{
		crbtree.RBTInsert(b[i]);
	}
	crbtree.RBTPrint();
	return 0;
}

