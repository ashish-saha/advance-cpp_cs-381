#include <iostream>
#include<fstream>
#include <sstream>      // std::istringstream
using namespace std;

template <class T>
class node {
private:
    T coefficient;
    T exponent;
    node* next;
public:
    node ()             {next = 0;}
    node (T i, T j)     {coefficient = i; exponent = j; next=0;}
    T &return_co()      {return coefficient;}
    T &return_ex()      {return exponent;}
    node* &return_next(){return next;}
};

template <class T>
class linkedList {
    friend class node<T>;
private:
    node<T>* head;
public:
    linkedList () {
        head = new node <T>(99999, 99999);
    }
    
    node<int>* &return_head () {
        return head->return_next();
    }
    
    void append (node<T>* n) {
        node<T>* p = head;
        while (p->return_next() != NULL) {
//            if (n->return_co() ==0)   return;
            if ((n->return_ex() <= p->return_ex()) && (n->return_ex() > p->return_next()->return_ex())) {
                if (n->return_ex() == p->return_ex())   {
                    p->return_co() += n->return_co();
//                    if (p->return_co() ==0)   { delete_Node (p);}
                    return;
                }
                node<T>* temp = p->return_next();
                p->return_next() = n;
                n->return_next() = temp;
                return;
            }
            p=p->return_next();
        }
//        if (n->return_co() ==0)   return;
        if (n->return_ex() == p->return_ex())   {
            p->return_co() += n->return_co();
//            if (p->return_co() ==0)   { delete_Node (p);}
            return;
        }
        p->return_next() = n;
    }
    
    void delete_Node (node<T>* n) {
        node<T>* temp = head;
        node<T>* previous = temp;
        while (temp) {
            if (temp->return_co() == n->return_co()) {
                previous->return_next() = temp->return_next();
            }
            previous = temp;
            temp=temp->return_next();
        }
    }

    linkedList<T>* add( linkedList<T>* s) {
        linkedList<T>* temp = new linkedList ();
        node<T>* this_Head = head;
        node<T>* other_Head = s->head;
        while (other_Head != NULL) {
            node <int>* a = new node<int> (other_Head->return_co(), other_Head->return_ex());
            node <int>* b = new node<int> (this_Head->return_co(), this_Head->return_ex());
            temp->append(a);
            temp->append(b);
            other_Head = other_Head->return_next();
            this_Head = this_Head->return_next();
        }
         return temp;
    }


    linkedList<T>* subtract( linkedList<T>* s) {
        linkedList<T>* temp = new linkedList ();
        node<T>* this_Head = head;
        node<T>* other_Head = s->head;
        while (other_Head != NULL) {
            node <int>* a = new node<int> ((-1)*other_Head->return_co(), other_Head->return_ex());
            node <int>* b = new node<int> (this_Head->return_co(), this_Head->return_ex());
            temp->append(a);
            temp->append(b);
            other_Head = other_Head->return_next();
            this_Head = this_Head->return_next();
        }
        return temp;
    }

    
    
    ~linkedList () {
        node<T>* temp = head;
        while (temp) {
            delete(temp);
            temp = temp->return_next ();
        }
    }
    friend ostream& operator<<(ostream& os, linkedList<T> s);
};

template <class T>
ostream& operator<<(ostream& os, linkedList<T>* s) {
    node<T>* p = s->return_head();
    while (p){
        if (p->return_co() == 0)  {
//            os << 0 << " " << 0 << "  ";
            p=p->return_next();
        }
        else    {
            os << p->return_co() << " " << p->return_ex() << "  ";
            p=p->return_next();
        }
    }
    return os;
};




template <class T>
void print_list (node<T> *p){
    while (p){
        if (p->return_co() == 0)        cout << 0 << " " << 0 << "  ";
        else                            cout << p->return_co() << " " << p->return_ex() << "  ";
        p=p->return_next();
    }
    cout << endl;
}

int main(int argc, const char * argv[]) {
    int size;
    ifstream infile0;
    string line0;
    infile0.open ("/Users/deep/desktop/input.txt");
    while (getline(infile0,line0)){
        size++;
    }
    infile0.close();
    
    
    ifstream infile;
    infile.open ("/Users/deep/desktop/input.txt");
    linkedList<int> *polynomial [size];
    int counter = 0;
    string line;
    int x, y;
    while (getline (infile, line)) {
        istringstream iss(line);
        linkedList<int>* list = new linkedList<int> ();
        polynomial[counter++] = list;
        while (iss >> x >> y) {
            node <int>* a = new node<int> (x,y);
            list->append(a);
        }
//        print_list<int> (list->return_head());
    }

//    for (int i=0; i<size; i++)  cout << i << ". " << polynomial[i] << endl;
    cout << polynomial[3] << endl;
    cout << polynomial [4] << endl;
    cout << polynomial[3]->subtract (polynomial[4]) << endl;
 
    infile.close();
    return 0;
}
