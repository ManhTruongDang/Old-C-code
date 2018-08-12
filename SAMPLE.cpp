#include <stdio.h>
void mystery1(char *s1,const char *s2);
int main(void)
{
    char string1[40]="ABC";
    char string2[40]="GHI";

    mystery1(string1,string2);
    printf("%s",string1);
    return 0;


}
void mystery1(char *s1, const char *s2)
{
    while (*s1 != '\0')
    {
        s1++;
    }
    for (; *s1 = *s2; s1++,s2++)
    {

    }

}
