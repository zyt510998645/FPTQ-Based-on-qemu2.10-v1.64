#ifndef QEMU_RB_TREE_H
#define QEMU_RB_TREE_H
//****************ZYT*****************

#include<math.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include "qemu/temp_his.h"
#include "qemu/Title.h"
#define RED        0    // 红色节点
#define BLACK    1    // 黑色节点
#define rb_parent(r)   ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r)   ((r)->color==RED)
#define rb_is_black(r)  ((r)->color==BLACK)
#define rb_set_black(r)  do { (r)->color = BLACK; } while (0)
#define rb_set_red(r)  do { (r)->color = RED; } while (0)
#define rb_set_parent(r,p)  do { (r)->parent = (p); } while (0)
#define rb_set_color(r,c)  do { (r)->color = (c); } while (0)

// 红黑树的节点
typedef struct RBTreeNode{
	unsigned char color;        // 颜色(RED 或 BLACK)
	TypeU64   key;                    // 关键字(键值)
	TypeU64   value;
	struct RBTreeNode *left;    // 左孩子
	struct RBTreeNode *right;    // 右孩子
	struct RBTreeNode *parent;    // 父结点
}Node, *RBTree;

// 红黑树的根
typedef struct rb_root{
	 Node *node;
         TypeU64 SET_TEMP_RDD;   
}RBRoot;

// 创建红黑树，返回"红黑树的根"！
static RBRoot* create_rbtree(void){
	RBRoot *root = (RBRoot *)malloc(sizeof(RBRoot));
	root->node = NULL;
        root->SET_TEMP_RDD = 1;
        //printf("Creat one root!\n");
	return root;
};

