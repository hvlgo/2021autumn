template <typename T> class Vector {

public:
    static constexpr const int EXPAND_RATIO = 2;
    static constexpr const int EXPAND_FACTOR = 2;

    int m_size;
    int m_capacity;
    T*  m_data;

    void expand() {
        if (m_data == nullptr)
            return;
        T* newData = new T[m_capacity * EXPAND_FACTOR];
        for (int i = 0; i < m_size; i++)
            newData[i] = m_data[i];
        delete[] m_data;
        m_data = newData;
        m_capacity = m_capacity * EXPAND_FACTOR;
    }

public:
    Vector(int t_capacity = 15) : m_capacity(t_capacity) {
        m_data = new T[t_capacity];
        m_capacity = t_capacity;
        m_size = 0;
    }

    ~Vector() {
        if (m_data != nullptr)
            delete[] m_data;
    }

    Vector(Vector<T>&& t_src) {
        m_capacity = t_src.m_capacity;
        m_size = t_src.m_size;
        m_data = t_src.m_data;
        t_src.m_data = nullptr;
    }

    Vector& operator=(const Vector<T>& src) {
        if (this != &src) {
            if (m_data != nullptr)
                delete[] m_data;
            m_capacity = src.m_capacity;
            m_size = src.m_size;
            m_data = new T[m_capacity];
            for (int i = 0; i < src.m_size; i++)
                m_data[i] = src.m_data[i];
        }
        return *this;
    }

    Vector(const Vector<T>& t_src) {
        m_capacity = t_src.m_capacity;
        m_size = t_src.m_size;
        m_data = new T[m_capacity];
        for (int i = 0; i < t_src.m_size; i++)
            m_data[i] = t_src.m_data[i];
    }

    bool empty() const {
        return m_size == 0;
    }

    int size() const {
        return m_size;
    }

    void push_back(T e) {
        m_data[m_size++] = e;
        if (m_size * 2 > m_capacity)
            expand();
    }

    T& operator[](int index) {
        if (index >= 0 && index < m_size)
            return m_data[index];
        throw("index out of range");
    }

    void insert(T e, int index) {
        if (m_size == m_capacity)
            expand();
        for (int i = m_size; i > index; i--)
        {
            m_data[i] = m_data[i - 1]; 
        }
        m_data[index] = e;
        m_size++;
    }

    T erase(int index)
    {
        T e = m_data[index];
        for (int i = index; i < m_size - 1; i++)
        {
            m_data[i] = m_data[i + 1];
        }
        m_size--;
        return e;
    }
};