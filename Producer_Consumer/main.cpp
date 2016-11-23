#include <iostream>
#include <thread>
#include <unistd.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include "ProducerConsumer.h"
#include "ReaderWriter.h"
#include "Philosophers.h"

using namespace std;

int main()
{
    ProducerConsumer *p;
    ReaderWriter *r;
    Philosophers *ph;
    Semaphore *sem;

    printf("1. ProducerConsumer\n2. ReaderWriter\n3. Philosophers\nopt: ");
    int opt;
    cin>>opt;

    printf("MySem?(0/1)\n");
    int s;
    cin>>s;

    if(opt == 1) //ProducerConsumer
    {
        cout<<"entro al 1"<<endl;
        sem = (s==0)?(Semaphore*)new MySem(6):(Semaphore*)new Sem(6);
        p = new ProducerConsumer((s==0)?(Semaphore*)new MySem(0):(Semaphore*)new Sem(0),sem);
        p->run();
    }else if(opt == 2) //ReaderWriter
    {
        printf("entro al 2");
        sem = (s==0)?(Semaphore*)new MySem(1):(Semaphore*)new Sem(1);
        r = new ReaderWriter(sem);
        r->run();
    }else if(opt == 3) //Philosophers
    {
        printf("numero de filosofos: ");
        int num;
        cin>>num;
        sem = (s==0)?(Semaphore*)new MySem(num):(Semaphore*)new Sem(num);
        ph = new Philosophers(sem);
        ph->run();
    }

    return 0;
}
