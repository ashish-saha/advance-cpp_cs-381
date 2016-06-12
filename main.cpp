
#include <iostream>
#include<fstream>
using namespace std;

 

int main(int argc, const char * argv[]) {
    ifstream infile;
    infile.open ("/Users/deep/desktop/input.txt");
    int x;
    while (infile >> x) {
        cout << x << endl;
    }
    if (infile.is_open())    cout << "Hello, World!\n";
    else                     cout << "The file is not open";
    infile.close();
    return 0;
}
