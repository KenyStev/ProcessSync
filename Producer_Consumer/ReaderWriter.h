#ifndef READERWRITER_H
#define READERWRITER_H

#include <thread>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
#include "Semaphore.h"

using namespace std;

class ReaderWriter
{
    public:
        string data;
        Semaphore *access_to_write;

        ReaderWriter();
        virtual ~ReaderWriter();
        void run();
        void* Reader(ReaderWriter * parent,int index);
        void* Writer(ReaderWriter * parent,string msg,int index);
    protected:
    private:
};

#endif // READERWRITER_H
