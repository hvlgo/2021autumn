#include <iostream>
#include "vector.h"

typedef int Rank;
void insertsort(int data[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int tmp = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > tmp)
        {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = tmp;
    }
}

void Shellsort(int data[], int count){
    int step = 0;
    int auxiliary = 0;
    for (step = count / 2; step > 0; step /= 2)
    {
        for (int i = step; i < count; i++)
        {
            if (data[i] < data[i - step]){
                auxiliary = data[i];
                int j = i - step;
                while (j >= 0 && data[j] > auxiliary)
                {
                    data[j + step] = data[j];
                    j -= step;
                }
                data[j + step] = auxiliary;
            }
        }
    }
}
template <typename T>
void bubblesort(Rank lo, Rank hi) {
	int times = 0; bool exchange = true; // 从第一趟开始
	int nSort = hi - lo;
	while (times < nSort && exchange) {
		exchange = false;      // 某趟是否有交换的标志，初始为无交换
		for (int j = hi - 1; j > lo + times; j--)
                                           //从最后元素开始到第一个未排序元素
			if (_elem[j - 1]>_elem[j]) {//若需要交换则置换元素          
				T temp = _elem[j - 1];
				_elem[j - 1] = _elem[j];
				_elem[j] = temp;
				exchange = true;
			}
		times++;
	}
}

void quickSort(int data[], int l, int r){
    if (l < r){
        int pivotL = l, pivotR = r, x = data[l];
        while (pivotL < pivotR){
            while (pivotL < pivotR && data[pivotR] > x) pivotR--;
            if (pivotL < pivotR) data[pivotL++] = data[pivotR];
            while (pivotL < pivotR && data[pivotL] < x) pivotL++;
            if (pivotL < pivotR) data[pivotR--] = data[pivotL];
        }
        data[pivotL] = x;
        quickSort(data, l, pivotL - 1);
        quickSort(data, pivotL + 1, r);
    }
}

