#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template<typename T>
unsigned min_index(const vector<T> &vals, unsigned index);
template<typename T>
void selection_sort(vector<T> &vals);
template<typename T>
T getElement(vector<T> vals, int index);

vector<char> createVector(){
    int vecSize = rand() % 26;
    char c = 'a';
    vector<char> vals;
    for(int i = 0; i < vecSize; i++)
    {
        vals.push_back(c);
        c++;
    }
    return vals;
}

int main() {
    cout<<"Staring program"<<endl;
    cout<<"Initializing vector of type double in decreasing order."<<endl;
    vector<double> doubVecDec = {4.0, 3.2, 2.5, 1.0};
    cout<<"Initializing vector of type double in random order."<<endl;
    vector<double> doubVecRan = {3.2, 1.0, 2.5, 4.3};

    cout<<"Initializing vector of type int in decreasing order."<<endl;
    vector<int> intVecDec = {4,3,2,1};
    cout<<"Initializing vector of type int in random order."<<endl;
    vector<int> intVecRan = {3,1,2,4};

    cout<<"Initializing vector of type string."<<endl;
    vector<string> strVec = {"2","4","5","1"};

    cout<<"Sort vectors of type double: "<<endl;
    selection_sort(doubVecDec);
    selection_sort(doubVecRan);
    for(unsigned i=0;i<4;++i) {
        cout<<doubVecDec[i]<<" ";
    }
    cout<<endl;
    for(unsigned i=0;i<4;++i) {
        cout<<doubVecRan[i]<<" ";
    }
    cout<<endl;

    cout<<"Sort vectors of type int: "<<endl;
    selection_sort(intVecDec);
    selection_sort(intVecRan);
    for(unsigned i=0;i<4;++i) {
        cout<<intVecDec[i]<<" ";
    }
    cout<<endl;
    for(unsigned i=0;i<4;++i) {
        cout<<intVecRan[i]<<" ";
    }
    cout<<endl;

    cout<<"Sort vectors of type str: "<<endl;
    selection_sort(strVec);
    for(unsigned i=0;i<4;++i) {
        cout<<strVec[i]<<" ";
    }
    cout<<endl;

    //Part B
    srand(time(0));
    vector<char> vals = createVector();
    char curChar;
    int index;
    int numOfRuns = 10;
    while(--numOfRuns >= 0){
        cout << "Enter a number: " << endl;
        cin >> index;
        curChar = getElement(vals,index);
        cout << "Element located at " << index << ": is " << curChar << endl;
    }
    return 0;
}

template<typename T>
unsigned min_index(const vector<T> &vals, unsigned index) {
    unsigned minIndex = index;
    for(unsigned i=index;i<vals.size();++i) {
        if(vals[i]<vals[minIndex]) {
            minIndex = i;
        }
    }
    return minIndex;
}

template<typename T>
void selection_sort(vector<T> &vals) {
    for(unsigned i=0;i<vals.size();++i) {
        unsigned minIndex = min_index(vals, i);
        swap(vals[i], vals[minIndex]);
    }
}

template<typename T>
T getElement(vector<T> vals, int index) {
    try{
        if(index>(int)vals.size() || index<0) {
            throw runtime_error("std::outofrange");
        }
        return vals[index];
    }
    catch (runtime_error &excp) {
        cout<<"out of range exception occured"<<endl;
    }
    throw runtime_error("error");
}
