#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void instruction();

typedef struct procceses
{
    int childP;
    int avg;
    int fatherID;
} procDat;

int main(int argc, char * const *argv)
{
    char * procNum = NULL;
    int args, itSup = 0, procNumInt = 0, contPID = 0, hijoCount = 0, state, avg = 0, counter = 0, index, fatherID = 0;

    pid_t pId;

    if (args = getopt(argc, argv, "n:") == 'n')
    {
        procNum = optarg;

        procNumInt = atoi(procNum);

        printf("Procesos a crear: %d\n\n", procNumInt);
    }

    pid_t * procCount = malloc(sizeof(pid_t) * procNumInt);
    int * total = procCount + procNumInt;
    int * contProcs = procCount;

    while ((contProcs < total) && (counter < procNumInt))
    {
        pId = fork();
        *contProcs = pId;

        if (pId == -1)
        {
            printf("Error. Hijo no pudo ser creado, se crearon %d hijos\n", hijoCount);
        }

        else if(pId == 0){

            fatherID = getppid();
            int son = getpid();

            avg = (fatherID + son)/2;
            printf("Soy el proceso hijo con PID = %d y mi promedio es = %d\n", son, avg);

            sleep(1);
            exit(avg);


        }


        else
        {
            hijoCount += 1;
        }
        ++counter;
        ++contProcs;

    }



    contProcs = procCount;

    procDat *proc = (procDat *)malloc(sizeof(procDat) * procNumInt);

    procDat *fin = proc + procNumInt;
    procDat *helper = proc;
    procDat *cont = proc;

    while ((helper < fin) && (contProcs < total)){

        if (waitpid(*contProcs, &index, 0) != -1){

            if (WIFEXITED(index)){

                helper->childP = *contProcs;
                helper->avg = WEXITSTATUS(index);

            }
        }

        ++helper;
        ++contProcs;
    }

    printf("\nPID Hijo \t Promedio \t Histograma");

    for (procDat *countX = proc; countX < fin; countX++)
    {

        int pidHijo = countX->childP;

        printf("\n%d \t\t %d \t\t ", pidHijo, countX->fatherID);

        for (int i = 0; i < 10; i++)
        {
            printf("*");
        }
        
    }

    free(proc);
    free(procCount);

    return 0;
}