#include<iostream>
#include<math.h>
#include <cstdlib>
#include<cassert>
using namespace std;
template <class T> // forward declaration
class SA;
template <class T>
class Matrix;
template <class T>
class VNT;

template <class T> //forward declaration
ostream& operator<<(ostream& os, SA<T> s);
template <class T>
ostream& operator<<(ostream& os, Matrix<T> m);
template <class T>
ostream& operator<<(ostream& os, VNT<T> v);

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
        for (int j=low; j<=high; j++)    p[j]=0;
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
    Matrix() {}
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

template < class T >
class VNT {
private:
    Matrix <T> table ;
    int row;
    int col;
    int max_row;
    int max_col;
public:
    VNT () {}
    VNT (int m, int n) {
        table = Matrix<T> (m, n);
        row = 0;
        col = 0;
        max_row =m;
        max_col=n;
    }
    void add (int x) {
        table[row][col] = x;

        for (int i=row; i>=0; i--) {
            for (int j=col; j>=0; j--) {
                //if its the first item no need to bubble up
                if      (i==0 && j==0)       break;
                //if the item is at the first row then only bubble to the left
                else if (i==0)     {if (table[i][j]<table[i][j-1])   {int temp=table[i][j]; table[i][j] = table[i][j-1]; table[i][j-1]=temp;}}
                //if the item is at the first column then only bubble to straight up
                else if (j==0)     {if (table[i][j]<table[i-1][j])   {int temp=table[i][j]; table[i][j] = table[i-1][j]; table[i-1][j]=temp;}}
                //swap with the one to the left or above
                else {
                    if      ((table[i-1][j] >= table [i][j-1]) && (table[i-1][j] > table[i][j]))    {table[i][j] = table[i-1][j]; table[i-1][j]=x;}
                    else if ((table[i][j-1] > table [i-1][j]) && (table[i][j-1] > table[i][j]))  {table[i][j] = table[i][j-1]; table[i][j-1]=x;}
                }
             }
        }
        col+=1;
        if      (col==max_col)   {col=0; row+=1; }
        if      (row==max_row && col==0)   { row=max_row-1;  col=max_col-1; }

    }
    
    int getMin() {
        int min = table[0][0];
        table[0][0] = table[row][col];
        table[row][col] = 0;
        col-=1;
        if (col==-1)    {col=max_col-1;     row-=1;}
        
        for (int i=0; i<=row; i++) {
            for (int j=0; j<max_col; j++) {
//              if the loop is at the end of the filled list then then the buuble down is complete
                if (i==row && j==col)              return min;
                //if the loop is at the last filled row just bubble to the right
                else if (i==row) {
                    if ((table[i][j] > table [i][j+1]) && table[i][j+1] != 0)   {int temp = table[i][j]; table[i][j] = table[i][j+1]; table[i][j+1] = temp;}
                }
                //if loop is at the last column then just bubble straight down
                else if (j==max_col-1)    {
                    if (table[i][j] > table[i+1][j] && table[i+1][j] != 0)    {int temp = table[i][j]; table[i][j] = table[i+1][j]; table[i+1][j] = temp;}
                }
                //swap with the one to the right
                else if ((table[i][j] > table[i][j+1]) && (table[i+1][j] >= table[i][j+1]) && table[i][j+1] != 0)   {
                    int temp = table[i][j];
                    table[i][j] = table[i][j+1];
                    table[i][j+1] = temp;
                }
                //swap with the one below
                else if ((table[i][j] > table[i+1][j]) && (table[i][j+1] > table[i+1][j]) && table[i+1][j] != 0)   {
                    int temp = table[i][j];
                    table[i][j] = table[i+1][j];
                    table[i+1][j] = temp;
                }
            }
        }
        return min;
    }

    bool find (int x) {
        for (int i=0; i<max_row; i++) {
            for (int j=max_col-1; j>=0; j--) {
                if      (x==table[i][j])     return true;
                else if (x>table[i][j])      break;
                else if (x<table[i][j])      continue;
            }
        }
        return false;
    }

    void sort (int k[], int size) {
        for (int i=0; i<size; i++)
            add(k[i]);
        
        for (int i=0; i<size; i++)
            k[i] = getMin();
    }
    friend ostream& operator<< <T>(ostream& os, VNT<T> v);
};

template <class T>
ostream & operator<<(ostream & os, VNT < T > v) {
    os << v.table;
    return os;
}

int main(){

    int k[16] = {5,7,1,3,6,5,8,45,21,85,36, 8, 3, 6, 19, 2};
    cout << "Original: ";
    for (int i=0; i<16; i++)        cout << k[i] << " ";
    cout << endl;
    
    VNT<int> A (4,4);
    A.sort(k, 16);
    
    cout << "Sorted:   " ;
    for (int i=0; i<16; i++)        cout << k[i] << " ";
    cout << endl;
    return 0;
}
