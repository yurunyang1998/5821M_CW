//
// Created by yurunyang on 2021/10/23.
//

#include "vector"
#include "iostream"
using namespace std;

class A{
public:
    vector<int> b;
    A(vector<int> &a){
        b = a;
    }
    void change(){
        cout<<b[0]<<" "<<b[1]<<" "<<b[2]<<endl;
        b[0] = 43;
    }
};



int main(){

    vector<int> a={1,2,3};
    A b(a);
    b.change();
    a[0] = -1;
    b.change();

}