#include "Vector.h"

template <typename T> // ! 大顶堆
class Heap{
    Vector<T> data;
    int count = 0;
public:
    void insert(T elem){
        data.push_back(elem);
        ++count;
        percolateUp(count - 1, data[count - 1]);
    }
    void percolateUp(int index, T value){
        int parentIndex = (index - 1) / 2;
        while (index > 0 && (data[parentindex] < value)){
            data[index] = data[parentindex];
            index = parentIndex;
            parentIndex = (index - 1) / 2;
        }
        data[index] = value;
    }

    void delMax(){
        T value = data[count - 1];
        data[count - 1] = data[0];
        count--;
        percolateDown(0, value);
    }

    void percolateDown(int childTree, T value){
        int index = childTree;
        int maxChild = 2 * (index + 1);
        bool godown = true;
        while (godown && maxChild < count){
            godown = false;
            if (data[maxchild] < data[maxchild - 1])
                --maxchild;
            if (value < data[maxchild]){
                godown = true;
                data[index] = data[maxchild];
                index = maxChild;
                maxchild = 2 * (index + 1);
            }
        }
        if (maxchild == count){
            if (value < data[maxchild - 1]){
                data[index] = data[maxchild - 1];
                index = maxchild - 1;
            }
        }
        data[index] = value;
    }

    void build(){
        if (count < 2) return;
        int parent = count / 2 - 1;
        while (1){
            percolateDown(parent, data[parent]);
            if (parent == 0) return;
            --parent;
        }
    }
};