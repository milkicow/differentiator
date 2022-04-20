#include "header.h"

node * TreeNodeAdd(int type, node ** nd, DATA data, node * left_son, node * right_son)
{
    LOX
    *nd = (node *) calloc(1, sizeof(node));
    assert(nd);

    (*nd) -> type = type;

    (*nd) -> data = data;

    (*nd) -> left_son = left_son;
    (*nd) -> right_son = right_son;

    return *nd;
}

node * TreeNodeAdd2(int type, node * nd, DATA data, node * left_son, node * right_son)
{
    LOX
    nd = (node *) calloc(1, sizeof(node));
    assert(nd);

    nd -> type = type;

    nd -> data = data;
    
    nd -> left_son = left_son;
    nd -> right_son = right_son;

    return nd;
}

void TreeDtor(node * nd)  //дерево и его поддерево
{   
    LOX
    if(nd != NULL)
    {   
        LOX
        TreeDtor(nd -> left_son);
        LOX
        TreeDtor(nd -> right_son);

        free(nd);
    }
    LOX
}


void TreePrintInOrder(FILE * fp, node * nd, int n)
{   
    assert(fp);
    assert(nd);
    fprintf(fp, "\n%*s", n, "{");
    if(nd -> left_son) TreePrintInOrder(fp, nd -> left_son, n + 4);

    switch (nd -> type)
    {
    case T_NUM:
        fprintf(fp, "%d", nd -> data.int_t);
        break;
    case T_VAR:
        fprintf(fp, "%c", nd -> data.ch_t);
        break;
    case T_OP:
        fprintf(fp, "%c", nd -> data.ch_t);
        break;
    case T_UNK:

        break;

    default:
        break;
    }

    if(nd -> right_son) TreePrintInOrder(fp, nd -> right_son, n + 4);
    if(!nd -> left_son && !nd -> right_son) n = 2;

    fprintf(fp, "%*s\n", n, "}");
}



/*
void TreePrintInOrder(node * nd)
{
    if (nd == NULL)
    {   
        return;
    }
    //printf("%*s", n, "{");

    TreePrintInOrder(nd -> left_son);
    printf(" "elem_t, nd -> data);
    TreePrintInOrder(nd -> right_son);

    //printf("%s", "}");
}
*/
/*
void TreePrintPostOrder(node * nd)
{
    if (nd == NULL)
    {   
        return;
    }
    TreePrintPostOrder(nd -> left_son);
    TreePrintPostOrder(nd -> right_son);
    printf(" "elem_t, nd -> data);
}
*/

void TreeFDump(node * nd)
{   
    LOX
    FILE * fp = fopen("dump.txt", "w");
    assert(fp);

    fprintf(fp, "digraph G {\n");
    fprintf(fp, "rankdir=UD;\n");
    LOX
    TreePrint(nd, fp);

    fprintf(fp, "}\n");
    fclose(fp);
    system("dot dump.txt -T pdf -o dump.pdf");
    system("open dump.pdf");
}

