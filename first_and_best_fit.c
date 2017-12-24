#include <stdio.h>
#include <malloc.h>

#define SIZE 10

//结构体定义每块内存块的可使用容量
typedef struct ram{
   // struct ram * precious;
    int lable;
    int size;
    int status;
    struct ram *next;
}Ram ,*RamPre;

//首次适应算法
void firstFit(int demand,RamPre *preHead){
    //对链表进行遍历，找出第一个适合的内存块
    struct ram* pre = *preHead,*p = *preHead,*pri = NULL;
    int result = pre->size - demand;
   // RamPre pri = pre;
    while (pre != NULL){
        if( result >= SIZE ){        //当剩余内存大于size的时候，只划出需要的部分
            p = (struct ram*)malloc(sizeof(struct ram));            //将指向新建节点
            if (p ==  NULL){
                printf("No enough memory !\n");
                break;
            }
            p->size = demand;
            p->status = 1;

            if (*preHead == NULL){
                //若原链表为空
                *preHead = p;
            }else{
                pri = pre;         //temp中保存当前节点的指针
            }
            if ( pre == *preHead){
                //若在头节点插入新节点
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
        }else if(result < SIZE && result >= 0 ){    //当剩余内存小于size且大于等于0的时候，将内存全部分配给
            p = (struct ram*)malloc(sizeof(struct ram));            //将指向新建节点
            if (p ==  NULL){
                printf("No enough memory !\n");
                break;
            }
            p->size = demand;
            p->status = 1;

            if (*preHead == NULL){
                //若原链表为空
                *preHead = p;
            }else{
                pri = pre;         //temp中保存当前节点的指针
            }
            if ( pre == *preHead){
                //若在头节点插入新节点
                p->next = *preHead;
                *preHead = p;
            }else{
                //  pre = pri;
                pri->next = p;
                p->next = pre;
            }
            pre->size = 0;
            printf("有内存可以分配\n");
            break;
        } else{
          //  pri->next = pre;
            pri = pre;              //保存当前节点的上一个节点
            pre = pre->next;
            result = pre->size - demand;
            if (pre == NULL){
                printf("没有足够大的内存可以分配");
            }
        }
    }

}

//最佳适应算法
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
    //再次便利找到最适合的内存块，进行分配
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
                //若原链表为空
                *preHead = p;
            }
            if ( pre == *preHead){
                //若在头节点插入新节点
                p->next = *preHead;
                *preHead = p;
            }else{
                //  pre = pri;
                pri->next = p;
                p->next = pre;
            }
            pre->size = result;
            printf("有内存可以分配\n");
            break;
        } else{
            pri = pre;              //保存当前节点的上一个节点
            pre = pre->next;
            result = pre->size - demand;
            if (pre == NULL){
                printf("没有足够大的内存可以分配");
            }
        }

    }



}

//回收内存算法
void recycleRam(RamPre idle){

}

//初始化空闲内存
void init(RamPre pre){
    char an ;
    int count = 0;
    //RamPre  tou = pre;
    printf("输入想要创建的内存空间:");
    scanf("%d",&(pre->size));
    pre->lable = count;
    pre->status = 0;
    pre->next = NULL;
    do{
        printf("是否继续创建(y/n)?");
        getchar();
        scanf("%c",&an);
        if (an == 'y' || an == 'Y'){
            struct ram* p = (struct ram*)malloc(sizeof(struct ram));
            p->next = NULL;
            printf("输入想要创建的内存空间:");
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
    printf("是否创建空闲内存（Y/N）?");
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