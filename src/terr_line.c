#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "terr.h"

T_RET terr_hash_line_set
(
    Terr_hash    *p_hash,
    T_VOID       *p_node,
    T_UINT32      ul_index
)
{
    Terr_l_node   *p_st_l_node;
    Terr_l_node   *p_st_l;

    M_NULL_RET(p_hash);
    M_NULL_RET(p_node);

    p_st_l_node = (Terr_l_node *)p_node;
    M_NULL_RET(p_hash->p_hash);
    p_st_l = (Terr_l_node *)p_hash->p_hash;

    M_BOUNDS_RET(ul_index, p_hash->ul_size);

    p_st_l[ul_index].us_line_num = p_st_l_node->us_line_num;
    p_st_l[ul_index].us_line_sum++;
    p_st_l[ul_index].b_used = E_TERR_TOGGLE_ON;
    M_RET_S();
}

T_UINT32 terr_hash_line_used
(
    Terr_hash    *p_hash,
    T_UINT32      ul_index
)
{
    M_NULL_RET(p_hash);
    M_BOUNDS_RET(ul_index, p_hash->ul_size);
    M_NULL_RET(p_hash->p_hash);

    return ((Terr_l_node *)((T_UINT8 *)(p_hash->p_hash) + ul_index * p_hash->ul_node_size))->b_used;
}

T_UINT32 terr_hash_line_hash
(
    T_VOID    *p_node
)
{
    Terr_l_node   *p_st_l_node;
    M_NULL_RET(p_node);
    p_st_l_node = (Terr_l_node *)p_node;

    return p_st_l_node->us_line_num % TERR_HASH_LINE_T;
}

T_UINT32 terr_hash_line_more_hash
(
    Terr_hash  *p_hash,
    T_VOID     *p_node
)
{
    Terr_l_node   *p_st_l_node;
    Terr_l_node   *p_st_l;
    Terr_l_node   st_l_node_cpy;
    T_UINT32       ul_index;

    M_NULL_RET(p_hash);
    M_NULL_RET(p_node);

    p_st_l_node = (Terr_l_node *)p_node;
    p_st_l = p_hash->p_hash;
    M_NULL_RET(p_st_l);
    memcpy(&st_l_node_cpy, p_st_l_node, p_hash->ul_node_size);
    st_l_node_cpy.us_line_num++;
    ul_index = p_hash->st_hash_f.pf_hash((T_VOID *)&st_l_node_cpy);

    if (p_hash->st_hash_f.pf_cmp((T_VOID*)&(p_st_l[ul_index]), p_st_l_node))
    /* if (p_st_l[ul_index].us_line_num == p_st_l_node->us_line_num) */
    {
        return E_TERR_TOGGLE_ON;
    }

    return E_TERR_TOGGLE_OFF;
}

T_UINT32 terr_hash_line_cmp
(
    T_VOID  *p_node_a,
    T_VOID  *p_node_b
)
{
    if (T_NULL == p_node_a && T_NULL == p_node_b)
    {
        return E_TERR_TOGGLE_ON;
    }

    if (T_NULL == p_node_a || T_NULL == p_node_b)
    {
        return E_TERR_TOGGLE_OFF;
    }

    if (((Terr_l_node *)(p_node_a))->us_line_num == ((Terr_l_node *)(p_node_b))->us_line_num)
    {
        return E_TERR_TOGGLE_ON;
    }

    return E_TERR_TOGGLE_OFF;
}
