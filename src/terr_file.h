#ifndef TERR_FILE_H
#define TERR_FILE_H

extern T_RET terr_hash_file_set
(
    Terr_hash    *p_hash,
    T_VOID       *p_node,
    T_UINT32      ul_index
);

extern T_UINT32 terr_hash_file_used
(
    Terr_hash    *p_hash,
    T_UINT32      ul_index
);

extern T_UINT32 terr_hash_file_hash
(
    T_VOID    *p_node
);

extern T_UINT32 terr_hash_file_more_hash
(
    Terr_hash  *p_hash,
    T_VOID     *p_node
);

extern T_UINT32 terr_hash_file_cmp
(
    T_VOID  *p_node_a,
    T_VOID  *p_node_b
);

#endif /* TERR_FILE_H */
