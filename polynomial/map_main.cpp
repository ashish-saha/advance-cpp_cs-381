#include<iostream>
#include<map>
#include<fstream>
#include <sstream>
using namespace std;

class polynomial {
public:
    map<int, int> poly;
    polynomial () {}
    void append (int co, int ex) {
        map<int, int>:: iterator it = poly.begin();
        while (it != poly.end()) {
            if (it->first == ex)    {it->second+=co;    return;}
            ++it;
        }
        poly.insert (pair<int, int>(ex, co));
    }
    
    polynomial operator+ (polynomial p) {
        polynomial temp;
        map<int,int>:: iterator it1 = poly.begin();
        while (it1 != poly.end()) {
            temp.append(it1->second, it1->first);
            ++it1;
        }
        
        map<int,int>:: iterator it2 = p.poly.begin();
        while (it2 != p.poly.end()) {
            temp.append(it2->second, it2->first);
            ++it2;
        }
        return temp;
    }
    
    polynomial operator- (polynomial p) {
        polynomial temp;
        map<int,int>:: iterator it1 = poly.begin();
        while (it1 != poly.end()) {
            temp.append(it1->second, it1->first);
            ++it1;
        }
        
        map<int,int>:: iterator it2 = p.poly.begin();
        while (it2 != p.poly.end()) {
            temp.append((-1)*it2->second, it2->first);
            ++it2;
        }
        return temp;
    }
    
    polynomial operator* (polynomial p) {
        polynomial temp;
        map<int,int>:: iterator it1 = poly.begin();
        map<int,int>:: iterator it2 = p.poly.begin();
        
        while (it1 != poly.end()) {
            while (it2 != p.poly.end()) {
                int x = it1->first + it2->first;
                temp.append(it1->second*it2->second, x);
                ++it2;
            }
            ++it1;
            it2 = p.poly.begin();
        }
        return temp;
    }
    friend ostream& operator<< (ostream& os, polynomial p);
};

ostream& operator<<(ostream& os, polynomial p) {
    map<int, int>:: reverse_iterator it = p.poly.rbegin();
    while (it != p.poly.rend()) {
        if          (it->second != 0)   {os << it->second << " " << it->first  << " ";}
        it++;
    }
    os << endl;
    return os;
};


int main () {
    ifstream infile;
    ofstream outfile;
    infile.open ("/Users/deep/desktop/input.txt");
    string line1, line2;
    int x, y;
    while (getline (infile, line1) ) {
        cout << "original  ";
        istringstream iss (line1);
        polynomial p1;
        while (iss >> x >> y) {
            cout << x << " " << y << " ";
            p1.append (x, y);
        }
        cout << endl <<  "canonical " << p1;
        
        if (getline(infile, line2)) {
            cout << "original  ";
            polynomial p2;
            istringstream iss2 (line2);
            while (iss2 >> x >> y) {
                cout << x << " " << y << " ";
                p2.append(x,y);
            }
            cout << endl;
            cout << "canonical  " << p2 ;
            cout << "sum        " << p1+p2;
            cout << "difference " << p1-p2;
            cout << "product    " << p1*p2 << endl;
        }        
    }
    infile.close();
    outfile.close();
}
