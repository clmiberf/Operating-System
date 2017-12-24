//
// Created by 17381 on 2017/12/23.
//

#ifndef FILESYSTEM_FILESYSTEM_H
#define FILESYSTEM_FILESYSTEM_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define USER_NUM 10
#define USER_FILE_NUM 10
#define USER_RUN_FILE_NUM 5
#define PROTECT_READ 4
#define PROTECT_WRITE 2
#define PROTECT_RUN 1


//用户文件目录
struct UFD{
    char file_name[50];             //文件名
    int protect_num;                //保护码
   // int file_length;                //文件长度
    unsigned int file_address;      //文件存放地址
    struct UFD *next;               //下一条文件信息
}FILE_UFD,*pFILE_UFD;


//主文件目录
struct MFD{
    char user_name[50];         //用户名
    struct FILE_UFD *ptr;       //文件目录指针
}FILE_MFD,*pFILE_MFD;

//打开文件目录
struct AFD{
    int file_num;         //打开文件号
    char file_name[50];         //文件名
    int file_protect_num;   //打开文件保护码
    unsigned int read_write_ptr;      //读写指针,这里为了简化工作量,直接定义成整形,实际项目中不能这样
    struct AFD *next;

}FILE_AFD,*pFILE_AFD;


//创建文件
void createFile(struct UFD **p,char fileName[30]);

//删除文件
void deleteFile(struct UFD *p,struct AFD ** str,char fileName[30]);

//打开文件
void openFile(struct UFD *p,struct AFD **str,char fileName[30]);

//关闭文件
void closeFile(struct AFD *str,char fileName[30]);

//读文件内容
void readFile(struct UFD *P,struct AFD **strHead,char fileName[30]);

//写文件内容
void writeFile(struct UFD *p,struct AFD **str,char fileName[30]);

//显示当前用户的文件目录
void showFile(struct UFD *p);


#endif //FILESYSTEM_FILESYSTEM_H
