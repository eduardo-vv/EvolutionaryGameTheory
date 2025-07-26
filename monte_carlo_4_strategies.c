/*
This code simulates the imitation dynamics [1,2] 
using a kind of Monte Carlo method [3]  
for any 4-strategy symmetrized bimatrix game, 
as described by Gaunersdorfer et al. [4],
*/
#include <stdio.h>  
#include <stdlib.h>  
#include <time.h>  

#define N 1000
#define T 1000000
#define S 10

#define A 1.0
#define B 0.0
#define C 0.0
#define D 1.0

#define a 0.0
#define b 1.0
#define c 1.0
#define d 0.0

//initial conditions
#define X1_0 .1
#define X2_0 .25
#define X3_0 .45
#define X4_0 (1 - X1_0 - X2_0 - X3_0)

/*convertion of frequencies to number of players
it only work if N mod 10 = 0
otherwise it would better to define the
initial conditions here already as integers*/

#define P1 (int)(N*X1_0)
#define P2 (int)(N*X2_0)
#define P3 (int)(N*X3_0)
#define P4 (int)(N*X4_0)

//payoff matrix
double M[4][4] = {{A+a, A+b, B+a, B+b},
                  {C+a, C+b, D+a, D+b},
                  {A+c, A+d, B+c, B+d},
                  {C+c, C+d, D+c, D+d}};
int players[N]; 

int X1[T+1];
int X2[T+1];
int X3[T+1];
int X4[T+1];

int tX1[T+1];
int tX2[T+1];
int tX3[T+1];
int tX4[T+1];

int x, y;
double fx, fy, avgfx, avgfy, dwMax, p;
clock_t start, end;

unsigned int rand_unif_int(unsigned int);

