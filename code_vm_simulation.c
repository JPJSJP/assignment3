#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


void main(){
    char buff[1024];
    size_t n_size;
    
    int line_count = 0;
    int process_count = 0;
    int inst_count = 0;

    int pid = -1;
    int function = -1;
    int alloId = -1;
    int demandPage = -1;
    
    char physic_mem[42];
    for(int i = 0; i < sizeof(physic_mem); i++) {
        if(i % 5 == 0) {
            physic_mem[i] = '|';
        }
        else {
            physic_mem[i] = '_';
        }
    }
    physic_mem[41] = '\0';
   
    char pid_page_aid[5][82];
    char pid_page_valid[5][82];

    /*
    typedef struct LRU{
        char* alloId;
        char* startLoca;
        char* endLoca;
    } LRU;
    LRU* lru;
    LRU** lru_pointer = lru;
    LRU** lru_start = lru;
    */
    

    while(fgets (buff, 1024, stdin)) {
        char line_tmp[32];
        if(line_count == 0) {
            process_count = atoi(strtok(buff, "\t")); 
            line_count++;

            for(int i = 0; i < process_count; i++) {
                for(int k = 0; k < sizeof(pid_page_aid[i]); k++) {
                    if(k % 5 == 0) {
                        pid_page_aid[i][k] = '|';
                    }
                    else {
                        pid_page_aid[i][k] = '_';
                    }
                } 
                
                for(int g = 0; g < sizeof(pid_page_valid[i]); g++) {
                    if(g%5 == 0) {
                        pid_page_valid[i][g] = '|';
                    }
                    else {
                        pid_page_valid[i][g] = '_';
                    }
                }
                pid_page_valid[i][81] = '\0';

                pid_page_aid[i][81] = '\0';    
            }
        }
        else if (line_count == 1) {
            inst_count = atoi(strtok(buff, "\t"));
            line_count++;
        }
        else {
            //printf("%s\n", buff);
            pid = atoi(strtok(buff, " "));
            function = atoi(strtok(NULL, " "));
            alloId = atoi(strtok(NULL, " "));
            printf("%d%d%d\n\n",pid, function,alloId);
            if(function == 1) {
                demandPage = atoi(strtok(NULL, " "));
                int aid_counter = 0;
                for(int i = 0; i < sizeof(pid_page_aid[pid]); i++) {
                    if (aid_counter == demandPage) {break;}
                    else if (pid_page_aid[pid][i] == '_') {
                        pid_page_aid[pid][i] = alloId + '0';
                        //sprintf(pid_page_aid[pid][i], "%d", alloId);
                        aid_counter++;
                        pid_page_valid[pid][i] = '0';
                    }
                    
                }


            }
            else {
                demandPage = 0;
                int physic_counter = 0; 
                for(int i = 0; i < sizeof(pid_page_aid[pid]); i++) {
                    if (pid_page_aid[pid][i] == (alloId + '0')) {
                        demandPage++;
                    }
                }
                int count = 1;
                int tmp = demandPage;
                while(1) {
                    if((tmp = tmp/2) > 0) {
                        count++;
                    }
                    else {
                        break;
                    }
                }

                tmp = (int) pow(2.0,count);


                /*
                if(lru_pointer == lru_start) {
                }
                else {
                    *lru_pointer.alloId++ = alloId;
                }
                lru_pointer.alloId = alloId;
                lru_pointer.startLoca;
                lru_pointer.endLoce;

                */



                for(int i = 0; i< sizeof(physic_mem); i++) {
                    if(physic_counter == tmp) {break;}
                    else if (physic_mem[i] == '_') {
                        physic_mem[i] = alloId + '0';
                        physic_counter++;
                        //valid
                        //Lru
                    }
                }



                for(int i = 0; i <sizeof(pid_page_valid[pid]); i++) {
                    if(pid_page_aid[pid][i] == alloId + '0') {
                        pid_page_valid[pid][i] = '1';
                    }
                }

            } 
        
            printf("* Input : Pid [%d] Function [%s] Alloc ID [%d] Page Num[%d]\n", pid, function==1?"ALLOCATION":"ACCESS", alloId, demandPage);
            printf("%-30s", ">> Physical Memory : "); printf("%s\n", physic_mem);

            for(int i = 0; i < process_count; i++) {
                printf(">> pid(%d) %-20s", i, "Page Table(AID) : "); printf("%s\n", pid_page_aid[i]);
                printf(">> pid(%d) %-20s", i, "Page Table(Valid) : "); printf("%s\n", pid_page_valid[i]);

            }
    
            printf("%-30s\n\n", ">> LRU : ");




            //line_count++;

        }




    }




/*    printf("%-30s”, “>> Physical Memory : "); printf(현재 Physical Memory 현황 출력);
    printf(">> pid(%d) %-20s",pid, "Page Table(AID) : "); printf(현재 Page Table 현황 출력);
    printf(">> pid(%d) %-20s",pid, "Page Table(Valid) : "); printf(현재 Page Table 현황 출력);
    printf("%-30s", ">> LRU : ");
    printf(LRU list 현황 출력);
*/
}
