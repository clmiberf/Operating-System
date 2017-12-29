//
// Created by 17381 on 2017/12/26.
//
#include "pcb.h"

//将链表中的结构体按优先数从大到小的规律排序
void insert_for_sort_operation(struct P_PCB **ppNode, struct P_PCB *pNode)
{
    struct P_PCB* prev;
    struct P_PCB* cur;

    /* 在第一个数据之前插入pNode */
    if(pNode->process_priority_num > (*ppNode)->process_priority_num){
        pNode->next = *ppNode;
        *ppNode = pNode;
        return;
    }

    cur = *ppNode;
    while(cur){
        if(pNode->process_priority_num > cur->process_priority_num)
            break;

        prev = cur;
        cur = cur->next;
    }

    pNode->next = prev->next;
    prev->next = pNode;
    return;
}


void sort_for_link_node(struct P_PCB **ppNode)
{
    struct P_PCB* prev;
    struct P_PCB* curr;

    if(NULL == ppNode || NULL == *ppNode)
        return;

    curr = (*ppNode) ->next;
    (*ppNode) ->next = NULL;

    while(curr){
        prev = curr;
        curr = curr->next;
        insert_for_sort_operation(ppNode, prev);
    }

    return;
}


//优先数法
/**
 *
 * @param p 链表指针，指向链首
 * @param run 表示当前运行进程指针
 * @param ready 就绪队列头指针
 * @param tail 就绪队列尾指针
 * @param finish 完成队列头指针
 */
void priority(struct P_PCB **run,struct P_PCB **ready,struct P_PCB **tail,struct P_PCB **finish){
    char sign = 'y';
    if (*run == NULL){
        //如果链表为空，结束程序
        printf("PCB进程控制块为空 !\n");
        exit(0);
    }
    while (sign == 'y' || sign=='Y'){
        *ready = (*run)->next;
        struct P_PCB *pReady = *ready,*pFinish = *finish;
       // struct P_PCB *tailHead = *tail;
        struct P_PCB* head = *run,*ptr = *run,*str = NULL,*runHead = *run;
        head->cpu_need_time --;
        head->process_priority_num = head->process_priority_num - 3;

        // str = head->next;
        //将链首与下一个结构体的优先数进行对比，如果少于下一个优先数,将下一个置为链首
        //将原链首按优先数从大到小插入链表中
        int count = head->cpu_need_time ;
        if ((head->process_priority_num < pReady->process_priority_num) && count > 0 ){
            str = *ready;
            //*ready = (*run)->next;
            if((head->next)->process_status == PROCESS_FINISH){
                //当只有一个进程未完成时
            } else{
                *run = (*run)->next;
                printf("%d\n",head->process_priority_num);
                (*run)->process_status = PROCESS_RUN;
                ptr = *run;
                while (ptr != NULL ){
                    printf("ptr = %d\n",ptr->process_priority_num);
                    if ((head->process_priority_num > ptr->process_priority_num) && ptr->process_status != PROCESS_FINISH){
                        //从链首开始遍历就绪链表段，将进程插入合适位置
                        head->process_status = PROCESS_READY;
                        str->next = head;
                        head ->next = ptr;
                        break;
                    }else if((ptr->process_priority_num == (*tail)->process_priority_num) && (head->process_priority_num < ptr->process_priority_num)){
                        //当进程未完成并且优先数最低的时候，将进程置于就绪段的段位
                        head->process_status = PROCESS_READY;
                        head->next = ptr->next;
                        ptr->next = head;
                        *tail = head;
                        *finish = (*tail)->next;
                        break;
                    } else{
                        str = ptr;      //让str指向当前进程的前一个进程
                        ptr = ptr->next;
                    }
                }
            }

        }else if(count == 0){
            //当进程完成后
            if ((*ready)->process_status == PROCESS_FINISH){
                printf("all process finished\n");
                return;
            }
            *run = *ready;
            (*run)->process_status = PROCESS_RUN;
            *ready = (*run)->next;
           // ptr = *run;
            pFinish = *run;
            if (*finish == NULL){
                //完成指针指向NULL
                *finish = ptr;
                pFinish = *finish;
            }
            while (pFinish->next != NULL){
              //  printf(" %d \n",pFinish->process_priority_num);
                pFinish = pFinish->next;
            }
            head->next = NULL;
            head->process_status = PROCESS_FINISH;
            pFinish->next = head;         //将完成的进程置于finish队列的最后
        }
        runHead = *run;
        while(runHead != NULL){
            //printf("优先数:%d 进程所需时间片数:%d 进程所占时间片数：%d",runHead->process_priority_num,runHead->cpu_need_time,runHead->cpu_time);
            printf("%d %d %d",runHead->process_priority_num,runHead->cpu_need_time,runHead->process_status);
            printf("\n");
            runHead = runHead->next;
        }
        printf("is continue(Y/N)?");
        getchar();
        scanf("%c",&sign);
    }

}

