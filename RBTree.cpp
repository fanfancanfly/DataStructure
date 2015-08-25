// RBTree.cpp : �������̨Ӧ�ó������ڵ㡣
/*******************************copyrights****************************************
   This code was programmed by xiefanfan,xi'an university of technology,all rights reserved;
**Function:research on Red-Black Tree
**Time:2015-08-23
********************************************************************************/

/********************************************************
**�����5�����ʣ�
**��1��ÿ�����Ǻ켴��
**��2��������Ǻ�ɫ
**��3��Ҷ�ӽ���Ǻ�ɫ�ģ�NULL������NIL��㣩
**��4�����һ������Ǻ�ɫ����ô���ĺ��ӽ��Ϊ��ɫ
**��5��������ڵ㣬�Ӹý�㵽����NIL���·���ϣ������ĺڽڵ������ͬ
********************************************************/
#include "stdafx.h"
#include "stdio.h"
#include <iostream>
#include <queue>

using namespace std;

//������ɫ���ͣ�ʹ��ö��
typedef enum color_t
{
	RED = 0,
	BLACK
}color_t;

//��������ṹ��
template <typename T>
struct RBTreeNode
{
	RBTreeNode():key(T()),lchild(NULL),rchild(NULL),parent(NULL),color(RED){}           //���캯���б��ʼ��
	RBTreeNode(const T& value):key(value),lchild(NULL),rchild(NULL),parent(NULL),color(RED){}
	T    key;                    //��ֵ
	struct RBTreeNode *lchild;
	struct RBTreeNode *rchild;
	struct RBTreeNode *parent;
	color_t  color;                //��ɫ
};

//�������
template <typename T>
class RBTree
{
public:
	RBTree():root(NULL){}	                              //���캯��
	void RBTPrint();                                      //��ӡ�����
	void RBTSearch(const T &value,RBTreeNode<T> *&ptr);    //�����������
	bool RBTInsert(const T &value);                 //������
	void RBTDelete(const T &value);                 //ɾ�����
	//void Destroy(RBTreeNode<T> *rt);                //���ٺ����
	void RBTInsertFixUp(RBTreeNode<T> *x);          //�����޸�
	void RBTDeleteFixUp(RBTreeNode<T> *p,RBTreeNode<T> *x);        //ɾ���޸�
	void RBTLeftRotate(RBTreeNode<T> *x);                          //��������
	void RBTRightRotate(RBTreeNode<T> *x);                         //��������
	RBTreeNode<T> *RBTSuccessor(RBTreeNode<T> *x);                 //����x���ĺ��
	~RBTree()                                                      //��������
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
**���ܣ��ݹ��ӡ�����,�������
**ptr:��������ڵ�
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
**���ܣ������������һ�����
**value�����������ֵ
**ptr:ָ�����ָ��
**warning:���û���ҵ���������ص�ptrָ������·���ϵ����һ����㡣������ڣ�ptrָ��������Ľ��
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
		else if (value < p->key)         //����������
		{
			ptr = p;                   //���浱ǰ���ָ��
			p = p->lchild;
		}
		else                            //����������
		{
			ptr = p;
			p = p->rchild;  
		}
	}
}

/*********************************************
**���ܣ�������в���һ�����
**value�������ֵ
**warning������һ����㣬�ý��Ϊ��ɫ���п����ƻ�����������ʣ���Ҫ�������޸����ָ������������
*********************************************/
template <typename T>
bool RBTree<T>::RBTInsert(const T &value)
 {
	RBTreeNode<T> *node,*p,*curNode;                 //�ֱ��ǣ��������㣬�������㸸��㣬��ǰ���
	p = NULL;
	node = new RBTreeNode<T>;
	if (!node)
	{
		return false;
	}
	node->key = value;               //ֻ��Ҫ��key��ֵ���������Ѿ��ù��캯����ʼ��
	RBTSearch(value,p);
	if (!p)                           //��ǰ�����Ϊ��
	{
		root = node;
		root->color = BLACK;       //�޸ĸ��ڵ���ɫ
		return true;
	}
	if (p->key == value)             //����Ѿ����ڣ����ò�����
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
	RBTInsertFixUp(node);             //�����޸�
	return true;
}

