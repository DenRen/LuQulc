//
// Created by tester on 18.12.2019.
//


// TODO FUNCTION FOR SYSTEM STRUCT

#include <cassert>
#include <cstdio>
#include <cstring>
#include "TreeLung.h"
#include "../../../CLionProjects/SandBoxQ/MyLib3.h"

Tree::Tree () {
    node = nullptr;
    if ((node = get_new_node ()) == nullptr) {
        perror ("Error construct tree");
        return;
    }
    node->left = node->right = nullptr;
    node->prev = node;
    assert (verificator ());
}

int nodeTree::visitor_pref_r (int (*func) (nodeTree *, void *), void *aux_arg) {
    // Визитор для строк, так как делает проверку на nullptr в data
    // Справа налево
    // Нет проверки на существование данных в узле !!!
    int state = 0;

    if ((state = func (this, aux_arg)) != 0)
        return state;

    if (right != nullptr && (state = right->visitor_pref_r (func, aux_arg)) != 0)
        return state;

    if (left != nullptr && (state = left->visitor_pref_r (func, aux_arg)) != 0)
        return state;

    return 0;
}

int nodeTree::visitor_pref_r_m (int (*func) (nodeTree *, void *), void *aux_arg) {
    // Визитор для строк, так как делает проверку на nullptr в data
    // Справа налево
    // Нет проверки на существование данных в узле !!!
    int state = 0;

    if (right != nullptr && (state = right->visitor_pref_r_m (func, aux_arg)) != 0)
        return state;

    if ((state = func (this, aux_arg)) != 0)
        return state;

    if (left != nullptr && (state = left->visitor_pref_r_m (func, aux_arg)) != 0)
        return state;

    return 0;
}

int Tree::verificator () {
    assert (node != nullptr);
    assert (node->prev != nullptr);   // Предком корня может быть только он сам

    return 1;
}

inline node_t *Tree::add_right (node_t *in_node, data_t value) {
    return add (RIGHT, in_node, value);
}

inline node_t *Tree::add_left (node_t *in_node, data_t value) {
    return add (LEFT, in_node, value);
}

node_t *Tree::add (int right_or_left, node_t *curr_node, data_t value) {
    // Не используется удобное добавление непосредственно и использованием БД
    //assert (verificator ());
    node_t *new_node = nullptr;                         // Указатель новый узел
    node_t **temp_ptr = nullptr;                        // Указатель для определения выбора режима вставки

    if (right_or_left == RIGHT)
        temp_ptr = &(curr_node->right);
    else
        temp_ptr = &(curr_node->left);

    if ((new_node = get_new_node ()) == nullptr)
        return nullptr;                                 // Критическая ошибка

    new_node->data = value;
    new_node->prev = curr_node;

    // Вставить между узлами новый узел
    // А его left и right указывают на следующий элемент (right == left)
    // сделать проверку на этот случай
    if ((new_node->left = new_node->right = *temp_ptr) != nullptr) {

        if (curr_node->left == curr_node->right)            // Для случая, когда в исходном
            new_node->left = new_node->right = nullptr;     // дереве указатели на left и right были равны
        else
            (*temp_ptr)->prev = new_node;
    }

    *temp_ptr = new_node;
    return new_node;
}

node_t *Tree::get_new_node () {
    node_t *new_node = nullptr;
    if ((new_node = new node_t{0}) == nullptr) {
        perror ("Failed to create a new node");
        return nullptr;
    }

    return new_node;
}



            // TODO FUNCTION FOR DIFF

unsigned char _arguments[MAX_QUANT_ARG][MAX_LEN_ARG + 1] = {0};     // Не существует нулевых аргументов

