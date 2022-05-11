//  ! there is bucket sort and queue to replace priority queue

#include <stdio.h>
#include <stdlib.h>
#include <queue>
#include <cctype>
using namespace std;
long long cnt[100005];
queue<long long> que;
queue<long long> after;
long long sum;

// inline long long read()
// {
//     int ans = 0;
//     char ch = getchar();
//     while(!isdigit(ch) && ch != '_') ch = getchar();
//     bool sign = false;
//     if (ch == '-') sign = true, ch = getchar();
//     while (ch >= '0' && ch <= '9') ans = ans * 10 + (ch - '0'), ch = getchar();
//     return (sign == true ? -ans : ans);
// }

struct FastIO {
    static const int S = 10;
    int wpos;
    char wbuf[S];
    FastIO() : wpos(0) {}
    inline int xchar() {
        static char buf[S];
        static int len = 0, pos = 0;
        if (pos == len)
            pos = 0, len = fread(buf, 1, S, stdin);
        if (pos == len) exit(0);
        return buf[pos++];
    }
    inline int xuint() {
        int c = xchar(), x = 0;
        while (c <= 32) c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x;
    }
    inline int xint()
    {
        int s = 1, c = xchar(), x = 0;
        while (c <= 32) c = xchar();
        if (c == '-') s = -1, c = xchar();
        for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
        return x * s;
    }
    inline void xstring(char *s)
    {
        int c = xchar();
        while (c <= 32) c = xchar();
        for (; c > 32; c = xchar()) * s++ = c;
        *s = 0;
    }
    inline void wchar(int x)
    {
        if (wpos == S) fwrite(wbuf, 1, S, stdout), wpos = 0;
        wbuf[wpos++] = x;
    }
    inline void wint(long long x)
    {
        if (x < 0) wchar('-'), x = -x;
        char s[24];
        int n = 0;
        while (x || !n) s[n++] = '0' + x % 10, x /= 10;
        while (n--) wchar(s[n]);
        wchar('\n');
    }
    inline void wstring(const char *s)
    {
        while (*s) wchar(*s++);
    }
    ~FastIO()
    {
        if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
    }
} io;

int main()
{
    int n;
    n = io.xint();
    for (int i = 0; i < n; i++)
    {
        int tmp = io.xint();
        cnt[tmp]++;
    }
    for (int i = 0; i < 100005; i++)
    {
        while (cnt[i] != 0)
        {
            que.push(i);
            cnt[i]--;
        }
    }

    for (int i = 1; i < n; i++)
    {
        long long first;
        long long second;
        
        if (que.empty())
        {
            first = after.front();
            after.pop();
        }
        else if (after.empty())
        {
            first = que.front();
            que.pop();
        }
        else if (que.front() <= after.front())
        {
            first = que.front();
            que.pop();
        }
        else
        {
            first = after.front();
            after.pop();
        }

        if (que.empty())
        {
            second = after.front();
            after.pop();
        }
        else if (after.empty())
        {
            second = que.front();
            que.pop();
        }
        else if (que.front() <= after.front())
        {
            second = que.front();
            que.pop();
        }
        else
        {
            second = after.front();
            after.pop();
        }
        long long ans = first + second;
        after.push(ans);
        sum += ans;
    }
    io.wint(sum);
    return 0;
}