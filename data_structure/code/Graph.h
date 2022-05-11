template <typename Tv> struct Vertex { //顶点对象
   Tv data;                            //数据
   int inDegree, outDegree;            //出入度数
   VStatus status;  //顶点遍历的状态,包括UNDISCOVERED, DISCOVERED, VISITED
   int dTime, fTime;                   //时间标签，用于遍历
   int parent; int priority;           //在遍历树中的父节点、优先级数
   Vertex ( Tv const& d = ( Tv )0 ) : //构造新顶点
      data(d), inDegree(0), outDegree(0), dTime(-1), fTime(-1),  
      status(UNDISCOVERED), parent(-1), priority(INT_MAX) {}
};

template <typename Te> struct Edge {   //边对象
   Te data;                            //数据
   int weight;                         //权重
   EType type;  //边遍历类型, UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD
   Edge (Te const& d, int w) : data(d), weight(w), type(UNDETERMINED) 
   {} //构造
};

template <typename Tv, typename Te> //顶点类型、边类型
class GraphMatrix : public Graph<Tv, Te> { 
                                //基于向量，以邻接矩阵形式实现的图
private:
   Vector<Vertex<Tv>> V;            //顶点集（向量）
   Vector<Vector<Edge<Te>*>> E;  //边集（邻接矩阵）
public:
   GraphMatrix() { n = e = 0; }         //构造
   ~GraphMatrix() {                     //析构
      for ( int j = 0; j < n; j++ )     //所有动态创建的
         for ( int k = 0; k < n; k++ )  //边记录
            delete E[j][k];             //逐条清除
}


// 顶点的基本操作：查询第i个顶点（0 <= i < n）
   virtual Tv& vertex ( int i ) { return V[i].data; }         //数据
   virtual int inDegree ( int i ) { return V[i].inDegree; }   //入度
   virtual int outDegree ( int i ) { return V[i].outDegree; } //出度
   virtual int firstNbr ( int i ) { return nextNbr ( i, n ); } //首个邻接顶点
   virtual int nextNbr ( int i, int j ) 
                        //相对于顶点j的下一邻接顶点（改用邻接表可提高效率）
   { while (( -1 < j ) && ( !exists ( i, --j ) ) ); return j; } //逆向线性试探
   virtual VStatus& status ( int i ) { return V[i].status; } //状态
   virtual int& dTime ( int i ) { return V[i].dTime; } //时间标签dTime
   virtual int& fTime ( int i ) { return V[i].fTime; } //时间标签fTime
   virtual int& parent ( int i ) { return V[i].parent; } //在遍历树中的父亲
   virtual int& priority ( int i ) { return V[i].priority; } //在遍历树中的优先级数

// 边的基本操作
   virtual bool exists ( int i, int j ) //边(i, j)是否存在
   { return ( 0 <= i ) && ( i < n ) && ( 0 <= j ) && ( j < n ) && E[i][j] != NULL; }
   virtual EType & type ( int i, int j ) { return E[i][j]->type; } //边(i, j)的类型
   virtual Te& edge ( int i, int j ) { return E[i][j]->data; } //边(i, j)的数据
   virtual int& weight ( int i, int j ) { return E[i][j]->weight; } //边(i, j)的权重
};

template <typename Tv, typename Te> //顶点类型、边类型
class GraphMatrix : public Graph<Tv, Te> { 
                                //基于向量，以邻接矩阵形式实现的图
private:
   Vector<Vertex<Tv>> V;            //顶点集（向量）
   Vector<Vector<Edge<Te>*>> E;  //边集（邻接矩阵）
public:
   GraphMatrix() { n = e = 0; }         //构造
   ~GraphMatrix() {                     //析构
      for ( int j = 0; j < n; j++ )     //所有动态创建的
         for ( int k = 0; k < n; k++ )  //边记录
            delete E[j][k];             //逐条清除
}

};


virtual int insert ( Tv const& vertex ) {         //插入顶点，返回编号
   for ( int j = 0; j < n; j++ ) 
       E[j].insert ( NULL );                     //各顶点预留一条潜在的关联边
   n++;                                          // 顶点数目加1
   E.insert(Vector<Edge<Te>*> (n,n,(Edge<Te>*)NULL)); //创建新顶点对应的边向量
   return V.insert (Vertex<Tv>(vertex));         //顶点向量增加一个顶点
}

 virtual Tv remove ( int i ) { //删除第i个顶点及其关联边（0 <= i < n）
      for ( int j = 0; j < n; j++ )                   //所有出边
         if ( exists ( i, j ) ) { 
             delete E[i][j]; V[j].inDegree--;         //逐条删除
         } 
      E.remove ( i ); n--;                            //删除第i行
      Tv vBak = vertex ( i ); V.remove ( i );         //删除顶点i
      for ( int j = 0; j < n; j++ )                   //所有入边
         if ( Edge<Te> * e = E[j].remove ( i ) ) { 
             delete e; V[j].outDegree--;              //逐条删除
         } return vBak;                               //返回被删除顶点的信息
 }

