#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

bool cmp(string a, string b)
{
    return (a+b)>(b+a);
}
int main() {
    int N = 0;
    cin>>N;
    vector <string> vac;
    for(int i=0;i<N;i++)
    {
        string a;
        cin>>a;
        vac.push_back(a);
//        sort(vac.begin(), vac.end(),cmp);
        //lamda表达式
        sort(vac.begin(),vac.end(),[](string s1,string s2){ return (s1+s2)>(s2+s1);});
//        cout<<vac.at(i)<<endl;
    }
//    cout<<vac.at(0)<<endl;
    for(auto s:vac)
//    for(int s = 0;s<N;s++)
        cout <<s;
    return 0;

}