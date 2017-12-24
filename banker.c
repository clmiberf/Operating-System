#include <stdio.h>
#include <stdbool.h>

#define AVAILABLE 20
#define MAX_X 20
#define MAX_Y 20
#define ALLOCATION_X 20
#define ALLOCATION_Y 20
#define NEED_X 20
#define NEED_Y 20

//系统资源量
int total[AVAILABLE];
//可用资源
int available[AVAILABLE];
//最大需求
int max[MAX_X][MAX_Y];
//分配数据,系统已分配给定义第i个进程多少个资源
int allocation[ALLOCATION_X][ALLOCATION_Y];
//表示每一个进程尚需的资源
int need[NEED_X][NEED_Y];


//初始化数据
void init(int n,int m){
    //int n,m;
    printf("请输入各类资源的数目:");
    for (int i = 0; i < n; ++i) {
        scanf("%d",&total[i]);
    }
    printf("请输入各进程对各类资源的最大需求：");
    for (int j = 0; j < m; ++j) {
        for (int i = 0; i < n; ++i) {
            scanf("%d",&max[j][i]);
        }

    }
    printf("请输入系统已分配给各进程的资源：");
    for (int k = 0; k <m ; ++k) {
        for (int i = 0; i <n ; ++i) {
            scanf("%d",&allocation[k][i]);
        }

    }

    //计算可用资源available
    for (int i1 = 0; i1 <m ; ++i1) {
        for (int i = 0; i <n ; ++i) {
            total[i] = total[i] - allocation[i1][i];

        }

    }
    for (int j1 = 0; j1 <n ; ++j1) {
        available[j1] = total[j1];
        printf("%d ",available[j1]);
    }
    printf("\n");
//    printf("请输入每个进程尚需的各类资源：");
//    for (int l = 0; l <m ; ++l) {
//        for (int i = 0; i <n ; ++i) {
//            scanf("%d",&need[l][i]);
//
//        }
//
//    }
    for (int i = 0; i <m ; ++i) {
        for (int j = 0; j <n ; ++j) {
            need[i][j] = max[i][j]-allocation[i][j];
            printf("%d ",need[i][j]);
        }
        printf("\n");
    }

}
//检查request是否符合要求
bool exam(int request[MAX_X],int object[AVAILABLE],int n){
    int i = 0;
    while (request[i]<=object[i] && i<n){
        i++;
    }
    if (i<n){
        return false;
    }
    return true;

}

//计算need
void calculate(int need[NEED_X][NEED_Y],int max[MAX_X][MAX_Y],int allocation[ALLOCATION_X][ALLOCATION_Y],int m,int n){
    for (int i = 0; i <m ; ++i) {
        for (int j = 0; j <n ; ++j) {
            need[i][j] = max[i][j]-allocation[i][j];
            printf("%d ",need[i][j]);
        }
        printf("\n");
    }


}



//试探性进行资源分配
void tryAssign(int *available,int *need,int *allocation ){

}


//安全性算法检查
void checkSecurity(int need[MAX_X][AVAILABLE],int allcation[MAX_X][MAX_Y],int n,int m){
    int count=0,k,t,o;        //记录已检查的进程个数//初始化finish跟work
    int work[n];                    //表示系统可分配给进程继续运行所需的各类进程数
    bool finish[m],exam[m];             //表示系统是否有足够的资源分配给进程
    for (int i = 0; i <n ; ++i) {
        work[i] = available[i];
        finish[i] = false;
        exam[i] = false;
    }

    for (int l = 0; l < m; ++l) {
        o++;
        for (int j = 0; j <m; ++j) {
            k=0;
            if (exam[j] == false){
                for (int i = 0; i <n && finish[j] == false; ++i) {
                    if (finish[j] == false){
                        k=i;
                        if (work[i] < need[j][i]){
                            exam[j]=true;
                            break;
                        }
                    }
                }
                if (k==n-1){
                    t = count;
                    count++;
                    printf("  %d  ",j);
                    finish[j]=true;
                    for (int i = 0; i <n ; ++i) {
                        work[i] = work[i] + allcation[j][i];
                        exam[i] = false;
                        printf("%d ",work[i]);
                    }
                    printf("\n");
                    break;
                }
            }

        }
        if(count == t){
            count=0;
            for (int i = 0; i < m; ++i) {
                printf("chucuole\n");
                work[i] = available[i];
                finish[i]=false;
            }
        }

    }


    if (count == m){
        printf("系统安全，可以进行资源分配");
    }else{
        printf("分配资源后，系统将进入不安全状态，不能进行资源分配");
    }
}




int main() {
    int n,m,count=0,b;
    bool exam1=false,exam2=false;
    int request[MAX_X];           //表示当前请求向量
    printf("输入系统资源种类数n 跟并行进程数m：");
    scanf("%d %d",&n,&m);
    printf("系统资源种类：%d,并行进程数:%d",n,m);
    init(n,m);
    do{
        printf("请输入本次请求资源的进程号:");
        scanf("%d",&b);
        printf("请输入请求的资源向量:");
        for (int i = 0; i <n ; ++i) {
            scanf("%d",&request[i]);

        }
        //检查是否request合理

        exam1 = exam(request,need[b],n);
        exam2 = exam(request,available,n);
        if (exam1 == true && exam2 ==true){
            for (int i = 0; i < n; ++i) {
                available[i] = available[i] - request[i];
                allocation[b][i] = allocation[b][i]+request[i];
                need[b][i] = need[b][i] - request[i];
            }

        }
        for (int j = 0; j <m ; ++j) {
            for (int i = 0; i <n ; ++i) {

            }

        }
        checkSecurity(need,allocation,n,m);

    }while(count==m);
    //可用资源

    return 0;
}