#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define POS_X1 35
#define POS_X2 40
#define POS_X3 50
#define POS_X4 65
#define POS_Y 3
int Menu(void);//主界面菜单
void SetPosition(int x,int y);
void VolunteerInfo();
void Register();
void Modify();
struct Will
{
    int Work;//前场还是后勤
    int Adjustice;//是否服从调剂
};
struct Skills
{
    int Interpersonal;//交际能力得分,评分由1-5分为5档
    int Exe;//行动能力得分,评分由1-5分为5档
    int Capacity;//管理能力得分,评分由1-5分为5档
};
struct volunteer{
    char* name;
    int gender;
    int age;
    char number[11];//电话号
    char ID[18];//身份证号
    char* workplace;
    int LanguageAbility;//掌握外语种类与熟练程度,评分由1-5分为5档
    int experience;//志愿服务经历，0表示从未，1表示有1-3次服务经历，2表示3次以上
    int servicetime;//提供服务的时间，0表示早上，1表示下午，2表示晚上。
    struct Skills;//个人特长
    struct Will;//个人意愿，前场还是后勤，是否服从调剂等
    struct volunteer* next;
};
//插入节点
void Insert(struct volunteer* head,struct volunteer* newnode)
{
    struct volunteer* p=head;
    while(p->next!=NULL)
    {
        p=p->next;
    }
    p->next=newnode;
}
//删除节点
void Delete(struct volunteer* head,struct volunteer* newnode)
{
    struct volunteer* p=head;
    while(p->next!=newnode)
    {
        p=p->next;
    }
    p->next=newnode->next;
}
//查找节点
struct volunteer* Search(struct volunteer* head,char* name)
{
    struct volunteer* p=head;
    while(p->next!=NULL)
    {
        if(strcmp(p->name,name)==0)
        {
            return p;
        }
        p=p->next;
    }
    return NULL;
}
//修改节点
void Modify(struct volunteer* head,struct volunteer* newnode)
{
    struct volunteer* p=head;
    while(p->next!=newnode)
    {
        p=p->next;
    }
    p->next=newnode->next;
}
void writeExcel()
{
    char chy[4]={ 'x' ,'a' ,'h','w' } ;
    int data[4]={ 1 , 3 , 6 ,9	};
    int i ;
    FILE *fp = NULL ;
    fp = fopen("test.xls","w") ;
    for (i=0 ; i<4 ;i++)
        fprintf(fp,"%c\t%d\n",chy[i],data[i] ) ;
    fclose(fp);
}

void ReadExcel()
{
    FILE *fp;
    char filename[40]  ;
    int i,j ;
    float da[6][5] = {0} ;
    printf(" 输入文件名: ");
    gets(filename);
    fp=fopen(filename,"r");     // fp指针指向文件头部
    for(i = 0 ;i < 6 ; i++)
        for(j = 0 ;j < 5 ; j++)
        {
            fscanf(fp,"%f",&da[i][j]);
            fseek(fp, 1L, SEEK_CUR);   /*fp指针从当前位置向后移动*/
        }

    for(i = 0 ;i < 6 ; i++)
        printf("%f\t%f\t%f\t%f\t%f\t\n",da[i][0],da[i][1],da[i][2],da[i][3],da[i][4]);
}

int main() {
    char ch;
    system("mode con cols=130 lines=60");
    system("color 0A");
    while (1)
    {
        system("cls");
        ch=Menu();
        switch (ch) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            case 9:
                break;
            case 10:
                break;
            case 11:
                break;
            case 12:
                break;
            case 13:
                break;
            case 14:
                break;
            case 15:
                break;
            case 16:
                break;
            case 0:
                break;
        }
    }
    return 0;
}


int Menu(void)
{
    int posy=13;
    int option;
    SetPosition(POS_X3,posy);
    printf("\t\t    ********************************************************\n");
    SetPosition(POS_X3,++posy);
    printf("\t\t    *               杭州亚运会志愿者管理系统               *\n");
    SetPosition(POS_X3,++posy);
    printf("\t\t    ********************************************************\n");
    SetPosition(POS_X3,++posy);
    printf("\t\t   ┌───────────────────────────────────────────────────────┐\n");
    SetPosition(POS_X3,++posy);
    printf("\t\t   │                                                       │\n");
    SetPosition(POS_X3,++posy);
    printf("\t\t   │                   1. 登记志愿者信息                   │\n");
    SetPosition(POS_X3,++posy);
    printf("\t\t   │                                                       │\n");
    SetPosition(POS_X3,++posy);
    printf("\t\t   │                                                       │\n");
    SetPosition(POS_X3,++posy);
    printf("\t\t   │                                                       │\n");
    SetPosition(POS_X3,++posy);
    printf("\t\t   │                    2. 比赛相关信息                    │\n");
    SetPosition(POS_X3,++posy);
    printf("\t\t   │                                                       │\n");
    SetPosition(POS_X3,++posy);
    printf("\t\t   │                                                       │\n");
    SetPosition(POS_X3,++posy);
    printf("\t\t   │                                                       │\n");
    SetPosition(POS_X3,++posy);
    printf("\t\t   │                    3. 志愿服务统计                    │\n");
    SetPosition(POS_X3,++posy);
    printf("\t\t   │                                                       │\n");
    SetPosition(POS_X3,++posy);
    printf("\t\t   │                                                       │\n");
    SetPosition(POS_X3,++posy);
    printf("\t\t   └───────────────────────────────────────────────────────┘\n");
    SetPosition(POS_X3,++posy);

    printf("\t\t   请选择你想要进行的操作[0~3]:[  ]\b\b\b");
    scanf("%d",option);
    return option;
}
void SetPosition(int x,int y)
{
    HANDLE hOut;
    COORD pos;
    hOut=GetStdHandle(STD_OUTPUT_HANDLE);
    pos.X=x;
    pos.Y=y;
    SetConsoleCursorPosition(hOut,pos);
}
void VolunteerInfo()
{
    //读取文件的函数
    int op;
    while(){

        printf("需要进行的操作是 登记1/修改2 ：[  ]\b\b\b");
    scanf("%d",op);

    switch (op) {
        case 0:
            break;
        case 1:
            Register();
            break;
        case 2:
            Modify();
            break;
    }
    system("cls");
}
    void Register()
    {
        int op;
        char ese;
        printf("按下ESE键以返回上一界面...\n");
        if(_kbhit())
        {
            ese=getch();
            if(ese!=27)
            {
                printf("新的志愿者信息登记表 ：");
                //读入新文件

            }
        }
        system("cls");
    }
    void Modify()
    {
        int op;
        char ese;
        printf("按下ESE键以返回上一界面...\n");
        if(_kbhit())
        {
            ese=getch();
            if(ese!=27)
            {
                printf("新的志愿者信息登记表 ：");
                //读入新文件

            }
        }
        system("cls");
    }