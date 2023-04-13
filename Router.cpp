#include<bits/stdc++.h>
#include "Router.h"
using namespace std;

int minId(vector<long long>&di,vector<bool>&b){ //Finds the index containing minimum distance from root
    int mini = INT_MAX;
    int mini_id = -1;
    for(int i=0;i<di.size();i++){
        if(b[i]==0 && mini>di[i]){
            mini = di[i];
            mini_id = i;
        }
    }
    return mini_id;
}

namespace Network{
    Router::Router(){ //Router Constructor
        Id = -1;
        n = -1;
    }
    void Router::tolayer2(const rtpkt pkt,std::queue<rtpkt>&buff){ //Given a pkt, it sends to the common buffer
        buff.push(pkt);
        return;
    }
    void Router::rtinit_dvr(const int id, const vector<long long>di,queue<rtpkt>&buff){ // Router Initialization using DV Routing Algorithm
        Id = id;
        n = di.size();
        Di = di;
        vector<bool>b(n,0);
        vector<int>v(n,-1);
        v[Id] = Id;
        for(int i=0;i<n;i++){
            if(i==Id) continue;
            if(di[i]!=-1){
                b[i] = 1;
                v[i] = i;
            }
            else Di[i] = INT_MAX;
        }
        Ci = b;
        for(int i=0;i<n;i++){
            if(Ci[i]){
                rtpkt npkt;
                npkt.sourceid = Id;
                npkt.destid = i;
                npkt.mincost = Di;
                tolayer2(npkt,buff);
            }
        }
        Rtable = v;
        return;
    }
    void Router::rtinit_lsr(const int id, const vector<vector<long long>>A){ // Router Initialization using LS Routing Algorithm
        Id = id;
        n = A.size();

        vector<long long> di(n,INT_MAX);
        vector<bool> b(n,0);
        vector<int>v(n,-1); // Vector that stores Next hop

        di[id] = 0;
        D = A;
        v[Id] = Id;
        
        for(int i=0;i<n;i++){
            if(i==Id) continue;
            if(A[id][i]!=-1){
                v[i] = i;
            }
        }
        
        int id1 = minId(di,b);
        while(id1!=-1){
            b[id1] = 1;
            for(int i=0;i<n;i++){
                if(A[id1][i]!=-1 && i!=id1 && b[i]==0){
                    if(di[i]>(di[id1]+A[id1][i])){
                        if(id1!=Id) v[i] = v[id1]; //Updates Next Hop for router i
                        di[i] = min(di[i],di[id1]+A[id1][i]);
                    }
                }
            } 
            id1 = minId(di,b);
        }
        Di = di;
        Rtable = v;
        return;
    }
    void Router::printDi(){ // Prints minimum distances for all the nodes from this router
        // cout << "Distance Vector for Router-"<<Id<< ": ";
        cout <<"["<<Id << "]| ";
        for(int i=0;i<n;i++){
            if(i==0)cout << " "<<Di[i] <<" ";
            else if(Di[i]==INT_MAX) cout << "  "<<-1 <<" ";
            else cout << "   "<<Di[i] <<" ";
        }
        cout << endl;
        return;
    }
    void Router::printRtable(){// Prints Round table of this router
        cout << "Routing Table for Router-"<<Id<< ": \n";
        cout << "Destid <-----> Next Hop  <-----> Min Cost\n";
        for(int i=0;i<n;i++){
            cout << " ["<<i <<"]             ["<<Rtable[i] << "]                "<< Di[i] << endl;
        }
        cout << endl;
        return;
    }
    void Router::rtupdate(const rtpkt pkt,queue<rtpkt>&buff){ // Performs update after receiving a rtpkt
        int sourceid = pkt.sourceid;
        bool b = 0;
        for(int i=0;i<n;i++){
            if(Di[i]>(pkt.mincost[i]+Di[sourceid])){
                b = 1;
                Rtable[i] = Rtable[sourceid];
                Di[i] = min(Di[i],pkt.mincost[i]+Di[sourceid]);
            }
        }
        if(b){
            for(int i=0;i<n;i++){
                if(Ci[i]){
                    rtpkt npkt;
                    npkt.sourceid = Id;
                    npkt.destid = i;
                    npkt.mincost = Di;
                    tolayer2(npkt,buff); // Sends the npkt into the buffer.
                }
            }
        }
        return;
    }
    const vector<long long>& Router::getDi(){ //Returns min distances for each node from this router
        return Di;
    }
    const vector<bool>& Router::getCi(){ //Returns the Connection in terms of bool
        return Ci;
    }
}