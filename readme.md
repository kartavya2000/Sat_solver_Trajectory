##Trajectory generation with miniSAT solver
1. Pull the directory inside the directory where minisat executable is located. 
2. The positions of obstacles are saved in `obstacles.txt` in the format:
   - First line gives the number of obstacles - K
   - After that K lines each has the position of $ith$ obstacle in the format (x+y*N) where x, y are coordinates
3. To generate the trajectory run `./run.sh <Time-Steps>`. 

The file trajectory.txt contains the final result of the path of two robots.

The value of *SAT* in first line of trajectory.txt indicates the existence of a valid path. The value of *UNSAT* indicates otherwise.


