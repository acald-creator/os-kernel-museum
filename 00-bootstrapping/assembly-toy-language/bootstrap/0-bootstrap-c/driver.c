#include <stdio.h>

extern int nani_main(void);

int main(int argc, char *argv[])
{
    int value = nani_main();
    printf("%d\n", value);
    return 0;
}