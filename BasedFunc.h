//
// Created by tester on 19.12.2019.
//

#ifndef LUQULC_BASEDFUNC_H
#define LUQULC_BASEDFUNC_H

#include "TreeLung.h"

#define CHECK_CALLOC(buf, string)                                   \
    if ((buf) == nullptr) {                                         \
        PRINT_ERROR (#string)                                       \
        free (buf);                                                 \
        return 0;                                                   \
    }



int comp (const trlt_t *left, const trlt_t *right);

int comp_ATL (const trlt_t *left, const trlt_t *right);

int find_num_in_lang (trlt_t *lexHL, char *str, bool second_cell = false);

char *ReadNotSpace (const char *name_file, size_t *size);

token_t *tokion (char *buf, size_t size);

void MakeAndStart (const char *path);

#endif //LUQULC_BASEDFUNC_H