/* 
* 对红黑树的节点(x)进行左旋转
*/
static void rbtree_left_rotate(RBRoot *root, Node *x)
{
	// 设置x的右孩子为y
	Node *y = x->right;

	// 将 “y的左孩子” 设为 “x的右孩子”；
	// 如果y的左孩子非空，将 “x” 设为 “y的左孩子的父亲”
	x->right = y->left;
	if (y->left != NULL)
		y->left->parent = x;

	// 将 “x的父亲” 设为 “y的父亲”
	y->parent = x->parent;
	if (x->parent == NULL)
	{
		//tree = y;            // 如果 “x的父亲” 是空节点，则将y设为根节点
		root->node = y;            // 如果 “x的父亲” 是空节点，则将y设为根节点
	}
	else
	{
		if (x->parent->left == x)
			x->parent->left = y;    // 如果 x是它父节点的左孩子，则将y设为“x的父节点的左孩子”
		else
			x->parent->right = y;    // 如果 x是它父节点的左孩子，则将y设为“x的父节点的左孩子”
	}    
	// 将 “x” 设为 “y的左孩子”
	y->left = x;
	// 将 “x的父节点” 设为 “y”
	x->parent = y;
};
/* 
* 对红黑树的节点(y)进行右旋转
*/
static void rbtree_right_rotate(RBRoot *root, Node *y)
{
	// 设置x是当前节点的左孩子。
	Node *x = y->left;

	// 将 “x的右孩子” 设为 “y的左孩子”；
	// 如果"x的右孩子"不为空的话，将 “y” 设为 “x的右孩子的父亲”
	y->left = x->right;
	if (x->right != NULL)
		x->right->parent = y;

	// 将 “y的父亲” 设为 “x的父亲”
	x->parent = y->parent;
	if (y->parent == NULL) 
	{
		//tree = x;            // 如果 “y的父亲” 是空节点，则将x设为根节点
		root->node = x;            // 如果 “y的父亲” 是空节点，则将x设为根节点
	}
	else
	{
		if (y == y->parent->right)
			y->parent->right = x;    // 如果 y是它父节点的右孩子，则将x设为“y的父节点的右孩子”
		else
			y->parent->left = x;    // (y是它父节点的左孩子) 将x设为“x的父节点的左孩子”
	}
	// 将 “y” 设为 “x的右孩子”
	x->right = y;
	// 将 “y的父节点” 设为 “x”
	y->parent = x;
};
/*
* (递归实现)查找"红黑树x"中键值为key的节点
*/
static Node* search(RBTree x, TypeU64 key)
{
	if (x==NULL || x->key==key)
		return x;
	if (key < x->key)
		return search(x->left, key);
	else
		return search(x->right, key);
};
/*
* 红黑树插入修正函数
*
* 在向红黑树中插入节点之后(失去平衡)，再调用该函数；
* 目的是将它重新塑造成一颗红黑树。
*
* 参数说明：
*     root 红黑树的根
*     node 插入的结点
*/
static void rbtree_insert_fixup(RBRoot *root, Node *node)
{
	Node *parent, *gparent;

	// 若“父节点存在，并且父节点的颜色是红色”
	while ((parent = rb_parent(node)) && rb_is_red(parent))
	{
		gparent = rb_parent(parent);
		//若“父节点”是“祖父节点的左孩子”
		if (parent == gparent->left)
		{
			// Case 1条件：叔叔节点是红色
			{
				Node *uncle = gparent->right;
				if (uncle && rb_is_red(uncle))
				{
					rb_set_black(uncle);
					rb_set_black(parent);
					rb_set_red(gparent);
					node = gparent;
					continue;
				}
			}
			// Case 2条件：叔叔是黑色，且当前节点是右孩子
			if (parent->right == node)
			{
				Node *tmp;
				rbtree_left_rotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}
			// Case 3条件：叔叔是黑色，且当前节点是左孩子。
			rb_set_black(parent);
			rb_set_red(gparent);
			rbtree_right_rotate(root, gparent);
		} 
		else//若“z的父节点”是“z的祖父节点的右孩子”
		{
			// Case 1条件：叔叔节点是红色
			{
				Node *uncle = gparent->left;
				if (uncle && rb_is_red(uncle))
				{
					rb_set_black(uncle);
					rb_set_black(parent);
					rb_set_red(gparent);
					node = gparent;
					continue;
				}
			}
			// Case 2条件：叔叔是黑色，且当前节点是左孩子
			if (parent->left == node)
			{
				Node *tmp;
				rbtree_right_rotate(root, parent);
				tmp = parent;
				parent = node;
				node = tmp;
			}
			// Case 3条件：叔叔是黑色，且当前节点是右孩子。
			rb_set_black(parent);
			rb_set_red(gparent);
			rbtree_left_rotate(root, gparent);
		}
	}
	// 将根节点设为黑色
	rb_set_black(root->node);
};
/*
* 添加节点：将节点(node)插入到红黑树中
*
* 参数说明：
*root 红黑树的根
*     node 插入的结点
*/
static void rbtree_insert(RBRoot *root, Node *node)
{
	Node *y = NULL;
	Node *x = root->node;
	// 1. 将红黑树当作一颗二叉查找树，将节点添加到二叉查找树中。
	while (x != NULL)
	{
		y = x;
		if (node->key < x->key)
			x = x->left;
		else
			x = x->right;
	}
	rb_parent(node) = y;
	if (y != NULL)
	{
		if (node->key < y->key)
			y->left = node;                // 情况2：若“node所包含的值” < “y所包含的值”，则将node设为“y的左孩子”
		else
			y->right = node;            // 情况3：(“node所包含的值” >= “y所包含的值”)将node设为“y的右孩子” 
	}
	else
	{
		root->node = node;                // 情况1：若y是空节点，则将node设为根
	}
	// 2. 设置节点的颜色为红色
	node->color = RED;

	// 3. 将它重新修正为一颗二叉查找树
	rbtree_insert_fixup(root, node);
};
/*
* 创建结点
*
* 参数说明：
*     key 是键值。
*     parent 是父结点。
*     left 是左孩子。
*     right 是右孩子。
*/
static Node* create_rbtree_node(TypeU64 key,TypeU64 value11, Node *parent, Node *left, Node* right)
{
	Node* p;
	assert ((p = (Node *)malloc(sizeof(Node))) != NULL);
		//return NULL;
	p->key = key;
	p->value = value11;
	p->left = left;
	p->right = right;
	p->parent = parent;
	p->color = BLACK; // 默认为黑色
	return p;
};
/* 
* 新建结点(节点键值为key)，并将其插入到红黑树中
*
* 参数说明：
*     root 红黑树的根
*     key 插入结点的键值
* 返回值：
*     0，插入成功
*     -1，插入失败
*/
//static TypeU64 insert_rbtree(RBRoot *root, TypeU64 key, TypeU64 value1, TypeU64 *H, TypeU64 *SET_LIST)
static TypeU64 insert_rbtree(RBRoot *root, TypeU64 key, TypeU64 value1, TypeU64 *H)
{
	Node *node;    // 新建结点
	TypeU64 temp;
        //*SET_LIST += 1;
	// 不允许插入相同键值的节点。
	// (若想允许插入相同键值的节点，注释掉下面两句话即可！)
	//if (search(root->node, key) != NULL)
	//	return -1;
	// 如果新建结点失败，则返回。
	if (search(root->node, key) == NULL) // 如果不存在
	{
		assert ((node=create_rbtree_node(key, value1, NULL, NULL, NULL)) != NULL);
			//return -1;
		rbtree_insert(root, node);
		temp = INTERVAL_RDD;
		*(H + temp) += 1;
	}
	else // 已经存在
	{
		//temp = (value1 - search(root->node, key)->value) - 1;
		temp = (root->SET_TEMP_RDD - search(root->node, key)->value) - 1;
		if( temp >= INTERVAL_RDD )
		{
			temp = INTERVAL_RDD;
		}
		//search(root->node, key)->value = value1;
		search(root->node, key)->value = root->SET_TEMP_RDD;
		*(H + temp) += 1;
	}
        root->SET_TEMP_RDD ++;
        //printf("%lu \n",root->SET_TEMP_RDD);
	return temp;
};

