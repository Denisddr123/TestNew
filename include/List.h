#include <iostream>

template <class Data> class List {
public:
class Element{
        public:
        Data d;
        Element * prev;
        Element(Data data = 0) {
            d=data;
            prev = nullptr;
        }
    };
    
    List() {pend = 0; size = 0;}
    ~List();
    void add(Data d);
    Element* find(Data i);
    Element* iterator();
    int remove(Data i);
    Element * insert(Data key, Data d);
    void print(void);
    int getSize() {return size;}
    Data getPend();
    private:
    Element * pend;
    Element * itr;
    int size;
    Element * findNext(Data i);
};

template <class Data> List<Data>::~List() {
    Element *pv = pend;
    while (pv)
    {
        pv = pv->prev;
        delete pend;
        pend = pv;
    }
    size = 0;
    
}

template <class Data> void List<Data>::add(Data d) {
    Element *pv = new Element(d);
    if (pend == 0) {
        pend = pv;
    } else {
        pv->prev = pend;
        pend = pv;
    }
    itr = pend;
    size++;
    
}

template <class Data> typename List<Data>::Element* List<Data>::find(Data d) {
    Element *pv = pend;
    while (pv)
    {
        if (pv->d == d)
        {
            break;
        }
        pv = pv->prev;
    }
    return pv;
}

template <class Data> typename List<Data>::Element * List<Data>::findNext(Data d) {
    Element *pv = pend;
    if (pend->d == d) return 0;
    while (pv)
    {
        if (pv->prev != 0 && pv->prev->d == d)
        {
            break;
        }
        pv = pv->prev;
    }
    return pv;
}

template <class Data> typename List<Data>::Element * List<Data>::iterator() {
    Element *pv = itr;
    if (itr)
    {
        itr = itr->prev;
    }
    
    return pv;
}

template <class Data> int List<Data>::remove(Data key) {
    Element *pkey = pend, *prev;
    if (pend->d == key)
    {
        pend = pend->prev;
        itr = pend;
        delete pkey;
        size--;
        return 1;
    }
    
    pkey = findNext(key);
    if(pkey) {
    prev = pkey->prev;
    pkey->prev = prev->prev;
    delete prev;
    size--;
    return 1;
    }
    return 0;
}

template <class Data> typename List<Data>::Element * List<Data>::insert(Data key, Data d) {
    if (pend->d == key)
    {
        add(d);
        return pend;
    }
    
    Element *next = findNext(key), *prev;
    if (next)
    {
        Element *pv = new Element;
        pv->d = d;
        prev = next->prev;
        pv->prev = prev;
        next->prev = pv;
        size++;
        return pv;
    }
    return 0;
}

template <class Data> void List<Data>::print() {
    Element *pv = pend;
    int i = size-1;
    while (pv)
    {
        std::cout<<pv->d<<" ";
        pv = pv->prev;
        i--;
    }
    std::cout<<std::endl;
}

template <class Data> Data List<Data>::getPend() {
    return pend->d;
}