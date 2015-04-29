#ifndef TERRINC_H
#define TERRINC_H

#define TERR_STAT() \
    terr_stat(__FILE__, __LINE__);

extern unsigned int terr_stat
(
    char  *p_char,
    unsigned int ul_line
);

extern unsigned int terr_dump();

#endif /* TERRINC_H */
