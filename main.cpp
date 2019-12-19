#include <cstdio>
#include <clocale>
#include "/home/tester/CLionProjects/SandBoxQ/MyLib3.h"
//#include "/home/tester/CLionProjects/SandBoxQ/MyLib3.cpp"
#include "TreeLung.h"
//#include "Translate.h"

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

int main () {
    setlocale (0, "");
    const char name_file[] = "../code.txt";

    size_t size = 0;

    char *buf = ReadNotSpace (name_file, &size);
    CHECK_CALLOC (buf, "Failed to read file")

    qsort (ATL_lex, size_trlt, sizeof (trlt_t), (int(*) (const void *, const void *)) comp_ATL);
/*
    for (int i = 0; i < size_trlt; i++)
        printf ("%d) %s\n", i, ATL_lex[i].trlt);
*/
    qsort (lexicon, size_trlt, sizeof (trlt_t), (int(*) (const void *, const void *)) comp);
/*
    for (int i = 0*printf ("\n"); i < size_trlt; i++)
        printf ("%d) %10s %d\n", i, lexicon[i].trlt, lexicon[i].orig);
*/

    token_t *token = tokion (buf, size);
    CHECK_CALLOC (buf, "Failed to create new buf")

    Tree tree;

    if (tree.read_expression (token)) {
        perror ("Failed to read tree from tokens");
        return 0;
    }

    Dump_Tree_img (tree.node);

    const char *name_out_file = "../../SandBoxQ/main.cpp";

    if (tree.write_expression (name_out_file)) {
        perror ("Failed to read tree from tokens");
        return 0;
    }

    const char *path = "../../SandBoxQ/cmake-build-debug";

    MakeAndStart (path);


/*

    malinka превратить в компот с kalinka процедить через супер марлю и через супер марлю;

    malinka превратить в компот с kalinka процедить через соковыжималку BOSCH;

 {Mtx_ADD_1,   "соковыжималкуBOSCH",   false},
{Mtx_ADD_1,   "соковыжималкуPHILIPS", false},
{Mtx_ADD_3,   "соковыжималкуToshiba", false},
{Mtx_ADD_4,   "соковыжималкуRedmond", false},


 */
    return 0;
}

void MakeAndStart (const char *path) {
    char str[256] = "";

    sprintf (str, "cd %s; make 2> nul;"
                  "./SandBoxQ > Result.txt;", path);
    system (str);

    sprintf (str, "%s/Result.txt", path);

    size_t size = 0;
    int state = 0;

    char *buf = Read_File_To_Buffer (str, &size, &state, true, true);

    if (state != rftb::ALL_RIGHT) {
        PRINT_ERROR ("Failed to read Result file")
        return;
    }

    printf ("\nResult file:\n%s"
            "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n", buf);
    free (buf);
}

