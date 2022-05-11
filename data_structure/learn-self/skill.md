### 数据的存储
* 数据的性质 -> 用下标对应，便于遍历和查找
* 数据性质的整合 -> 结构体，便于映射
* 性质的计数 -> 总数上限已知 -> 桶计数
* 性质的计数 -> 总数上限未知 -> map计数

### 常数优化
* register int : always used in the for-loop
* space -> time (record the middle value)
* cin -> scanf -> std::ios::sync_with_stdio(false) -> getchar()
    -> fread fwrite(now to use) / streambuf sgetn -> mmap
    warning: when the input is small, the optimize may worse than scanf and printf

### small trick
* 两个数据 -> 一个数据