int partition(int data[], int l, int r)
{
        if (l < r){
        int pivotL = l, pivotR = r, x = data[l];
        while (pivotL < pivotR){
            while (pivotL < pivotR && data[pivotR] > x) pivotR--;
            if (pivotL < pivotR) data[pivotL++] = data[pivotR];
            while (pivotL < pivotR && data[pivotL] < x) pivotL++;
            if (pivotL < pivotR) data[pivotR--] = data[pivotL];
        }
        data[pivotL] = x;
        return pivotL + 1; // ! transfer the index to the range rank
}

int quickSelect(int data[], int k, int l, int r)
{
    int pivot = partition(data, l, r);
    if (k == pivot) return data[pivot];
    else if (k < pivot) return quickSelect(data, k, l, pivot - 1);
    else return quickSelect(data, k - pivot - 1, pivot + 1, r);
}

template <typename T>
void Vector<T>::selectSort(Rank lo, Rank hi) {
	for (Rank i = hi - 1; i > lo; i--) { // 从后往前
		int max = i;
		for (Rank j = 0; j < i + 1; j++) { 
					// 遍历前面未排序，选择最大元素
			if (_elem[j] > _elem[max]) 
				max = j;
		}
		if (max != i) {              // 交换
			T temp = _elem[i];
			_elem[i] = _elem[max];
			_elem[max] = temp;
		}
	}
}

static void merge(int data[], int first, int mid, int last, int sorted[])
{
    int i = first, j = mid;
    int k = 0;
    while (i < mid && j < last)
    {
        if (data[i] < data[j])
            sorted[k++] = data[i++];
        else
            sorted[k++] = data[j++];
    }
    while (i < mid) sorted[k++] = data[i++];
    while (j < last) sorted[k++] = data[j++];
    for (int v = 0; v < k; v++)
        data[first + v] = sorted[v];
}

static void mergeSort(int data[], int first, int last, int sorted[]){
    if (first + 1 < last){
        int mid = (first + last) / 2;
        mergeSort(data, first, mid, sorted);
        mergeSort(data, mid, last, sorted);
        merge(data, first, mid, last, sorted);
    }
}
// this is updated version
// template<typename T>
// void Vector<T>::mergeSort(Rank lo, Rank hi)
// {
//     if (hi - lo < 2) return;

//     bool flag = true;
//     for (int i = lo; i < hi - 1; i++)
//         if (A[i] > A[i+1])
//             flag = false, break;
//     if (flag) return;

//     int mi = (lo + hi)/2;
//     mergeSort(lo, mi), mergeSort(mi, hi);
//     merge(lo, mi, hi);
// }

// template <typename T>
// void Vector<T>::merge ( Rank lo, Rank mi, Rank hi ) {
// T* A = _elem + lo;
// int lb = mi - lo; T* B = new T[lb];
// for ( Rank i = 0; i < lb; i++)
//     B[i] = A[i];
// int lc = hi - mi; T* C = _elem + mi;
// for ( Rank i = 0, j = 0, k = 0; (j < lb)||(k < lc);) { 
//     if ( ( j < lb ) && ( ! ( k < lc ) || ( B[j] <= C[k] ) ) ) A[i++] = B[j++];
//     if ( ( k < lc ) && ( ! ( j < lb ) || ( C[k] <  B[j] ) ) ) A[i++] = C[k++];
// }
// delete [] B; 
// } 


template <typename T> 
static Rank binSearch ( T* A, T const& e, Rank lo, Rank hi ) {
   while ( lo < hi ) {                //每步迭代仅需做一次比较判断，有两个分支
      Rank mi = ( lo + hi ) >> 1;     //以中点为轴点
      ( e < A[mi] ) ? hi = mi : lo = mi + 1; //经比较后确定深入[lo, mi)或(mi, hi)
   }                                         //成功查找不能提前终止
   return --lo; //循环结束时，lo为大于e的元素的最小秩，故lo - 1即不大于e的元素的最大秩
} //有多个命中元素时，总能保证返回秩最大者；查找失败时，能够返回失败的位置



template <typename T>
static Rank binSearch(T* A, T const& e, Rank lo, Rank hi)
{
    while (lo < hi){
            Rank mi = ( lo + hi ) >> 1;
            (e > A[mi]) ? lo = mi : hi = mi - 1;
    }
    return ++hi;
}



// ! 单调栈
vector<int> FindFirstBigNum(vector<int>& v){
    int len = v.size();
    vector<int> res(len, -1);
    if(len == 0){
        return res;
    }
    stack<int> st;
    st.push(0);
    for(int i = 1; i < len; i++){
    while(!st.empty() && v[i] > v[st.top()]){
        res[st.top()] = v[i];
        st.pop();
    }
    st.push(i);
}
return res;
}
// ! 单调队列
// deque<int>que;// 双向队列
// for(int i=1;i<=n;i++)
// {
//     while(!que.empty() && a[que.back()]<a[i])
//     {
//         que.pop_back();// 去尾操作
//     }
//     que.push_back(i);// 新元素(的序号) 入队列
//     if(i>=k)// 这个很明显
//     {
//         while(!que.empty() && que.front()<i-k+1)
//         {
//             que.pop_front();// 删头操作 
//         }
//         cout<<a[que.front()]<<" ";// 取解操作
//     }
// }


int * buildNext(char * p){
    size_t m = strlen(p);
    size_t j = 0;
    int * N = new int[m];
    int t = N[0] = -1;
    while (j < m - 1){
        if (0 > t || p[j] == p[t]){
            j++;
            t++;
            N[j] = t;
        }
        else
            t = N[t];
    }
    return N;
}

int match(char * p, char * T){
    int * next = buildNext(p);
    int n = (int) strlen(T), i = 0;
    int m = (int) strlen(p), j = 0;
    while (j < m && i < n){
        if (T[i] == p[j] || j < 0){
            i++;
            j++;
        }
        else
            j = next[j];
    }
    delete [] next;
    return i - j;
}

void Graph<Tv, Te>::TS () {
   Stack<int> S; 
   for(int i=0; i<n; i++)
       if(V[i].inDegree==0) S.push(i);
   if(S.size()==0) return false;
   while ( !S.empty() ) {
       int s = S.pop();
       status ( s ) = DISCOVERED;
       for ( int u = firstNbr ( v ); 
              -1 < u; u = nextNbr ( v, u ) )
           if ( UNDISCOVERED == status ( u ) )
		if((--V[u].inDegree)==0) S.push(u);
	}
   }
   for(int i=0; i<n; i++)
       if(status (s) != DISCOVERED) return false;
   return true;
}
