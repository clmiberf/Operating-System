#include "pcb.h"

//int count = 0;

//�Խ��̿��ƿ���г�ʼ��
void init(struct P_PCB *pre ){
    char an ;
    int count = 0;
    //RamPre  tou = pre;
    printf("���������������");
    scanf("%d",&(pre->process_priority_num));
//    printf("���������ռCPUʱ��Ƭ����");
//    scanf("%d",&(pre->cpu_time));
    printf("�����������ʱ��Ƭ��:");
    scanf("%d",&(pre->cpu_need_time));
    pre->process_status = PROCESS_READY;
    pre->process_sign = count;
    pre->next = NULL;
    do{
        printf("�Ƿ��������(y/n)?");
        getchar();
        scanf("%c",&an);
        if (an == 'y' || an == 'Y'){
            struct P_PCB *p = (struct P_PCB*)malloc(sizeof(struct P_PCB));
            count++;
            printf("���������������");
            scanf("%d",&(p->process_priority_num));
//            printf("���������ռCPUʱ��Ƭ����");
//            scanf("%d",&(p->cpu_time));
            printf("�����������ʱ��Ƭ��:");
            scanf("%d",&(p->cpu_need_time));
            p->process_status = PROCESS_READY;
            p->process_sign = count;
            p->next = NULL;
            pre->next = p;
            pre = pre->next;
        }

    }while (an == 'y' ||an == 'Y');
}


int main() {

    struct P_PCB* p_pcb = (struct P_PCB *)malloc(sizeof(struct P_PCB));
    struct P_PCB* run=NULL,*ready = NULL,*tail = NULL,*finish = NULL;
    char an;
    printf("�Ƿ񴴽�����(Y/N)?");
    scanf("%c",&an);
    if (an == 'Y'){
        init (p_pcb);
    }
    struct P_PCB *s = p_pcb;
    while(s != NULL){
        printf("%d-",s->process_sign);
        s= s->next;
    };
    printf("\n");
    sort_for_link_node(&p_pcb);
    s = p_pcb;
    while(s->next != NULL){
        printf("%d-",s->process_priority_num);
        s= s->next;
    };
    printf("\n");
    ready = p_pcb->next;
    tail = s;
    finish = NULL;
    p_pcb->process_status = PROCESS_RUN;
    priority(&p_pcb,&ready,&tail,&finish);
    s = p_pcb;
    while(s != NULL){
        printf("%d-",s->process_sign);
        s= s->next;
    };
    return 0;
}