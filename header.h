#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <ctype.h>
#include <math.h>

#define LOX  printf("повезло повезло %d\n", __LINE__);                     


enum TYPE
{
    T_NUM,
    T_VAR,
    T_OP,
    T_FUN,
    T_UNK,
};

enum OP
{
    OP_ADD = '+',
    OP_SUB = '-',
    OP_MUL = '*',
    OP_DIV = '/',
    OP_DEG = '^',
};

enum FUN
{
    F_sin,
    F_cos,
    F_tg,
    F_ctg,
    F_ln,
    F_log,
    F_sh,
    F_ch,
    F_th,
    F_cth,
};

struct DATA
{
    int int_t;
    char ch_t;
    double d_t;
};

struct node
{   
    int type;
    DATA data;
    node * left_son;
    node * right_son;

};


node * TreeNodeAdd(int type, node ** nd, DATA data, node * left_son = NULL, node * right_son = NULL);
void TreeDtor(struct node * nd);
void TreePrintInOrder(FILE * fp, node * nd, int n);
void TreeFDump(node * nd);
void TreePrint(node * nd, FILE * fp);
void TreeSegDtor(node * nd);
void TreeScanf(FILE * fp, node ** nd);
void Read(FILE * fp, node ** nd);
node * TreeDiff(node * nd);
node * TreeAdd(node * left_son, node * right_son);
node * TreeSub(node * left_son, node * right_son);
node * TreeMul(node * left_son, node * right_son);
node * TreeDiv(node * left_son, node * right_son);
node * TreeNodeAdd2(int type, node * nd, DATA data, node * left_son = NULL, node * right_son = NULL);
node * TreeNodeCopy(node * nd);
node * TreeSin(node * right_son);
node * TreeCos(node * right_son);
node * NUM(int num);
node * LN(node * nd);
node * TreeSh(node * right_son);
node * TreeCh(node * right_son);









//void TreePrintInOrder(node * nd);
//void TreePrintPostOrder(node * nd);
//node * TreeFind(node * root, int value);

//node * TreeFileCtor(FILE * fp, node * korney);