#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "terr.h"
#include "terr_line.h"
#include "terr_file.h"

#define MAX_LINE (4 * 10000)

Terr_hash  g_st_file_hash;
Terr_hash  *gp_st_line_hash[TERR_HASH_LINE_SIZE];

T_VOID* terr_hash_index
(
    Terr_hash *p_hash,
    T_UINT32   ul_index
)
{
    M_NULL_RET_NULL(p_hash);
    M_NULL_RET_NULL(p_hash->p_hash);

    M_BOUNDS_RET_NULL(ul_index, p_hash->ul_size);

    return (T_UINT8 *)(p_hash->p_hash) + ul_index * p_hash->ul_node_size;
}

T_RET terr_hash_insert
(
    Terr_hash  *p_st_hash,
    T_VOID     *p_node,
    T_UINT32   *p_ul_index      /* OUT param */
)
{
    T_UINT32            ul_hash_index;
    T_UINT32            ul_hash_size;
    Terr_hash_set       pf_set;
    Terr_hash_cmp       pf_cmp;
    Terr_hash_hash      pf_hash;
    Terr_hash_used      pf_used;
    Terr_hash_more_hash pf_more_hash;

    M_NULL_RET(p_st_hash);
    M_NULL_RET(p_node);
    M_NULL_RET(p_ul_index);

    M_NULL_RET(p_st_hash->st_hash_f.pf_hash);

    pf_set       = p_st_hash->st_hash_f.pf_set;
    pf_cmp       = p_st_hash->st_hash_f.pf_cmp;
    pf_more_hash = p_st_hash->st_hash_f.pf_more_hash;
    pf_used      = p_st_hash->st_hash_f.pf_used;
    pf_hash      = p_st_hash->st_hash_f.pf_hash;

    M_NULL_RET(pf_set);
    M_NULL_RET(pf_cmp);
    M_NULL_RET(pf_more_hash);
    M_NULL_RET(pf_used);
    M_NULL_RET(pf_hash);

    ul_hash_index = pf_hash(p_node);
    ul_hash_size  = p_st_hash->ul_size;
    do
    {
        if (pf_cmp(terr_hash_index(p_st_hash, ul_hash_index), p_node))
        {
            break;
        }

        while (pf_used(p_st_hash, ul_hash_index)
               && ul_hash_size--)
        {
            ul_hash_index = pf_more_hash(p_st_hash, p_node);
        }

    }while(0);

    pf_set(p_st_hash, p_node, ul_hash_index);
    *p_ul_index = ul_hash_index;
    M_RET_S();
}

T_RET terr_hash_init
(
    T_UINT32     ul_hash_size,
    T_UINT32     ul_node_size,
    T_UINT32     ul_hash_type,
    Terr_hash_f *p_st_hash_f,
    Terr_hash   *p_st_hash
)
{
    M_NULL_RET(p_st_hash_f);
    M_NULL_RET(p_st_hash);
    memset(p_st_hash, 0, sizeof(*p_st_hash));
    p_st_hash->ul_size = ul_hash_size;
    p_st_hash->ul_type = ul_hash_type;
    p_st_hash->ul_node_size = ul_node_size;
    memcpy(&(p_st_hash->st_hash_f), p_st_hash_f, sizeof(*p_st_hash_f));
    p_st_hash->p_hash = (T_VOID *)malloc(ul_hash_size * ul_node_size);
    M_NULL_RET(p_st_hash->p_hash);
    memset(p_st_hash->p_hash, 0, ul_hash_size * ul_node_size);
    M_RET_S();
}

T_RET terr_init_hash_line
(
    Terr_hash *p_st_hash
)
{
    Terr_hash_f   st_hash_f;
    T_RET         ul_ret;

    M_NULL_RET(p_st_hash);
    /* set hash function */
    st_hash_f.pf_cmp       = terr_hash_line_cmp;
    st_hash_f.pf_hash      = terr_hash_line_hash;
    st_hash_f.pf_used      = terr_hash_line_used;
    st_hash_f.pf_set       = terr_hash_line_set;
    st_hash_f.pf_more_hash = terr_hash_line_more_hash;

    ul_ret = terr_hash_init(TERR_HASH_LINE_SIZE,
                            sizeof(Terr_l_node),
                            E_TERR_HASH_TYPE_LINE,
                            &st_hash_f,
                            p_st_hash);
    M_RET(ul_ret);
    M_RET_S();
}

