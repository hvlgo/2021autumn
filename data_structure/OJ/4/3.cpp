#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <math.h>
#define maxn 4000010
#define INF 2147483648
using namespace std;

namespace fastIO {
#define BUF_SIZE 10000000 // ! 缓存区大小（应根据实际情况修改）
#define DECIMAL 6   // ! double 类型的 默认输出保留位数(应根据实际情况修改)
#define LL long long
    bool IOerror = 0;//是否读到文件末尾
    inline char nc() { static char buf[BUF_SIZE], * p1 = buf + BUF_SIZE, * pend = buf + BUF_SIZE; if (p1 == pend) { p1 = buf; pend = buf + fread(buf, 1, BUF_SIZE, stdin); if (pend == p1) { IOerror = 1; return -1; } }return *p1++; }
    inline bool blank(char ch) { return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t'; }
    template<class T> inline bool read(T& x) { bool sign = 0; char ch = nc(); x = 0; for (; blank(ch); ch = nc()); if (IOerror)return false; if (ch == '-')sign = 1, ch = nc(); for (; ch >= '0' && ch <= '9'; ch = nc())x = x * 10 + ch - '0'; if (sign)x = -x; return true; }
    inline bool read(unsigned long long& x) { char ch = nc(); x = 0; for (; blank(ch); ch = nc()); if (IOerror)return false; for (; ch >= '0' && ch <= '9'; ch = nc())x = x * 10 + ch - '0'; return true; }
    inline bool read(unsigned int& x) { char ch = nc(); x = 0; for (; blank(ch); ch = nc()); if (IOerror)return false; for (; ch >= '0' && ch <= '9'; ch = nc())x = x * 10 + ch - '0'; return true; }
    inline bool read(double& x) { bool sign = 0; char ch = nc(); x = 0; for (; blank(ch); ch = nc()); if (IOerror)return false; if (ch == '-')sign = 1, ch = nc(); for (; ch >= '0' && ch <= '9'; ch = nc())x = x * 10 + ch - '0'; if (ch == '.') { double tmp = 1; ch = nc(); for (; ch >= '0' && ch <= '9'; ch = nc())tmp /= 10.0, x += tmp * (ch - '0'); }if (sign)x = -x; return true; }
    inline bool read(char* s) { char ch = nc(); for (; blank(ch); ch = nc()); if (IOerror)return false; for (; !blank(ch) && !IOerror; ch = nc())*s++ = ch; *s = 0; return true; }
    inline bool read(char& c) { for (c = nc(); blank(c); c = nc()); if (IOerror) { c = -1; return false; }return true; }
    inline bool read(std::string& s) { s.clear(); char ch = nc(); for (; blank(ch); ch = nc()); if (IOerror)return false; for (; !blank(ch) && !IOerror; ch = nc())s += ch; return true; }
    template<class T, class... U>bool read(T& h, U&... t) { return read(h) && read(t...); }
    struct Ostream_fwrite {
        char* buf, * p1, * pend;
        Ostream_fwrite() { buf = new char[BUF_SIZE]; p1 = buf; pend = buf + BUF_SIZE; }
        inline void out(char ch) { if (p1 == pend) { fwrite(buf, 1, BUF_SIZE, stdout); p1 = buf; }*p1++ = ch; }
        template<class T>inline void print(T x) { static char s[41], * s1; s1 = s; if (!x)*s1++ = '0'; if (x < 0)out('-'), x = -x; while (x)*s1++ = x % 10 + '0', x /= 10; while (s1-- != s)out(*s1); }
        inline void print(char ch) { out(ch); }
        inline void print(unsigned long long x) { static char s[41], * s1; s1 = s; if (!x)*s1++ = '0'; while (x)*s1++ = x % 10 + '0', x /= 10; while (s1-- != s)out(*s1); }
        inline void print(unsigned int x) { static char s[41], * s1; s1 = s; if (!x)*s1++ = '0'; while (x)*s1++ = x % 10 + '0', x /= 10; while (s1-- != s)out(*s1); }
        inline void print(double x, int y = DECIMAL) {
            static LL mul[] = { 1,10,100,1000,10000,100000,1000000,10000000,100000000,
                            1000000000,10000000000LL,100000000000LL,1000000000000LL,10000000000000LL,
                            100000000000000LL,1000000000000000LL,10000000000000000LL,100000000000000000LL };
            if (x < -1e-12)out('-'), x = -x; x *= mul[y];
            LL x1 = (LL)floor(x); if (x - floor(x) >= 0.5)++x1;
            LL x2 = x1 / mul[y], x3 = x1 - x2 * mul[y]; print(x2);
            if (y > 0) { out('.'); for (size_t i = 1; i < y && x3 * mul[i] < mul[y]; out('0'), ++i); print(x3); }

        }
        inline void print(char* s) { while (*s)out(*s++); }
        inline void print(const char* s) { while (*s)out(*s++); }
        inline void print(std::string s) { print(s.c_str()); }
        inline void flush() { if (p1 != buf) { fwrite(buf, 1, p1 - buf, stdout); p1 = buf; } }
        ~Ostream_fwrite() { flush(); }
    }Ostream;
    template<class T>inline void print(T x) { Ostream.print(x); }
    template<class T>inline void println(T x) { Ostream.print(x); Ostream.out('\n'); }
    inline void print(double x, int y = DECIMAL) { Ostream.print(x, y); }
    inline void println(double x, int y = DECIMAL) { Ostream.print(x, y); Ostream.out('\n'); }
    template<class T, class... U>void print(const T& h, const U&... t) { print(h); Ostream.out(' '); print(t...); }
    template<class T, class... U>void println(const T& h, const U&... t) { print(h); Ostream.out(' '); println(t...); }
    inline void flush() { Ostream.flush(); }
    // ! C   int,long long ,__int128,unsigned long long,unsigned int,double,char[],char
    // ! c++ string
#undef LL
#undef DECIMAL
#undef BUF_SIZE
};
using namespace fastIO;
int n, m;

struct pri{
    long long int  val;
    string name;
    bool operator < (const pri& other) const
    {
        if (val > other.val) return true;
        else if (val == other.val && name > other.name) return true;
        return false;
    }
};
class heap{
    pri data[maxn];
    int count = 0;
public:
    void insert(pri elem)
    {
        data[count++] = elem;
        percolateUp(count - 1, data[count - 1]);
    }
    void percolateUp(int index, pri val)
    {
        int parentIndex = (index - 1) /2;
        while (index > 0 && (data[parentIndex] < val))
        {
            data[index] = data[parentIndex];
            index = parentIndex;
            parentIndex = (index - 1) / 2;
        }
        data[index] = val;
    }
    pri pop()
    {
        pri val = data[count - 1];
        data[count - 1] = data[0];
        count--;
        percolateDown(0, val);
        return data[count];
    }
    void percolateDown(int child, pri val)
    {
        int index = child;
        int maxchild = 2 * (index + 1);
        bool godown = true;
        while (godown && maxchild < count)
        {
            godown = false;
            if (data[maxchild] < data[maxchild - 1])
                --maxchild;
            if (val < data[maxchild])
            {
                godown = true;
                data[index] = data[maxchild];
                index = maxchild;
                maxchild = 2 * (index + 1);
            }
        }
        if (maxchild == count)
        {
            if (val < data[maxchild - 1])
            {
                data[index] = data[maxchild - 1];
                index = maxchild - 1;
            }
        }
        data[index] = val;
    }
    void build()
    {
        count = n;
        for (int i = 0; i < n; i++)
        {
            read(data[i].val, data[i].name);
        }
        if (count < 2) return;
        int parent = (count) / 2 - 1;
        while (1)
        {
            percolateDown(parent, data[parent]);
            if (parent == 0) return;
            --parent;
        }
    }
    bool empty()
    {
        return count == 0;
    }
};
heap h;
int main()
{
    read(n, m);
    h.build();
    while (m--)
    {
        if (h.empty()) return 0;
        pri tmp = h.pop();
        println(tmp.name);
        if (tmp.val < INF)
        {
            tmp.val *= 2;
            h.insert(tmp);
        }
    }

}