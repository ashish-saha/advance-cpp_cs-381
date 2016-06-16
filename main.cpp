#include<iostream>
#include <cstdlib>
#include<cassert>
using namespace std;
// see: http://www.devx.com/cplus/10MinuteSolution/30302/1954 for friend template functions
template <class T> // forward declaration
class SA;
template <class T>
class Matrix;
template <class T> //forward declaration
ostream& operator<<(ostream& os, SA<T> s);
template <class T> //forward declaration
ostream& operator<<(ostream& os, Matrix<T> m);

template < class T>
class SA{
private:
    int low, high;
    T* p;
public:
    // default constructor
    // allows for writing things like SA a;
    SA(){low=0; high=-1;p=NULL;}
    // 2 parameter constructor lets us write
    // SA x(10,20);
    SA(int l, int h){
        if((h-l+1)<=0)
        {cout<< "constructor error in bounds definition"<<endl;
            exit(1);}
        low=l;
        high=h;
        p=new T[h-l+1];
    }
    // single parameter constructor lets us
    // create a SA almost like a "standard" one by writing
    // SA x(10); and getting an array x indexed from 0 to 9
    SA(int i){low=0; high=i-1;
        p=new T[i];
    }
    // copy constructor for pass by value and
    // initialization
    SA(const SA & s){
        int size=s.high-s.low+1;
        p=new T[size];
        for(int i=0; i<size; i++)
            p[i]=s.p[i];
        low=s.low;
        high=s.high;
    }
    // destructor
    ~SA(){
        delete [] p;
    }
    //overloaded [] lets us write
    //SA x(10,20); x[15]= 100;
    T& operator[](int i){
        if(i<low || i>high)
        {cout<< "index "<<i<<" out of range"<<endl;
            exit(1);}
        return p[i-low];
    }
    // overloaded assignment lets us assign
    // one SA to another
    SA & operator=(const SA s){
        if(this==&s)return *this;
        delete [] p;
        int size=s.high-s.low+1;
        p=new T[size];
        for(int i=0; i<size; i++)
            p[i]=s.p[i];
        low=s.low;
        high=s.high;
        return *this;
    }
    // overloads << so we can directly print SAs
    //template <class T>
    friend ostream& operator<< <T> (ostream& os, SA<T> s);
};
template <class T>
ostream& operator<<(ostream& os, SA<T> s){
    int size=s.high-s.low+1;
    for(int i=0; i<size; i++)
        cout<<s.p[i]<<endl;
    return os;
};


template < class T >
class Matrix {
private:
    SA <SA <T>> matrix;
    int row_low;
    int row_high;
    int col_low;
    int col_high;
public:
    Matrix(int r, int c) {
        row_low = 0;
        row_high = r - 1;
        col_low = 0;
        col_high = c - 1;
        matrix = SA < SA < T > >(r);
        for (int j = 0; j < r; j++)
            matrix[j] = SA <T> (c);
    }
//  Matrix() {
//  }
    Matrix(int rowl, int rowh, int coll, int colh) {
        row_low = rowl;
        row_high = rowh;
        col_low = coll;
        col_high = colh;
        matrix = SA < SA < T > >(rowl, rowh);
        for (int i = rowl; i <= (rowh); i++)
            matrix[i] = SA < T > (coll, colh);
    }
    
    ~Matrix() {
    }
    
    SA < T > &operator[](int i) {
        return matrix[i];
    }

    Matrix<T> operator* (Matrix& m){
        int rows = m.row_high-m.row_low+1;
        int cols = col_low=col_high+1;
        SA <T> temp(rows, cols);
        
        for (int i=0; i<rows; i++) {
            for (int j=0; j<cols; j++) {
                for (int k=0; k<m.col_high-m.col_low+1; i++)
                    temp[i][j] += matrix[i+row_low][i+col_low] * m.matrix[i+m.row_low][j+m.col_low];
            }
        }
    }
    
    friend ostream& operator<< <T>(ostream& os, Matrix<T> s);
    
};

template <class T>
ostream & operator<<(ostream & os, Matrix < T > m) {
    for (int i = m.row_low; i <= m.row_high; i++) {
        for (int j = m.col_low; j <= m.col_high; j++) {
            os << m.matrix[i][j] << " ";
        }
        os << endl;
    }
    return os;
}

int main(){
/*    SA<int> a(10);
    int i;
    for( i=0;i<10;i++)
        a[i]=i;
    cout<<"printing using []"<<endl;
    for( i=0;i<10;i++)
        cout<<a[i]<<endl;
    cout<<"and now with overloaded <<"<<endl;
    cout<<a;
*/
    
    Matrix <int> m (3,20) ;
    m[2][15]=5;
    cout << m;
    
    
    
    
//    system("pause");
    return 0;
}