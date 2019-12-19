//
// Created by tester on 16.12.2019.
//

#include <cassert>
#include "TreeLung.h"

trlt_t lexicon [] {

        {LOCALE,  "Зайтивогород"},
        {CRTqBIT, "Сорватьягодку", true, SYSTEM},

        // Работа с кубитами
        {EQUAL_Q,   "сдерева",              true},
        {ENT_Q,     "превратитьвкомпотс",   true},
        {OPER_Q,    "процедитьчерез",       true},
        {OPER_MES,  "налитьв",              true},

        // Работа с матрицами
        {EQUAL_M,     "=",                    true},
        {MUL_M,       "ичерез",               true},
        {POW_M,       "^",                    true},

        // Основные константные матрицы
        {Mtx_H,       "супермарлю"},
        {Mtx_Y,       "Y"},
        {Mtx_Z,       "Z"},
        {Mtx_CNOT,    "CNOT"},
        {Mtx_RCNOT,   "RCNOT"},

        // Основные неконстантные матрицы
        {Mtx_I,       "I",                    true},
        {Mtx_X,       "X",                    true},

        // Уникальные объекты
        {Mtx_ADD_1,   "соковыжималкуBOSCH",   false},
        {Mtx_ADD_2,   "соковыжималкуPHILIPS", false},

        {Mtx_ADD_3,   "соковыжималкуToshiba", false},
        {Mtx_ADD_4,   "соковыжималкуRedmond", false},
        {MES,         "стакан"},

        {BRACKET_ON,  "(",                    true},
        {BRACKET_OFF, ")",                    true},
        {BRACE_ON,    "фартукнадеть",         true},
        {BRACE_OFF,   "фартукснять",          true},

        {SEP,         ";",                    true},
        {COMMA,       ",",                    true}
};

trlt_t ATL_lex [] {

        {LOCALE,      "Locale"},
        {CRTqBIT,     "CrtQBit",       true, SYSTEM},

        // Работа с кубитами
        {EQUAL_Q,     "=",             true},
        {ENT_Q,       "&&",   true},
        {OPER_Q,      ">>=",  true},
        {OPER_MES,    "<<=",           true},

        // Работа с матрицами
        {EQUAL_M,     "=",             true},
        {MUL_M,       "&",             true},
        {POW_M,       "^",             true},

        // Основные константные матрицы
        {Mtx_H,       "getH"},
        {Mtx_Y,       "getY"},
        {Mtx_Z,       "getZ"},
        {Mtx_CNOT,    "getCNOT"},
        {Mtx_RCNOT,   "getRCNOT"},

        // Основные неконстантные матрицы
        {Mtx_I,       "getI (1)",      true},
        {Mtx_X,       "getX (1)",      true},

        // Уникальные объекты
        {Mtx_ADD_1,   "funcAlgDD (1)", false},
        {Mtx_ADD_2,   "funcAlgDD (2)", false},
        {Mtx_ADD_3,   "funcAlgDD (3)", false},
        {Mtx_ADD_4,   "funcAlgDD (4)", false},
        {MES,         "measure"},

        {BRACKET_ON,  "(",             true},
        {BRACKET_OFF, ")",             true},
        {BRACE_ON,    "{",             true},
        {BRACE_OFF,   "}",             true},

        {SEP,         ";",             true},
        {COMMA,       ",",             true}
};

const char sep_code  = ';';
const char comm_code = '`';

const int size_trlt = sizeof (lexicon) / sizeof (trlt_t);


char *find_trlt_type (int num) {
    for (int i = 0; i < size_trlt; i++)
        if (lexicon[i].orig == num)
            return lexicon[i].trlt;

    assert (0);
    return nullptr;
}