static void getSampleRdd(TypeU64 *Sample_RDD, TypeU64 *Sample_RDD_taddr, TypeU64 taddr, TypeU64 *HIS_sample_RDD, TypeU64 *Sample_RDD_flag, TypeU64 *Sample_RDD_LS)
{
        if( (Sample_RDD[Set_Id(taddr)]++) % INTERVAL_RDD_SAMPLE_RATE ==0)
	{
	    *Sample_RDD_LS += 1;
	    Sample_RDD_taddr[Set_Id(taddr)] = (TypeU64)(taddr)>>CACHE_LINE_BIT;
	    //Sample_RDD[Set_Id(taddr)] += 1;
	}
	else
	{
	    if(( (TypeU64)(taddr)>>CACHE_LINE_BIT == Sample_RDD_taddr[Set_Id(taddr)]) || (Sample_RDD[Set_Id(taddr)] >= INTERVAL_RDD_SAMPLE_RATE))
	    {
	        if((((TypeU64)(taddr)>>CACHE_LINE_BIT) == Sample_RDD_taddr[Set_Id(taddr)]) && (Sample_RDD_flag[Set_Id(taddr)] == 0))
	        {
	    	if(Sample_RDD[Set_Id(taddr)] <= (INTERVAL_RDD_SAMPLE+2))
	    	{
	                HIS_sample_RDD[ Sample_RDD[Set_Id(taddr)]-2 ] += 1;    
	    	}
                    else
	    	    HIS_sample_RDD[INTERVAL_RDD_SAMPLE] += 1;
	    	Sample_RDD_flag[Set_Id(taddr)] = 1;
	        }
	        if(Sample_RDD[Set_Id(taddr)] >= INTERVAL_RDD_SAMPLE_RATE)
	        {
	    	if( Sample_RDD_flag[Set_Id(taddr)] == 0 )
	    	    HIS_sample_RDD[INTERVAL_RDD_SAMPLE] += 1;
	    	Sample_RDD[Set_Id(taddr)] = 0;
	    	Sample_RDD_flag[Set_Id(taddr)] = 0;
	        }
	    }	
	    //Sample_RDD[Set_Id(taddr)] += 1;
	}
};
/*
* 销毁红黑树
*/
/*
static void rbtree_destroy(RBTree tree)
{
	if (tree==NULL)
		return ;
	if (tree->left != NULL)
		rbtree_destroy(tree->left);
	if (tree->right != NULL)
		rbtree_destroy(tree->right);
	free(tree);
};
// 销毁红黑树
static void destroy_rbtree(RBRoot *root)
{
	if (root != NULL)
		rbtree_destroy(root->node);
	free(root);
};
*/
/*
static void print_HIS(TypeU64 *H)
{
    TypeU64 i=0;
    for(i=0;i < (INTERVAL_RDD+1);i++)
    {
        printf("%lu ",H[i]);
    }
    printf("\n");
};
*/
//*********************************ZYT
/*
static void print_RDD(TypeU64 *H)
{
    TypeU64 i=0;
    for(i=0;i < (INTERVAL_RDD + 1);i++)
        printf("%lu ",*(H + i));
    printf("\n");  
};
*/

#endif
