#include <stdio.h>
#include <malloc.h>

#define SIZE 10

//�ṹ�嶨��ÿ���ڴ��Ŀ�ʹ������
typedef struct ram{
   // struct ram * precious;
    int lable;
    int size;
    int status;
    struct ram *next;
}Ram ,*RamPre;

//�״���Ӧ�㷨
void firstFit(int demand,RamPre *preHead){
    //��������б������ҳ���һ���ʺϵ��ڴ��
    struct ram* pre = *preHead,*p = *preHead,*pri = NULL;
    int result = pre->size - demand;
   // RamPre pri = pre;
    while (pre != NULL){
        if( result >= SIZE ){        //��ʣ���ڴ����size��ʱ��ֻ������Ҫ�Ĳ���
            p = (struct ram*)malloc(sizeof(struct ram));            //��ָ���½��ڵ�
            if (p ==  NULL){
                printf("No enough memory !\n");
                break;
            }
            p->size = demand;
            p->status = 1;

            if (*preHead == NULL){
                //��ԭ����Ϊ��
                *preHead = p;
            }else{
                pri = pre;         //temp�б��浱ǰ�ڵ��ָ��
            }
            if ( pre == *preHead){
                //����ͷ�ڵ�����½ڵ�
                p->next = *preHead;
                *preHead = p;
            }else{
              //  pre = pri;
                pri->next = p;
                p->next = pre;
            }
            pre->size -= demand;
            printf("yes\n");
            printf("%d\n",p->size);
            printf("%d\n",p->next->size);
            break;
        }else if(result < SIZE && result >= 0 ){    //��ʣ���ڴ�С��size�Ҵ��ڵ���0��ʱ�򣬽��ڴ�ȫ�������
            p = (struct ram*)malloc(sizeof(struct ram));            //��ָ���½��ڵ�
            if (p ==  NULL){
                printf("No enough memory !\n");
                break;
            }
            p->size = demand;
            p->status = 1;

            if (*preHead == NULL){
                //��ԭ����Ϊ��
                *preHead = p;
            }else{
                pri = pre;         //temp�б��浱ǰ�ڵ��ָ��
            }
            if ( pre == *preHead){
                //����ͷ�ڵ�����½ڵ�
                p->next = *preHead;
                *preHead = p;
            }else{
                //  pre = pri;
                pri->next = p;
                p->next = pre;
            }
            pre->size = 0;
            printf("���ڴ���Է���\n");
            break;
        } else{
          //  pri->next = pre;
            pri = pre;              //���浱ǰ�ڵ����һ���ڵ�
            pre = pre->next;
            result = pre->size - demand;
            if (pre == NULL){
                printf("û���㹻����ڴ���Է���");
            }
        }
    }

}

//�����Ӧ�㷨
void bestFit(int demand,RamPre *preHead){
    //RamPre str = pre;
    struct ram *str = *preHead,*p = *preHead ,*pre = *preHead,*pri = NULL;
    int result = 1000;
    int n;
    int lable = -1;
    while (str != NULL){
        n = str->size - demand;
       // n = str->size;
        if(n > 0 && n < result){
            result = n;
            lable = str->lable;
        }
        str = str->next;
    }

    printf("lable = %d\n",lable);
    //�ٴα����ҵ����ʺϵ��ڴ�飬���з���
    while (pre != NULL){
        if(lable == pre->lable){
            printf("pre->lable = %d\n",pre->lable);
            p = (struct ram*)malloc(sizeof(struct ram));
            if (p ==  NULL){
                printf("No enough memory !\n");
               // exit(0);
                break;
            }
            p->size = demand;
            p->status = 1;
            p->lable = 0;

            if (*preHead == NULL) {
                //��ԭ����Ϊ��
                *preHead = p;
            }
            if ( pre == *preHead){
                //����ͷ�ڵ�����½ڵ�
                p->next = *preHead;
                *preHead = p;
            }else{
                //  pre = pri;
                pri->next = p;
                p->next = pre;
            }
            pre->size = result;
            printf("���ڴ���Է���\n");
            break;
        } else{
            pri = pre;              //���浱ǰ�ڵ����һ���ڵ�
            pre = pre->next;
            result = pre->size - demand;
            if (pre == NULL){
                printf("û���㹻����ڴ���Է���");
            }
        }

    }



}

//�����ڴ��㷨
void recycleRam(RamPre idle){

}

//��ʼ�������ڴ�
void init(RamPre pre){
    char an ;
    int count = 0;
    //RamPre  tou = pre;
    printf("������Ҫ�������ڴ�ռ�:");
    scanf("%d",&(pre->size));
    pre->lable = count;
    pre->status = 0;
    pre->next = NULL;
    do{
        printf("�Ƿ��������(y/n)?");
        getchar();
        scanf("%c",&an);
        if (an == 'y' || an == 'Y'){
            struct ram* p = (struct ram*)malloc(sizeof(struct ram));
            p->next = NULL;
            printf("������Ҫ�������ڴ�ռ�:");
            scanf("%d",&(p->size));
            count++;
            p->lable = count;
            p->status = 0;
            pre->next = p;
            pre = pre->next;
        }

    }while (an == 'y' ||an == 'Y');
}

int main() {
    struct ram *p = (struct ram*)malloc(sizeof(struct ram));
    char an;
    printf("�Ƿ񴴽������ڴ棨Y/N��?");
    scanf("%c",&an);
    if (an == 'Y'){
        init (p);
    }
    struct ram *s = p;
    while(s != NULL){
        printf("%d-",s->size);
        s= s->next;

    };
    printf("\n");

   // printf("%d",p->size);

    bestFit(20,&p);
    while(p != NULL){
        printf("%d-",p->size);
        p= p->next;

    };
    return 0;
}