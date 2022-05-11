#define BinNodePosi BinNode<T>* //节点位置 // ! not compeleted
template <typename T> struct BinNode { 
   T data;                           //数值
   BinNodePosi parent;          //父节点
   BinNodePosi lc,rc;         //左、右孩子
   int height;                     //高度

// 操作接口
   int size();      //统计当前节点子树的规模
   BinNodePosi insertAsLC ( T const& ); 
	      //作为当前节点的左孩子插入新节点
   BinNodePosi insertAsRC ( T const& ); 
              //作为当前节点的右孩子插入新节点
   BinNodePosi succ(); //当前节点直接后继
   template <typename VST> void travLevel(VST&);
                             //子树层次遍历
   template <typename VST> void travPre(VST&); 
                             //子树先序遍历
   template <typename VST> void travIn(VST&); 
                            //子树中序遍历
   template <typename VST> void travPost(VST&); 
                            //子树后序遍历
};

template <typename T> 
BinNodePosi BinNode<T>::insertAsLC ( T const& e )
{ return lc = new BinNode ( e, this ); } 
//将e作为当前节点的左孩子插入二叉树

template <typename T> class BinTree { //二叉树模板类
protected:
   int _size; 
   BinNodePosi _root; //规模、根节点
   virtual int updateHeight ( BinNodePosi x ); //更新节点x高度
   void updateHeightAbove ( BinNodePosi x ); //更新节点x及其祖先高度
public:
   int size() const { return _size; } //规模
   bool empty() const { return !_root; } //判空
   BinNodePosi root() const { return _root; } //树根

    /* 子树插入、删除、分离接口 */
    BinNodePosi insertAsLC(BinNodePosi x, T const& e);
    ~BinTree();
    int remove(BinNodePosi x);
   /* 遍历接口 */
};

#define stature(p) ((p) ? (p)->height : -1) 
// 节点高度（宏定义封装，使得实现简便，
// 与“空树高度为-1”的约定相统一）
template <typename T> 
int BinTree<T>::updateHeight ( BinNodePosi x ) { //更新节点x高度
    return x->height = 1 + 
    max (stature(x->lc), stature(x->rc));
} 

template <typename T> 
void BinTree<T>::updateHeightAbove ( BinNodePosi x ) { //更新高度
    while ( x ) {//从x出发，覆盖历代祖先
    updateHeight ( x ); 
    x = x->parent; } 
}

template <typename T>
BinNodePosi BinTree<T>::insertAsLC ( BinNodePosi x, T const& e )
{//e插入为x的左孩子
	_size++; 
	x->insertAsLC ( e ); 
	updateHeightAbove ( x ); 
	return x->lc; 
}

template <typename T> template <typename VST> //元素类型、操作器
void BinNode<T>::travLevel ( VST& visit ) { //二叉树层次遍历算法
   Queue<BinNodePosi> Q;                //辅助队列
   Q.enqueue ( this );                    //根节点入队
   while ( !Q.empty() ) {          //在队列再次变空之前，反复迭代
      BinNodePosi x = Q.dequeue(); 
      visit ( x->data );                  //取出队首节点并访问之
      if ( HasLChild ( *x ) ) Q.enqueue ( x->lc ); //左孩子入队
      if ( HasRChild ( *x ) ) Q.enqueue ( x->rc ); //右孩子入队
   }
}

template <typename T, typename VST> void travPre 
( BinNodePosi x, VST& visit ) 
{
    if ( !x ) return;
   visit ( x->data );
   travPre ( x->lc, visit );
   travPre ( x->rc, visit );
}

template <typename T, typename VST> void travIn_R 
( BinNodePosi x, VST& visit ) 
{
    if ( !x ) return;
   travIn_R ( x->lc, visit );
   visit ( x->data );
   travIn_R ( x->rc, visit );
}


template <typename T, typename VST> void travPost_R 
( BinNodePosi x, VST& visit ) 
{
    if ( !x ) return;
   travPost_R ( x->lc, visit );
   travPost_R ( x->rc, visit );
   visit ( x->data );
}

template <typename T>
BinTree<T>::~BinTree() { if (0 < _size) remove(_root); } //析构函数


template <typename T> //删除树中位置x处节点及其后代，返回被删除节点的数值
int BinTree<T>::remove(BinNodePosi x) {
	FromParentTo(*x) = NULL; //切断来自父节点的指针
	updateHeightAbove(x->parent); //更新祖先高度
	int n = removeAt(x); _size -= n; return n; 
                              //删除子树x，更新规模，返回删除节点总数
}

template <typename T> //删除树中位置x处节点及其后代，返回被删除节点的数值
static int removeAt(BinNodePosi x) { 
	if (!x) return 0; //递归基：空树
	int n = 1 + removeAt(x->lc) + removeAt(x->rc);//递归释放左右子树
       delete(x); 
       return n; //释放被摘除节点，并返回删除节点总数
}

