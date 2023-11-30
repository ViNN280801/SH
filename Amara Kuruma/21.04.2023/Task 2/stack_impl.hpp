#ifndef STACK_IMPL_HPP
#define STACK_IMPL_HPP

#include "stack.hpp"

template <typename T>
Stack<T>::Stack() : m_data(new T), m_size(1), m_indexTop(0) {}

template <typename T>
Stack<T>::Stack(size_t size)
{
    m_data = new T[size];
    m_size = size;
    m_indexTop = 0;
}

template <typename T>
Stack<T>::~Stack()
{
    delete[] m_data;
    m_data = nullptr;
}

template <typename T>
size_t Stack<T>::size() const { return m_indexTop + 1; }

template <typename T>
bool Stack<T>::empty() const { return m_indexTop == 0; }

template <typename T>
bool Stack<T>::full() const { return m_indexTop == m_size - 1; }

template <typename T>
void Stack<T>::push(const T &data)
{
    if (empty())
        m_data = new T(data);
    m_data[++m_indexTop] = data;
}

template <typename T>
void Stack<T>::push(T &&data)
{
    if (empty())
        m_data = new T(data);
    m_data[++m_indexTop] = std::move(data);
}

template <typename T>
void Stack<T>::pop()
{
    if (empty())
        return;
    m_indexTop--;
}

template <typename T>
T &Stack<T>::top()
{
    T null{};
    return (!empty()) ? m_data[m_indexTop] : null;
}

template <typename T>
const T &Stack<T>::top() const
{
    return (!empty()) ? const_cast<T &>(m_data[m_indexTop]) : T{};
}

template <typename T>
void Stack<T>::clear()
{
    while (!empty())
        pop();
}

#endif // !STACK_IMPL_HPP
