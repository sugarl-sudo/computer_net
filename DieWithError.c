#include <stdio.h> 
#include <stdlib.h> 

//エラーメッセージ
void DieWithError(char *errorMessage)
{
    perror(errorMessage);
    exit(1);
}
