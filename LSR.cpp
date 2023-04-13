#include<bits/stdc++.h>
#include"Router.h"
#include"Router.cpp"
using namespace std;
using namespace Network;
int main(){
    int n = 4;
    
    vector<vector<long long>> A = {{0,1,3,7},{1,0,1,-1},{3,1,0,2},{7,-1,2,0}};
    Router R0,R1,R2,R3;
    
    R0.rtinit_lsr(0,A);
    R1.rtinit_lsr(1,A);
    R2.rtinit_lsr(2,A);
    R3.rtinit_lsr(3,A);

    cout << "\nDistance Matrix after implementing LS Routing Algorithm: "<<endl;
    cout << " Id| [0]  [1]  [2]  [3]"<< endl;
    R0.printDi();
    R1.printDi();
    R2.printDi();
    R3.printDi();
    cout << endl;

    R0.printRtable();

    R1.printRtable();

    R2.printRtable();

    R3.printRtable();


    return 0;
}