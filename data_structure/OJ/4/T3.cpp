#include <iostream>
#include <string>
#define maxn 4000005
#define INF 1e16
using namespace std;

inline int lson(int x) {
    return x << 1;
}

inline int rson(int x) {
    return x << 1 | 1;
}

inline int par(int x) {
    return x >> 1;
}

string s[maxn];

struct Pair {
    long long first;
    int       second;
    bool      operator<(const Pair& other) {
        if (first != other.first)
            return first < other.first;
        return s[second] < s[other.second];
    }
};

Pair heap[maxn];
int  tot, n, m;

void init() {
    for (int i = 1; i <= min(n << 1, maxn - 1); i++)
        heap[i].first = INF;
    heap[0].first = 0;
}

Pair top() {
    return heap[1];
}

void upMaintain(int x) {
    if (x == 1)
        return;
    if (heap[x] < heap[par(x)]) {
        swap(heap[x], heap[par(x)]);
        upMaintain(par(x));
    }
}

void downMaintain(int x) {
    if (heap[lson(x)].first == INF || lson(x) >= maxn)
        return;
    if (heap[lson(x)] < heap[rson(x)]) {
        if (heap[lson(x)] < heap[x]) {
            swap(heap[x], heap[lson(x)]);
            downMaintain(lson(x));
        }
    }
    else {
        if (heap[rson(x)] < heap[x]) {
            swap(heap[x], heap[rson(x)]);
            downMaintain(rson(x));
        }
    }
}

void push(Pair x) {
    heap[++tot] = x;
    upMaintain(tot);
}

void pop() {
    heap[1] = heap[tot];
    heap[tot].first = INF;
    tot--;
    downMaintain(1);
}

void make_heap(int cnt) {
    if (cnt < 2)
        return;
    int parent = (n - 2) / 2;
    while (parent) {
        downMaintain(parent);
        parent--;
    }
}

inline long long llRead()  //内联函数稍微快一点点
{
    char ch = getchar();
    long long  s = 0, w = 1;
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        s = s * 10 + ch - '0', ch = getchar();
    }
    return s * w;
}
inline string StringRead() {
    string str;
    char   s = getchar();
    //处理多余回车或空格
    while (s == ' ' || s == '\n' || s == '\r') {
        s = getchar();
    }
    //不断读入直到遇到回车或空格
    while (s != ' ' && s != '\n' && s != '\r') {
        str += s;
        s = getchar();
    }
    return str;
}

inline void StringWrite(std::string& str)
{
    int i = 0;
    while (str[i] != '\0')
    {
        putchar(str[i]), i++;
    }
    putchar('\n');
}

int main() {
    cin >> n >> m;
    init();
    for (int i = 1; i <= n; i++) {
        // heap[i].first = llRead();
        // s[i] = StringRead();
        cin >> heap[i].first >> s[i];
        // cin >> heap[i].first;
        // cin >> s[i];
        heap[i].second = i;
    }
    tot = n;
    make_heap(n);
    while (m && tot) {
        Pair tmp = top();
        cout << s[tmp.second] << endl;
        pop();
        tmp.first *= 2;
        if (tmp.first < (1ll << 32))
            push(tmp);
        m--;
    }
    return 0;
}