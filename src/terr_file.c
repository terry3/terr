#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "terr.h"

T_RET terr_hash_file_set
(
    Terr_hash    *p_hash,
    T_VOID       *p_node,
    T_UINT32      ul_index
)
{
    Terr_f_node   *p_st_f_node;
    Terr_f_node   *p_st_f;

    M_NULL_RET(p_hash);
    M_NULL_RET(p_node);

    p_st_f_node = (Terr_f_node *)p_node;
    M_NULL_RET(p_hash->p_hash);
    p_st_f = (Terr_f_node *)p_hash->p_hash;

    M_BOUNDS_RET(ul_index, p_hash->ul_size);

    p_st_f[ul_index].pc_file = p_st_f_node->pc_file;
    p_st_f[ul_index].b_used = E_TERR_TOGGLE_ON;

    M_RET_S();
}

T_UINT32 terr_hash_file_used
(
    Terr_hash    *p_hash,
    T_UINT32      ul_index
)
{
    M_NULL_RET(p_hash);
    M_BOUNDS_RET(ul_index, p_hash->ul_size);
    M_NULL_RET(p_hash->p_hash);

    return ((Terr_f_node *)((T_UINT8 *)(p_hash->p_hash) + ul_index * p_hash->ul_node_size))->b_used;
}

T_UINT32 APHash(char* str, unsigned int len)
{
   unsigned int hash = 0xAAAAAAAA;
   unsigned int i    = 0;

   for(i = 0; i < len; str++, i++)
   {
      hash ^= ((i & 1) == 0) ? (  (hash <<  7) ^ (*str) * (hash >> 3)) :
                               (~((hash << 11) + ((*str) ^ (hash >> 5))));
   }

   return hash;
}

T_UINT32 terr_hash_file_more_hash
(
    Terr_hash  *p_hash,
    T_VOID     *p_node
)
{
    Terr_f_node   *p_st_f_node;
    Terr_f_node   *p_st_f;
    Terr_f_node   st_f_node_cpy;
    T_UINT32       ul_index;
    Terr_hash_cmp       pf_cmp;
    Terr_hash_hash      pf_hash;

    M_NULL_RET(p_hash);
    M_NULL_RET(p_node);

    p_st_f_node = (Terr_f_node *)p_node;
    p_st_f      = p_hash->p_hash;
    M_NULL_RET(p_st_f);
    pf_cmp      = p_hash->st_hash_f.pf_cmp;
    pf_hash     = p_hash->st_hash_f.pf_hash;
    M_NULL_RET(pf_cmp);
    M_NULL_RET(pf_hash);
    memcpy(&st_f_node_cpy, p_st_f_node, p_hash->ul_node_size);
    st_f_node_cpy.pc_file[0]++;
    ul_index    = pf_hash((T_VOID *)&st_f_node_cpy);

    if (pf_cmp((T_VOID*)&(p_st_f[ul_index]), p_st_f_node))
    /* if (p_st_f[ul_index].us_fine_num == p_st_f_node->us_fine_num) */
    {
        return E_TERR_TOGGLE_ON;
    }

    return E_TERR_TOGGLE_OFF;
}

T_UINT32 terr_hash_file_hash
(
    T_VOID    *p_node
)
{
    Terr_f_node   *p_st_f_node;
    M_NULL_RET(p_node);
    p_st_f_node = (Terr_f_node *)p_node;

    return APHash(p_st_f_node->pc_file, strlen(p_st_f_node->pc_file)) % TERR_HASH_LINE_T;
}

T_UINT32 terr_hash_file_cmp
(
    T_VOID  *p_node_a,
    T_VOID  *p_node_b
)
{
    T_CHAR   *pc_a;
    T_CHAR   *pc_b;
    if (T_NULL == p_node_a && T_NULL == p_node_b)
    {
        return E_TERR_TOGGLE_ON;
    }

    if (T_NULL == p_node_a || T_NULL == p_node_b)
    {
        return E_TERR_TOGGLE_OFF;
    }


    pc_a = ((Terr_f_node *)(p_node_a))->pc_file;
    pc_b = ((Terr_f_node *)(p_node_b))->pc_file;

    if (T_NULL == pc_a && T_NULL == pc_b)
    {
        return E_TERR_TOGGLE_ON;
    }

    if (T_NULL == pc_a || T_NULL == pc_b)
    {
        return E_TERR_TOGGLE_OFF;
    }

    if (0 == strcmp(pc_a, pc_b))
    {
        return E_TERR_TOGGLE_ON;
    }

    return E_TERR_TOGGLE_OFF;
}
