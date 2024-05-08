#include<iostream>
#include<cmath>
#include<fstream>
#include<string>
using namespace std;

int main() {
    ifstream filein;
	filein.open("test.txt", ios_base::in);
    string str = "";
    while(!filein.eof()) {
        filein>>str;
        if(str == "REGM") {
            cout<<str<<endl;
            string name;
            getline(filein,name,' ');
            getline(filein,name,' ');
            string Age;
            getline(filein,Age,' ');
            int age = stoi(Age);
            string Num;
            getline(filein,Num);
            int NUM = stoi(Num);
            cout<<"Age:"<<age<<"|"<<"Num:"<<NUM<<endl;
        }
    }
    return 0;
}