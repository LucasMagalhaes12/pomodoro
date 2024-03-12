#ifdef _WIN64
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define TOTALHASHTAG 10

unsigned short int totalTime = 25;
char taskName[50] = "Pomodoro";


void printHelp() {
    printf("\
Usage: pomodoro [options] ...\n\n\
Options:\n\n\
--help / -h                 Display this information.\n\
--name / -n [activity name] Set name for pomodoro.\n\
--time / -t [time]          set time in minutes for pomodoro.\n");
}


bool input(int numargs, char *arg[]) {
    for (int i=1; i < numargs; i++) {
        if (numargs-1 != i) {
            if (!strcmp(arg[i], "-n") || !strcmp(arg[i], "--name"))
                strcpy(taskName, arg[i+1]);

            else if (!strcmp(arg[i], "-t") || !strcmp(arg[i], "--time")) {
                if (atoi(arg[i+1]) > 0)
                    totalTime = atoi(arg[i+1]);
            }
        }
        if (!strcmp(arg[i], "-h") || !strcmp(arg[i], "--help")) {
            printHelp();
            return true;
        }
    }
    return false;
}


void showTime(unsigned int min, unsigned int sec) {
    system("clear");
    printf("Time: %02d:%02d ", min, sec);
}


void statusBar(unsigned int min, unsigned int sec) {
    printf("[");
    unsigned int amountHashtag = ((min*60+sec) * TOTALHASHTAG) / (totalTime*60);
    
    for (int i=0; i<TOTALHASHTAG - amountHashtag; i++)
        printf("#");
    
    for (int i=0; i<amountHashtag; i++)
        printf(".");

    printf("]\n");
}


void timeControl() {
    unsigned short int min = totalTime, sec = 0, miliseconds=0;
    do {
        showTime(min, sec);
        statusBar(min, sec);

        #ifdef _WIN64
            Sleep(1000);
        #else
            usleep(1000000);
        #endif

        if (sec == 0) {
            min--;
            sec = 59;
        }
        else
            sec--;
    } while (min>0 || sec>0);
}


void writeText(char *path) {
    FILE *file = fopen(path, "a");

    if (file != NULL) {
        struct tm *localTime;
        time_t timeSeconds;
        time(&timeSeconds);
        localTime = localtime(&timeSeconds);
        fprintf(file, "%d.%d.%d;", localTime->tm_mday, localTime->tm_mon+1, localTime->tm_year+1900);
        fprintf(file, "%d:%d:%d;", localTime->tm_hour, localTime->tm_min, localTime->tm_sec);
        fprintf(file, "%s;%d\n", taskName, totalTime);
        fclose(file);
        printf("Write Sucessful!\n");
    }
    else
        printf("Error Open File!\n");
}


void main(int numargs, char *arg[]) {
    bool justInformation = input(numargs, arg);
    
    if (!justInformation) {
        timeControl(totalTime);
        writeText("log.csv");
        printf("Time is Over\a\n");
        for (int i=0; i<10; i++) {
            #ifdef _WIN64
                Sleep(1000);
            #else
                usleep(1000000);
            #endif
        }
    }
}
