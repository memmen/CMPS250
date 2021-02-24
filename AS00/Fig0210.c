#include <stdio.h>
int main()
{
    const int limit = 100;
    int num;
    scanf("%d", &num);
    if (num >= limit)
    {
        printf("high\n");
    }
    else
    {
        printf("low\n");
    }
    return 0;
}