template <typename T> struct BTNode { //B-树节点模板类
   BTNodePosi(T) parent; //父节点
   Vector<T> key; //关键码向量
   Vector<BTNodePosi(T)> child; //孩子向量（其长度总比key多一）
   BTNode() { parent = NULL; child.insert ( 0, NULL ); }
   BTNode ( T e, BTNodePosi(T) lc = NULL, BTNodePosi(T) rc = NULL )      
   {
      parent = NULL; //作为根节点，而且初始时
      key.insert ( 0, e ); //只有一个关键码，以及
      child.insert ( 0, lc ); child.insert ( 1, rc ); //两个孩子
      if ( lc ) lc->parent = this; if ( rc ) rc->parent = this;
   }
};

template <typename T> class BTree { //B-树模板类

protected:
   int _size; //存放的关键码总数
   int _order; //B-树的阶次，至少为3——创建时指定，一般不能修改
   BTNodePosi(T) _root; //根节点
   BTNodePosi(T) _hot; //BTree::search()最后访问的非空节点位置
   void solveOverflow ( BTNodePosi(T) ); //因插入而上溢之后的分裂处理
   void solveUnderflow ( BTNodePosi(T) ); //因删除而下溢之后的合并处理

public:
   

}; //BTree
template <typename T>
BTNodePosi(T) BTree<T>::search ( const T& e ) { //在B-树中查找关键码e
   BTNodePosi(T) v = _root; _hot = NULL;                 //从根节点出发
   while ( v ) {                                         //逐层查找
      Rank r = v->key.search ( e );        //在当前节点中，找到不大于e的最大关键码（向量查找）
      if ( ( 0 <= r ) && ( e == v->key[r] ) ) return v;  //成功：在当前节点中命中目标关键码
      _hot = v; v = v->child[r + 1]; //否则，转入对应子树（_hot指向其父）——需做I/O，最费时间
   }                                //这里在向量内是二分查找，但对通常的_order可直接顺序查找
   return NULL;                                       //失败：最终抵达外部节点
}

template <typename T> bool BTree<T>::insert ( const T& e ) { //将关键码e插入B树中
   BTNodePosi(T) v = search ( e ); if ( v ) return false; //确认目标节点不存在
   Rank r = _hot->key.search ( e ); //在节点_hot的有序关键码向量中查找合适的插入位置
   _hot->key.insert ( r + 1, e ); //将新关键码插至对应的位置
   _hot->child.insert ( r + 2, NULL ); //创建一个空子树指针
   _size++; //更新全树规模
   solveOverflow ( _hot ); //如有必要，需做分裂
   return true; //插入成功
}


template <typename T> bool BTree<T>::remove ( const T& e ) { //从BTree树中删除关键码e
   BTNodePosi(T) v = search ( e ); if ( !v ) return false; //确认目标关键码存在
   Rank r = v->key.search ( e ); //确定目标关键码在节点v中的秩（由上，肯定合法）
   if ( v->child[0] ) { //若v非叶子，则e的后继必属于某叶节点
      BTNodePosi(T) u = v->child[r+1]; //在右子树中一直向左，即可
      while ( u->child[0] ) u = u->child[0]; //找出e的后继
      v->key[r] = u->key[0]; v = u; r = 0; //并与之交换位置
   } //至此，v必然位于最底层，且其中第r个关键码就是待删除者
   v->key.remove ( r ); v->child.remove ( r + 1 ); _size--; //删除e以及其下两个外部节点之一
   solveUnderflow ( v ); //如有必要，需做旋转或合并
   return true;
}

