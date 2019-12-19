//
// Created by tester on 27.11.2019.
//

#ifndef DIFFERENTIATOR_TEMPHEAD_H
#define DIFFERENTIATOR_TEMPHEAD_H

#include <cmath>

#include "Lung_Names.h"

            // TODO Tokeneater

namespace tkn {
    enum consts {
        NUM, LEX, STR
    };
}

struct token_t {
    int type;
    int number;
    char *name;
};

#define MAXLENCOMMAND 40

enum trlt_enum {
    USUAL,
    SYSTEM,
    FUNC
};

struct trlt_t {
    //char orig [MAXLENCOMMAND] = "";
    int orig;
    char trlt [MAXLENCOMMAND] = "";
    bool spec = false;
    int type = USUAL;
};

extern const char sep_code;
extern const char comm_code;
extern const int size_trlt;

extern token_t *GT;                      // Global token

extern trlt_t lexicon [];

extern trlt_t ATL_lex [];

char *find_trlt_type (int i);

extern char spec_symb [][MAXLENCOMMAND];



            // TODO Tree

typedef int number_t;


typedef token_t data_t;

enum consts {
    RIGHT,
    LEFT,
};

enum errors {
    ALL_RIGHT,
    EFILLROOT,
    EFILLNODE,
    EREAD,
    EADDRIGHT,
    EADDLEFT,
    SYNERROR,
    EUNIDENT,
    EARG
};

typedef struct nodeTree {
public:
    data_t data;
    nodeTree *prev;
    nodeTree *right;
    nodeTree *left;

    // Аргумент aux_arg может исопльзоваться для передачи, например указателя на дерево этого узла
    int visitor_pref_r (int (*func) (nodeTree *, void *), void *aux_arg = nullptr);
    int visitor_pref_r_m (int (*func) (nodeTree *, void *), void *aux_arg = nullptr);
} node_t;

typedef struct Tree {
    node_t *node;       // Указатель на корень

    Tree ();

    int verificator ();

    inline node_t *add_right (node_t *in_node, data_t value);

    inline node_t *add_left (node_t *in_node, data_t value);

    int read_expression (token_t *cur_tok);
    int write_expression (const char *name_file);

    static node_t *crtNode (data_t value, node_t *left, node_t *right, node_t *prev = nullptr);

    static node_t *Copy (const node_t *curr_node);

    static int del_Branch_Left (node_t *curr_node);     // Рекурентно удалить у переданного узла левую ветку

    static int del_Branch_Right (node_t *curr_node);    // Рекурентно удалить у переданного узла правую ветку

    static int del_Node_Left (node_t *curr_node);   // Вырезает узел с его левой частью из дерева, устраняя разрыв
    // Рекурентно удалить у переданного узла левую ветку, сам узел
    // и склеить правую ветку и родителя удалённого узла.
    static int del_Node_Right (node_t *curr_node);  // Вырезает узел с его правой частью из дерева, устраняя разрыв
    // Рекурентно удалить у переданного узла правую ветку, сам узел
    // и склеить левую ветку и родителя удалённого узла.

    static int set_Prev (node_t *curr_node);

    static node_t *getLoc   ();   // Главный :D
    static node_t *getLine  ();   // Получает выражение до ;
    static node_t *crtQBit  ();   // Если подаётся запрос на кубит

    static node_t *getNumb  ();   // Число
    static node_t *getExpr  ();   // Какая-то операция над кубитами q0 && q1 >= H;
    static node_t *getQBit  ();   // Переменная
    static node_t *getMtx   ();   // Матрица
    //static node_t *getFunc  ();   // Функция

    static node_t *getPosledQ   ();  // Последовательность q0 && q1 && ...
    static node_t *getPosledM   ();  // Последовательность q0 && q1 && ...


private:
    static node_t *add (int right_or_left, node_t *curr_node, data_t value);

    static node_t *get_new_node ();



    static int del_Branch (node_t *del_node);
} tree_t;

void Dump_Tree (node_t *head);

void Dump_Tree_img (node_t *head);

//void Dump_Tree_Tex (node_t *head, char *name_file = nullptr);

#include "BasedFunc.h"

#endif //DIFFERENTIATOR_TEMPHEAD_H
