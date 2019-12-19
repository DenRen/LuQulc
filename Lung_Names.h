#ifndef DIFFERENTIATOR_DIFF_NAMES_H
#define DIFFERENTIATOR_DIFF_NAMES_H

#define MAX_LEN_OPER    31
#define MAX_LEN_ARG     31
#define MAX_QUANT_ARG   32
/*
enum _data_type {
    NUM = 1,
    VAR, OPER_or_FUNC
};*/

enum operators_number {
    LOCALE, CRTqBIT,

    EQUAL_Q, ENT_Q, OPER_Q,
    EQUAL_M, MUL_M, POW_M,

    Mtx_H, Mtx_Y, Mtx_Z, Mtx_CNOT, Mtx_RCNOT,
    Mtx_I, Mtx_X,
    Mtx_ADD_1, Mtx_ADD_2, Mtx_ADD_3, Mtx_ADD_4,

    BRACE_ON, BRACE_OFF,
    BRACKET_ON, BRACKET_OFF,
    OPER_MES, MES,
    SEP, COMMA,
    NUM_OPER
};

enum separators {
    // При их изменении необходимо также изменить sscanf в Tree::read_expression
            LSEP = '(', RSEP = ')'
};

extern char _operators[NUM_OPER][MAX_LEN_OPER];

#define GTLEX GT->number
#define GTpp1 if (GT->type == tkn::LEX) printf ("GT: %s\n", ATL_lex[GT->number].trlt);      \
             else if (GT->type == tkn::NUM) printf ("GT: %d\n", GT->number);                \
             else printf ("GT: %s\n", GT->name); GT++;
#define GTpp GT++;

#define PREV *(GT - 1)

#define CRT(val, left_expr, right_expr) \
        crtNode (val, left_expr, right_expr, nullptr)

#define _NUM(value) crtNode (NUM, value, nullptr, nullptr, curr_node->prev)

#define L curr_node->left
#define R curr_node->right
#define C curr_node
#define _TYPE(curr_node) curr_node->data.type
#define _NUMBER(curr_node) curr_node->data.number

#define cL Copy (curr_node->left)
#define cR Copy (curr_node->right)
#define cN Copy (curr_node)

#endif //DIFFERENTIATOR_DIFF_NAMES_H
