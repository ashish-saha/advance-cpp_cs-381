#include<iostream>
#include<map>
#include<fstream>
#include <sstream>
#include<vector>
using namespace std;

int main (int argc, const char * argv[]) {
    ifstream infile;
    infile.open (argv[1]);    //"/Users/deep/desktop/input.txt");
    string line1;
    int lineNo = 0;
    map<string, vector<int>> myMap;
    
    while (getline (infile, line1) ) {
        istringstream iss (line1);
        string word;
        char c[] = " .-,!@#$%^&*()[]{}:<>/?+/";
        
        int wordNo = 0;
        while (iss >> word) {
            for (unsigned int i=0; i<strlen(c); ++i)
                word.erase (remove(word.begin(),word.end(), c[i]), word.end());
//            for (auto c: word)
//                if(ispunct(c)) word.erase(word.find_first_of(c));
            if (word == "")    continue;
            myMap[word].push_back(lineNo);
            myMap[word].push_back(wordNo);
            wordNo++;
        }
        lineNo++;
    }
    
    map<string, vector<int>>:: iterator it = myMap.begin();
    while (it != myMap.end()) {
        cout << it->first << " " ;
        vector<int> inVect = (*it).second;
        cout <<  inVect.size()/2 << " [ ";
        for (int i=0; i<inVect.size(); i+=2)
            cout << "(" << inVect [i] << "," << inVect[i+1] << ") ";
        cout << "]" << endl;
        ++it;
    }
}