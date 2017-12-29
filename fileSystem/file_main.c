#include <stdio.h>
#include "fileSystem.h"

//比较命令,选择函数
void choose(char command[30],char fileName[50],struct UFD **p,struct AFD **str,struct MFD *m,int *count){
    int i;
    printf("command = %s \n",command);

    if(strcmp(command,"create") == 0){
        i = 0;
    }else if(strcmp(command,"exit") == 0){
        *count = 0;
        i = 7;
    }else if(strcmp(command,"delete") == 0){
        i = 1;
    }else if(strcmp(command,"open") == 0){
        i = 2;
    }else if(strcmp(command,"close") == 0){
        i = 3;
    }else if(strcmp(command,"read") == 0){
        i = 4;
    }else if(strcmp(command,"write") == 0){
        i = 5;
    }else if(strcmp(command,"ls") == 0){
        i = 6;
    }else {
        printf("please input legal input \n");
        return;
    }
    printf("i = %d\n",i);
    switch( i ){
        case 0:
          //  printf("fileName = %s \n",fileName);
            createFile(p,fileName);
           // printf("fileName = %s",(*p)->file_name);
            break;
        case 1:
            deleteFile(*p,str,fileName);
            break;
        case 2:
            openFile(*p,str,fileName);
            break;
        case 3:
            closeFile(*str,fileName);
            break;
        case 4:
            readFile(*p,str,fileName);
            break;
        case 5:
            writeFile(*p,str,fileName);
            break;
        case 6:         //ls
            printf("%s\n",(*p)->file_name);
            showFile(*p);
            break;
        case 7:
            printf("exit\n");
            exit(0);
    }
}

void init(struct UFD *p, struct MFD* m, struct AFD* str){
    //表头指针
    p = NULL;
    m = NULL;
    str = NULL;
//    p = (struct UFD *)malloc(sizeof(struct UFD));
//    m = (struct UFD *)malloc(sizeof(struct UFD));
//    str = (struct UFD *)malloc(sizeof(struct UFD));
//
//    strcpy(p->file_name ,"");
//    p->protect_num = 1;
//    p->file_address = 0;
//    p->next = NULL;
//
//    strcpy(str->file_name ,"");
//    str->file_num = 1;
//    str->file_protect_num = 0;
//    str->next = NULL;
//    str->read_write_ptr = 0;
//
//    strcpy(m->user_name ,"tp");
//    m->ptr = 0;

}

int main() {
    char command[30],fileName[30];
    struct UFD *p = NULL;
    struct AFD *str = NULL;
    struct MFD *m = NULL;
    int count = 1;
    while (count){
        printf("**********  HELP MENU  **********\n");
        printf("1. 创建文件: create + file\n");
        printf("2. 删除文件: delete + file\n");
        printf("3. 打开文件: open   + file\n");
        printf("4. 关闭文件: close  + file\n");
        printf("5. 读取文件: read   + file\n");
        printf("6. 写入文件: write  + file\n");
        printf("7. 显示目录: ls           \n");
        printf("8. 退出：    exit         \n");
        scanf("%s %s",command,fileName);
        //getchar();
        //init(p,m,str);
        choose(command,fileName,&p,&str,m ,&count);
        printf("%d",count);
    }
    return 0;
}