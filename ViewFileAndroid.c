/* Просмотр файлов в андроид. Что бы выбрать какую папку открыть, нужно ввести номер этой папки.
Что бы вернуться в начало, нужно ввести ноль(0). Что бы выйти из программы, нужно нажать крестик */
#include<stdio.h>
#include<dirent.h>

struct numStr
{
    int num;
    char * str;
    struct numStr * next;
};
int cnt = 1;
struct dirent * strName;

struct numStr * first;
struct numStr * current;

char strPrev[255][255];
int cntPrev = 0;
DIR * dir;
int point = 0;

void recordFolder();
void printList();

int main()
{
    strcpy(strPrev, "/storage/emulated/0/");
    
    while(1)
    {
        printList();
        fflush(stdin);
        scanf("%d", &point);
        system("clear");
        if(point)
        {
            current = first;
            while(current->num != point)
                current = current->next;
            strcpy(strPrev[cntPrev], strPrev[cntPrev-1]);
            strcat(strPrev[cntPrev], current->str);
            strcat(strPrev[cntPrev], "/");
        }
        else
        {
            strcpy(strPrev[cntPrev], strPrev[0]);
        }
    }
}

void recordFolder()
{
    if(first)
    {
        current->next = (struct numStr * ) malloc(sizeof(struct numStr));
        current = current->next;
        current->num = cnt;
        current->str = strName->d_name;
        current->next = NULL;
    }
    else
    {
        current = (struct numStr * ) malloc(sizeof(struct numStr));
        first = current;
        first->num = cnt;
        first->str = strName->d_name;
        current->next = NULL;
    }
    cnt++;
}

void printList()
{  
    dir = opendir(strPrev[cntPrev]);
    while(strName = readdir(dir))
    {
        recordFolder();
        printf("%d %s\n", current->num, current->str);
    }    
    cnt = 1;
    closedir(dir);    
    cntPrev++;
}