int add_or_check_arg (const char *argument) {
    for (int i = 0; i < MAX_QUANT_ARG; i++)
        if (!_arguments[i][0]) {
            if (strcpy ((char *) _arguments[i], argument) == nullptr) {
                if (strlen (argument) > MAX_LEN_ARG) {
                    perror ("Error to add a new argument: argument name too long");
                    return -1;
                }
                perror ("Error to add a new argument");
                return -1;
            } else
                return i;
        } else if (strcmp ((char *) _arguments[i], argument) == 0)
            return i;

    perror ("Too many arguments!");
    return -1;
}

int add_or_check_arg_or_func (const char *argument) {
    for (int i = 0; i < MAX_QUANT_ARG; i++)
        if (!_arguments[i][0]) {
            if (strcpy ((char *) _arguments[i], argument) == nullptr) {
                if (strlen (argument) > MAX_LEN_ARG) {
                    perror ("Error to add a new argument: argument name too long");
                    return -1;
                }
                perror ("Error to add a new argument");
                return -1;
            } else
                return i;
        } else if (strcmp ((char *) _arguments[i], argument) == 0)
            return i;

    perror ("Too many arguments!");
    return -1;
}

number_t get_ind_oper (char *oper) {
    for (int i = 0; i < NUM_OPER; i++)
        if (strcmp (oper, _operators[i]) == 0)
            return i;
    return -1;
}

node_t *Tree::crtNode (token_t value, node_t *left, node_t *right, node_t *prev) {
    node_t *new_node = nullptr;

    if ((new_node = get_new_node ()) == nullptr) {
        perror ("ERROR IN DIFF");
        return nullptr;
    }
    new_node->data = value;

    new_node->prev = prev;
    if (left != nullptr)
        new_node->left = left;
    if (right != nullptr)
        new_node->right = right;
    return new_node;
}

node_t *Tree::Copy (const node_t *curr_node) {
    node_t *new_node = nullptr;

    if ((new_node = get_new_node ()) == nullptr) {
        perror ("Error copy tree");
        return nullptr;
    }

    new_node->data = curr_node->data;
    new_node->prev = curr_node->prev;

    if (curr_node->left != nullptr)
        if ((new_node->left = Copy (curr_node->left)) == nullptr) {
            perror ("Error copy left tree");
            return nullptr;
        }
    if (curr_node->right != nullptr)
        if ((new_node->right = Copy (curr_node->right)) == nullptr) {
            perror ("Error copy right tree");
            return nullptr;
        }
    return new_node;
}



            // TODO FUNCTION FOR OPTIMIZER
/*
int Tree::Optimizer (node_t *head_node) {
    if (head_node == nullptr)
        return 0;
    // Оптимизируем, пока не перестанет изменяться
    while (true) {
        if (!Opt (head_node))
            continue;
        else if (Opt (head_node))
            break;
        else
            continue;
    }

    return 1;
}
*/
int Tree::set_Prev (node_t *curr_node) {
    if (R != nullptr) {
        R->prev = curr_node;
        set_Prev (R);
    }

    if (L != nullptr) {
        L->prev = curr_node;
        set_Prev (L);
    }

    return 0;
}



            // TODO FUNCTION FOR DEL BRANCH OR NODE

int Tree::del_Branch_Left (node_t *curr_node) {
    if (curr_node->left != nullptr) {
        del_Branch (curr_node->left);
        curr_node->left = nullptr;
    }
    return 0;
}

int Tree::del_Branch_Right (node_t *curr_node) {
    if (curr_node->right != nullptr) {
        del_Branch (curr_node->right);
        curr_node->right = nullptr;
    }
    return 0;
}

int Tree::del_Branch (node_t *del_node) {
    if (del_node->right != nullptr) {
        del_Branch (del_node->right);
        del_node->right = nullptr;
    }

    if (del_node->left != nullptr) {
        del_Branch (del_node->left);
        del_node->left = nullptr;
    }

    free (del_node);
    return 0;
}

