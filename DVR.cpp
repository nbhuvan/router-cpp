#include<bits/stdc++.h>
#include"Router.h"
#include"Router.cpp"
using namespace std;
using namespace Network;
int main(){
    int n = 4;
    queue<rtpkt>buff;
    
    vector<vector<long long>> A = {{0,1,3,7},{1,0,1,-1},{3,1,0,2},{7,-1,2,0}};
    Router R0,R1,R2,R3;
    R0.rtinit_dvr(0,A[0],buff);
    R1.rtinit_dvr(1,A[1],buff);
    R2.rtinit_dvr(2,A[2],buff);
    R3.rtinit_dvr(3,A[3],buff);

    cout << "\nInitial Distance Matrix: \n"<<endl;
    cout << " Id| [0]  [1]  [2]  [3]"<< endl;
    R0.printDi();
    R1.printDi();
    R2.printDi();
    R3.printDi();
    cout << endl;
    
    while(buff.size()){
        rtpkt pkt = buff.front();
        buff.pop();

        switch (pkt.destid)
        {
        case 0:
            R0.rtupdate(pkt,buff);
            break;
        case 1:
            R1.rtupdate(pkt,buff);
            break;
        case 2:
            R2.rtupdate(pkt,buff);
            break;
        case 3:
            R3.rtupdate(pkt,buff);
            break;
        default:
            break;
        }

    }
    
    cout << "Distance Matrix after implementation of DV routing algorithm: \n"<< endl;
    R0.printDi();
    R1.printDi();
    R2.printDi();
    R3.printDi();
    cout << endl;

    R0.printRtable();
    cout << endl;

    R1.printRtable();
    cout << endl;

    R2.printRtable();
    cout << endl;

    R3.printRtable();
    return 0;
}