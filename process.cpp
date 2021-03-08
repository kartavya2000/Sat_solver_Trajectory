//usr/bin/clang++ -O3 -std=c++11 "$0" && ./a.out; exit
#include<bits/stdc++.h>
using namespace std;

int main(int argc, char **argv){
    freopen(argv[2],"r",stdin);
    freopen(argv[3],"w", stdout);
    int N=5, T=atoi(argv[1]), C=2*N*N*T;
    string sat; cin>>sat; if(sat!="SAT") return cout<<"UNSATISFIED, EXITING...",0 ;
    for(int i=0; i<2; i++){
        cout<<"Trajectory of Particle "<<i+1<<endl;
        for(int t=0; t<T; t++){
            for(int j=0; j<N*N; j++){
                int x; cin>>x; 
                if(x>0) 
                    cout<<"t="<<t<<" -> ("<<(x-1-i*T*N*N-t*N*N)%N<<","<<(x-1-i*T*N*N-t*N*N)/N<<")\n";
            }
        }
    }
} 