int Tree::del_Node_Left (node_t *curr_node) {
    del_Branch_Left (curr_node);

    node_t **ptrPrev_to_curr = nullptr;         // Сюда будет записан указатель на ячейку родителя, которая указывает на
    // текущее дерево

    if (curr_node->prev->left == curr_node)     // Получаем этот указатель
        ptrPrev_to_curr = &(curr_node->prev->left);
    else
        ptrPrev_to_curr = &(curr_node->prev->right);

    if (curr_node->prev != curr_node) {         // Если это не корень
        if (R != nullptr) {
            R->prev = curr_node->prev;
            *ptrPrev_to_curr = R;
            free (curr_node);
        } else {
            free (curr_node);
            *ptrPrev_to_curr = nullptr;
        }
    } else if (R != nullptr) {                                    // Если это корень
        node_t *save_R_node = R;
        *curr_node = *R;
        if (L != nullptr)
            L->prev = curr_node;
        if (R != nullptr)
            R->prev = curr_node;
        free (save_R_node);
    }
    return 0;
}

int Tree::del_Node_Right (node_t *curr_node) {
    del_Branch_Right (curr_node);

    node_t **ptrPrev_to_curr = nullptr;         // Сюда будет записан указатель на ячейку родителя, которая указывает на
    // текущее дерево

    if (curr_node->prev->left == curr_node)     // Получаем этот указатель
        ptrPrev_to_curr = &(curr_node->prev->left);
    else
        ptrPrev_to_curr = &(curr_node->prev->right);

    if (curr_node->prev != curr_node) {         // Если это не корень
        if (L != nullptr) {
            L->prev = curr_node->prev;
            *ptrPrev_to_curr = L;
            free (curr_node);
        } else {
            free (curr_node);
            *ptrPrev_to_curr = nullptr;
        }
    } else if (L != nullptr) {                                    // Если это корень
        node_t *save_L_node = L;
        *curr_node = *L;
        if (R != nullptr)
            R->prev = curr_node;
        if (L != nullptr)
            L->prev = curr_node;
        free (save_L_node);
    }
    return 0;
}



            // TODO FUNCTION FOR DUMP

namespace Dtdot {

    int ident_dot (node_t *node, void *) {
        printf ("\t%zu [label = \"", (size_t) node);
        if (node->data.type == tkn::NUM) {
            printf ("%d\"];\n", node->data.number);
        } else if (node->data.type == tkn::LEX) {
            printf ("%s\"];\n", ATL_lex[node->data.number].trlt);
        } else if (node->data.type == tkn::STR)
            printf ("%s\"];\n", node->data.name);
        else {
            printf (" \"]");
        }
        return 0;
    }

    int build_tree_dot (node_t *node, void *) {
        if (node->left != nullptr)
            printf ("\t%zu -> %zu [label = \"L\"]\n", (size_t) node, (size_t) node->left);

        if (node->right != nullptr)
            printf ("\t%zu -> %zu [label = \"R\"]\n", (size_t) node, (size_t) node->right);

        return 0;
    }

    inline void recreate_dot_dir () {
        system ("rm -rf TreeSnapshot/ 2> /dev/null");
        system ("mkdir TreeSnapshot");
        system ("touch TreeSnapshot/README.txt; echo This folder constatly deleted! > TreeSnapshot/README.txt");
    }

    bool fill_dot_file (node_t *head) {
        FILE *file_dot = fopen ("temp_file.dot", "w");
        if (file_dot == nullptr) {
            perror ("DONT CREATE FILE_DOT");
            return false;
        }

        fprintf (file_dot, "digraph G {\n"
                           "    rankdir = TR;\n"
                           "    node[shape=ellipse, fontsize=50, color = red];\n"
                           "    edge[fontsize=25, color = blue, fillcolor = blue];\n");

        FILE *save_stdout = stdout;
        stdout = file_dot;                        // Крайне удобный приём для перенаправления потока

        head->visitor_pref_r (ident_dot);         // Идентифицирую каждый узел и связываю его с его содержимым

        fprintf (file_dot, "\n");

        head->visitor_pref_r (build_tree_dot);    // Строю дерево

        fprintf (file_dot, "}");

        fclose (file_dot);
        stdout = save_stdout;
        return true;
    }
}

