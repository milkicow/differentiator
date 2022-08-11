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


void TreePrintInOrder(FILE * fp, node * nd)
{   
    assert(fp);
    assert(nd);
    fprintf(fp, "%s", "{");
    if(nd -> left_son) TreePrintInOrder(fp, nd -> left_son);

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


    #define function(f)            \
    case F_##f:                     \
            fprintf(fp, #f);         \
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
                printf("unidentified function");
                exit(EXIT_FAILURE);
                LOX
                break;
        }

        break;


    case T_UNK:

        printf("unknow type");
        exit(EXIT_FAILURE);
        break;

    default:

        LOX
        printf("unidentified type");
        exit(EXIT_FAILURE);
        break;
    }

    if(nd -> right_son) TreePrintInOrder(fp, nd -> right_son);
    fprintf(fp, "%s", "}");
} 

void TreePrintTex(FILE * fp, node * nd)
{
    assert(fp);
    assert(nd);

    switch(nd -> type)
    {
    case T_NUM:
        fprintf(fp, "%d", nd -> data.int_t);
        break;

    case T_VAR:
        fprintf(fp, "%c", nd -> data.ch_t);
        break;
    
    case T_OP:
        switch(nd -> data.ch_t)
        {
        case OP_ADD:  
            fprintf(fp, "\\left(");
            if (nd -> left_son) TreePrintTex(fp, nd -> left_son);
            fprintf(fp, "%c", nd -> data.ch_t);
            if (nd -> right_son) TreePrintTex(fp, nd -> right_son);
            fprintf(fp, "\\right)");
            break;
        
        case OP_SUB:
            fprintf(fp, "\\left(");
            if (nd -> left_son) TreePrintTex(fp, nd -> left_son);
            fprintf(fp, "%c", nd -> data.ch_t);
            if (nd -> right_son) TreePrintTex(fp, nd -> right_son);
            fprintf(fp, "\\right)");
            break;
        
        case OP_MUL:
            if (nd -> left_son) TreePrintTex(fp, nd -> left_son);
            fprintf(fp, "\\cdot ");
            if (nd -> right_son) TreePrintTex(fp, nd -> right_son);
            break;
        
        case OP_DIV:
            fprintf(fp, "\\frac{");
            if (nd -> left_son) TreePrintTex(fp, nd -> left_son);
            fprintf(fp, "}{");
            if (nd -> right_son) TreePrintTex(fp, nd -> right_son);
            fprintf(fp, "}");
            break;
        
        case OP_DEG:
            if (nd -> left_son) 
            {   
                fprintf(fp, " \\left( ");
                TreePrintTex(fp, nd -> left_son);
                fprintf(fp, " \\right) ");
            }
            fprintf(fp, "%c", nd -> data.ch_t);
            fprintf(fp, "{");
            if (nd -> right_son) TreePrintTex(fp, nd -> right_son);
            fprintf(fp, "}");
            break;

        default:
            LOX
            printf("unidentified type");
            exit(EXIT_FAILURE);
            break;
            

        }
        break;


    #define function(f)                                     \
    case F_##f:                                              \
        fprintf(fp, "\\"#f"\\left(");                         \
        if(nd -> right_son) TreePrintTex(fp, nd -> right_son); \
        fprintf(fp, "\\right)");                                \
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
                printf("unidentified function");
                exit(EXIT_FAILURE);
                LOX
                break;
        }

        break;

    
    default:
        LOX
        printf("unidentified type");
        exit(EXIT_FAILURE);
        break;
    }
}

