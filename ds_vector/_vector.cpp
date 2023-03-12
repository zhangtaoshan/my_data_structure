#include "_vector.hpp"

template <typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi)
{
    // 分配空间，规模清零
    _elem = new T[_capacity = 2 * (hi - lo)];
    _size = 0;
    // 赋值
    while (lo < hi)
    {
        _elem[_size++] = A[lo++];
    }
}

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& V)
{
    if (_elem)
    {
        delete [] _elem;    // 释放原有内容
    }
    copyFrom(V._elem, 0, V.size()); // 整体赋值
    return *this;   // 返回引用，连续赋值
}

template <typename T>
void Vector<T>::expand()
{
    if (_size < _capacity)
    {
        return; // 尚未满员，不必扩容
    }
    if (_capacity < DEFAULT_CAPACITY)
    {
        _capacity = DEFAULT_CAPACITY;   // 不低于最小容量
    }
    // 容量加倍
    T* oldElem  _elem;
    _elem = new T[_capacity <<= 1];
    for (int i = 0; i < _size; ++i)
    {
        _elem[i] = oldElem[i];  // 赋值原来内容
    }
    delete [] oldElem;
}

template<typename T>
void Vector<T>::shrink()
{
    if (_capacity < DEFAULT_CAPACITY << 1)
    {
        return; // 不致收缩到DEFAULT_CAPACITY以下
    }
    if (_size << 2 > _capacity)
    {
        return; // 以25%为界，装填因子：实际规模/数组容量
    }
    // 容量减半
    T* oldElem = _elem;
    _elem = T[_capacity >>= 1];
    // 赋值原来内容
    for (int i = 0; i < _size; ++i)
    {
        _elem[i] = oldElem[i];
    }
    delete [] oldElem;
}

template <typename T>
T& Vector<T>::operator[](Rank r) const
{
    return _elem[r];
}

template <typename T>
void permute(Vector<T>& V)
{
    for (int i = V.size(); i > 0; --i)
    {
        swap(V[i - 1], V[rand() % i]);  // V[i-1]与V[0,i)内的某个数置换
    }
}

template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi)
{
    T* V = _elem + lo;
    for (Rank i = hi - lo; i > 0; --i)
    {
        swap(V[i - 1], V[rand() % i]);  // V[i-1]与V[0,i)内的某个数置换
    }
}

template <typename T>
Rank Vector<T>::find(T const& e, Rank lo, Rank hi) const 
{
    while ((lo < hi--) && (e != _elem[hi]));    // 从后向前顺序查找
    return hi;  // 查询失败
}

template <typename T>
Rank Vector<T>::insert(Rank r, T const& e)
{
    expand();   // 若有必要，扩容
    for (int i = _size; i > r; --i)
    {
        _elem[i] = _elem[i - 1];    // 自后向前移动元素
    }
    // 置入新元素并更新容量
    _elem[r] = e;
    _size++;
    return r;   // 返回秩
}

template <typename T>
int Vector<T>::remove(Rank lo, Rank hi)
{
    if (lo == hi)
    {
        return 0;
    }
    while (hi < _size)
    {
        _elem[lo++] = _elem[hi++];
    }
    _size = lo; // 更新规模'
    shrink();   // 如有必要，缩容
    return hi - lo; // 返回被删除元素数目
}

template <typename T>
T Vector<T>::remove(Rank r)
{
    T e = _elem[r]; // 备份被删除的元素
    remove(r, r + 1);   // 调用区间删除算法
    return e;
}

template <typename T>
int Vector<T>::deduplicate()
{
    int oldSize = _size;    // 记录原规模
    Rank i = 1; // 从_elem[1]开始
    while (i < _size)
    {
        (find(_elem[i], 0, i) < 0) ? i++ : remove(i);
    }
    return oldSize - _size; // 向量规模变化
}

template <typename T>
void Vector<T>::traverse(void(*visit)(T&))
{
    for (int i = 0; i < _size; ++i)
    {
        visit(_elem[i]);
    }
}

template <typename T> template <typename VST>
void Vector<T>::traverse(VST& visit)
{
    for (int i = 0; i < _size; ++i)
    {
        visit(_elem[i]);
    }
}

template <typename T>
int Vector<T>::disordered() const
{
    int n = 0;
    for (int i = 1; i < _size; ++i)
    {
        if (_elem[i - 1] > _elem[i])
        {
            n++;
        }
    }
    return n = 0;
}

template <typename T>
int Vector<T>::uniquify()
{
    Rank i = 0, j = 0;
    while (++j < _size)
    {
        if (_elem[i] != _elem[j])
        {
            _elem[++i] = _elem[j];
        }
    }
    // 删除尾部多余元素
    _size = ++i;
    shrink();
    return j - i;   // 向量规模变化
}