int tex_printf (node_t *curr_node, FILE *file) {
    if (curr_node == nullptr)
        return 0;
/*
    switch (_TYPE (C)) {
        case NUM:
            fprintf (file, " %lg ", _NUMBER (C));
            break;
        case VAR:
            fprintf (file, " %s ", _arguments[(int) _NUMBER (C)]);
            break;
        default:
            switch ((int) _NUMBER (C)) {
                case ADD:
                case SUB:
                    fprintf (file, "(");
                    tex_printf (L, file);
                    fprintf (file, " %s ", _operators[(int) _NUMBER (C)]);
                    tex_printf (R, file);
                    fprintf (file, ")");
                    break;
                case MUL:
                case POW:
                    tex_printf (L, file);
                    fprintf (file, " %s ", _operators[(int) _NUMBER (C)]);
                    tex_printf (R, file);
                    break;
                case DIV:
                    fprintf (file, "\\frac {");
                    tex_printf (L, file);
                    fprintf (file, "}{");
                    tex_printf (R, file);
                    fprintf (file, "}");
                    break;
                default:
                    fprintf (file, " %s(", _operators[(int) _NUMBER (C)]);
                    tex_printf (R, file);
                    fprintf (file, ")");
            }
    }
*/
    /*
    fprintf (file, "(");

    if (node->left != nullptr) {
        if (tex_printf (node->left, file) < 0) {
            perror ("Failed to visitor")
            return -1;
        }
    }

    switch (node->data.type) {
        case OPER_or_FUNC:
            fprintf (file, "%s", &(_operators[(int) node->data.number][0]));
            break;
        case VAR:
            fprintf (file, "%c", 'x');
            break;
        case NUM:
            fprintf (file, "%lg", node->data.number);
            break;
        default:
            perror ("Undefined type's node")
    }

    if (node->right != nullptr) {
        if (tex_printf (node->right, file) < 0) {
            perror ("Failed to visitor")
            return -1;
        }
    }

    fprintf (file, ")");
*/
    return 0;
}

void Dump_Tree_Tex (node_t *head, char *name_file) {
    static int number_calls = 0;

    char name[256] = "";
    sprintf (name, "%s.tex", name_file);

    FILE *file = nullptr;

    if (name_file == nullptr)
        file = stdout;
    else if ((file = fopen (name, "w")) == nullptr) {
        perror ("Error create TEX file");
        return;
    }

    fprintf (file, "%s", "\\begin{document}$\n");

    if (tex_printf (head, file) < 0) {
        perror ("Failed to visitor");
    }

    fprintf (file, "%s", "\n$\\end{document}");
    fclose (file);

    char sys_call[128] = "";
    sprintf (sys_call, "texi2pdf %s -b > /dev/null; mv %s.pdf %d.pdf;",
             name, name_file, number_calls);
    system (sys_call);

    sprintf (sys_call, "xdg-open %d.pdf", number_calls);
    system (sys_call);
    number_calls++;
}
/*
int spec_printf (node_t *node, void *) {
    if (node->data.type == VAR) {
        printf ("%s:\n", _arguments[(int) node->data.number]);
    } else if (node->data.type == OPER_or_FUNC) {
        printf ("%s:\n", _operators[(int) node->data.number]);
    } else if (node->data.type == NUM)
        printf ("%lg:\n", node->data.number);

    if (node->right != nullptr) {
        if (node->right->data.type == VAR) {
            printf ("\tright: %s\n", _arguments[(int) node->data.number]);
        } else if (node->right->data.type == OPER_or_FUNC) {
            printf ("\tright: %s\n", _operators[(int) node->right->data.number]);
        } else if (node->right->data.type == NUM)
            printf ("\tright: %lg\n", node->right->data.number);
    }

    if (node->left != nullptr) {
        if (node->left->data.type == VAR) {
            printf ("\tleft: %s\n", _arguments[(int) node->data.number]);
        } else if (node->left->data.type == OPER_or_FUNC) {
            printf ("\tleft: %s\n", _operators[(int) node->left->data.number]);
        } else if (node->left->data.type == NUM)
            printf ("\tleft: %lg\n", node->left->data.number);
    }
    return 0;
}

void Dump_Tree (node_t *head) {
    printf ("\n\n");
    if (head->visitor_pref_r (spec_printf) < 0) {
        perror ("Failed to visitor");
    }
    printf (R"(//////END\\\\\\)");
}
*/

