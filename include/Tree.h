#include "List.h"

template <class Data> class Tree {
public:
class Element{
        public:
        Data d;
        bool b;
        bool doubleBlack;
        Element * parent;
        Element * left;
        Element * right;
        Element(Data data = 0) {
            d=data;
            b = true;
            doubleBlack = false;
            left = nullptr;
            right = nullptr;
        }
    };
    Element * root = 0;

    Tree(Data d);
    ~Tree();
    void add(Data d);
    void remove(Data d);
    Data * find(Data d);
    List<Data> * treeToList(List<Data> *list);
private:
    bool uncleIsRed();
    void swapColorGrandAndParent();
    void balanceRestoration();
    void selectRotation();
    void leftLeftRotation();
    void leftRightRotation();
    void rightRightRotation();
    void rightLeftRotation();

    void caseRemoveBlackOrRed();
    void removeBlack();
    void removeRed();
    void brotherIsRed();
    void brotherIsBlack();
    void brotherLeftIsBlack();
    void bLBChildLeftRed();
    void bLBChildRightRed();
    void removeDoubleBlack();
    void brotherRightIsBlack();
    void bRBChildLeftRed();
    void bRBChildRightRed();
    Tree<Data>::Element* elementCloseInValue(Element *el);
    Tree<Data>::Element* findElement(Data d);

    Element *checkElement;
    Element *brother;
};

template <class Data>
Tree<Data>::Tree(Data d)
{
    root = new Element(d);
    root->b=false;
    root->parent = nullptr;
}

template <class Data>
Tree<Data>::~Tree()
{
    List<Tree<Data>::Element *> ls = List<Tree<Data>::Element *>();
    Element *pv = root;
    Element *del;
    while ((ls.getSize() !=0) or (pv != nullptr))
    {
        if (pv != nullptr)
        {
            ls.add(pv);
            pv = pv->left;
        } else {
            pv = ls.getPend();
            del = pv;
            pv = pv->right;
            ls.remove(del);
            delete del;
        }
        
    }
}

template <class Data>
void Tree<Data>::add(Data d) {
    Element * it = root;
    Element * parent;
    while (it)
    {
        parent = it;
        if (d > it->d)
        {
            it = parent->right;
        } else if (d < it->d)
        {
            it = parent->left;
        }
    }
    
    Element *pv = new Element(d);
    pv->parent = parent;
    if (d > parent->d)
    {
        parent->right = pv;
    } else parent->left = pv;

    checkElement = pv;
    if(parent->b) {
        balanceRestoration();
    }
}

template <class Data>
bool Tree<Data>::uncleIsRed() {
    Element *parent = checkElement->parent;
    Element *grand = parent->parent;
    
    Element *uncle = grand->left;
    if (checkElement->parent == uncle)
    {
        uncle = grand->right;
    }
    if (uncle == nullptr)
    {
        return false;
    }
    
    return uncle->b;
}

template <class Data>
void Tree<Data>::balanceRestoration() {
    bool f = false;
    
    f = uncleIsRed();
    if (f)
    {
        swapColorGrandAndParent();
    } else selectRotation();
}

template <class Data>
void Tree<Data>::selectRotation() {
    Element *parent = checkElement->parent;
    Element *grand = parent->parent;
    
    if (grand->left == parent and parent->left == checkElement)
    {
        leftLeftRotation();
    } else if (grand->left == parent and parent->right == checkElement)
    {
        leftRightRotation();
    } else if (grand->right == parent and parent->right == checkElement)
    {
        rightRightRotation();
    } else if (grand->right == parent and parent->left == checkElement)
    {
        rightLeftRotation();
    }
}

template <class Data>
void Tree<Data>::rightRightRotation() {
    Element *parent = checkElement->parent;
    Element *grand = parent->parent;
    Element *greatGrand = grand->parent;
    Element *leftParent = parent->left;

    grand->right = leftParent;
    if (leftParent != nullptr)
    {
        leftParent->parent = grand;
    } 
    grand->parent = parent;
    parent->parent = greatGrand;
    parent->left = grand;
    if (greatGrand != nullptr)
    {
        greatGrand->left == grand ? greatGrand->left = parent : greatGrand->right = parent;
    } else root = parent;

    parent->b = false;
    grand->b = true;
}

