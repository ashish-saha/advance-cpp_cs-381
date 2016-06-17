#include<iostream>
#include <cstdlib>
#include<cassert>
using namespace std;
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
        {cout<< "constructor error in bounds definition SA"<<endl;
            exit(1);}
        low=l;
        high=h;
        p=new T[h-l+1];
        for (int i=0;i<h-l+1; i++)  p[i]=0;
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
        {cout<< "index "<<i<<" out of range SA"<<endl;
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
    SA <SA <T> > matrix;
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
/*    Matrix (const Matrix & m) {
        for (int i=m.row_low; i<=m.row_high;i++)
            matrix[i] = SA <T> (m.col_low, m.col_high);
    }
*/
    Matrix(int rowl, int rowh, int coll, int colh) {
        row_low = rowl;
        row_high = rowh;
        col_low = coll;
        col_high = colh;
        matrix = SA < SA < T > >(rowl, rowh);
        for (int i = rowl; i <= (rowh); i++)
            matrix[i] = SA < T > (coll, colh);
    }

    SA < T > &operator[](int i) {
        return matrix[i];
    }
    
    Matrix<T> operator* (Matrix& m){
        if (col_high-col_low  !=  m.row_high-m.row_low)       {cout << "Matrix is impossible " << endl;      exit(0);}
        cout << "Multiplication :" << endl;
        Matrix <T> temp(row_low, row_high, m.col_low, m.col_high);
        for (int i=row_low; i<=row_high; i++) {
            for (int j=m.col_low; j<=m.col_high; j++) {
                for (int k=0; k<=col_high-col_low; k++)
                    temp[i][j] += matrix[i][k+col_low] * m.matrix[k+m.row_low][j];
            }
        }
        return temp;
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
    
    Matrix <int> m (5,7,11,14) ;
    m[5][11]=2;
    m[5][12]=6;
    m[5][13]=3;
    m[5][14] =4;
    
    m[6][11]=1;
    m[6][12]=4;
    m[6][13]=4;
    m[6][14] =0;
    
    m[7][11]=0;
    m[7][12]=2;
    m[7][13]=3;
    m[7][14] =5;

    cout << m << endl;
    
    Matrix <int> n (10,13,5,6);
    n[10][5] = 3;
    n[10][6] = 0;
    n[11][5] = 0;
    n[11][6] = 2;
    n[12][5] = 3;
    n[12][6] = 1;
    n[13][5] = 4;
    n[13][6] = 0;
    
    cout << n << endl;
    
    cout << m*n;
    return 0;
}