/*********************************************
**���ܣ�������в���һ��Ԫ�غ󣬿����ƻ��˺���������ʣ���Ҫ�Ժ�������в������޸�����
**x���Ӹý�㿪ʼ�޸�
**warning��������޸���Ҫ�������ֲ�����޸��������,����������ƻ�����4������2.
*********************************************/
template <typename T>
void RBTree<T>::RBTInsertFixUp(RBTreeNode<T> *x)
{
	RBTreeNode<T> *p,*gparent,*uncle;                //����㡢�游����������ָ��
	//��������2
	while ((p = x->parent) != NULL && p->color == RED)               //�����Ϊ��ɫ�������游���һ������
	{
		gparent = p->parent;
		if (p == gparent->lchild)               //��������游����������
		{
			uncle = gparent->rchild;
			//���1�������Ϊ��ɫ��㣬������Ϊ��ɫ��㣻
			//����������������������Ϳ�ڣ��游���Ϳ�죬Ȼ����游��㴦�����޸�
			if (uncle != NULL && uncle->color == RED)
			{
				gparent->color = RED;
				p->color = BLACK;
				uncle->color = BLACK;
				x = gparent;
			}
			else                              //�����㲻���ڻ���Ϊ��ɫ��ͨ����ת�����ֺ��������
			{
				//���2����ǰ���Ϊ������������,
				//����������ָ��ǰ���ĸ����Ϊ֧�㣬��������������תΪ���3
				if (x == p->rchild)         
				{
					x = p;
					RBTLeftRotate(x);
					p = x->parent;               //��ת������޸���ʹp��Ϊx�ĸ����
				}
				//���3����ǰ���Ϊ������������
				//����������������Ϊ�ڣ��游����Ϊ�죬�游���Ϊ֧���������������
				else                             
				{
					p->color = BLACK;
					gparent->color = RED;
					RBTRightRotate(gparent);
				}
			}
		}
		else                                    //��������游����������,���ϱ��ǶԳ����
		{
			uncle = gparent->lchild;
			//���1��������������Ϊ��ɫ
			if (uncle != NULL && uncle->color == RED)
			{
				p->color = BLACK;
				uncle->color = BLACK;
				gparent->color = RED;
				x = gparent;
			}
			else                              //�����㲻���ڻ���Ϊ��ɫ��ͨ����ת�����ֺ��������
			{
				//���2��xΪ�丸������ӣ�ͨ����תת��Ϊ���3
				if (x == p->lchild)
				{
					x = p;
					RBTRightRotate(x);
					p = x->parent;
				}
				//���3��xΪ�丸������������������ɫִ�ڣ��游�����ɫֵ�죬Ȼ�����游���Ϊ֧���������
				else
				{
					p->color = BLACK;
					gparent->color = RED;
					RBTLeftRotate(gparent);
				}
			}
		}
	}
	//��������2
	root->color = BLACK;
}

/*********************************************
**���ܣ��������������
**x����ǰ��ת��ָ����
*********************************************/
template <typename T>
void RBTree<T>::RBTLeftRotate(RBTreeNode<T> *x)
{
	//����˳���ȵ���x������������������ĸ���㣬Ȼ�����R��x�ĸ�������ӹ�ϵ��������x����㲻����x������������R������������޸�R��x�����ӡ�
	RBTreeNode<T> *R;                                   //ָ��x����������
	R = x->rchild;
	x->rchild = R->lchild;
	if (R->lchild)
	{
		R->lchild->parent = x;                     //R�������ĸ�����޸�Ϊx
	}
	R->parent = x->parent;
	if (x->parent == NULL)                           //���ڵ�
	{
		root = R;
	}
	else
	{
		if (x->parent->lchild == x)                //x�������������Ϲ���R
		{
			x->parent->lchild = R;
		}
		else
		{
			x->parent->rchild = R;
		}
	}
	R->lchild = x;                                   //�޸�R��x֮��Ĺ�ϵ
	x->parent = R;
}