virtual void insert ( Te const& edge, int w, int i, int j ) { 
                                         //插入权重为w的边e = (i, j)
     if ( exists ( i, j ) ) return;      //确保该边尚不存在
     E[i][j] = new Edge<Te> ( edge, w ); //创建新边
     e++;                                //更新边计数
     V[i].outDegree++;                   //更新关联顶点度数
     V[j].inDegree++;                    //更新关联顶点度数
}
virtual Te remove ( int i, int j ) {     //删除顶点i和j之间的联边
     Te eBak = edge ( i, j );            //备份后删除边记录
     delete E[i][j]; E[i][j] = NULL; 
     e--;                                //更新边计数
     V[i].outDegree--; V[j].inDegree--;  //更新关联顶点的度数
     return eBak; //返回被删除边的信息
}


// ! 邻接表实现
class Graph{
private:
   Vector< Vertex< Tv > > V;     //顶点集（向量）
   Vector< List< Edge<Te> *> > E; //边集（邻接表）
   template <typename Te> struct Edge { Te data;    //边的数据
   int weight; //边的权重
   EType type; //边的类型
   int v; //边指向的顶点(新增)
};



template <typename Tv, typename Te> //广度优先搜索BFS算法（全图）
void Graph<Tv, Te>::bfs ( int s ) {
   reset(); int clock = 0; int v = s; //初始化
   do //逐一检查所有顶点
      if ( UNDISCOVERED == status ( v ) ) //一旦遇到尚未发现的顶点
         BFS ( v, clock ); //即从该顶点出发启动一次BFS
   while ( s != ( v = ( ++v % n ) ) ); //按序号检查，故不漏不重
}
template <typename Tv, typename Te> //广度优先搜索BFS算法（单个连通域）
void Graph<Tv, Te>::BFS ( int v, int& clock ) { 
   Queue<int> Q; status ( v ) = DISCOVERED; Q.enqueue ( v ); //初始化起点
   while ( !Q.empty() ) { //在Q变空之前，不断
      int v = Q.dequeue(); dTime ( v ) = ++clock; //取出队首顶点v
      for ( int u = firstNbr ( v ); -1 < u; u = nextNbr ( v, u ) ) //枚举v邻居
         if ( UNDISCOVERED == status ( u ) ) { //若u尚未被发现，则
            status ( u ) = DISCOVERED; Q.enqueue ( u ); //发现该顶点
            type ( v, u ) = TREE; parent ( u ) = v; //引入树边拓展支撑树
         } else { //若u已被发现，或者甚至已访问完毕，则
            type ( v, u ) = CROSS; //将(v, u)归类于跨边
         }
      status ( v ) = VISITED; //至此，当前顶点访问完毕
   }
}
void Graph<Tv, Te>::DFS ( int v) {
   Stack<int> S; 
   S.push ( v );  
   while ( !S.empty() ) {
      int v = S.pop(); 
      status ( v ) = DISCOVERED;
      for ( int u = firstNbr ( v ); 
             -1 < u; u = nextNbr ( v, u ) )
         if ( UNDISCOVERED == status ( u ) ) {
            S.push (u); 
         //   status (u) = DISCOVERED;
         }
   }
}

template <typename Tv, typename Te> //深度优先搜索DFS算法（单个连通域）
void Graph<Tv, Te>::DFS ( int v) {
   status (v) = DISCOVERED;    //设置v已被访问，此处可加代码，如打印等
   for (int u = firstNbr ( v ); -1 < u; u = nextNbr ( v, u )) 
       if (UNDISCOVERED == status ( u ) )  DFS ( u ); //深搜v所有未访问过邻居u
   status (v) = VISITED;
}


template <typename Tv, typename Te> //深度优先搜索DFS算法（全图）
void Graph<Tv, Te>::dfs ( int s ) { //assert: 0 <= s < n
   reset(); int clock = 0; int v = s; //初始化
   do //逐一检查所有顶点
      if ( UNDISCOVERED == status ( v ) ) //一旦遇到尚未发现的顶点
         DFS ( v, clock ); //即从该顶点出发启动一次DFS
   while ( s != ( v = ( ++v % n ) ) ); //按序号检查，故不漏不重
}


