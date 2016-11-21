#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

#include <thread>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Semaphore.h"

using namespace std;

class Philosophers
{
    public:
        Semaphore *sticks,*turn;

        Philosophers();
        virtual ~Philosophers();

        void run();
        void* Eat(Philosophers*parent,int index);
    protected:
    private:
};

#endif // PHILOSOPHERS_H
