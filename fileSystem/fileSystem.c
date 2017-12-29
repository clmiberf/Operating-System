//
// Created by 17381 on 2017/12/23.
//
#include "fileSystem.h"
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

int FILE_RUNNING_NUM = 0;

//创建文件
void createFile(struct UFD **head,char fileName[30]){
    struct UFD *pFile = NULL,*p = *head;
    pFile = (struct UFD*)malloc(sizeof(struct UFD));
//    printf("input file name: ");
//    gets(pFile->file_name);
//    getchar();
    //如果申请内存失败,退出程序
    printf("1\n");
    if (pFile == NULL){
        printf("No enough memory to allocation ! \n");
        exit(0);
    }
    printf("2\n");
    if (*head == NULL){
        //若原链表为空
        *head = pFile;   //将新建节点设为头节点
        printf("3\n");
    }else{
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = pFile;        //让末节点的指针域 指向新建节点
    }
    printf("sdfsdaf\n");
    strcpy(pFile->file_name,fileName);
    printf("name = %s\n",pFile->file_name);
    printf("input protect num:");
    scanf("%d",&pFile->protect_num);
    printf("input file address(执行/读/写->1/5/7): ");
    scanf("%d",&pFile->file_address);
    pFile->next = NULL;
    printf("name2 = %s",p->file_name);
    //return head;
}

//删除文件
/**
 *删除一个文件前，首先遍历打开文件目录,查看是否是打开状态,
 * 打开状态下不让删除
 * @param p 用户文件目录
 * @param str   打开文件目录
 * @param fileName  需要操作的文件
 */
void deleteFile(struct UFD *head,struct AFD **strHead,char fileName[30]){
    int count = 0;              //记录是否存在该文件，当用户目录下有该文件的时候，将count改变为1
    struct UFD* p = head;
    struct AFD* str = *strHead;
    while (str != NULL){
        if (strcmp(str->file_name,fileName) == 0){
            printf("文件当前处于打开状态,不允许删除\n");
            return;
        }else{
           // struct AFD *delete = NULL;
           // delete = str;
            str = str->next;
           // free(delete);
        }
    }

    while (p != NULL){
        if (strcmp(p->file_name,fileName) == 0){
            struct UFD *o = NULL;          //删除当前文件节点
            o = p;
            p = p->next;
            free(o);
            count = 1;
            break;
        }else{
            p = p->next;
        }

    }

    if (count){
        printf("delete successful !\n");
    }else{
        printf("no such file  !\n");
    }

}

//打开文件
void openFile(struct UFD *p,struct AFD **strHead,char fileName[30]){
    int count = 0;
    struct AFD * ptr = NULL,*str = *strHead;
    ptr = (struct AFD *)malloc(sizeof(struct AFD));
    if (FILE_RUNNING_NUM == USER_RUN_FILE_NUM ){
        //判断当前打开文件的个数,如果超过最大值,则不允许再打开
        printf("当前打开文件已经到达可打开上限,不能再打开了\n");
        return;
    } else if(*strHead == NULL){
        //原链表为空
        *strHead = ptr;
    } else{
        while(str->next != NULL){                 //将指针指向AFD链表的末尾
            str = str->next;
        }
        str->next = ptr;          //将新创建的AFD置于AFD链表的末尾
    }

    while (p != NULL){
        if (strcmp(p->file_name,fileName) == 0){

            strcpy(ptr->file_name,p->file_name);
            ptr->file_num = FILE_RUNNING_NUM + 1;
//                printf("input file protect num: ");
//                scanf("%d",&ptr->file_protect_num);
            ptr->file_protect_num = p->protect_num;
            ptr->next = NULL;
            ptr->read_write_ptr = 0;
            count = 1;
            FILE_RUNNING_NUM ++;
            break;
        }
    }

    if (count){
        printf("open success !\n");
    }else{
        printf("open failed \n");
    }

}

//关闭文件
void closeFile(struct AFD *str,char fileName[30]){
    int count = 0;
    //遍历打开文件目录
    while(str != NULL){
        if (strcmp(str->file_name,fileName) == 0){
            struct AFD* o;
            o = str;
            str = str->next;
            free(o);
            count = 1;
            break;
        }else{
            str = str->next;
        }
    }
    if (count == 1){
        printf("colse successful !\n");
    }else{
        printf("no such file in openFile !\n");
    }

}

//读文件内容
void readFile(struct UFD *p,struct AFD **strHead,char fileName[30]){
    struct AFD* str = *strHead;
    int count = 0;
    //遍历打开文件目录
    while (str != NULL){
        if (strcmp(str->file_name,fileName) == 0){
            if (str->file_protect_num >= 5){
                //当保护码大于等于5的时候，文件可读
                //遍历用户文件目录,将文件存放的地址赋给读写指针
                while (p != NULL){
                    if (strcmp(p->file_name,fileName) == 0){
                        str->read_write_ptr = p->file_address;
                        break;
                    }else{
                        p = p->next;
                    }
                }
                count = 1;
                break;
            }
        }else{
            str = str->next;
        }

    }
    if (count == 0){
        //如果打开文件目录中没有当前文件,则进行对用户目录的遍历
        while(p != NULL){
            if (strcmp(p->file_name,fileName) == 0){
                //可读访问权限
                if (p->protect_num >= 5){
                    openFile(p,strHead,fileName);
                    count = 1;
                    break;
                }
            } else{
                p = p->next;
            }
        }
    }

    if (count == 1){
        printf("read success !\n");
    }else{
        printf("no such file or no root !\n");
    }

}

//写文件内容
void writeFile(struct UFD *p,struct AFD **strHead,char fileName[30]){
    struct AFD* str = *strHead;
    int count = 0;
    //遍历打开文件目录
    while (str != NULL){
        if (strcmp(str->file_name,fileName) == 0){
            if (str->file_protect_num == 7){
                //当保护码等于7的时候，文件可写
                //遍历用户文件目录,将文件存放的地址赋给读写指针
                while (p != NULL){
                    if (strcmp(p->file_name,fileName) == 0){
                        str->read_write_ptr = p->file_address;
                        break;
                    }else{
                        p = p->next;
                    }
                }
                count = 1;
                break;
            }
        }else{
            str = str->next;
        }
    }

    if (count == 0){
        //如果打开文件目录中没有当前文件,则进行对用户目录的遍历
        while(p != NULL){
            if (strcmp(p->file_name,fileName) == 0){
                //可写访问权限
                if (p->protect_num == 7){
                    openFile(p,strHead,fileName);
                    count = 1;
                    break;
                }
            } else{
                p = p->next;
            }
        }
    }

    if (count == 1){
        printf("write success !\n");
    }else{
        printf("no such file or no root !\n");
    }
}

//显示当前用户的文件目录
/**
 *
 * @param p
 * @param fileName
 */
void showFile(struct UFD *p){
    //遍历用户文件目录
    if (p == NULL){
        printf("no file\n");
    }else{
        printf("protect = %d\n",p->protect_num);
        while (p != NULL){
            printf("%s  \n",p->file_name);
            p = p->next;
        }
    }


}