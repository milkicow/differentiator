#include "header.h"

int main()
{   
    node * korney = NULL;
    node * diff = NULL;
    node * nd = NULL;
    FILE * in = fopen("graph.txt", "r");
    TreeScanf(in, &korney);

    LOX
    diff = TreeDiff(korney);
    TreeFDump(diff);


    fclose(in);

    return 0;
}