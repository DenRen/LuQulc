#include <cstdio>
#include <clocale>
#include "/home/tester/CLionProjects/SandBoxQ/MyLib3.h"
//#include "/home/tester/CLionProjects/SandBoxQ/MyLib3.cpp"
#include "TreeLung.h"
//#include "Translate.h"


int main () {

    // Считываем код и очищяем его от space

    setlocale (0, "");
    const char name_file[] = "../code.txt";

    size_t size = 0;

    char *buf = ReadNotSpace (name_file, &size);
    CHECK_CALLOC (buf, "Failed to read file")

    // Сортируем массивы перевеодчиков: первый для удобного обращения к каждому элементу,
    // второй для увеличения возможжностей токенезатора

    qsort (ATL_lex, size_trlt, sizeof (trlt_t), (int(*) (const void *, const void *)) comp_ATL);
    qsort (lexicon, size_trlt, sizeof (trlt_t), (int(*) (const void *, const void *)) comp);

    // Сама токенезация

    token_t *token = tokion (buf, size);
    CHECK_CALLOC (buf, "Failed to create new buf")

    // Создаём и записываем в дерево токенезированный текст

    Tree tree;

    if (tree.read_expression (token)) {
        perror ("Failed to read tree from tokens");
        return 0;
    }

    Dump_Tree_img (tree.node);

    // Транслируем из дерево в итоговый код

    const char *name_out_file = "../../SandBoxQ/main.cpp";

    if (tree.write_expression (name_out_file)) {
        perror ("Failed to read tree from tokens");
        return 0;
    }

    // Запускаем make, запускаем прогу, и выводим результат в консоль

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
































