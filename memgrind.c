#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "mymalloc.h"

float test1 (int runs) {
    float total = 0.0;
    struct timeval start, end;
    for(int i = 0; i < runs; i++){
        gettimeofday(&start, NULL);
        for(int i = 0; i < 120; i++) {
            char *p = malloc(1);
            free(p);
        }
        gettimeofday(&end, NULL);
        float elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
        total += elapsed;
    }
    return total/runs;
}

float test2 (int runs) {
    float total = 0.0;
    struct timeval start, end;
    for(int i = 0; i < runs; i++){
        gettimeofday(&start, NULL);
        char *objects[120];
        for(int i = 0; i < 120; i ++){
            objects[i] = malloc(1);
        }
        for(int i = 0; i < 120; i ++){
            free(objects[i]);
        }
        gettimeofday(&end, NULL);
        float elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
        total += elapsed;
    }
    return total/runs;
}

float test3 (int runs) {
    float total = 0.0;
    struct timeval start, end;
    for(int i = 0; i < runs; i++){
        gettimeofday(&start, NULL);
        char *objects[120];
        int cur = 0;
        int count = 0;
        while (count < 120){
            if(rand() % 2) {
                objects[cur] = malloc(1);
                cur++;
                count++;
            }
            else if (cur != 0){
                cur--;
                free(objects[cur]);
            }
        }
        gettimeofday(&end, NULL);
        float elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
        total += elapsed;
        for (int j = 0; j < cur; j++) free(objects[j]);
    }
    return total/runs;
}


float test4 (int runs) {
    float total = 0.0;
    struct timeval start, end;
    for(int i = 0; i < runs; i++){
        gettimeofday(&start, NULL);
        char *objects[120];
        for(int i = 0; i < 120; i ++){
            objects[i] = malloc(1);
        }
        for(int i = 0; i < 120; i += 3){
            free(objects[i]);
        }
        for(int i = 1; i < 120; i += 3){
            free(objects[i]);
        }
        for(int i = 2; i < 120; i += 3){
            free(objects[i]);
        }
        gettimeofday(&end, NULL);
        float elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
        total += elapsed;
    }
    return total/runs;
}

float test5 (int runs) {
    float total = 0.0;
    struct timeval start, end;
    for(int i = 0; i < runs; i++){
        gettimeofday(&start, NULL);
        char *objects[120];
        for(int i = 0; i < 120; i += 4){
            objects[i] = malloc(sizeof(int)*1);
        }
        for(int i = 0; i < 120; i += 4){
            free(objects[i]);
        }
        gettimeofday(&end, NULL);
        float elapsed = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
        total += elapsed;
    }
    return total/runs;
}

int main () {
    printf("Test 1 Avg: %f\n", test1(50));
    printf("Test 2 Avg: %f\n", test2(50));
    printf("Test 3 Avg: %f\n", test3(50));
    printf("Test 4 Avg: %f\n", test4(50));
    printf("Test 5 Avg: %f\n", test5(50));
}