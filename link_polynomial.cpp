#include <iostream>
#include<fstream>
#include <sstream>      // std::istringstream
using namespace std;

template<class T>
class linkedList;

template <class T>
ostream& operator<<(ostream& os, linkedList<T> l);

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
            return;
        }
        p->return_next() = n;
    }
    
    linkedList<T> operator+(linkedList<T> l){
        linkedList<T> temp;
        node<T>* this_head = head->return_next();
        node<T>* other_head = l.head->return_next();
        while (this_head != NULL) {
            temp.append(new node<T> (this_head->return_co(), this_head->return_ex()));
            this_head = this_head->return_next();
        }
        while (other_head != NULL) {
            temp.append(new node<T> (other_head->return_co(), other_head->return_ex()));
            other_head = other_head->return_next();
        }
        return temp;
    }
    
    linkedList<T> operator-(linkedList<T> l){
        linkedList<T> temp;
        node<T>* this_head = head->return_next();
        node<T>* other_head = l.head->return_next();
        while (this_head != NULL) {
            temp.append(new node<T> (this_head->return_co(), this_head->return_ex()));
            this_head = this_head->return_next();
        }
        while (other_head != NULL) {
            temp.append(new node<T> ((-1)*other_head->return_co(), other_head->return_ex()));
            other_head = other_head->return_next();
        }
        return temp;
    }
    
    ~linkedList () {
//        node<T>* temp = head;
//        while (temp) {
 //           delete(temp);
 //           temp = temp->return_next ();
//        }
    }
    friend ostream& operator<< <T>(ostream& os, linkedList<T> s);
};

template <class T>
ostream& operator<<(ostream& os, linkedList<T> s) {
    node<T>* p = s.head->return_next();
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

    ifstream infile;
    infile.open("/Users/deep/desktop/input.txt");
    string line, line2;
    int x, y;
    while (getline (infile, line)) {
        cout << "Originial ";
        linkedList<int> list;
        istringstream iss (line);
        while (iss >> x >> y)   {
            cout << x << " " << y << " ";
            node<int>* n = new node <int> (x,y);
            list.append(n);
        }
        cout << endl;
        
        getline(infile,line2);
        cout << "Originial ";
        linkedList<int> list2;
        istringstream iss2 (line2);
        while (iss2 >> x >> y)   {
            cout << x << " " << y << " ";
            node<int>* n = new node <int> (x,y);
            list2.append(n);
        }
        
        
        cout << endl;
        cout << "cannonical " << list << endl;
        cout << "cannonical " << list2 << endl;
        cout << "Sum        " << list+list2 << endl;
        cout << "Subtract   " << list-list2 << endl << endl;
    }
        
        
    infile.close();

    return 0;
}