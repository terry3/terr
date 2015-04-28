#include <stdio.h>
#include "../src/terr.h"
#include "terr_test.h"
#define TERR_TEST_SIZE 100

T_UINT32 terr_test_1()
{
    T_UINT32 ul_index;
    for (ul_index = 0; ul_index < TERR_TEST_SIZE; ul_index++)
    {
        TERR_STAT();
    }

    M_RET_S();
}

int main(int argc, char *argv[])
{
    T_UINT32     ul_ret;
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
