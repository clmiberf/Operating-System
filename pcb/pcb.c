//
// Created by 17381 on 2017/12/26.
//
#include "pcb.h"

//�������еĽṹ�尴�������Ӵ�С�Ĺ�������
void insert_for_sort_operation(struct P_PCB **ppNode, struct P_PCB *pNode)
{
    struct P_PCB* prev;
    struct P_PCB* cur;

    /* �ڵ�һ������֮ǰ����pNode */
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


//��������
/**
 *
 * @param p ����ָ�룬ָ������
 * @param run ��ʾ��ǰ���н���ָ��
 * @param ready ��������ͷָ��
 * @param tail ��������βָ��
 * @param finish ��ɶ���ͷָ��
 */
void priority(struct P_PCB **run,struct P_PCB **ready,struct P_PCB **tail,struct P_PCB **finish){
    char sign = 'y';
    if (*run == NULL){
        //�������Ϊ�գ���������
        printf("PCB���̿��ƿ�Ϊ�� !\n");
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
        //����������һ���ṹ������������жԱȣ����������һ��������,����һ����Ϊ����
        //��ԭ���װ��������Ӵ�С����������
        int count = head->cpu_need_time ;
        if ((head->process_priority_num < pReady->process_priority_num) && count > 0 ){
            str = *ready;
            //*ready = (*run)->next;
            if((head->next)->process_status == PROCESS_FINISH){
                //��ֻ��һ������δ���ʱ
            } else{
                *run = (*run)->next;
                printf("%d\n",head->process_priority_num);
                (*run)->process_status = PROCESS_RUN;
                ptr = *run;
                while (ptr != NULL ){
                    printf("ptr = %d\n",ptr->process_priority_num);
                    if ((head->process_priority_num > ptr->process_priority_num) && ptr->process_status != PROCESS_FINISH){
                        //�����׿�ʼ������������Σ������̲������λ��
                        head->process_status = PROCESS_READY;
                        str->next = head;
                        head ->next = ptr;
                        break;
                    }else if((ptr->process_priority_num == (*tail)->process_priority_num) && (head->process_priority_num < ptr->process_priority_num)){
                        //������δ��ɲ�����������͵�ʱ�򣬽��������ھ����εĶ�λ
                        head->process_status = PROCESS_READY;
                        head->next = ptr->next;
                        ptr->next = head;
                        *tail = head;
                        *finish = (*tail)->next;
                        break;
                    } else{
                        str = ptr;      //��strָ��ǰ���̵�ǰһ������
                        ptr = ptr->next;
                    }
                }
            }

        }else if(count == 0){
            //��������ɺ�
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
                //���ָ��ָ��NULL
                *finish = ptr;
                pFinish = *finish;
            }
            while (pFinish->next != NULL){
              //  printf(" %d \n",pFinish->process_priority_num);
                pFinish = pFinish->next;
            }
            head->next = NULL;
            head->process_status = PROCESS_FINISH;
            pFinish->next = head;         //����ɵĽ�������finish���е����
        }
        runHead = *run;
        while(runHead != NULL){
            //printf("������:%d ��������ʱ��Ƭ��:%d ������ռʱ��Ƭ����%d",runHead->process_priority_num,runHead->cpu_need_time,runHead->cpu_time);
            printf("%d %d %d",runHead->process_priority_num,runHead->cpu_need_time,runHead->process_status);
            printf("\n");
            runHead = runHead->next;
        }
        printf("is continue(Y/N)?");
        getchar();
        scanf("%c",&sign);
    }

}

