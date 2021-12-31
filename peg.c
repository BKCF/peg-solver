#include <stdio.h>
#include <stdbool.h>

#define NUMPEGS 15
#define JUMPED 1 //adjacency list magic numbers
#define LANDING 2 

static void printPath();
static bool greedySearch(int);
static void findAll(int, int);

static bool pegs[15]; //true if ith hole has a peg in it 
static int A[13];
static int B[13];
static int numPaths = 0;

//number of holes you can jump to from the ith hole
//                        0 1 2 3 4 ...
static int num_adj[15] = {2,2,4,2,2,
                           2,2,2,2,
                            4,2,4,
                             2,2,
                              2};

//adjacency list of holes, {hole number, jumped piece, landing hole}
int adj_list[36][3] = {
    {0,1,2},{0,5,9},
    {1,2,3},{1,6,10},
    {2,3,4},{2,7,11},{2,6,9},{2,1,0},
    {3,2,1},{3,7,10},
    {4,3,2},{4,8,11},
    {5,9,12},{5,6,7},
    {6,10,13},{6,7,8},
    {7,6,5},{7,10,12},
    {8,7,6},{8,11,13},
    {9,5,0},{9,6,2},{9,10,11},{9,12,14},
    {10,6,1},{10,7,3},
    {11,8,4},{11,7,2},{11,10,9},{11,13,14},
    {12,9,5},{12,10,7},
    {13,10,6},{13,11,8},
    {14,12,9},{14,13,11}
};

int main(){
   // bool pegs[NUMPEGS];
    
    //skip 0
    for(int i = 1 ; i < NUMPEGS ; i++){
        pegs[i] = 1;
    }
    findAll(0, NUMPEGS - 1);
    //printf("%s\n", findAll(0, NUMPEGS - 1) ? "true":"false");
    printf("%d\n",numPaths);
    return 0;
}

static void findAll(int depth, int pegs_left){
    int adj_pos = 0; //position in adj_array
    int moves_checked = 0; //if 0, we are stuck, kill it.
    int range_end = 0;
    for(int i = 0 ; i < NUMPEGS ; i++){
        //if peg in this spot
        if(pegs[i]){
            range_end = adj_pos + num_adj[i];
            //while we are searching through this element's adjacency list
            while(adj_pos < range_end) 
            {
               // printf("%d %d\n",i, adj_pos);
                int landing_spot = adj_list[adj_pos][LANDING];
                int jumped_spot = adj_list[adj_pos][JUMPED];

                if(!pegs[landing_spot] && pegs[jumped_spot]){
                    moves_checked++;

                    pegs[i] = 0; //remove peg from original spot
                    pegs[landing_spot] = 1; //place it in landing spot
                    pegs[jumped_spot] = 0; //remove jumped piece
                    A[depth] = i;
                    B[depth] = landing_spot;

                    pegs_left--;
                    if(pegs_left == 1) {//win condition base case
                        //printf("(%d -> %d)\n",i, landing_spot);
                        printPath();
                        //return;
                    }
                    else{
                    //if somewhere deep down we succeeded
                        findAll(depth+1,pegs_left);
                    }
                       // printf("(%d -> %d)\n",i, landing_spot);
                        //return true;
                    

                    pegs[i] = 1; //put peg in original spot
                    pegs[landing_spot] = 0; //take back from landing spot
                    pegs[jumped_spot] = 1; //replace jumped piece
                    pegs_left++;
                }
                adj_pos+=1;
            }
        }
        else{
            adj_pos += num_adj[i];
        }
    }
    // if(moves_checked == 0){
    //     return false; //we're stuck and stop here
    // }
    return; //fail!
}

static void printPath(){
    numPaths++;
    for(int i = 0; i < 13 ; i++){
        printf("(%d -> %d) ",A[i],B[i]);
    }
    printf("\n");
    
}


static bool greedySearch(int pegs_left){
    int adj_pos = 0; //position in adj_array
    int moves_checked = 0; //if 0, we are stuck, kill it.
    int range_end = 0;
    for(int i = 0 ; i < NUMPEGS ; i++){
        //if peg in this spot
        if(pegs[i]){
            range_end = adj_pos + num_adj[i];
            //while we are searching through this element's adjacency list
            while(adj_pos < range_end) 
            {
               // printf("%d %d\n",i, adj_pos);
                int landing_spot = adj_list[adj_pos][LANDING];
                int jumped_spot = adj_list[adj_pos][JUMPED];

                if(!pegs[landing_spot] && pegs[jumped_spot]){
                    moves_checked++;

                    pegs[i] = 0; //remove peg from original spot
                    pegs[landing_spot] = 1; //place it in landing spot
                    pegs[jumped_spot] = 0; //remove jumped piece

                    pegs_left--;
                    if(pegs_left == 1) {//win condition base case
                        //printf("(%d -> %d)\n",i, landing_spot);
                       // print_path();
                        return true;
                    }

                    //if somewhere deep down we succeeded
                    if(greedySearch(pegs_left)){ 
                        printf("(%d -> %d)\n",i, landing_spot);
                        return true;
                    }

                    pegs[i] = 1; //put peg in original spot
                    pegs[landing_spot] = 0; //take back from landing spot
                    pegs[jumped_spot] = 1; //replace jumped piece
                    pegs_left++;
                }
                adj_pos+=1;
            }
        }
        else{
            adj_pos += num_adj[i];
        }
    }
    // if(moves_checked == 0){
    //     return false; //we're stuck and stop here
    // }
    return false; //should never reach here
}
