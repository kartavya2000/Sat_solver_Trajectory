//usr/bin/clang++ -O3 -std=c++11 "$0" && ./a.out; exit

/* ===============================================================================================================================
-> use the following format for arguments:                                                                                        |
<Starting_Pos_Robot_1> <Starting_Pos_Robot_2> <Time_Steps> <Ending_Pos_Robot_1> <Ending_Pos_Robot_2> <Obstacles position file>    |
                                                                                                                                  |
-> Final output produced in input.txt                                                                                             |
                                                                                                                                  |
-> For complete solving trajectory production Run the following command:                                                          |
./run.sh <time-steps>                                                                                                             |
                                                                                                                                  |
=================================================================================================================================*/ 
#include<bits/stdc++.h>
using namespace std;

int main(int argc, char **argv){
    freopen(argv[6], "r", stdin);
    freopen("input.txt", "w", stdout);
    int obst_cnt; 
    cin>>obst_cnt; //inputting obstacles position from obstacles.txt
    vector<int> obst(obst_cnt);
    while(obst_cnt--) cin>>obst[obst_cnt];

    int T=atoi(argv[3]);
    int S1=atoi(argv[1]), S2=atoi(argv[2]), E1=atoi(argv[4]), E2=atoi(argv[5]);
    int N=5;

    vector<int> dir{1,-1,N,-N};
    auto checkdir=[&](int j, int d){
        int x=j%N, y=j/N, dx=d%N, dy=d/N;
        if(x+dx>=N || x+dx<0 || y+dy>=N || y+dy<0) return false; 
        return true;
    }; 
    int sz=0;
    //no. of Clauses:
    int clauses= (T*N*N*(N*N-1))+(2*T)+T*N*N+4+2*(T-1)*N*N+2*T*obst.size();
    //return the variable corresponding to the i-th robot, t-th time step and j-th cell in the grid
    auto x=[&](int i, int t, int j){return i*T*N*N+t*N*N+j+1; };
    //outputting the parameter line 
    cout<<"p cnf "<<(N*N*T*2)<<" "<<clauses<<"\n";

    for(int i=0; i<2; i++){
        for(int t=0; t<T; t++){
            for(int j=0; j<N*N; j++) 
                for(int k=0; k<j; k++)
                    cout<<(-(x(i,t,j)))<<" "<<(-(x(i,t,k)))<<" 0\n";// condition for at most one value of position at each time step.
            for(int j=0; j<N*N; j++) cout<<x(i,t,j)<<" "; // condition for at least one position for each time step. 
            cout<<"0\n";
            for(int j: obst) cout<<(-(x(i,t,j)))<<" 0\n"; //condition for obstacle prevention
        }
    }
    
    for(int t=0; t<T; t++) for(int j=0; j<N*N; j++) cout<<(-x(0,t,j))<<" "<<(-x(1,t,j))<<" 0\n"; // condition for distinct positions for both robots.

    cout<<x(0,0,S1)<<" 0\n"; cout<<x(1,0,S2)<<" 0\n"; cout<<x(0,T-1,E1)<<" 0\n"; cout<<x(1,T-1,E2)<<" 0\n";// specifiying starting and ending positions for the robots

    for(int i=0; i<2; i++){
        for(int t=0; t<T-1; t++){
            for(int j=0; j<N*N; j++){
                cout<<(-x(i,t,j))<<" ";
                for(int k=0; k<dir.size(); k++) if(checkdir(j,dir[k])) cout<<x(i,t+1,j+dir[k])<<" "; // condition for movement in steps of 1 along x and y directions.
                cout<<"0\n";
            }
        }
    }

}
