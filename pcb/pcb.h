//
// Created by 17381 on 2017/12/26.
//

#ifndef PCBPROJECT_PCB_H
#define PCBPROJECT_PCB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//进程三种状态
#define PROCESS_RUN 1
#define PROCESS_READY 0
#define PROCESS_FINISH 2

//优先数法
typedef struct P_PCB{
    int process_sign;       //进程标识符
    int process_priority_num;       //进程优先数
   // int cpu_time;           //进程所占CPU时间片数
    int cpu_need_time;      //进程所需时间片数
    int process_status;     //进程当前状态
    struct P_PCB * next;
}*pPCB;

////简单轮转法
//typedef struct R_PCB{
//    int process_sign;       //进程标识符
//    int process_rotation_num;       //轮转时间片
//    int cpu_time;           //进程所占CPU时间
//    int cpu_need_time;      //进程所需时间片数
//    int process_status;     //进程当前状态
//    struct PCB * next;
//}*pRPCB;

//将链表中的结构体按优先数从大到小的规律排序
void insert_for_sort_operation(struct P_PCB** ppNode, struct P_PCB* pNode);

void sort_for_link_node(struct P_PCB** ppNode);


//优先数法
void priority(struct P_PCB **run,struct P_PCB **ready,struct P_PCB **tail,struct P_PCB **finish);


#endif //PCBPROJECT_PCB_H
