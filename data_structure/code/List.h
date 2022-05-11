typedef int Rank; //秩
#define ListNodePosi(T) ListNode<T>* //列表节点位置

template <typename T>
struct ListNode { 
//列表节点模板类（以双向链表形式实现）
T data; ListNodePosi(T) pred; ListNodePosi(T) succ; //数值、前驱、后继
// 构造函数
   ListNode() {} //针对header和trailer的构造
   ListNode ( T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL )
      : data ( e ), pred ( p ), succ ( s ) {} //默认构造器
// 操作接口
   ListNodePosi(T) insertAsPred(T const& e); //紧靠当前节点之前插入新节点
   ListNodePosi(T) insertAsSucc(T const& e); //紧随当前节点之后插入新节点
};

template <typename T> ListNodePosi(T) ListNode<T>::insertAsPred ( T const& e ) {
   ListNodePosi(T) x = new ListNode ( e, pred, this ); //创建新节点
   pred->succ = x; this->pred = x; //设置正向链接
   return x; //返回新节点的位置
}

template <typename T> ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e ) {
    ListNodePosi(T) x = new ListNode(e, this, succ);
    this->succ = x; succ->pred = x;
    return x;
}


template <typename T> class List { //列表模板类
private:                                   //规模、头哨兵、尾哨兵
   int _size; ListNodePosi(T) header; ListNodePosi(T) trailer; 
protected:
   void init();                                //列表创建时的初始化
   int clear();                               //清除所有节点
   void copyNodes ( ListNodePosi(T) p, int n); //复制列表中自位置p起的n项
public:
// 构造函数
   List() { init(); } //默认
   List ( List<T> const& L); //整体复制列表L
   List ( List<T> const& L, Rank r, int n);//复制列表L中自第r项起的n项
   List ( ListNodePosi(T) p, int n); //复制列表中自位置p起的n项
// 析构函数
   ~List(); //释放（包含头、尾哨兵在内的）所有节点


template <typename T> 
void List<T>::init() { //列表初始化，在创建列表对象时统一调用
   header = new ListNode<T>; //创建头哨兵节点
   trailer = new ListNode<T>; //创建尾哨兵节点
   header->succ = trailer; header->pred = NULL;
   trailer->pred = header; trailer->succ = NULL;
   _size = 0; //记录规模
}

template <typename T> 
//重载下标操作符，以通过秩直接访问列表节点（虽方便，效率低，需慎用）
T& List<T>::operator[] ( Rank r ) const 
{
   ListNodePosi(T) p = first();    //从首节点出发
   while ( 0 < r-- ) p = p->succ;  //顺数第r个节点即是
   return p->data;                 //目标节点，返回其中所存元素
}

template <typename T> 
ListNodePosi(T) List<T>::insertAsFirst ( T const& e )
{  _size++; return header->insertAsSucc (e); }      //e当作首节点插入

template <typename T> 
ListNodePosi(T) List<T>::insertAsLast ( T const& e )
{  _size++; return trailer->insertAsPred (e); }     //e当作末节点插入

template <typename T> 
ListNodePosi(T) List<T>::insertA ( ListNodePosi(T) p, T const& e )
{  _size++; return p->insertAsSucc (e); }    //e当作p的后继插入（After）

template <typename T> 
ListNodePosi(T) List<T>::insertB ( ListNodePosi(T) p, T const& e )
{  _size++; return p->insertAsPred (e); }    //e当作p的前驱插入（Before）

template <typename T> T List<T>::remove ( ListNodePosi(T) p ) {
   T e = p->data;                    //备份待删除节点的数值（假定T类型可直接赋值）
   p->pred->succ = p->succ; p->succ->pred = p->pred;             //后继、前驱
   delete p; _size--;                                     //释放节点，更新规模
   return e;                                                  //返回备份的数值
}

template <typename T> List<T>::~List() //列表析构器
{
    int oldSize = _size;
    while ( 0 < _size ) remove ( header->succ ); 
    //反复删除首节点，直至列表变空
    delete header; 
    delete trailer; 
} //清空列表，释放头、尾哨兵节点

template <typename T> ListNodePosi(T) 
//在无序列表内节点p（可能是trailer）的n个（真）前驱中，找到等于e的最后者
List<T>::find (T const& e, int n, ListNodePosi(T)p) const {
   while ( 0 < n-- )            // 对于p的最近的n个前驱，从右向左
        if(e==(p=p->pred)->data) return p; //逐个比对直至命中或越界
   return NULL;            //p越出左边界意味着区间内不含e，查找失败
}                                            //失败时，返回NULL

template <typename T> ListNodePosi(T) 
List<T>::search ( T const& e, int n, ListNodePosi(T) p ) const {
   while ( 0 <= n-- )           //对于p的最近的n个前驱，从右向左逐个比较
        if (((p=p->pred)->data)<=e) break; // assert: 至此位置p必符合输出语义约定——尽管此前最后一次关键码比较可能没有意义（等效于与-inf比较）
   return p; //返回查找终止的位置
} //失败时，返回区间左边界的前驱（可能是header),可通过valid()判断成功与否

template <typename T> 
int List<T>::deduplicate() {                //剔除无序列表中的重复节点
   if ( _size < 2 ) return 0;               //平凡列表自然无重复
   int oldSize = _size;                     //记录原规模
   ListNodePosi(T) p = header; Rank r = 0;  //p从首节点开始
   while ( trailer != ( p = p->succ ) ) {   //依次直到末节点
      ListNodePosi(T) q = find ( p->data, r, p ); 
                                            //在p的r个（真）前驱中查找雷同者
      q ? remove ( q ) : r++;          //若的确存在，则删除之；否则秩加一
   } 
   return oldSize - _size;             //列表规模变化量，即被删除元素总数
}

template <typename T> 
int List<T>::uniquify() {               //成批剔除重复元素，效率更高
   if ( _size < 2 ) return 0;           //平凡列表自然无重复
   int oldSize = _size;                 //记录原规模
   ListNodePosi(T) p = first(); 
   ListNodePosi(T) q;                   //p为各区段起点，q为其后继
   while ( trailer != ( q = p->succ ) ) //反复考查紧邻的节点对(p, q)
      if ( p->data != q->data ) p = q;  //若互异，则转向下一区段
      else remove ( q );                //否则（雷同），删除后者
   return oldSize - _size;              //列表规模变化量，即被删除元素总数
}


};