 switch ( status ( u ) ) { //并视其状态分别处理
         case UNDISCOVERED: //u尚未发现，意味着支撑树可在此拓展
            type ( v, u ) = TREE; parent ( u ) = v; DFS ( u, clock ); break;
         case DISCOVERED: //u已被发现但尚未访问完毕，应属被后代指向的祖先
            type ( v, u ) = BACKWARD; break;
         default: //u已访问完毕（VISITED，有向图），则视承袭关系分为前向边或跨边
            type ( v, u ) = ( dTime ( v ) < dTime ( u ) ) ? FORWARD : CROSS; break;
}

template <typename Tv, typename Te> //深度优先搜索DFS算法（单个连通域）
void Graph<Tv, Te>::DFS ( int v, int& clock ) { //assert: 0 <= v < n
   dTime ( v ) = ++clock; status ( v ) = DISCOVERED; //发现当前顶点v
   for ( int u = firstNbr ( v ); -1 < u; u = nextNbr ( v, u ) ) //枚举v的所有邻居u
      switch ( status ( u ) ) { //并视其状态分别处理
         case UNDISCOVERED: //u尚未发现，意味着支撑树可在此拓展
            type ( v, u ) = TREE; parent ( u ) = v; DFS ( u, clock ); break;
         case DISCOVERED: //u已被发现但尚未访问完毕，应属被后代指向的祖先
            type ( v, u ) = BACKWARD; break;
         default: //u已访问完毕（VISITED，有向图），则视承袭关系分为前向边或跨边
            type ( v, u ) = ( dTime ( v ) < dTime ( u ) ) ? FORWARD : CROSS; break;
      }
   status ( v ) = VISITED; fTime ( v ) = ++clock; //至此，当前顶点v方告访问完毕
}

void minSpanTreePrim(MGraph g){
    int min, i, j, k; int pred[MAXVEX];int cutcost[MAXVEX];
    cutcost[0] = 0; //0节点直接加入生成树，其割边权重为0
    precede[0] = 0; //0节点前驱为自己
    for (i = 1; i<g.numVertexes; i++){ 
        //将节点0加入后，更新其他每个节点的割边权重
        cutcost[i] = g.arc[0][i]; //割边权重更新(初始化)
        pred[i] = 0; // 初始化各节点的前驱为节点0
    }
    for (i = 1; i<g.numVertexes; i++){ //循环nV-1次,查找最小割边加入节点加入
        min = INFINITY; // 设置最小
        for (j = 1; j<g.numVertexes; j++){ // 循环节点1至节点nV-1，判断哪个节点加入生成树
            if (cutcost[j] != 0 && cutcost[j]<min){ 
                 min = cutcost[j]; // 更新最小割边权重为j的割边权重
                 k = j; // 设置j为当前生成树准备加入的节点
            }
        }
        printf("(%d,%d)", pred[k], k); //k加入生成树，并输出其前驱
        cutcost[k] = 0;//表示该点k已经加入生成树
        for (j = 1; j<g.numVertexes; j++){//该循环检查在k加入后，各顶点割边是否权重是否更新
            if (cutcost[j] != 0 && g.arc[k][j]<cutcost[j]){
                cutcost[j] = g.arc[k][j]; // j点的割边权重更新
                pred[j] = k; // 设置j点的割边连接的点k
            }
        }
    }
}

void Dijkstra(MGraph g,int v0){
    int min,i,j,k; bool inTree[MAXVEX]; 
    int mindist[MAXVEX]; //当前每个节点的最短路径
    int pred[MAXVEX];    //每个节点的前驱
    for (int i = 0; i < g.numVertexes; ++i){
        mindist[i] = g.arc[v0][i]; //节点的初始最短距离为与v0的直接距离
        inTree[i] = false;    //初始都未用过该点
        if (mindist[i] == INFINITY) pred[i] = -1;
        else pred[i] = v0;  //设置前驱
    }
    inTree[v0] = true;  //节点v0为起始顶点  mindist[v0] = 0;
    for (i = 1; i < g.numVertexes; i++){//循环nV-1次加新节点
        min = INFINITY;
        for (j = 0; j < g.numVertexes; ++j) 
        if ((!inTree[j]) && mindist[j]<min){ 
             k = j; // 保存当前节点号 
             min = mindist[j]; //更新最小长度
        }
        inTree[k] = true; // 设置节点k进入最短路径树
        printf("(%d,%d,%d)", pred[k], k, mindist[k]); //k加入最短路径树，并输出其前驱
        for (j = 0; j < g.numVertexes; j++) // 循环k的所有邻域节点进行
        if ((!inTree[j]) && g.arc[k][j]<INFINITY){ //k的邻域节点
             if (mindist[k] + g.arc[k][j] < mindist[j]){ //通过k点找更短的路径  
                   mindist[j] = mindist[k] + g.arc[k][j];  //更新j的最短路径 
                   pred[j] = k;    //记录j的前驱顶点为k 
             }
        }
    }
}




