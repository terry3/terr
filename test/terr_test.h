#ifndef TERR_TEST_H
#define TERR_TEST_H



#define TERR_EXPECT(s)                          \
    if ((s) != E_TERR_RET_SUCCESS)              \
    {                                           \
        printf("Terr error src[%d], line[%d]", (s), __LINE__); \
    }

#define TERR_SUCCESS()\
    printf("Terr OK."); \


#endif /* TERR_TEST_H */
