#include "ReaderWriter.h"

ReaderWriter::ReaderWriter()
{
    data = "Nada";
    access_to_write = new Sem(1);
}

ReaderWriter::~ReaderWriter()
{
    delete access_to_write;
}

void ReaderWriter::run()
{
    int NP=3, NC = 4;
    thread *idP[NP],*idC[NC];
    int index;

    idP[0] = new thread(&ReaderWriter::Writer,this,this,"Hola",0);
    idP[1] = new thread(&ReaderWriter::Writer,this,this,"Mundo",1);
    idP[2] = new thread(&ReaderWriter::Writer,this,this,"Adios",2);


    /*create a new Consumer*/
    for(index=0; index<NC; index++)
    {
        idC[index] = new thread(&ReaderWriter::Reader, this,this,index);
    }

    pthread_exit(NULL);
}

void* ReaderWriter::Reader(ReaderWriter * parent,int index)
{
    while(1)
    {
        printf("%d Reader read: %s\n",index,parent->data.c_str());
        sleep(2);
    }
}

void* ReaderWriter::Writer(ReaderWriter * parent,string msg,int index)
{
    while(1)
    {
        parent->access_to_write->wait();
        printf("%d Writer waiting\n",index);
        sleep(3);
        parent->data = msg;
        printf("%d Writer wrote: %s\n",index,parent->data.c_str());
        parent->access_to_write->signal();
        sleep(1);
    }
}