token_t *tokion (char *buf, size_t size) {
    // Принимает buf без пробелов (!isspace)
    assert (buf != nullptr);

    token_t *token = (token_t *) calloc (size, sizeof (token_t));

    token_t *save_token = token;

/*
    for (int i = 0; i < size_trlt; i++)
        printf ("%s\n", lexicon[i].trlt);
    printf ("____\n");

    int u = find_num_in_lang (lexicon, "H;G");
    printf ("%s", lexicon[u].orig);

    return 0;
*/

    // Токенизируем
    int n0 = 0, n1 = 0, value = 0, len_var = 0;
    char *save_buf = buf, *buf_var = nullptr;

    while (*buf != '\0') {
        if (*buf >= '0' && *buf <= '9') {               // Если это число
            if (sscanf (buf, "%n%d%n", &n0, &value, &n1) != 1) {
                printf ("\nError in read code: %20s\n", buf);
                abort ();
            }
//            printf ("%d\n", value);
            buf += n1 - n0;

            token->type = tkn::NUM;
            token->number = value;
            token++;

            continue;
        } else {
            int num = 0;
            if ((num = find_num_in_lang (lexicon, buf)) >= 0) { // Если это какой-то элемент из словаря
//                printf ("%s\n", ATL_lex[num].trlt);
                buf += strlen (find_trlt_type (num));

                token->type = tkn::LEX;
                token->number = num;
                token++;

                continue;
            }
        }

        // Получаем и зписываем имя переменной
        char *begin_var = buf++;
        int num = 0;

        while (*buf != '\0' && (num = find_num_in_lang (lexicon, buf)) < 0)
            buf++;

        len_var = buf - begin_var;

        if (*(buf - 1) == '\0' || !ATL_lex[num].spec) {
            printf ("%20s", buf);
            PRINT_ERROR ("SYNTAX_ERROR")
            free (buf_var);
            free (save_buf);
            return 0;
        } else if (len_var >= MAXLENCOMMAND) {
            PRINT_ERROR ("SYNTAX_ERROR: Very long name of variable")
            free (buf_var);
            free (save_buf);
            return 0;
        }

        buf_var = (char *) calloc (MAXLENCOMMAND, 1);
        CHECK_CALLOC (buf_var, "Failed to create buffer with names of variables")

        memcpy (buf_var, begin_var, len_var);       // Сохраняем имя

        token->type = tkn::STR;
        token->name = buf_var;
        token++;
    }

    printf ("Lexemes: \n\n");

    int size_token = token - save_token;
    // NUM, OPER_or_FUNC, VAR
    token = save_token;
    for (int i = 0; i < size_token; i++) {
        switch (token[i].type) {
            case tkn::NUM:
                printf ("%-3s == %d\n", "NUM", token[i].number);
                break;
            case tkn::LEX:
                printf ("%-3s == %s\n", "LEX", ATL_lex[token[i].number].trlt);
                break;
            case tkn::STR: {
                char *temp_ = token[i].name;
                printf ("%-3s == %s\n", "STR", token[i].name);
                break;
            }
            default:
                printf ("Error type\n");
        }
    }

    return token;
}

char *ReadNotSpace (const char *name_file, size_t *size) {

    int state = 0;

    char *buf = Read_File_To_Buffer (name_file, size, &state, true, true);
    if (state != 0) {
        PRINT_ERROR ("Failed to read file")
        printf ("\nstate: %d\n", state);
        return nullptr;
    }
    char *save_buf = buf;

    // Убираем разделительные символы и комментарии
    bool comm_on = false;
    char *write = buf;
    while (*buf != '\0') {

        if (comm_on) {
            if (*buf == '\n')
                comm_on = false;

            buf++;

        } else if (*buf == comm_code) {
            comm_on = true;
            buf++;
        } else if (isspace (*buf)) {
            buf++;
        } else
            *(write++) = *(buf++);

    }

    *write = '\0';
    *size -= buf - write;
    buf = (char *) realloc (save_buf, *size);

//    printf ("%s\n", buf);

    return buf;
}

int comp (const trlt_t *left, const trlt_t *right) {
    return  strcmp (right->trlt, left->trlt);
}

int comp_ATL (const trlt_t *left, const trlt_t *right) {
    return  left->orig - right->orig;
}

int find_num_in_lang (trlt_t *lexHL, char *str, bool second_cell) {

    int i = 0, j = 0;
    bool equal = false;

    for (i = 0; i < size_trlt; i++) {
        for (j = 0; lexHL[i].trlt[j] != '\0' && str[j] != '\0'; j++)
            if (lexHL[i].trlt[j] != str[j]) {
                equal = false;
                break;
            } else
                equal = true;

        if (lexHL[i].trlt[j] == '\0' && equal) {

            if (second_cell) {
                if (lexHL[i].spec)
                    return -2;      // Известное имя
                else
                    return -1;      // Неизвестное имя
            }

            if (lexHL[i].spec)  // Если является типом разделителя
                return lexHL[i].orig;
                // Если нет, то дальше чекнем разделитель
            else if (find_num_in_lang (lexHL, str + j, true) == -2)
                return lexHL[i].orig;       // Известное имя
            else
                return -1;      // Неизвестно имя

        }

    }
    return -1;
}


// >=()
//
































