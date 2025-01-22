#include <pcosynchro/pcosemaphore.h>

#ifndef PCOBARRIER_H
#define PCOBARRIER_H

class PcoBarrier
{
    unsigned int nbToWait;
    unsigned int count;
    PcoSemaphore sem;
    PcoSemaphore mutex;

public:
    PcoBarrier(unsigned int nbToWait)
        : nbToWait(nbToWait)
        , count(0)
        , sem(0)
        , mutex(1)
    {}

    ~PcoBarrier() {}

    void arrive()
    {
        mutex.acquire();
        ++count;

        if (count == nbToWait) {
            for (unsigned int i = 0; i < nbToWait; ++i) {
                sem.release();
            }
            count = 0;
        }

        mutex.release();
        sem.acquire();
    }
};

#endif // PCOBARRIER_H
