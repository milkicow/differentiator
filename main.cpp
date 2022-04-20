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

    LOX
    diff = TreeDiff(korney);
    LOX
    TreeSimp(&diff);
    LOX
    TreeFDump(diff);

    TreeDtor(korney);
    TreeDtor(diff);


    fclose(in);

    return 0;
}