template <class Data>
void Tree<Data>::leftRightRotation() {
    Element *parent = checkElement->parent;
    Element *grand = parent->parent;
    Element *greatGrand = grand->parent;
    Element *left = checkElement->left;
    Element *right = checkElement->right;

    checkElement->left = parent;
    checkElement->parent = greatGrand;
    parent->parent = checkElement;

    parent->right = left;
    if (left != nullptr)
    {
        left->parent = parent;
    }
    
    grand->parent = checkElement;
    grand->left = right;
    if (right != nullptr)
    {
        right->parent = grand;
    }
    
    checkElement->right = grand;
    if (greatGrand != nullptr)
    {
        greatGrand->left == grand ? greatGrand->left = checkElement : greatGrand->right = checkElement;
    } else root = checkElement;
   
    checkElement->b = false;
    grand->b = true;
}

template <class Data>
void Tree<Data>::rightLeftRotation() {
    Element *parent = checkElement->parent;
    Element *grand = parent->parent;
    Element *greatGrand = grand->parent;
    Element *left = checkElement->left;
    Element *right = checkElement->right;

    checkElement->right = parent;
    checkElement->parent = greatGrand;

    parent->parent = checkElement;
    parent->left = right;
    if (right != nullptr)
    {
        right->parent = parent;
    }
    
    grand->parent = checkElement;
    grand->right = left;
    if (left != nullptr)
    {
        left->parent = grand;
    }
    
    checkElement->left = grand;
    if (greatGrand != nullptr)
    {
        greatGrand->left == grand ? greatGrand->left = checkElement : greatGrand->right = checkElement;
    } else root = checkElement;

    checkElement->b = false;
    grand->b = true;
}

template <class Data>
void Tree<Data>::leftLeftRotation() {
    Element *parent = checkElement->parent;
    Element *grand = parent->parent;
    Element *greatGrand = grand->parent;
    Element *rightParent = parent->right;
    grand->left = rightParent;
    if (rightParent != nullptr)
    {
        rightParent->parent = grand;
    }
    
    grand->parent = parent;
    parent->parent = greatGrand;
    parent->right = grand;
    if (greatGrand != nullptr)
    {
        greatGrand->left == grand ? greatGrand->left = parent : greatGrand->right = parent;
    } else root = parent;

    parent->b = false;
    grand->b = true;
}

template <class Data>
void Tree<Data>::swapColorGrandAndParent() {
    Element *parent = checkElement->parent;
    Element *grand = parent->parent;
    Element *child = grand->left;
    child->b = false;
    child = grand->right;
    child->b = false;
    if (grand == root)
    {
        return;
    }
    grand->b = true;
    parent = grand->parent;
    if(parent->b) {
        checkElement = grand;
        balanceRestoration();
    }
    
}

template <class Data>
typename Tree<Data>::Element* Tree<Data>::findElement(Data d) {
    Element *pv = root;
    while (pv != nullptr)
    {
        if (d == pv->d)
        {
            break;
        } else if (d < pv->d)
        {
            pv = pv->left;
        } else pv = pv->right;
    }
    if (pv != nullptr)
    {
        return pv;
    } else return nullptr;
}

template <class Data>
Data * Tree<Data>::find(Data d) {
    Element *pv = findElement(d);
    if (pv != nullptr)
    {
        return &pv->d;
    } return nullptr;
}

template <class Data>
void Tree<Data>::remove(Data d) {
    Element *el = findElement(d);
    Element *close;
    if ((el->left != nullptr) and (el->right != nullptr))
    {
        close = elementCloseInValue(el);
        el->d = close->d;
        checkElement = close;
    } else
    {
        checkElement = el;
    }
    caseRemoveBlackOrRed();
    
}

template <class Data>
void Tree<Data>::caseRemoveBlackOrRed() {
    if (checkElement->b)
    {
        removeRed();
    } else removeBlack();
}

