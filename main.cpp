#include "header.h"

int main()
{   
    node * korney = NULL;
    node * diff = NULL;
    node * nd = NULL;
    FILE * in = fopen("graph.txt", "r");
    TreeScanf(in, &korney);

    //printf("left_son ptr = %p\n", korney -> left_son);
    //printf("right_son ptr = %p\n", korney -> right_son);


    FILE * tex = fopen("laba.tex", "w");

    TexPrint(tex, korney);

    TreeDtor(diff);

    fclose(in);
    fclose(tex);

    system("latex laba.tex");
    system("open laba.dvi"); 

    return 0;
}