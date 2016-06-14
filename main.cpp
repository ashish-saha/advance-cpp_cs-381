#include <iostream>
#include<fstream>
#include <sstream>      // std::istringstream
using namespace std;
class polynomial  {
public:
    int array [20]= {0};
    polynomial () {}
    
    
    polynomial(int *a)  {
        for (int i=0; i<20; i++)
            array[i] = a[i];
    }
    
    void print () {
        for (int i=19; i>=0; i--) {
            if ( array[i] == -99 || array[i] == 0)        continue;
            else                                          cout << array[i] << " " << i << " ";
        }
    }
    
    polynomial operator+ (polynomial p) {
        polynomial temp;
        for (int i=0; i<19; i++)
            temp.array[i]= array[i] + p.array[i];
        return temp;
    }
    
    polynomial operator- (polynomial p) {
        polynomial temp;
        for (int i=0; i<19; i++)
            temp.array[i]= array[i] - p.array[i];
        return temp;
    }
    
    polynomial operator* (polynomial p) {
        polynomial temp;
        for (int i=0; i<19; i++) {
            for (int j=0; j<19; j++) {
                if (array[i] == 0 || p.array[j] == 0)       continue;
                temp.array[i+j] = temp.array[i+j] + array[i]*p.array[j];
            }
        }
        return temp;
    }
    
    friend ostream& operator<<(ostream& os, polynomial p);
    
};

ostream& operator<<(ostream& os, polynomial p) {
    for (int i=19; i>=0; i--) {
        if ( p.array[i] == -99 || p.array[i] == 0)        continue;
        else                                          os << p.array[i] << " " << i << " ";
    }
    return os;
}

int main(int argc, const char * argv[]) {
    int size_array [100] = {0};
    int size = 0;
    int max = 0;
    ifstream infile0;
    string line0;
    infile0.open (argv[1]);              //"/Users/deep/desktop/input.txt");
    while (getline(infile0,line0)){
        int a, b;
        istringstream iss (line0);
        while (iss >> a >> b)       if (b>max)  max=b;
        size_array[size] = max;
        max=0;
        size++;
    }
    infile0.close();

    int** array = new int*[size];
    for (int i=0; i<size; ++i){
        array[i] = new int [20];
    }
    
    for (int i=0; i<size; i++)
        for (int j=0; j<20; j++)
            array[i][j] = 0;
    
    int x, y, row = 0;
    ifstream infile;
    infile.open (argv[1]);              //"/Users/deep/desktop/input.txt");
    string line;
    while (getline (infile, line)){
        istringstream iss (line);
        while (iss >> x >> y) {
            array[row][y] += x;
        }
        row++;
    }
    infile.close();
    
    ofstream outfile;
    outfile.open(argv[2]);              //"/Users/deep/desktop/output.txt");
    for (int i=0; i<size; i=i+2){
        polynomial x = array[i];
        polynomial y = array[i+1];
        outfile << i << ".   cannonical  " << x << endl;
        outfile << i+1 << ".   cannonical  " << y << endl;
        outfile << i << "+" << i+1 << ". sum         " << x+y << endl;
        outfile << i << "-" << i+1 << ". difference  " << x-y << endl;
        outfile << i << "*" << i+1 << ". Multiply    " << x*y << endl;
        outfile << endl ;
    }
    outfile.close();
    return 0;
}
