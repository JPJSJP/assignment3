#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


//LRU에 대한 구조체입니다.

typedef struct LRU{
    int pid;
    char alloId;
    int startLoca;
    int endLoca;
} LRU;


void main(){

//과제에 사용한 변수를 선언하고 정의하는 과정입니다.
    char buff[1024];
    size_t n_size;
    
    int line_count = 0;
    int process_count = 0;
    int inst_count = 0;

    int pid = -1;
    int function = -1;
    int alloId = -1;
    int demandPage = -1;
    
    int physic_null_counter = 0;

//1KB의 물리메모리의 출력 형식을 만듭니다.

    char physic_mem[42];
    for(int i = 0; i < sizeof(physic_mem); i++) {
        if(i % 5 == 0) {
            physic_mem[i] = '|';
        }
        else {
            physic_mem[i] = '_';
            physic_null_counter++;
        }
    }
    physic_mem[41] = '\0';
   


    LRU *lru;
    int lru_pointer = 0;
    int lru_start = 0;



    char pid_page_aid[5][82];
    char pid_page_valid[5][82];



    int page_fault = 0;

    

//여기서부터 TXT파일을 읽어들이게 됩니다.

    while(fgets (buff, 1024, stdin)) {
        char line_tmp[32];

//첫번재 라인에선 프로세스의 수를 읽고 그와 관련된 작업을 처리합니다.

        if(line_count == 0) {
            process_count = atoi(strtok(buff, "\t ")); 
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

//두번째 라인에서는 인스트럭션의 수를 읽습니다.

        else if (line_count == 1) {
            inst_count = atoi(strtok(buff, "\t "));
            lru = malloc(sizeof(LRU)*inst_count);

            line_count++;
        }

//여기서부턴 세번째 라인부터 마지막 라인까지 인스트럭션을 처리합니다.

        else {
            pid = atoi(strtok(buff, "\t "));
            function = atoi(strtok(NULL, "\t "));
            alloId = atoi(strtok(NULL, "\t "));
            if(function == 1) {
//ALLOCATION
                demandPage = atoi(strtok(NULL, "\t "));
                int aid_counter = 0;
                for(int i = 0; i < sizeof(pid_page_aid[pid]); i++) {
                    if (aid_counter == demandPage) {break;}
                    else if (pid_page_aid[pid][i] == '_') {
                        pid_page_aid[pid][i] = alloId + '0';    
                        aid_counter++;
                        pid_page_valid[pid][i] = '0';
                    }
                    
                }


            }
            else {
//ACCESS
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


int alloId_exist = 0;

for(int i = 0; i < sizeof(physic_mem) ; i++) {
if (physic_mem[i] == alloId + '0' ) {
alloId_exist = 1;
break;
}

}

if(alloId_exist) {

int search_flag = 0;

LRU lru_tmp;


for(int i = lru_start; i < lru_pointer; i++) {
    if(lru[i].alloId == alloId + '0') {
        lru_tmp.pid = lru[i].pid;
        lru_tmp.alloId = lru[i].alloId;
        lru_tmp.startLoca = lru[i].startLoca;
        lru_tmp.endLoca = lru[i].endLoca;
        search_flag = 1;
    }
    
    if(search_flag == 1 && i != lru_pointer - 1) {
        lru[i].pid = lru[i+1].pid;
        lru[i].alloId = lru[i+1].alloId;
        lru[i].startLoca = lru[i+1].startLoca;
        lru[i].endLoca = lru[i+1].endLoca;
    }
    else if(search_flag == 1 && i == lru_pointer - 1) {
        lru[i].pid = lru_tmp.pid;
        lru[i].alloId = lru_tmp.alloId;
        lru[i].startLoca = lru_tmp.startLoca;
        lru[i].endLoca = lru_tmp.endLoca;
    }

}
}

else {

page_fault++;



                while(tmp > physic_null_counter) {
                    for(int i = 0; i< sizeof(pid_page_valid[lru[lru_start].pid]); i++) {
                        if(pid_page_aid[lru[lru_start].pid][i] == lru[lru_start].alloId) {
                            pid_page_valid[lru[lru_start].pid][i] = '0';
                        }
                    }
                    
                    for(int i = 0; i< sizeof(physic_mem); i++) {
                        if(physic_mem[i] == lru[lru_start].alloId) {
                            physic_mem[i] = '_';
                            physic_null_counter++;
                        } 
                    }
                    lru_start++;
                }

                int lru_start_tmp = -1;
                int lru_end_tmp;
                int stopword = 0;

                for(int i = 0; i< sizeof(physic_mem); i++) {
                    if(physic_counter == tmp) {
                        lru_end_tmp = i - stopword - 1;
                        break;
                    }
                    else if (physic_mem[i] == '_') {
                        if(lru_start_tmp == -1) {lru_start_tmp = i - stopword;}
                        physic_mem[i] = alloId + '0';
                        physic_counter++;
                        physic_null_counter--;;
                    }
                    else if(physic_mem[i] == '|') {
                        stopword++;
                    }
                }

                for(int i = 0; i <sizeof(pid_page_valid[pid]); i++) {
                    if(pid_page_aid[pid][i] == alloId + '0') {
                        pid_page_valid[pid][i] = '1';
                    }
                }
                


                lru[lru_pointer].pid = pid;
                lru[lru_pointer].alloId = alloId + '0';
                lru[lru_pointer].startLoca = lru_start_tmp;
                lru[lru_pointer].endLoca = lru_end_tmp;
                lru_pointer++;
}

            } 
        
            printf("* Input : Pid [%d] Function [%s] Alloc ID [%d] Page Num[%d]\n", pid, function==1?"ALLOCATION":"ACCESS", alloId, demandPage);


            printf("%-30s", ">> Physical Memory : "); 


            for(int i = 0; i < sizeof(physic_mem)-1; i++) {
               
                    if((physic_mem[i] == '_' || physic_mem[i] == '|') || (physic_mem[i] >= 48 && physic_mem[i] <= 57)) {
                        printf("%c", physic_mem[i]);
                    }
                    else {printf("%d", physic_mem[i] - '0');}
                     
            }
            printf("\n");
        


            for(int i = 0; i < process_count; i++) {

                printf(">> pid(%d) %-20s", i, "Page Table(AID) : "); 

                for(int k = 0; k < sizeof(pid_page_aid[i]) -1; k++) {
                    if((pid_page_aid[i][k] == '_' || pid_page_aid[i][k] == '|') || (pid_page_aid[i][k] >= 48 && pid_page_aid[i][k] <= 57)) {
                        printf("%c", pid_page_aid[i][k]);
                    }
                    else {printf("%d", pid_page_aid[i][k] - '0');}
                } 
                    printf("\n");


                    printf(">> pid(%d) %-20s", i, "Page Table(Valid) : "); printf("%s\n", pid_page_valid[i]);

            }

    
            printf("%-30s", ">> LRU : ");
            for(int i = lru_start; i < lru_pointer; i++) {
                if(lru[i].alloId >= 48 && lru[i].alloId <= 57) {
                    printf("%c:%i-%i ", lru[i].alloId, lru[i].startLoca, lru[i].endLoca);
                }
                else {printf("%i:%i-%i ", lru[i].alloId - '0', lru[i].startLoca, lru[i].endLoca);}
            }
            printf("\n\n");

        }
    }

    printf("page fault = %d\n\n", page_fault);

}