/*
void TreePrintInOrder(FILE * fp, node * nd)
{   
    assert(fp);
    assert(nd);
    //fprintf(fp, "%s", "{");
    if (nd -> type == T_OP && (nd -> data.ch_t == OP_ADD || nd -> data.ch_t == OP_SUB))
    {
        fprintf(fp, "%s", "(");
    }
    else if (nd -> type == T_OP && (nd -> data.ch_t == OP_MUL || nd -> data.ch_t == OP_DIV || nd -> data.ch_t == OP_DEG))
    {
        fprintf(fp, "%s", "{");
    }
    
    if(nd -> left_son) TreePrintInOrder(fp, nd -> left_son);

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


    #define function(f)            \
    case F_##f:                     \
            fprintf(fp, #f);         \
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
                printf("unidentified function");
                exit(EXIT_FAILURE);
                LOX
                break;
        }

        break;


    case T_UNK:

        printf("unknow type");
        exit(EXIT_FAILURE);
        break;

    default:

        LOX
        printf("unidentified type");
        exit(EXIT_FAILURE);
        break;
    }

    if(nd -> right_son) TreePrintInOrder(fp, nd -> right_son);
    if (nd -> type == T_OP && (nd -> data.ch_t == OP_ADD || nd -> data.ch_t == OP_SUB))
    {
        fprintf(fp, "%s", ")");
    }
    else if (nd -> type == T_OP && (nd -> data.ch_t == OP_MUL || nd -> data.ch_t == OP_DIV || nd -> data.ch_t == OP_DEG))
    {
        fprintf(fp, "%s", "}");
    }
}
*/


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
        //printf("%c\n", symbol);
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
        //printf("%s\n", func);

        #define function(f)                     \
        if(strcmp(func, #f) == 0)                \
        {                                         \
            (*nd) -> type = T_FUN;                 \
            (*nd) -> data.ch_t = F_##f;             \
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



#define dL TreeDiff(fp, nd -> left_son)
#define dR TreeDiff(fp, nd -> right_son)
#define cL TreeNodeCopy(nd -> left_son)
#define cR TreeNodeCopy(nd -> right_son)
#define sin TreeSin(nd -> right_son)
#define cos TreeCos(nd -> right_son)
#define sh TreeSh(nd -> right_son)
#define ch TreeCh(nd -> right_son)
#define minus TreeNodeAdd2(T_NUM, NULL, data_minus)


node * TreeDiff(FILE * fp, node * nd)
{
    DATA data = { 0 };

    switch (nd -> type)
    {
    case T_NUM:
        TexConst(fp, nd, 0);
        return NUM(0);
        break;

    case T_VAR:
        TexConst(fp, nd, 1);
        return NUM(1);
        break;

    case T_OP:
        switch(nd -> data.ch_t)
        {
        case OP_ADD:
            LOX
            TexAdd(fp, nd);
            return TreeAdd(dL, dR);
            break;

        case OP_SUB:
            LOX
            TexSub(fp, nd);
            return TreeSub(dL, dR);
            break;

        case OP_MUL:
            LOX
            TexMul(fp, nd);
            return TreeAdd(TreeMul(dL, cR), TreeMul(cL, dR));
            break;

        case OP_DIV:
            LOX
            TexDiv(fp, nd);
            return TreeDiv(TreeSub(TreeMul(dL, cR), TreeMul(cL, dR)), DEG(cR, NUM(2)));

            break;

        case OP_DEG:
            LOX
            if(nd -> left_son -> type == T_NUM)
            {   
                if(nd -> right_son -> type == T_NUM)
                {   
                    TexConst(fp, nd, 0);
                    return NUM(0);
                }
                else
                {   
                    TexDegFun(fp, nd);
                    return TreeMul(TreeMul(DEG(nd -> left_son, nd -> right_son), LN(nd -> left_son)), dR);
                }
            }
            else if(nd -> right_son -> type == T_NUM)
            {  
                TexDegNum(fp, nd);
                data.int_t = nd -> right_son -> data.int_t - 1;
                return TreeMul(TreeMul(DEG(nd -> left_son, TreeNodeAdd2(T_NUM, NULL, data)), cR), dL);
                data.int_t = 0;
            
            }
            else
            {
                TexDegTow(fp, nd);
                return TreeMul(DEG(nd -> left_son, nd -> right_son), TreeDiff(fp, TreeMul(nd -> right_son, LN(nd -> left_son))));
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
            TexSin(fp, nd);
            return TreeMul(cos, dR);
            break;
        
        case F_cos:
            LOX
            TexCos(fp, nd);
            return TreeMul(TreeMul(sin, NUM(-1)), dR);
            break;

        case F_tg:
            LOX
            TexTg(fp, nd);
            return TreeDiv(dR, TreeMul(cos, cos));
            break;

        case F_ctg:
            LOX
            TexCtg(fp, nd);
            return TreeDiv(TreeMul(NUM(-1), dR), TreeMul(sin, sin));
            break;

        case F_ln:
            LOX
            TexLn(fp, nd);
            return TreeDiv(dR, cR);
            break;

        case F_log:
            LOX
            TexLog(fp, nd);
            return TreeDiv(dR, TreeMul(cR, LN(NUM(10))));
            break;

        case F_sh:
            LOX
            TexSh(fp, nd);
            return TreeMul(ch, dR);
            break;

        case F_ch:
            LOX
            TexCh(fp, nd);
            return TreeMul(sh, dR);
            break;

        case F_th:
            LOX
            TexTh(fp, nd);
            return TreeDiv(dR, TreeMul(ch, ch));
            break;

        case F_cth:
            LOX
            TexCth(fp, nd);
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

void TexDiffNode(FILE * fp, node * nd)
{
    fprintf(fp, " \\left(");
    TreePrintTex(fp, nd);
    fprintf(fp, " \\right)'");
}

void TexNode(FILE * fp, node * nd)
{
    fprintf(fp, " \\left(");
    TreePrintTex(fp, nd);
    fprintf(fp, " \\right)");
}

void TexConst(FILE * fp, node * nd, int num)
{
    fprintf(fp, "$$ ");
    TexDiffNode(fp, nd);
    fprintf(fp, " = ");
    fprintf(fp, "%d", num);
    fprintf(fp, " $$\n \\newline");
}

void TexAdd(FILE * fp, node * nd)
{
    fprintf(fp, "$$ ");
    TexDiffNode(fp, nd);
    fprintf(fp, " = ");
    TexDiffNode(fp, nd -> left_son);
    fprintf(fp, " + ");
    TexDiffNode(fp, nd -> right_son);
    fprintf(fp, "$$\n \\newline");
}

void TexSub(FILE * fp, node * nd)
{
    fprintf(fp, "$$ ");
    TexDiffNode(fp, nd);
    fprintf(fp, " = ");
    TexDiffNode(fp, nd -> left_son);
    fprintf(fp, " - ");
    TexDiffNode(fp, nd -> right_son);
    fprintf(fp, "$$\n \\newline"); 
}

void TexMul(FILE * fp, node * nd)
{
    fprintf(fp, "$$ ");
    TexDiffNode(fp, nd);
    fprintf(fp, " = ");

    TexDiffNode(fp, nd -> left_son);
    fprintf(fp, " \\cdot ");
    TexNode(fp, nd -> right_son);
    fprintf(fp, " + ");
    TexNode(fp, nd -> left_son);
    fprintf(fp, " \\cdot ");
    TexDiffNode(fp, nd -> right_son);

    fprintf(fp, " $$\n \\newline");
}

void TexDiv(FILE * fp, node * nd)
{
    fprintf(fp, "$$ ");
    TexDiffNode(fp, nd);
    fprintf(fp, " = ");

    fprintf(fp, "\\frac{ ");
    TexDiffNode(fp, nd -> left_son);
    fprintf(fp, " \\cdot ");
    TexNode(fp, nd -> right_son);
    fprintf(fp, " - ");
    TexNode(fp, nd -> left_son);
    fprintf(fp, " \\cdot ");
    TexDiffNode(fp, nd -> right_son);
    fprintf(fp, "}{");
    TexDiffNode(fp, nd -> right_son);
    fprintf(fp, "^2 }");

    fprintf(fp, " $$\n \\newline");
}

void TexDegFun(FILE * fp, node * nd)
{
    fprintf(fp, "$$ ");
    TexDiffNode(fp, nd);
    fprintf(fp, " = "); 

    TexNode(fp, nd);
    fprintf(fp, " \\cdot \\ln \\left( %d \\right) \\cdot", nd -> left_son -> data.int_t);
    TexDiffNode(fp, nd -> right_son);

    fprintf(fp, " $$\n \\newline");
}

void TexDegNum(FILE * fp, node * nd)
{
    fprintf(fp, "$$ ");
    TexDiffNode(fp, nd);
    fprintf(fp, " = "); 

    fprintf(fp, "%d", nd -> right_son -> data.int_t);
    nd -> right_son -> data.int_t = nd -> right_son -> data.int_t - 1;
    fprintf(fp, " \\cdot ");
    TexNode(fp, nd);
    nd -> right_son -> data.int_t = nd -> right_son -> data.int_t + 1;    
    fprintf(fp, " \\cdot ");
    TexDiffNode(fp, nd -> left_son);

    fprintf(fp, " $$\n \\newline");
}

void TexDegTow(FILE * fp, node * nd)
{   
    fprintf(fp, "$$ ");
    TexDiffNode(fp, nd);
    fprintf(fp, " = "); 

    TexNode(fp, nd);
    fprintf(fp, " \\cdot \\left(");
    TexNode(fp, nd -> right_son);
    fprintf(fp, " \\cdot \\ln ");
    TexNode(fp, nd -> left_son);
    fprintf(fp, " \\right)' ");

    fprintf(fp, " $$\n \\newline");
}

void TexSin(FILE * fp, node * nd)
{
    fprintf(fp, "$$ ");
    TexDiffNode(fp, nd);
    fprintf(fp, " = ");

    fprintf(fp, " \\cos \\left( ");
    TreePrintTex(fp, nd -> right_son);
    fprintf(fp, " \\right) ");
    fprintf(fp, " \\cdot ");
    TexDiffNode(fp, nd -> right_son);

    fprintf(fp, " $$\n \\newline");
}


void TexCos(FILE * fp, node * nd)
{
    fprintf(fp, "$$ ");
    TexDiffNode(fp, nd);
    fprintf(fp, " = ");

    fprintf(fp, " - \\sin \\left( ");
    TreePrintTex(fp, nd -> right_son);
    fprintf(fp, " \\right) ");
    fprintf(fp, " \\cdot ");
    TexDiffNode(fp, nd -> right_son);

    fprintf(fp, " $$\n \\newline");
}

void TexTg(FILE * fp, node * nd)
{
    fprintf(fp, "$$ ");
    TexDiffNode(fp, nd);
    fprintf(fp, " = ");

    fprintf(fp, " \\frac{ ");
    TexDiffNode(fp, nd -> right_son);
    fprintf(fp, " }{ ");
    fprintf(fp, " \\cos \\left( ");
    TreePrintTex(fp, nd -> right_son);
    fprintf(fp, " \\right)^2 }");

    fprintf(fp, " $$\n \\newline"); 
}

void TexCtg(FILE * fp, node * nd)
{
    fprintf(fp, "$$ ");
    TexDiffNode(fp, nd);
    fprintf(fp, " = ");

    fprintf(fp, " - \\frac{ ");
    TexDiffNode(fp, nd -> right_son);
    fprintf(fp, " }{ ");
    fprintf(fp, " \\sin \\left( ");
    TreePrintTex(fp, nd -> right_son);
    fprintf(fp, " \\right)^2 }");

    fprintf(fp, " $$\n \\newline"); 
}

void TexLn(FILE * fp, node * nd)
{
    fprintf(fp, "$$ ");
    TexDiffNode(fp, nd);
    fprintf(fp, " = ");

    fprintf(fp, " \\frac{ ");
    TexDiffNode(fp, nd -> right_son);
    fprintf(fp, " }{ ");
    TreePrintTex(fp, nd -> right_son);
    fprintf(fp, " }");

    fprintf(fp, " $$\n \\newline"); 
}

void TexLog(FILE * fp, node * nd)
{
    fprintf(fp, "$$ ");
    TexDiffNode(fp, nd);
    fprintf(fp, " = ");

    fprintf(fp, " \\frac{ ");
    TexDiffNode(fp, nd -> right_son);
    fprintf(fp, " }{ ");
    TreePrintTex(fp, nd -> right_son);
    fprintf(fp, " \\cdot ");
    fprintf(fp, "ln(10)");
    fprintf(fp, " }");

    fprintf(fp, " $$\n \\newline"); 

}

void TexSh(FILE * fp, node * nd)
{
    fprintf(fp, "$$ ");
    TexDiffNode(fp, nd);
    fprintf(fp, " = ");

    fprintf(fp, " \\ch \\left( ");
    TreePrintTex(fp, nd -> right_son);
    fprintf(fp, " \\right) ");
    fprintf(fp, " \\cdot ");
    TexDiffNode(fp, nd -> right_son);

    fprintf(fp, " $$\n \\newline");
}

void TexCh(FILE * fp, node * nd)
{
    fprintf(fp, "$$ ");
    TexDiffNode(fp, nd);
    fprintf(fp, " = ");

    fprintf(fp, " \\sh \\left( ");
    TreePrintTex(fp, nd -> right_son);
    fprintf(fp, " \\right) ");
    fprintf(fp, " \\cdot ");
    TexDiffNode(fp, nd -> right_son);

    fprintf(fp, " $$\n \\newline");
}

void TexTh(FILE * fp, node * nd)
{
    fprintf(fp, "$$ ");
    TexDiffNode(fp, nd);
    fprintf(fp, " = ");

    fprintf(fp, " \\frac{ ");
    TexDiffNode(fp, nd -> right_son);
    fprintf(fp, " }{ ");
    fprintf(fp, " \\ch \\left( ");
    TreePrintTex(fp, nd -> right_son);
    fprintf(fp, " \\right)^2 }");

    fprintf(fp, " $$\n \\newline"); 
}

void TexCth(FILE * fp, node * nd)
{
    fprintf(fp, "$$ ");
    TexDiffNode(fp, nd);
    fprintf(fp, " = ");

    fprintf(fp, " - \\frac{ ");
    TexDiffNode(fp, nd -> right_son);
    fprintf(fp, " }{ ");
    fprintf(fp, " \\sh \\left( ");
    TreePrintTex(fp, nd -> right_son);
    fprintf(fp, " \\right)^2 }");

    fprintf(fp, " $$\n \\newline"); 
}

#undef dL
#undef dR
#undef cL
#undef cR
#undef sin
#undef cos
#undef sh
#undef ch
#undef minus

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

void TreeSimp(node ** nd, int * status)
{   
    node * original = *nd;
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
        else if(((*nd) -> right_son -> type == T_OP) && ((*nd) -> right_son -> data.ch_t == OP_DIV) && ((*nd) -> right_son -> left_son -> type == T_NUM) && ((*nd) -> right_son -> left_son -> data.int_t == 1) && ((*nd) -> left_son))
        {
            TreeDtor((*nd) -> right_son -> left_son);
            (*nd) -> right_son = TreeNodeCopy((*nd) -> right_son -> right_son);

            TreeDtor((*nd) -> right_son -> right_son);
            (*nd) -> data.ch_t = OP_DIV;
        }
        else if(((*nd) -> left_son -> type == T_OP) && ((*nd) -> left_son -> data.ch_t == OP_DIV) && ((*nd) -> left_son -> left_son -> type == T_NUM) && ((*nd) -> left_son -> left_son -> data.int_t == 1) && ((*nd) -> right_son))
        {   

            node * copy = NULL;
            copy = TreeNodeCopy((*nd) -> left_son -> right_son);

            (*nd) -> left_son = TreeNodeCopy((*nd) -> right_son);
            (*nd) -> right_son = copy;
            (*nd) -> data.ch_t = OP_DIV;
        } 
    }
    if((*nd) -> type == T_OP && (*nd) -> data.ch_t == OP_ADD)
    {
        if(((*nd) -> right_son -> type == T_NUM) && ((*nd) -> right_son -> data.int_t == 0))
        {
            TreeDtor((*nd) -> right_son);
            (*nd) = TreeNodeCopy((*nd) -> left_son);
        } 
        else if(((*nd) -> left_son -> type == T_NUM) && ((*nd) -> left_son -> data.int_t == 0))
        {
            TreeDtor((*nd) -> left_son);
            (*nd) = TreeNodeCopy((*nd) -> right_son);
        }
    }
    if((*nd) -> type == T_OP && (*nd) -> data.ch_t == OP_SUB)
    {
        if(((*nd) -> right_son -> type == T_NUM) && ((*nd) -> right_son -> data.int_t == 0))
        {
            TreeDtor((*nd) -> right_son);
            (*nd) = TreeNodeCopy((*nd) -> left_son);
        }
        else if(((*nd) -> left_son -> type == T_NUM) && ((*nd) -> left_son -> data.int_t == 0))
        {
            TreeDtor((*nd) -> left_son);
            (*nd) = TreeNodeCopy((*nd) -> right_son);
            (*nd) -> data.int_t = 0 - (*nd) -> data.int_t;
        }

    }

    LOX
    if((*nd) -> left_son) TreeSimp(&((*nd) ->left_son), status);
    LOX
    if((*nd) -> right_son) TreeSimp(&((*nd) -> right_son), status);
    LOX

    if (*nd != original) 
    {
        *status = changed;
    }

}

void TexIntro(FILE * fp)
{
    fprintf(fp, "\\documentclass[a4paper,12pt]{article} %% добавить leqno в [] для нумерации слева\n\
\\usepackage[a4paper,top=1.3cm,bottom=2cm,left=1.5cm,right=1.5cm,marginparwidth=0.75cm]{geometry}\n\
\\usepackage{cmap}					%% поиск в PDF\n\
\\usepackage[warn]{mathtext} 		%% русские буквы в фомулах\n\
\\usepackage[T2A]{fontenc}			%% кодировка\n\
\\usepackage[utf8]{inputenc}			%% кодировка исходного текста\n\
\\usepackage[english,russian]{babel}	%% локализация и переносы\n\
\\usepackage{physics}\n\
\\usepackage{multirow}\n\
\\allowdisplaybreaks\n\
\n\
%%%%%% Нормальное размещение таблиц (писать [H] в окружении таблицы)\n\
\\usepackage{float}\n\
\\restylefloat{table}\n\
\n\
\n\
\n\
\\usepackage{graphicx}\n\
\n\
\\usepackage{wrapfig}\n\
\\usepackage{tabularx}\n\
\n\
\\usepackage{hyperref}\n\
\\usepackage[rgb]{xcolor}\n\
\\hypersetup{\n\
	colorlinks=true,urlcolor=blue\n\
}\n\
\n\
\\usepackage{pgfplots}\n\
\\pgfplotsset{compat=1.9}\n\
\n\
%%%%%% Дополнительная работа с математикой\n\
\\usepackage{amsmath,amsfonts,amssymb,amsthm,mathtools}  %%AMS\n\
\\usepackage{icomma} %% \"Умная\" запятая: $0,2$ --- число, $0, 2$ --- перечисление\n\
\n\
%%%%%% Номера формул\n\
\\mathtoolsset{showonlyrefs=true} %% Показывать номера только у тех формул, на которые есть \\eqref{} в тексте.\n\
\n\
%%%%%% Шрифты\n\
\\usepackage{euscript}	 %% Шрифт Евклид\n\
\\usepackage{mathrsfs} %% Красивый матшрифт\n\
\n\
%%%%%% Свои команды\n\
\\DeclareMathOperator{\\sgn}{\\mathop{sgn}}\n\
\n\
%%%%%% Перенос знаков в формулах (по Львовскому)\n\
\\newcommand*{\\hm}[1]{#1\\nobreak\\discretionary{}\n\
	{\\hbox{$\\mathsurround=0pt #1$}}{}}\n\
\n\
\\date{\\today}\n\
\n\
\\usepackage{gensymb}\n\
\n\
\\title{Взятие производной}\n\
\\author{Козлов Александр}\n\
\\begin{document}\n\
\\maketitle\n");

    fprintf(fp, "\\section{}\n");

}

void TexPrint(FILE * fp, node * nd)
{
    node * diff = NULL;
    int status = unchanged;

    TexIntro(fp);
    diff = TreeDiff(fp, nd);

    do
    {   
        status = unchanged;
        TreeSimp(&diff, &status);

    } while (status == changed);


    fprintf(fp, " Итого: \n \\newline ");
    fprintf(fp, " $$ ");
    TreePrintTex(fp, diff);
    fprintf(fp, " $$ ");
    TreeFDump(diff);

    fprintf(fp, "\\end{document}\n");
}