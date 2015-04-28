#ifndef TERR_H
#define TERR_H
typedef unsigned int   T_UINT32;
typedef unsigned short T_UINT16;
typedef unsigned char  T_UINT8;
typedef char           T_CHAR;
typedef unsigned int   T_RET;
typedef unsigned int   T_TOGGLE;
#define T_VOID         void
#define T_NULL         0L

#define TERR_HASH_LINE_T 997 /* 997 is max prime number less than 1k */
#define TERR_HASH_FILE_SIZE  0xfff
#define TERR_HASH_LINE_SIZE  0xfff

#define TERR_STAT() \
    terr_stat(__FILE__, __LINE__);

/* return ret if p is null */
#define M_NULL_RET(p)                           \
    if (T_NULL == p)                            \
    {                                           \
        return E_TERR_RET_NULL_P;               \
    }

/* return ret null if p is null */
#define M_NULL_RET_NULL(p)                      \
    if (T_NULL == p)                            \
    {                                           \
        return T_NULL;                          \
    }

/* return ret if index out of bounds */
#define M_BOUNDS_RET(index,size)                \
    if ((index) >= (size))                      \
    {                                           \
        return E_TERR_RET_OUT_BOUNDS;           \
    }

/* return ret null if index out of bounds */
#define M_BOUNDS_RET_NULL(index,size)           \
    if ((index) >= (size))                      \
    {                                           \
        return T_NULL;                          \
    }

/* return ret if ret isn't E_RET_SUCCESS */
#define M_RET(ret)                              \
    if (E_TERR_RET_SUCCESS != ret)              \
    {                                           \
        return ret;                             \
    }

/* return E_RET_SUCCESS */
#define M_RET_S()                               \
    return E_TERR_RET_SUCCESS;

typedef enum
{
    E_TERR_RET_SUCCESS = 0,
    E_TERR_RET_ERROR,
    E_TERR_RET_NULL_P,
    E_TERR_RET_OUT_BOUNDS,
    E_TERR_RET_BUTT,
}E_TERR_RET;

typedef enum
{
    E_TERR_HASH_TYPE_FILE = 0,
    E_TERR_HASH_TYPE_LINE,
    E_TERR_HASH_TYPE_BUTT,
}E_TERR_HASH_TYPE;

typedef enum
{
    E_TERR_TOGGLE_OFF = 0,
    E_TERR_TOGGLE_ON,
}E_TERR_TOGGLE;

typedef struct _terr_hash Terr_hash;

/* 行号存储Hash节点 */
typedef struct _terr_line_node
{
    T_UINT16 us_line_num;
    T_UINT16 us_line_sum;
    T_UINT8  b_used:1;
    T_UINT8  uc_resbit:7;
    T_UINT8  uc_res[3];
}Terr_l_node;

typedef struct _terr_file_node
{
    T_CHAR    *pc_file;
    T_UINT32   ul_line_hash_index;
    T_UINT8    b_used:1;
    T_UINT8    uc_resbit:7;
    T_UINT8    uc_res[3];
}Terr_f_node;

typedef T_UINT32 (*Terr_hash_set)(Terr_hash*,T_VOID*,T_UINT32);
typedef T_UINT32 (*Terr_hash_used)(Terr_hash*, T_UINT32);
typedef T_UINT32 (*Terr_hash_hash)(T_VOID*);
typedef T_UINT32 (*Terr_hash_more_hash)(Terr_hash*, T_VOID*);
typedef T_UINT32 (*Terr_hash_cmp)(T_VOID*, T_VOID*);
typedef T_RET    (*Terr_hash_query)();

typedef struct _terr_hash_f
{
    Terr_hash_set       pf_set;
    Terr_hash_cmp       pf_cmp;
    Terr_hash_query     pf_query;
    Terr_hash_hash      pf_hash;
    Terr_hash_used      pf_used;
    Terr_hash_more_hash pf_more_hash;
}Terr_hash_f;

typedef struct _terr_hash
{
    T_UINT32      ul_size;
    T_UINT32      ul_type;
    T_UINT32      ul_node_size;
    Terr_hash_f   st_hash_f;
    T_VOID       *p_hash;
}Terr_hash;

/* function decale */
extern T_RET terr_stat
(
    T_CHAR  *p_char,
    T_UINT32 ul_line
);
extern T_RET terr_dump();
extern T_RET terr_init();

#endif /* TERR_H */