template <class Data>
typename Tree<Data>::Element* Tree<Data>::elementCloseInValue(Element *el) {
    Element *right = el->right;
    while (right->left != nullptr)
    {
        right = right->left;
    }
    return right;
}

template <class Data>
void Tree<Data>::removeRed() {
    Element * parent = checkElement->parent;
    parent->left == checkElement ? parent->left = nullptr : parent->right = nullptr;
    delete checkElement;
}

template <class Data>
void Tree<Data>::removeBlack() {
    Element *left = checkElement->left;
    Element *right = checkElement->right;
    if (left != nullptr)
    {
        checkElement->d = left->d;
        checkElement->left = nullptr;
        delete left;
    } else if (right != nullptr) {
        checkElement->d = right->d;
        checkElement->right = nullptr;
        delete right;
    } else {
        removeDoubleBlack();
    }
    
}
template <class Data>
void Tree<Data>::removeDoubleBlack() {
    if (checkElement == root)
    {
        return;
    }
        
    Element *parent = checkElement->parent;
    Element *left, *right;
    left = parent->left;
    right = parent->right;
    if (left == checkElement)
    {
        brother = right;
    } else brother = left;
    
    if (brother->b)
    {
        brotherIsRed();
    } else {
        brotherIsBlack();
    }
}

template <class Data>
void Tree<Data>::brotherIsRed() {
    Element *parent = checkElement->parent;
    Element *grandParent = parent->parent;
    if (parent->left == checkElement)
    {
        Element *left = brother->left;
        parent->right = left;
        parent->b = true;

        left->parent = parent;
        parent->parent = brother;
        brother->b = false;
        brother->left = parent;
        brother->parent = grandParent;

        if (grandParent != nullptr)
        {
            grandParent->left == parent ? grandParent->left = brother : grandParent->right = brother;
        } else root = brother;
        brother = left;
        brotherRightIsBlack();
    } else {
        Element *right = brother->right;
        parent->left = right;
        parent->b = true;

        right->parent = parent;
        parent->parent = brother;
        brother->b = false;
        brother->right = parent;
        brother->parent = grandParent;

        if (grandParent != nullptr)
        {
            grandParent->left == parent ? grandParent->left = brother : grandParent->right = brother;
        } else root = brother;
        brother->right;
        brotherLeftIsBlack();
    }
    
}

template <class Data>
void Tree<Data>::brotherIsBlack() {
    Element *parent = checkElement->parent;
    if (checkElement == parent->left)
    {
        brotherRightIsBlack();
        
    } else brotherLeftIsBlack();
    
}

template <class Data>
void Tree<Data>::brotherLeftIsBlack() {
    Element *left = brother->left;
    Element *right = brother->right;
    Element *parent = checkElement->parent;

    if ((left != nullptr) and left->b)
    {
        bLBChildLeftRed();
    } else if ((right != nullptr) and right->b)
    {
        bLBChildRightRed();
    } else {
        brother->b = true;
        if (parent->b)
        {
            parent->b = false;
            if (!checkElement->doubleBlack)
            {
                parent->right = nullptr;
                delete checkElement;
            }
            
        } else {
            if (!checkElement->doubleBlack)
            {
                delete checkElement;
                parent->right = nullptr;
            }
            checkElement = parent;
            checkElement->doubleBlack = true;
            removeDoubleBlack();
        }
        
    }
    
}

template <class Data>
void Tree<Data>::bLBChildLeftRed() {
    Element *left = brother->left;
    Element *right = brother->right;
    Element *parent = checkElement->parent;
    Element *grandParent = parent->parent;
    bool colorParent = parent->b;

    parent->left = right;
    if (right != nullptr)
    {
        right->parent = parent;
    }
    parent->parent = brother;
    brother->right = parent;
    left->b = false;
    parent->b = false;
    brother->b = colorParent;
    brother->parent = grandParent;

    if (grandParent != nullptr)
    {
        grandParent->left == parent ? grandParent->left = brother : grandParent->right = brother;
    } else root = brother;
    if (!checkElement->doubleBlack)
    {
        parent->right = nullptr;
        delete checkElement;
    }
    
}

