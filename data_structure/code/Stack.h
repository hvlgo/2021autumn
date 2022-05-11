#include "Vector.h"
template <typename T>
class Stack: public Vector<T>{
public:
    void push(T const & e){
        push_back(e);
    }
    T pop(){
        return erase(m_size - 1);
    }
    T& top(){
        return m_data[m_size - 1];
    }
};