void Dump_Tree_img (node_t *head) {
    static size_t number_calls = 0;
    static bool first = false;

    // Удаляю папку со старыми данными и создаю пустую новую для хранения результата (фото, видео, GIF)
    if (!first) {
        Dtdot::recreate_dot_dir ();
        first = true;
    }

    if (!Dtdot::fill_dot_file (head))
        return;

    char comand[256] = "";
    sprintf (comand, "dot -Tsvg -Gsize=10,20\\! temp_file.dot -o TreeSnapshot/%zu.svg", number_calls);
    system (comand);

    number_calls++;
}



int Tree::read_expression (token_t *source) {
    if ((GT = source) == nullptr) {
        perror ("Empty source");
        return -1;
    }

    this->node = getLoc ();

    printf ("\n");

    return 0;
}

token_t *GT = nullptr;                   // Global token

node_t *Tree::getLoc () {
    node_t *cur_node = nullptr;
    node_t *NextL = nullptr, *NextR = nullptr;

    //GTpp
    if (GTLEX == LOCALE) {
        GTpp;
        if (GTLEX == BRACE_ON) {
            GTpp
            token_t curr = *(GT - 2);

            NextR = getLine ();

            cur_node = CRT (curr, nullptr, NextR);
            if (GTLEX == BRACE_OFF)
                return cur_node;
        }
    }

    PRINT_ERROR ("Failed to get locale")

    return nullptr;
}

node_t *Tree::getLine () {
    node_t *curr_node = nullptr;

    if ((curr_node = crtQBit ()) != nullptr ||
        (curr_node = getExpr ()) != nullptr) {
        if (GTLEX == SEP) {
            GTpp
            return CRT (PREV, C, getLine ());
        } else {
            PRINT_ERROR ("SYNTAX ERROR")
            return 0;
        }
    }

    return nullptr;
}

node_t *Tree::crtQBit () {

    if (GTLEX == CRTqBIT) {
        token_t curr = *GT;
        node_t *NextL = nullptr, *NextR = nullptr;

        GTpp

        if ((NextL = getQBit ()) != nullptr) {

            if (GTLEX == EQUAL_Q) {
                GTpp
                if ((NextR = getNumb ()) != nullptr) {
                    return CRT (curr, NextL, NextR);
                }
            }
        }

        PRINT_ERROR ("SYNTAX ERROR")
        assert (0);
        return nullptr;
    }

    return nullptr;
}

node_t *Tree::getNumb () {
    if (GT->type == tkn::NUM) {
        GTpp
        return CRT (PREV, nullptr, nullptr);
    }

    return nullptr;
}
/*
node_t *Tree::getExpr () {
    return nullptr;
}*/

node_t *Tree::getQBit () {
    if (GT->type == tkn::STR && GT->name != nullptr) {
        GTpp;
        return CRT (PREV, nullptr, nullptr);
    }

    return nullptr;
}

node_t *Tree::getExpr () {
    node_t *C = getPosledQ ();

    if (C != nullptr) {
        if (GTLEX == OPER_Q || GTLEX == OPER_MES) {
            GTpp
            token_t curr = PREV;
            node_t *NextR = getPosledM ();
            return CRT (curr, C, NextR);
        }

        PRINT_ERROR ("SYNTAX_ERROR")

        assert (0);
    }

    return nullptr;
}

