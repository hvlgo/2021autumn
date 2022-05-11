#define BinNodePosi BinNode<T>* 
#include "BinTree.h"

BSTNode* Search(int x, BSTNode *p) {
    if (p == NULL) return NULL;
    BSTNode* temp = p;
    while (temp != NULL) {
        if (x == temp->data) return temp;
        if (x < temp->data) 
            temp = temp->left;
        else temp = temp->right;
    }
    return NULL; 
};

BSTNode* Search(int x, BSTNode *p) {
    if (p == NULL) return NULL;
    else if (x < p->data) return Search(x, p->left);
    else if (x > p->data) return Search(x, p->right);
    else return p;
};

bool Insert(int x, BSTNode *&p) {
    if (p == NULL) {
        p = new BSTNode;
        p->data = x;
        p->left = NULL;
        p->right = NULL;
        return true;
    }
    else if (x < p->data) 
        Insert(x, p->left);
    else if (x > p->data) 
        Insert(x, p->right);
    else return false;
};

bool Remove(int x, BSTNode* &p) {        //在以p为根节点的树中删除元素x
    if (p != NULL) {      //若递归的各层子树不为空，说明顺利删除返回true
        if (x < p->data) Remove(x, p->left);   //递归进入左子树进行删除
        else if (x > p->data) Remove(x, p->right); //递归进入右子树删除
        else if (p->left == NULL||p->right == NULL){//若至多有一个孩子
            BSTNode* temp = p;               // 以temp指向即将删除节点
            if (p->left == NULL) 
                p = p->right;      //若左子树空，p地址更新为其右孩子地址
            else p = p->left;      //若右子树空，p地址更新为其左孩子地址
            delete temp;           // 删除节点
        }        
        else {                     //左右子树皆存在
            BSTNode* temp = p->right;
            while (temp->left!=NULL) temp = temp->left; //递归寻找右孩子
            p->data = temp->data;             //更新该被删除节点的关键码
            Remove(p->data, p->right); // 递归调用删除右子树中的p->data
	}
        return true;               // 删除成功，返回true
    }
    return false;                  // 树中无关键码x，删除失败
};

template <typename T> 
class BST : public BinTree<T> { //由BinTree派生BST模板类
protected:
   BinNodePosi(T) _hot;       //“命中”节点的父亲

public: //基本接口：以virtual修饰，强制要求所有派生类（BST变种）根据各自的规则对其重写
   virtual BinNodePosi & search ( const T& e ); //查找
   virtual BinNodePosi insert ( const T& e ); //插入
   virtual bool remove ( const T& e ); //删除


};

#define EQUAL(e, v)  (!(v) || (e) == (v)->data) 

template <typename T> 
BinNodePosi & BST<T>::search(const T & e ) //在BST中查找关键码e
{ return searchIn ( _root, e, _hot = NULL ); } //返回目标节点位置的引用，以便后续插入、删除操作


template <typename T>
static BinNodePosi & searchIn ( BinNodePosi(T) & v, const T& e, BinNodePosi(T) & hot ) {
   if ( !v || ( e == v->data ) ) return v; 
   hot = v; //一般情况：先记下当前节点，然后再
   return searchIn ( ( ( e < v->data ) ? v->lc : v->rc ), e, hot ); 
                            //深入一层，递归查找
} //返回时，返回值指向命中节点（或假想的通配哨兵），hot指向其父亲

template <typename T> 
BinNodePosi BST<T>::insert ( const T& e ) { 
                                      //将关键码e插入BST树中
   BinNodePosi(T) & x = search ( e ); 
   if ( x ) return x;                 // 目标存在则返回
                            //确认目标不存在（留意对_hot的设置）
   x = new BinNode<T> ( e, _hot ); 
                       //创建新节点x：以e为关键码，以_hot为父
   _size++; //更新全树规模
   updateHeightAbove ( x ); //更新x及其历代祖先的高度
   return x; //新插入的节点，必为叶子
} //无论e是否存在于原树中，返回时总有x->data == e

template <typename T> bool BST<T>::remove ( const T& e ) { 
   BinNodePosi(T) & x = search ( e ); 
   if ( !x ) return false; 
   removeAt ( x, _hot ); _size--;    //实施删除
   updateHeightAbove ( _hot );       //更新_hot及其历代祖先的高度
   return true;
} //删除成功与否，由返回值指示

template <typename T>
static BinNodePosi(T) removeAt (BinNodePosi(T) & x, BinNodePosi(T) & hot ) {
   BinNodePosi(T) w = x; //实际被摘除的节点，初值同x
   BinNodePosi(T) succ = NULL; //被删除节点接替者
   if ( !HasLChild ( *x ) ) //若x的左子树为空 
      succ = x = x->rc; //直接将*x替换为其右子树
   else if ( !HasRChild ( *x ) ) //若右子树为空
      succ = x = x->lc; 
   else {
       //左右子树均存在，
      w = w->succ(); //在右子树中找到*x的直接后继*w
      swap ( x->data, w->data ); //交换*x和*w数据      
      BinNodePosi(T) u = w->parent;
      ((u == x) ? u->rc : u->lc) = succ = w->rc;
                  //在右子树中找到*x的直接后继*w

   }              //双分支部分代码
   hot = w->parent;    //记录实际被删除节点的父亲
   if ( succ ) succ->parent = hot; 
                    //并将被删除节点的接替者与hot相联
   release ( w->data ); 
   release ( w ); 
   return succ;    //释放被摘除节点，返回接替者
}

template <typename T> BinNodePosi(T) BinNode<T>::succ() { //定位节点v直接后继
   BinNodePosi(T) s = this; //记录后继的临时变量
      if ( rc ) {
   //若有右孩子，则直接后继必在右子树中，具体地就是
           s = rc; //右子树中
           while ( HasLChild ( *s ) ) 
              s = s->lc; //最靠左（最小）的节点
      } 
      else { 
//否则，直接后继应是“将当前节点包含于其左子树中的最低祖先”，具体地就是
          while ( IsRChild ( *s ) ) 
             s = s->parent; 
              //逆向地沿右向分支不断朝左上方移动
          s = s->parent; 
//最后再朝右上方移动一步，即抵达直接后继（如果存在）
      }
      return s;
}