T_RET terr_stat
(
    T_CHAR  *p_char,
    T_UINT32 ul_line
)
{
    Terr_l_node  st_l_node;
    Terr_f_node  st_f_node;
    Terr_f_node  *p_st_f_node;

    T_UINT32     ul_index_out;
    T_UINT32     ul_ret;


    st_l_node.us_line_num = (T_UINT16)ul_line;
    st_f_node.pc_file = p_char;
    ul_ret =terr_hash_insert(&g_st_file_hash, &st_f_node, &ul_index_out);
    M_RET(ul_ret);
    M_BOUNDS_RET(ul_index_out, g_st_file_hash.ul_size);
    p_st_f_node = (Terr_f_node*)g_st_file_hash.p_hash;
    p_st_f_node = &(p_st_f_node[ul_index_out]);
    if (T_NULL == gp_st_line_hash[ul_index_out])
    {
        gp_st_line_hash[ul_index_out] = (Terr_hash *)malloc(sizeof(*gp_st_line_hash[0]));
        M_NULL_RET(gp_st_line_hash[ul_index_out]);
        ul_ret = terr_init_hash_line(gp_st_line_hash[ul_index_out]);
        M_RET(ul_ret);
    }
    p_st_f_node->ul_line_hash_index = ul_index_out;

    ul_ret = terr_hash_insert(gp_st_line_hash[ul_index_out], &st_l_node, &ul_index_out);
    M_RET(ul_ret);
    M_RET_S();
}


T_RET terr_init_hash_file()
{
    Terr_hash_f   st_hash_f;
    T_RET         ul_ret;
    /* set hash function */
    st_hash_f.pf_cmp       = terr_hash_file_cmp;
    st_hash_f.pf_hash      = terr_hash_file_hash;
    st_hash_f.pf_used      = terr_hash_file_used;
    st_hash_f.pf_set       = terr_hash_file_set;
    st_hash_f.pf_more_hash = terr_hash_file_more_hash;

    ul_ret = terr_hash_init(TERR_HASH_FILE_SIZE,
                            sizeof(Terr_f_node),
                            E_TERR_HASH_TYPE_FILE,
                            &st_hash_f,
                            &g_st_file_hash);

    M_RET(ul_ret);
    M_RET_S();
}


T_RET terr_init()
{
    T_RET    ul_ret;
    ul_ret = terr_init_hash_file();
    M_RET(ul_ret);
    M_RET_S();
}

T_RET terr_dump()
{
    T_UINT32 ul_index;
    T_UINT32 ul_l_index;
    Terr_f_node *p_f_node;
    Terr_l_node *p_l_hash;
    Terr_hash *p_st_hash = &g_st_file_hash;

    M_NULL_RET(p_st_hash);
    M_NULL_RET(p_st_hash->p_hash);
    p_f_node = p_st_hash->p_hash;
    for (ul_index = 0; ul_index < p_st_hash->ul_size; ul_index++)
    {
        if (p_f_node[ul_index].b_used)
        {
            p_l_hash = gp_st_line_hash[p_f_node[ul_index].ul_line_hash_index]->p_hash;
            M_NULL_RET(p_l_hash);
            for (ul_l_index = 0; ul_l_index < TERR_HASH_LINE_SIZE; ul_l_index++)
            {
                if (p_l_hash[ul_l_index].b_used)
                {
                    printf("file_used[%d],file[%s],line_used[%d],line[%d],sum[%d]\n", ul_index, p_f_node[ul_index].pc_file, ul_l_index, p_l_hash[ul_l_index].us_line_num, p_l_hash[ul_l_index].us_line_sum);

                }

            }

        }
    }
    M_RET_S();
}