node_t *Tree::getPosledQ () {

    if (GTLEX == ENT_Q) {
        GTpp
    }

    node_t *curr_node = getQBit ();

    if (curr_node != nullptr)
        return CRT ((token_t {tkn::LEX, ENT_Q, nullptr}),
                    curr_node, getPosledQ ());

    return nullptr;
}

node_t *Tree::getPosledM () {
    if (GTLEX == MUL_M) {
        GTpp
    }

    node_t *curr_node = getMtx ();

    if (curr_node != nullptr)
        return CRT ((token_t {tkn::LEX, MUL_M, nullptr}),
                    curr_node, getPosledM ());

    return nullptr;
}

node_t *Tree::getMtx () {
    switch (GTLEX) {
        case Mtx_H:
        case Mtx_Y:
        case Mtx_Z:
        case Mtx_CNOT:
        case Mtx_RCNOT:
        case Mtx_I:
        case Mtx_X:
        case Mtx_ADD_1:
        case Mtx_ADD_2:
        case Mtx_ADD_3:
        case Mtx_ADD_4:
        case MES:
            GTpp
            return CRT (PREV, nullptr, nullptr);
    }

    return nullptr;
}

void req_write_code (node_t *curr_node, FILE* file) {
    if (curr_node == nullptr)
        return;

    if (_TYPE (C) == tkn::LEX) {
        switch (_NUMBER (C)) {
            case LOCALE:
                fprintf (file, "#include \"Qulc.h\"\n\n"
                        "int main () { \n\n\t"
                        "qRAM_t *_qRAM = new qRAM_t (10);\n\n\t");
                req_write_code (R, file);
                fprintf (file, "\n}");
                break;

            case SEP:
                req_write_code (L, file);
                fprintf (file, ";\n\t");
                req_write_code (R, file);
                break;

            case CRTqBIT:
                fprintf (file, "qBit_t %s (\"%d\", _qRAM)", L->data.name, R->data.number);
                break;

            case OPER_Q:
            case OPER_MES:
                req_write_code (L, file);
                fprintf (file, " %s ", ATL_lex[_NUMBER (C)].trlt);
                req_write_code (R, file);
                break;
            case ENT_Q:
                if (R != nullptr) {
                    fprintf (file, "%s %s ", L->data.name, ATL_lex[_NUMBER (C)].trlt);
                    fflush (file);
                    req_write_code (R, file);
                } else {
                    fprintf (file, "%s", L->data.name);
                }
                break;
            case MUL_M:
                if (R != nullptr) {
                    fprintf (file, "%s %s ", ATL_lex[_NUMBER (L)].trlt, ATL_lex[_NUMBER (C)].trlt);
                    fflush (file);
                    req_write_code (R, file);
                } else {
                    fprintf (file, "%s", ATL_lex[_NUMBER (L)].trlt);
                }
                break;
        }
    }
}

int Tree::write_expression (const char *name_file) {
    FILE* file = nullptr;
    if ((file = fopen (name_file, "w")) == nullptr) {
        PRINT_ERROR ("Failed to create file with code on qASM")
        return -1;
    }

    req_write_code (node, file);

    fclose (file);

    return 0;
}


/*
node_t *Tree::getFunc () {
    node_t *curr_node = getQBit ();
    if (curr_node != nullptr) {
        token_t curr = PREV;

        if (GT->number == BRACKET_ON) {
            GTpp
            node_t *NextL = getNumb (); //todo заменить на выражение
            if (NextL != nullptr) {

            }
            if (GT->number == BRACKET_OFF)
                return CRT (curr, curr_node, nullptr);
        }

        PRINT_ERROR ("SYNTAX_ERROR")

        assert (0);
        return nullptr;
    }
    return nullptr;
}*/

char _operators[NUM_OPER][MAX_LEN_OPER] =   {
        ">"
};
