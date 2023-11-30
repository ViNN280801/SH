#ifndef STACK_HPP
#define STACK_HPP

#include <cstddef>

// Linear data structure that stores template type of object
// Serves as a container of objects that are inserted and removed according
// LIFO rule (Last-In-First-Out) like a stack of plates
template <typename T>
class Stack
{
    T *m_data;
    size_t m_size;
    size_t m_indexTop;

public:
    explicit Stack();
    explicit Stack(size_t size);
    explicit Stack(const Stack &) = default;
    explicit Stack(Stack &&) = default;
    Stack &operator=(const Stack &) = default;
    Stack &operator=(Stack &&) = default;
    virtual ~Stack();

    inline size_t size() const;
    inline bool empty() const;
    inline bool full() const;
    void push(const T &);
    void push(T &&);
    void pop();
    T &top();
    const T &top() const;
    void clear();
};

#endif // !STACK_HPP