/*********************************************
**���ܣ��������������
**T:����������
**x����ǰ��ת��ָ����
*********************************************/
template <typename T>
void RBTree<T>::RBTRightRotate(RBTreeNode<T> *x)
{
	//��������������
	RBTreeNode<T> *L;
	L = x->lchild;
	x->lchild = L->rchild;
	if (L->rchild)
	{
		L->rchild->parent = x;
	}
	L->parent = x->parent;
	if (x->parent == NULL)                //�����
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
**���ܣ������ɾ�����
**T��ɾ�����ֵ
*********************************************/
template <typename T>
void RBTree<T>::RBTDelete(const T &value)
{
	RBTreeNode<T> *target,*realDel,*child;
	target = NULL;
	RBTSearch(value,target);
	if (!target)                       //�ýڵ㲻����
	{
		return;
	}
	if (target->lchild == NULL || target->rchild == NULL)        //�ҵ���ɾ�������������λ��,��������������һ��Ϊ��
	{
		realDel = target;
	}
	else                                                         //������������Ϊ��
	{
		realDel = RBTSuccessor(target);                        //�ҵ���ǰ���ĺ�̽��
	}
	if (realDel->lchild)                             //��ɾ�����ֻ��һ���������ؽӸ�����
	{
		child = realDel->lchild;
	}
	else
	{
		child = realDel->rchild;
	}

	if (child)                                       //���ӽ��ĸ����ָ������ɾ�����ĸ����
	{
		child->parent = realDel->parent;
	}

	if (realDel->parent == NULL)                    //����㣿
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

	if (realDel->color == BLACK)                             //����ɾ���Ľ���Ǻ�ɫ���Ž���ɾ���޸�����ɫ���ɾ����Ӱ����������
	{
		RBTDeleteFixUp(realDel->parent ,child);
	}
	free(realDel);
}

/*********************************************
**���ܣ����ҵ�ǰ���ĺ�̽��
**x����ǰ���
*********************************************/
template <typename T>
RBTreeNode<T> *RBTree<T>::RBTSuccessor(RBTreeNode<T> *x)
{
	RBTreeNode<T> *rp;
	rp = x->rchild;                      //���ң�Ȼ�����󵽾�ͷ
	while(rp->lchild)
	{
		rp = rp->lchild;
	}
	return rp;
}

/*********************************************
**���ܣ�ɾ���޸������ֺ����������
**p����ǰ��㸸���
**x����ǰ���
*********************************************/
template <typename T>
void RBTree<T>::RBTDeleteFixUp(RBTreeNode<T> *p,RBTreeNode<T> *x)
{
	RBTreeNode<T> *brother;                      //�ֵܽ��ָ��
	while ((x == NULL || x->color == BLACK) && x != root)        
	{
		if (x == p->lchild)                 //��ǰ���Ϊ���������
		{
			brother = p->rchild;
			//���1���ֵܽ��Ϊ��ɫ
			//����취��������ú죬�ֵܽ���úڣ��Ը����Ϊ֧���������
			if (brother->color == RED)
			{
				brother->color = BLACK;
				p->color = RED;
				RBTLeftRotate(p);
				brother = p->rchild;
			}
			//���2���ֵܽ��Ϊ�ڣ��ֵܽڵ���������ӽ�㶼Ϊ��(NULLҲΪ�ڽڵ�)����x��brotherĨ��һ�غ�ɫ
			//����취��brother��ɫ��Ϊ�죬x������Ƶ��丸���
			if ((brother->lchild == NULL || brother->lchild->color == BLACK) && (brother->rchild == NULL || brother->rchild->color == BLACK))
			{
				brother->color = RED;
				x = p;
				p = p->parent;
			}                  
			else
			{
				//���3���ֵܽ��Ϊ�ڣ��ֵܽ������Ϊ�죬����Ϊ��
				//����������ֵܽ��Ⱦ�죬�ֵܽ������Ⱦ�ڣ����ֵܽ��Ϊ֧���������   
				if (brother->rchild == NULL && brother->color == BLACK)
				{
					brother->lchild->color = BLACK;
					brother->color = RED;
					RBTRightRotate(brother);
					brother = p->rchild;
				}
				//���4���ֵܽ��Ϊ�ڣ��ֵܽ������Ϊ�죬��������
				//������������ֵܽڵ�Ⱦ�ɸ������ɫ�������Ⱦ�ڣ��ֵܽ���ҽ��Ⱦ�ڣ��Ը����Ϊָ���������
				else
				{
					brother->color = p->color;
					p->color = BLACK;
					brother->rchild->color = BLACK;
					RBTLeftRotate(p);
				}

				x = root;                        //��xΪ����ʱ������ѭ��
			}
		}
		else
		{
			brother = p->lchild;
			//���1
			if (brother->color == RED)
			{
				brother->color = BLACK;
				p->color = RED;
				RBTRightRotate(p);
				brother = p->lchild;
			}
			//���2
			if ((brother->lchild == NULL || brother->lchild->color == BLACK) && (brother->rchild == NULL || brother->rchild->color == BLACK))
			{
				brother->color = RED;
				x = p;
				p = p->parent;
			}
			else
			{
				//���3
				if (brother->lchild == NULL || brother->lchild->color == BLACK)
				{
					brother->rchild->color = BLACK;
					brother->color = RED;
					RBTLeftRotate(brother);
					//����brother
					brother = p->lchild;
				}
				//���4
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

