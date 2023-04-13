#pragma once
#include<bits/stdc++.h>
namespace Network{
    struct rtpkt{
        int sourceid;
        int destid;
        std::vector<long long> mincost;
    };
    class Router{
        private:
            int n;
            int Id;
            std::vector<long long>Di;
            std::vector<std::vector<long long>>D;
            std::vector<bool>Ci;
            std::vector<int>Rtable;

        public:
        Router();
        void rtinit_dvr(const int id, const std::vector<long long>di,std::queue<rtpkt>&buff);
        void rtinit_lsr(const int id, const std::vector<std::vector<long long>>D);
        const std::vector<long long>& getDi();
        const std::vector<bool>& getCi();
        void printDi();
        void printRtable();
        void rtupdate(const rtpkt,std::queue<rtpkt>&buff);
        void tolayer2(const rtpkt,std::queue<rtpkt>&buff);
    };
}
