#include <stdio.h>
#include "../include/terrinc.h"
#include "terr_test.h"
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

    ul_ret = terr_dump();
    TERR_EXPECT(ul_ret);
    TERR_SUCCESS();
    return 0;
}