int main(){
    start = clock();
    FILE *fp = fopen("strat_freq_x_time.txt", "w");

    if (fp == NULL){
        printf("Error while opening the file!");
        return -1;
    }
    double max = M[0][0];
    double min = M[0][0];
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if (M[i][j] > max) max = M[i][j];
            if (M[i][j] < min) min = M[i][j];
        }
    }        
    dwMax = max - min;

    srand((unsigned int)time(NULL));  
    printf("%d %d %d %d\n", P1, P2, P3, P4);

    //initializing arrays
    for(int t = 0; t <= T; t++){
        tX1[t] = 0;
        tX2[t] = 0;
        tX3[t] = 0;
        tX4[t] = 0;
    }
    
    //simulation loop
    for(int s = 0; s < S; s++){
        printf("%d/%d\n", s, S);

        int pos = 0;
        int aux = 0;
    
        for (int i = 0; i < P1; i++){
            players[i] = 0; //strategy 1
            pos++;
        }
        aux = pos;
        for(int i = aux; i < aux + P2; i++){
            players[i] = 1; //strategy 2
            pos++;
        }
        aux = pos;
        for(int i = aux; i < aux + P3; i++){
            players[i] = 2; //strategy 3
            pos++;
        }
        aux = pos;
        for(int i = aux; i < aux + P4; i++){
            players[i] = 3; //strategy 4
            pos++;
        } 
       
        X1[0] = P1;
        X2[0] = P2;
        X3[0] = P3;
        X4[0] = P4;

        //time loop
        for(int t = 0; t < T; ++t){
            //printf("%d/%d\n", t, T);
            fx = 0;
            fy = 0;
            x = rand_unif_int(N);

            //x plays the game with all N-1
            for(int k = 0; k < N; ++k)
                if(x != k) 
                    fx += M[players[x]][players[k]];                    
            
            avgfx = fx/(2.0*(double)(N-1));    

            do y = rand_unif_int(N); while (y == x);
            
            //y plays the game with all N-1
            for (int k = 0; k < N; ++k)
                if(y != k) 
                    fy += M[players[y]][players[k]];
            
            avgfy = fy/(2.0*(double)(N-1));


            //most of the array will remain the same      
            X1[t+1] = X1[t];
            X2[t+1] = X2[t];
            X3[t+1] = X3[t];
            X4[t+1] = X4[t]; 

            //update
            if (avgfy > avgfx){
                p = (avgfy-avgfx)/dwMax;
                if ((double)rand()/((double)RAND_MAX) < p){
                    //only updates the changes 
                     switch (players[y]){
                        case 0: X1[t+1]++; break;
                        case 1: X2[t+1]++; break;
                        case 2: X3[t+1]++; break;
                        case 3: X4[t+1]++; break;
                    }
                    switch (players[x]){
                        case 0: X1[t+1]--; break;
                        case 1: X2[t+1]--; break;
                        case 2: X3[t+1]--; break;
                        case 3: X4[t+1]--; break;
                    } 
                    players[x] = players[y]; 
                } 

            }    
   
        }
        //accumulate the data to caculate the averages
        for(int t = 0; t <= T; t++){
            tX1[t] += X1[t];
            tX2[t] += X2[t];
            tX3[t] += X3[t];
            tX4[t] += X4[t];  
        }               
    }
    double x1, x2, x3, x4;
    fprintf(fp, "Imitation dynamics with 4 strategies\n");
    fprintf(fp, "N = %d, S = %d\n\n", N, S);
    fprintf(fp, "A = %.2f B = %.2f\n", A, B);
    fprintf(fp, "C = %.2f D = %.2f\n\n", C, D);      
    fprintf(fp, "a = %.2f b = %.2f\n", a, b);
    fprintf(fp, "c = %.2f d = %.2f\n", c, d);

    fprintf(fp, "------------------------------------\n");  

    fprintf(fp, "t|1     |2     |3     |4  \n");
    for(int t = 0; t <= T; t++){
        //averages
        x1 = (double)tX1[t]/((double)S*N);
        x2 = (double)tX2[t]/((double)S*N);
        x3 = (double)tX3[t]/((double)S*N);
        x4 = (double)tX4[t]/((double)S*N);
       
        fprintf(fp, "%d %.4f %.4f %.4f %.4f\n", t, x1 ,x2, x3, x4);
    }

    fclose(fp);
    end = clock();
    double totalTime = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Total time: %fs", totalTime);
    return 0;
}


//uniform, but far from ideal
unsigned int rand_unif_int(unsigned int n){
    //credit: https://c-faq.com/lib/randrange.html
	unsigned int intdiv = (RAND_MAX + 1u) / n;
	unsigned int max = intdiv * n;
	unsigned int r;
	do r = rand(); while(r >= max);

	return r / intdiv;
}

/*
[1] TRAULSEN, A.; CLAUSSEN, J. C.; HAUERT, C. Coevolutionary Dynamics: From
Finite to Infinite Populations. Physical Review Letters, v. 95, n. 23, p. 238701,
dez. 2005. ISSN 0031-9007, 1079-7114. Available at: https://link.aps.org/doi/10.1103/
PhysRevLett.95.238701

[2] FONTANARI, J. F. Imitation dynamics and the replicator equation. Europhysics
Letters, v. 146, n. 4, p. 47001, maio 2024. ISSN 0295-5075, 1286-4854. Available at:
https://iopscience.iop.org/article/10.1209/0295-5075/ad473e

[3]CAPRARO, V.; PERC, M.; VILONE, D. The evolution of lying in well-mixed
populations. Journal of The Royal Society Interface, v. 16, n. 156, p. 20190211, jul.
2019. ISSN 1742-5689, 1742-5662. Available at: https://royalsocietypublishing.org/doi/
10.1098/rsif.2019.0211

[4] GAUNERSDORFER, A.; HOFBAUER, J.; SIGMUND, K. On the dynamics
of asymmetric games. Theoretical Population Biology, v. 39, n. 3, p. 345–357,
jun. 1991. ISSN 00405809. Available at: https://linkinghub.elsevier.com/retrieve/pii/
004058099190028E
*/

