libterr
========

terr is a _library_ for record function run statistics in C.

* __Fast__ All hash design.
* __Common Use__ All ANSI c implementation.

Example
-------

```c
/* Example libterr Program */
#include <stdio.h>
#include "terrinc.h"

#define TERR_TEST_SIZE 100

unsigned int terr_test_1()
{
    unsigned int ul_index;
    for (ul_index = 0; ul_index < TERR_TEST_SIZE; ul_index++)
    {
        TERR_STAT();
    }

    return 0;
}

int main(int argc, char *argv[])
{
    unsigned int     ul_ret;
    ul_ret = terr_init();
    TERR_EXPECT(ul_ret);
    TERR_STAT();
    terr_test_1();

    TERR_STAT();
    terr_dump();

    return 0;
}
```

_terry3 (terryr3rd at yeah.net)