template <class Data>
void Tree<Data>::bLBChildRightRed() {
    Element *left = brother->left;
    Element *right = brother->right;
    Element *parent = checkElement->parent;
    Element *grandParent = parent->parent;
    Element *pv = right->left;
    bool colorParent = parent->b;

    brother->right = pv;
    if (pv != nullptr)
    {
        pv->parent = brother;
    }
    
    brother->parent = right;

    right->left = brother;
    pv = right->right;
    right->right = parent;
    right->parent = grandParent;
    right->b = colorParent;

    parent->parent = right;
    parent->left = pv;
    if (pv != nullptr)
    {
        pv->parent = parent;
    }
    parent->b = false;

    if (grandParent != nullptr)
    {
        grandParent->left == parent ? grandParent->left = right : grandParent->right = right;
    } else root = right;
    if (!checkElement->doubleBlack)
    {
        parent->right = nullptr;
        delete checkElement;
    }
}

template <class Data>
void Tree<Data>::brotherRightIsBlack() {
    Element *left = brother->left;
    Element *right = brother->right;
    Element *parent = checkElement->parent;

    if ((right != nullptr) and right->b)
    {
        bRBChildRightRed();
    } else if ((left != nullptr) and left->b)
    {
        bRBChildLeftRed();
    } else {
        brother->b = true;
        if (parent->b)
        {
            parent->b = false;
            if (!checkElement->doubleBlack)
            {
                parent->left = nullptr;
                delete checkElement;
            }
          
        } else {
            if (!checkElement->doubleBlack)
            {
                delete checkElement;
                parent->left = nullptr;
            }
            checkElement = parent;
            checkElement->doubleBlack = true;
            removeDoubleBlack();
        }
        
    }
    
}

template <class Data>
void Tree<Data>::bRBChildRightRed() {
    Element *left = brother->left;
    Element *right = brother->right;
    Element *parent = checkElement->parent;
    Element *grandParent = parent->parent;
    bool colorParent = parent->b;

    parent->right = left;
    if (left != nullptr)
    {
        left->parent = parent;
    }
    parent->parent = brother;
    brother->left = parent;
    right->b = false;
    parent->b = false;
    brother->b = colorParent;
    brother->parent = grandParent;

    if (grandParent != nullptr)
    {
        grandParent->left == parent ? grandParent->left = brother : grandParent->right = brother;
    } else root = brother;
    if (!checkElement->doubleBlack)
    {
        parent->left = nullptr;
        delete checkElement;
    }
}

template <class Data>
void Tree<Data>::bRBChildLeftRed() {
    Element *left = brother->left;
    Element *right = brother->right;
    Element *parent = checkElement->parent;
    Element *grandParent = parent->parent;
    Element *pv = left->right;
    bool colorParent = parent->b;

    brother->left = pv;
    if (pv != nullptr)
    {
        pv->parent = brother;
    }
    
    brother->parent = left;

    left->right = brother;
    pv = left->left;
    left->left = parent;
    left->parent = grandParent;
    left->b = colorParent;

    parent->parent = left;
    parent->right = pv;
    if (pv != nullptr)
    {
        pv->parent = parent;
    }
    parent->b = false;

    if (grandParent != nullptr)
    {
        grandParent->left == parent ? grandParent->left = left : grandParent->right = left;
    } else root = left;
    if (!checkElement->doubleBlack)
    {
        parent->left = nullptr;
        delete checkElement;
    }
}

template <class Data>
List<Data> * Tree<Data>::treeToList(List<Data> *list) {
    List<Tree<Data>::Element *> ls = List<Tree<Data>::Element *>();
    Element *pv = root;
    Element *del;
    while ((ls.getSize() !=0) or (pv != nullptr))
    {
        if (pv != nullptr)
        {
            ls.add(pv);
            pv = pv->left;
        } else {
            pv = ls.getPend();
            list->add(pv->d);
            del = pv;
            pv = pv->right;
            ls.remove(del);
        }
        
    }
    return list;
    
}                                                  