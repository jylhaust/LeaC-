#include <iostream>
#include <fstream>

using namespace std;
int main() {
    string fileroute;
    fileroute = "/home/yuanlin/Desktop/test.txt";
    /*
    fstream fin(fileroute);
    if (!fin)
        cout<<"cannot find txt"<<endl;
    while(!fin.eof())
    {
        string cpt;
        fin>>cpt;
        cout<<"print code :"<<cpt<<endl;
    }*/
    fstream fin;
    string s;
    fin.open("/home/yuanlin/Desktop/test.txt",ios::in); //ios::in|ios::out|ios::binary
    while (getline(fin,s))
    {
        cout<<s<<endl;
    }
    fin.close();
    return 0;
}