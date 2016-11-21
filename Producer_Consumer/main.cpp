#include <iostream>
#include <thread>
#include <unistd.h>
#include "ProducerConsumer.h"

using namespace std;

int main()
{
    ProducerConsumer *p = new ProducerConsumer();
    p->run();

    return 0;
}
