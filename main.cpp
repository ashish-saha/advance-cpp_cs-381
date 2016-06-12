
#include <iostream>
#include<fstream>
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
private:
    node<T>* head;
public:
    linkedList () {
        head = new node <T>();
    }
    
    node<int>* &return_head () {
        return head->return_next();
    }
    
    void append (node<T>* n) {
        node<T>* p = head;
        while (p->return_next() != NULL) {
            p=p->return_next();
        }
        p->return_next() = n;
    }
};

template <class T>
void print_list (node<T> *p){
    while (p){
        cout << p->return_co() << "x" << p->return_ex() << endl;
        p=p->return_next();
    }
    cout << endl;
}






int main(int argc, const char * argv[]) {
    ifstream infile;
    infile.open ("/Users/deep/desktop/input.txt");
    int x;
    int y;
    linkedList<int>* list = new linkedList<int> ();
    while (infile >> x) {
        int co = x;
        infile >> y;
        int ex = y;
        node <int>* a = new node<int> (co,ex);
        list->append(a);
        
    }
    print_list<int> (list->return_head());
    infile.close();
    return 0;
}
