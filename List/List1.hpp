#ifndef _LIST1_HPP_
#define _LIST1_HPP_

#include <iostream>

using namespace std;

template <class T>
class List_El
{
public:
    List_El *next;
    T data;
};

template <class T>
class List1
{
private:
    List_El<T> *current;
    List_El<T> base;
public:
    List1 () {current = base.next = &base;}
    ~List1 ();
    List1 (const List1<T>&);
    void Add (T data);
    void Del ();
    T Get () const;
    void Step ();
    void Set (T);
    T* NextEl ();
    void ToBase () {current = &base;}
    bool AtEnd() const {return current == &base;}
    bool IsEmpty () const {return base.next == &base;}
    List1<T>& operator = (const List1<T> &);
    template <class K>
    friend ostream& operator << (ostream &, const List1<K>&);
};

template <class T>
List1<T>::~List1()
{
    for (ToBase(); !AtEnd(); Del());
}

template <class T>
List1<T>::List1(const List1<T> &x)
{
    current = base.next = &base;
    List_El<T> *pos = new List_El<T>;
    pos = x.base.next;
    while (pos->next != &x.base)
        {
            Add (pos->data);
            pos = pos->next;
        }
}

template <class T>
void List1<T>::Add (T data)
{
    List_El<T> *pos = new List_El<T>;
    pos->data = data;
    pos->next = current->next;
    current->next = pos;
}

template <class T>
void List1<T>::Del ()
{
    if (AtEnd()) throw -1;
    List_El<T> *pos = current->next;
    current->next = pos->next;
    delete pos;
}

template <class T>
T List1<T>::Get() const
{
    if (AtEnd()) throw -1;
    T data = current->data;
    return data;
}

template <class T>
void List1<T>::Step()
{
    if (AtEnd()) throw -1;
    current = current->next;
}

template <class T>
void List1<T>::Set(T data)
{
    if (current == &base) throw -1;
    current->data = data;
}

template <class T>
T*List1<T>::NextEl()
{
    if (AtEnd()) throw -1;
    return &(current->next->data);
}

template <class T>
ostream& operator << (ostream &out, const List1<T>&x)
{
    bool first(true);
    List_El<T> *pos = new List_El<T>;
    pos = x.base.next;
    out << "(";
    while (pos != &x.base)
    {
        out <<(first ? "" : ", ")<< pos->data;
        pos = pos->next;
        first = false;
    }
    out << ")";
    return out;
}


template <class T>
List1<T>&List1<T>::operator = (const List1<T> &x)
{
    List_El<T> *pos = new List_El<T>;
    pos = x.base.next;
    for (ToBase(); !AtEnd(); Step())
        {
            if (pos != &x.base) current->data = pos->data;
            if (pos == &x.base) Del();
            pos = pos->next;
        }
    while (pos != &x.base)
    {
        Add(pos->data);
        Step();
        pos = pos->next;
    }
    return *this;
}

#endif // _LIST1_HPP_
