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
