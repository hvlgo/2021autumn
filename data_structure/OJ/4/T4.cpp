#include <iostream>
#include <string.h>
#include <cmath>
#include <stdio.h>
const long long int MAX = (long long int)1 << 32;
using namespace std;

struct Node
{
	char name[10];
	long long int priority;

    friend bool operator < (const Node &x, const Node &y)
    {
        if (x.priority != y.priority)
            return x.priority < y.priority;
        return strcmp(x.name, y.name) < 0;
    }
};

int n, m;
//Node myHeap[4000005];
Node* myHeap;

//bool smaller(const Node &n1, const Node &n2)  //1比2小
//{
//    if (n1.priority < n2.priority)
//        return true;
//    else if (n1.priority == n2.priority)
//    {
//        if (strcmp(n1.name, n2.name) == -1)
//            return true;
//    }
//    return false;
//}

int best(int parent)
{
    int tmp = parent;
    int rChild = (parent << 1) + 2;
    int lChild = rChild - 1;
    if (rChild < n)
    {
        tmp = (myHeap[rChild] < myHeap[lChild]) ? rChild : lChild;
        tmp = (myHeap[tmp] < myHeap[parent]) ? tmp : parent;
    }
    else if (rChild >= n && lChild < n)
        tmp = (myHeap[lChild] < myHeap[parent]) ? lChild : parent;
    return tmp;
}

void percolateDown(int index)
{
//父节点若大于子节点，则与其较小的孩子交换，迭代该过程
    int b = best(index);

    while (b != index) 
    {
        swap(myHeap[index], myHeap[b]);   //交换 
        index = b;                            //该交换节点索引下移  
        b = best(index);
    }

    //if (Child == n) 
    //{
    //    if (smaller(myHeap[Child - 1], value)) //令左子节点值为交换值
    //    {          
    //        myHeap[index] = myHeap[Child - 1];
    //        index = Child - 1;
    //    }
    //}
    //myHeap[index] = value;
}

//小顶堆
void makeHeap()
{
	for (int i = n - 1; i >= 0; i--)
	{
		percolateDown(i);
	}
}

void getMin()
{
    //cout << myHeap[0].name << endl;
    printf("%s\n", myHeap[0].name);
    myHeap[0].priority <<= 1;
    if (myHeap[0].priority >= MAX)
    {
        myHeap[0] = myHeap[n - 1];
        n--;
    }
    percolateDown(0);
}

int main()
{
	//cin >> n >> m;
    scanf("%d%d", &n, &m);
	myHeap = new Node[n];
	for (int i = 0; i < n; i++)
	{
		//cin >> myHeap[i].priority >> myHeap[i].name;
        scanf("%lld%s", &myHeap[i].priority, myHeap[i].name);
	}

	makeHeap();

    /*for (int i = 0; i < n; i++)
    {
        cout << myHeap[i].priority << ' ' << myHeap[i].name << endl;
    }*/

    for (int i = 0; n && i < m; i++)
    {
        getMin();
    }

    return 0;
}