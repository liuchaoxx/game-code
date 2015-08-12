#ifndef _OX_COREUTILS_H
#define _OX_COREUTILS_H

#include <sys/timeb.h>
#include <time.h>
#include "../ox_commondef.h"


class CoreUtils
{
public:
    static INT64 GetCurrentTimme()
    {
        long long time_last;    
        time_last = time(NULL);     //×ÜÃëÊý  
        struct timeb t1;    
        ftime(&t1);   
        return t1.time * 1000 + t1.millitm;
    }
};

#endif