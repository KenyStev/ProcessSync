#include <iostream>
#include <thread>
#include <unistd.h>
#include "ProducerConsumer.h"
#include "ReaderWriter.h"

using namespace std;

int main()
{
    //ProducerConsumer
//    ProducerConsumer *p = new ProducerConsumer();
//    p->run();

    //ReaderWriter
    ReaderWriter *r = new ReaderWriter();
    r->run();

    return 0;
}
