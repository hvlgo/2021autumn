void RotateR(Node *& ptr) {//左子树比右子树高, 旋转后新根在ptr
    Node *subR = ptr;//要右旋转的结点
    ptr = subR->left;
    subR->left = ptr->right;//转移ptr右边负载
    ptr->right = subR;//ptr成为新根
    ptr->bf = subR->bf = 0; // 修改v和c的平衡因子
};

template <typename T> BinNodePosi(T) BST<T>::connect34 (
   BinNodePosi(T) a, BinNodePosi(T) b, BinNodePosi(T) c,
   BinNodePosi(T) T0, BinNodePosi(T) T1, BinNodePosi(T) T2, BinNodePosi(T) T3
) { // 在确定a,b,c节点及四棵子树情况下组装重构平衡子树
   a->lc = T0; if ( T0 ) T0->parent = a;
   a->rc = T1; if ( T1 ) T1->parent = a; 
   updateHeight ( a ); // 组装左子树并更新高度
   c->lc = T2; if ( T2 ) T2->parent = c;
   c->rc = T3; if ( T3 ) T3->parent = c; 
   updateHeight ( c ); // 组装右子树并更新高度
   b->lc = a; a->parent = b;
   b->rc = c; c->parent = b; 
   updateHeight ( b ); // 组装子树根节点
   return b; //返回该子树新的根节点
}

template <typename T> BinNodePosi(T) 
BST<T>::rotateAt ( BinNodePosi(T) v ) { //v为非空孙辈节点
    BinNodePosi(T) p = v->parent; 
    BinNodePosi(T) g = p->parent; //视v、p和g相对位置分四种情况
    if ( IsLChild ( *p ) ) /* zig */
      if ( IsLChild ( *v ) ) { /* zig-zig */ 
        p->parent = g->parent; //向上联接
        return connect34 (v, p, g, v->lc, v->rc, p->rc, g->rc);
      } 
      else { /* zig-zag */ 
        v->parent = g->parent; //向上联接
        return connect34 (p, v, g, p->lc, v->lc, v->rc, g->rc);
      }
    else  /* zag */
}

template <typename T> bool AVL<T>::remove ( const T& e ) { 
   BinNodePosi(T) & x = search ( e ); if ( !x ) return false; //确认目标存在       
   removeAt ( x, _hot ); _size--; 
                    //先按BST规则删除之（此后，原节点之父_hot及其祖先均可能失衡）
   for ( BinNodePosi(T) g = _hot; g; g = g->parent ) { 
                                           //从_hot出发向上，逐层检查各代祖先g
      if ( !AvlBalanced ( *g ) )                 //一旦发现g失衡
         g = FromParentTo (*g)=rotateAt(tallerChild(tallerChild(g))); //原父亲
      updateHeight ( g ); //并更新其高度（注意：即便g未失衡，高度亦可能降低）
   }            //可能需做Omega(logn)次调整——无论是否做过调整，全树高度均可能降低
   return true; //删除成功
} //若目标节点存在且被删除，返回true；否则返回false