void TreePrint(node * nd, FILE * fp)
{   
    LOX
    if(nd == NULL)
    {
        return;
    }
    if(nd -> left_son != NULL)
    {
        fprintf(fp, "node%p -> node%p[color = pink];\n", nd , nd -> left_son );
        TreePrint(nd -> left_son, fp);
    }

    switch (nd -> type)
    {
    case T_NUM:
        LOX

        fprintf(fp, "node%p [shape=record,label=\"%d \" ];\n", nd, nd -> data.int_t);
        break;

    case T_VAR:
        LOX

        fprintf(fp, "node%p [shape=record,label=\"%c \" ];\n", nd, nd -> data.ch_t);
        break;

    case T_OP:
        LOX

        fprintf(fp, "node%p [shape=record,label=\"%c \" ];\n", nd, nd -> data.ch_t);
        break;

    #define function(f)                                                         \
    case F_##f:                                                                  \
            fprintf(fp, "node%p [shape=record,label=\"" #f "\"];\n", nd);         \
            break;

    case T_FUN:
        switch (nd -> data.ch_t)
        {
            function(sin)
            function(cos)
            function(tg)
            function(ctg)
            function(ln)
            function(log)
            function(sh)
            function(ch)
            function(th)
            function(cth)

            #undef function

            default:
                LOX
                break;
        }
    /*
    case T_FUN:
        LOX
        switch (nd -> data.ch_t)
        {
        case F_sin:
            fprintf(fp, "node%p [shape=record,label= sin ];\n", nd);
            break;
        
        case F_cos:
            fprintf(fp, "node%p [shape=record,label= cos ];\n", nd);
            break;

        case F_tg:
            fprintf(fp, "node%p [shape=record,label= tg ];\n", nd);
            break;

        default:
            LOX
            break;
        }
    */

    default:
        LOX
        break;
    }
    if(nd -> right_son != NULL)
    {
        fprintf(fp, "node%p -> node%p[color = pink];\n", nd , nd -> right_son);
        TreePrint(nd -> right_son, fp);
    }
}

/*
node * TreeFind(node * root, DATA value)
{   
    assert(root);
    assert(value);

    node * nd = root;
    while(nd)
    {
        if(nd -> data == value) 
            return nd;
        if(nd -> data < value)
            nd = nd -> right_son;
        if(nd -> data > value)
            nd = nd -> left_son;
    }

    return NULL;
}
*/

void TreeSegDtor(node * nd)
{
    assert(nd);

    nd -> right_son = NULL;
    nd -> left_son = NULL;
}


void Read(FILE * fp, node ** nd)
{
    char symbol = 0;
    int number = 0;
    char func[10] = "";

    fscanf(fp, "%c", &symbol); 

    if(symbol == OP_ADD || symbol == OP_SUB || symbol == OP_MUL || symbol == OP_DIV || symbol == OP_DEG)
    {       
        LOX
        (*nd) -> type = T_OP;
        (*nd) -> data.ch_t = symbol;
        printf("%c\n", symbol);
    }
    else if(isalpha(symbol))
    {   
        LOX
        for(int i = 0; isalpha(symbol); i++)
        {
            func[i] = symbol;
            fscanf(fp, "%c", &symbol); 
        }
        ungetc(symbol, fp);
        printf("%s\n", func);

        #define function(f)                     \
        if(strcmp(func, #f) == 0)                \
        {                                         \
            (*nd) -> type = T_FUN;                 \
            (*nd) -> data.ch_t = F_##f;             \
            printf("in def enum = %d\n", F_##f);     \
        } else                                         

        function(sin)
        function(cos)
        function(tg)
        function(ctg)
        function(ln)
        function(log)
        function(sh)
        function(ch)
        function(th)
        function(cth)
        /*
        if(strcmp(func, "sin") == 0)
        {   
            LOX
            (*nd) -> type = T_FUN;
            (*nd) -> data.ch_t = F_SIN;
        }
        else if(strcmp(func, "cos") == 0)
        {   
            LOX
            (*nd) -> type = T_FUN;
            (*nd) -> data.ch_t = F_COS;
        }
        else if(strcmp(func, "tg") == 0)
        {   
            LOX
            (*nd) -> type = T_FUN;
            (*nd) -> data.ch_t = F_TG;
        }
        */
        #undef function
        {
            LOX
            (*nd) -> type = T_VAR;
            (*nd) -> data.ch_t = func[0]; 
        }
    }
    else
    {
        ungetc(symbol, fp);

        fscanf(fp, "%d", &number); 

        (*nd) -> type = T_NUM;
        (*nd) -> data.int_t = number;
    }
}

/*
void TreeScanf(FILE * fp, node ** nd)
{   
    LOX
    DATA data = { 0 };
    char bracket[10];
    LOX
    fscanf(fp, "%s", bracket);
    LOX
    if(strcmp(bracket, "{") == 0)
    {   
        LOX
        TreeNodeAdd(T_UNK, nd, data);
        LOX
        TreeScanf(fp, &(*nd) -> left_son);
        LOX
        Read(fp, nd);
        //fscanf(fp, "%d", data); вместо этого - Read
        LOX
        TreeScanf(fp, &(*nd) -> right_son);
    }
    else if(strcmp(bracket, "}") == 0)
    {   
        LOX
        ungetc('}', fp);
        return;
    }
    fscanf(fp, "%s", bracket);   

}*/


void TreeScanf(FILE * fp, node ** nd)
{   
    LOX
    DATA data = { 0 };
    char bracket;
    LOX
    fscanf(fp, "%c", &bracket);
    LOX
    if(bracket == '(')
    {   
        LOX
        TreeNodeAdd(T_UNK, nd, data);
        LOX
        TreeScanf(fp, &(*nd) -> left_son);
        LOX
        Read(fp, nd);
        LOX
        TreeScanf(fp, &(*nd) -> right_son);
    }
    else 
    {   
        LOX
        ungetc(bracket, fp);
        return;
    }
    fscanf(fp, "%c", &bracket);   
}



#define dL TreeDiff(nd -> left_son)
#define dR TreeDiff(nd -> right_son)
#define cL TreeNodeCopy(nd -> left_son)
#define cR TreeNodeCopy(nd -> right_son)
#define sin TreeSin(nd -> right_son)
#define cos TreeCos(nd -> right_son)
#define sh TreeSh(nd -> right_son)
#define ch TreeCh(nd -> right_son)
#define minus TreeNodeAdd2(T_NUM, NULL, data_minus)


node * TreeDiff(node * nd)
{
    DATA data = { 0 };

    switch (nd -> type)
    {
    case T_NUM:
        return NUM(0);
        break;

    case T_VAR:
        return NUM(1);
        break;

    case T_OP:
        switch(nd -> data.ch_t)
        {
        case OP_ADD:
            LOX

            return TreeAdd(dL, dR);
            break;

        case OP_SUB:
            LOX

            return TreeSub(dL, dR);
            break;

        case OP_MUL:
            LOX
            return TreeAdd(TreeMul(dL, cR), TreeMul(cL, dR));
            break;

        case OP_DIV:
            LOX
            return TreeDiv(TreeSub(TreeMul(dL, cR), TreeMul(cL, dR)), DEG(cR, NUM(2)));

            break;

        case OP_DEG:
            LOX
            if(nd -> left_son -> type == T_NUM)
            {   
                if(nd -> right_son -> type == T_NUM)
                {
                    return NUM(0);
                }
                else
                {
                    return TreeMul(TreeMul(DEG(nd -> left_son, nd ->right_son), LN(nd -> left_son)), dR);
                }
            }
            else if(nd -> right_son -> type == T_NUM)
            {  
                data.int_t = nd -> right_son -> data.int_t - 1;
                return TreeMul(TreeMul(DEG(nd -> left_son, TreeNodeAdd2(T_NUM, NULL, data)), cR), dL);
                data.int_t = 0;
            
            }
            else
            {
                return TreeMul(DEG(nd -> left_son, nd -> right_son), TreeDiff(TreeMul(nd -> right_son, LN(nd -> left_son))));
            }
            break;
        
        default:
            LOX
            printf("unidentified operand\n");
            exit(EXIT_FAILURE);
            break;
        }
        break;

    case T_FUN:
        switch(nd -> data.ch_t)
        {
        case F_sin:
            LOX

            return TreeMul(cos, dR);
            break;
        
        case F_cos:
            LOX

            return TreeMul(TreeMul(sin, NUM(-1)), dR);
            break;

        case F_tg:
            LOX

            return TreeDiv(dR, TreeMul(cos, cos));
            break;

        case F_ctg:
            LOX

            return TreeDiv(TreeMul(NUM(-1), dR), TreeMul(sin, sin));
            break;

        case F_ln:
            LOX

            return TreeDiv(dR, cR);
            break;

        case F_log:
            LOX

            return TreeDiv(dR, TreeMul(cR, LN(NUM(10))));
            break;

        case F_sh:
            LOX

            return TreeMul(ch, dR);
            break;

        case F_ch:
            LOX

            return TreeMul(sh, dR);
            break;

        case F_th:
            LOX

            return TreeDiv(dR, TreeMul(ch, ch));
            break;

        case F_cth:
            LOX

            return TreeDiv(TreeMul(NUM(-1), dR), TreeMul(sh, sh));
            break;

        default:
            LOX
            printf("unidentified function\n");
            exit(EXIT_FAILURE);
            break;
        }
        break;
    
    default:
        LOX
        printf("unidentified type\n");
        exit(EXIT_FAILURE);
        break;
    }
}

node * TreeAdd(node * left_son, node * right_son)
{
    LOX
    DATA data = { 0 };

    data.ch_t = OP_ADD;

    return TreeNodeAdd2(T_OP, NULL, data, left_son, right_son);
}

node * TreeSub(node * left_son, node * right_son)
{
    LOX
    DATA data = { 0 };

    data.ch_t = OP_SUB;
    return TreeNodeAdd2(T_OP, NULL, data, left_son, right_son);
}

node * TreeMul(node * left_son, node * right_son)
{
    LOX
    DATA data = { 0 };

    data.ch_t = OP_MUL;
    return TreeNodeAdd2(T_OP, NULL, data, TreeNodeCopy(left_son), TreeNodeCopy(right_son));
}

node * TreeDiv(node * left_son, node * right_son)
{
    LOX
    DATA data = { 0 };

    data.ch_t = OP_DIV;
    return TreeNodeAdd2(T_OP, NULL, data, TreeNodeCopy(left_son), TreeNodeCopy(right_son));
}

node * TreeSin(node * right_son)
{
    LOX
    DATA data = { 0 };
    data.ch_t = F_sin;

    return TreeNodeAdd2(T_FUN, NULL, data, NULL, TreeNodeCopy(right_son));
}

node * TreeSh(node * right_son)
{
    LOX
    DATA data = { 0 };
    data.ch_t = F_sh;

    return TreeNodeAdd2(T_FUN, NULL, data, NULL, TreeNodeCopy(right_son));
}

node * TreeCos(node * right_son)
{
    LOX
    DATA data = { 0 };
    data.ch_t = F_cos;

    return TreeNodeAdd2(T_FUN, NULL, data, NULL, TreeNodeCopy(right_son));
}

node * TreeCh(node * right_son)
{
    LOX
    DATA data = { 0 };
    data.ch_t = F_ch;

    return TreeNodeAdd2(T_FUN, NULL, data, NULL, TreeNodeCopy(right_son));
}

node * NUM(int num)
{   
    DATA data = { 0 };
    data.int_t = num;

    return TreeNodeAdd2(T_NUM, NULL, data);
}

node * LN(node * nd)
{
    DATA data = { 0 };
    data.ch_t = F_ln;

    return TreeNodeAdd2(T_FUN, NULL, data, NULL, TreeNodeCopy(nd));
}

node * DEG(node * left_son, node * right_son)
{
    DATA data = { 0 };
    data.ch_t = OP_DEG;

    return TreeNodeAdd2(T_OP, NULL, data, TreeNodeCopy(left_son), TreeNodeCopy(right_son));
}

node * TreeNodeCopy(node * nd)
{
    if(nd -> left_son) nd -> left_son = TreeNodeCopy(nd ->left_son);
    if(nd -> right_son) nd -> right_son = TreeNodeCopy(nd -> right_son);

    node * new_nd = (node *) calloc(1, sizeof(node));
    assert(new_nd);

        new_nd -> type = nd -> type;

        new_nd -> data = nd -> data;
        
        if(nd -> left_son) new_nd -> left_son  = (node *) calloc(1, sizeof(node));

        if(nd -> right_son) new_nd -> right_son = (node *) calloc(1, sizeof(node));

        if(nd -> left_son) *new_nd -> left_son = *nd ->left_son;
        if(nd -> right_son) *new_nd -> right_son = *nd -> right_son;

    return new_nd;
}

void TreeSimp(node ** nd)
{   
    LOX
    if((*nd) -> type == T_OP && (*nd) -> data.ch_t == OP_MUL)
    {   
        LOX
        if(((*nd) -> right_son -> type == T_NUM) && ((*nd) -> right_son -> data.int_t == 1))
        {
            LOX
            TreeDtor((*nd) -> right_son);
            (*nd) -> right_son = NULL;
            *nd = TreeNodeCopy((*nd) -> left_son);

        }
        else if(((*nd) -> left_son -> type == T_NUM) && ((*nd) -> left_son -> data.int_t == 1))
        {
            LOX
            TreeDtor((*nd) -> left_son);
            (*nd) -> left_son = NULL;
            *nd = TreeNodeCopy((*nd) -> right_son);
        }
        else if(((*nd) -> right_son -> type == T_NUM) && ((*nd) -> right_son -> data.int_t == 0) || ((*nd) -> left_son -> type == T_NUM) && ((*nd) -> left_son -> data.int_t == 0))
        {
            LOX
            TreeDtor((*nd) -> left_son);
            TreeDtor((*nd) -> right_son);

            (*nd) -> left_son = NULL;
            (*nd) -> right_son = NULL;

            *nd = NUM(0);
        }
    }
    LOX
    if((*nd) -> left_son) TreeSimp(&((*nd) ->left_son));
    LOX
    if((*nd) -> right_son) TreeSimp(&((*nd) -> right_son));
    LOX

}