#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#define POS_X1 35
#define POS_X2 40
#define POS_X3 50
#define POS_X4 65
#define POS_Y 3

typedef struct Will
{
    int Work;//前场还是后勤
    int Adjustice;//是否服从调剂
}Will;
typedef struct Skills
{
    int Interpersonal;//交际能力得分,评分由1-5分为5档
    int Exe;//行动能力得分,评分由1-5分为5档
    int Capacity;//管理能力得分,评分由1-5分为5档
}Skills;
typedef struct Volunteer{
    char* name;
    int gender;
    int age;
    char number[11];//电话号
    char ID[18];//身份证号
    char* workplace;
    int LanguageAbility;//掌握外语种类与熟练程度,评分由1-5分为5档,我们假定仅以英语为例
    int experience;//志愿服务经历，0表示从未，1表示有1-3次服务经历，2表示3次以上
    int servicetime;//提供服务的时间，0表示早上，1表示下午，2表示晚上。
    Skills skills;//个人特长
    Will will;//个人意愿，前场还是后勤，是否服从调剂等
    struct Volunteer* next;
}Volunteer;

Volunteer *volunteer;
void WriteExcel();
void ReadExcel(char *filename);
int Menu(void);//主界面菜单
void SetPosition(int x,int y);
void pInfo();
void Register();
void CheckS();//
void Modify();
void CompetitionInfo();
void CheckC();
void Arrangement();
void Statistic();

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
void WriteExcel()
{
    FILE *fp = NULL ;
    fp = fopen("volunteer.xls","w") ;
    Volunteer *p=volunteer;
    while(!feof(fp))
    {
        fprintf(fp,"%s\t%d\t%d\t%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t\n",p->name,p->gender,p->age,p->number,p->ID,p->workplace,p->LanguageAbility,p->experience,p->servicetime,p->skills.Interpersonal,p->skills.Exe,p->skills.Capacity,p->will.Work,p->will.Adjustice) ;
        p=p->next;
    }
    fclose(fp);
}
void ReadExcel(char *filename)
{
    FILE *fp;
    fp=fopen(filename,"r");     // fp指针指向文件头部
    while (!feof(fp))
    {
        Volunteer *p= (Volunteer *)malloc(sizeof(Volunteer));
        fscanf(fp,"%f",p->name);
        fseek(fp, 1L, SEEK_CUR);   /*fp指针从当前位置向后移动*/
        fscanf(fp,"%d",p->gender);
        fseek(fp, 1L, SEEK_CUR);
        fscanf(fp,"%d",p->age);
        fseek(fp, 1L, SEEK_CUR);
        fscanf(fp,"%s",p->number);
        fseek(fp, 1L, SEEK_CUR);
        fscanf(fp,"%s",p->ID);
        fseek(fp, 1L, SEEK_CUR);
        fscanf(fp,"%s",p->workplace);
        fseek(fp, 1L, SEEK_CUR);
        fscanf(fp,"%d",p->LanguageAbility);
        fseek(fp, 1L, SEEK_CUR);
        fscanf(fp,"%d",p->experience);
        fseek(fp, 1L, SEEK_CUR);
        fscanf(fp,"%d",p->servicetime);
        fseek(fp, 1L, SEEK_CUR);
        fscanf(fp,"%d",p->skills.Interpersonal);
        fseek(fp, 1L, SEEK_CUR);
        fscanf(fp,"%d",p->skills.Exe);
        fseek(fp, 1L, SEEK_CUR);
        fscanf(fp,"%d",p->skills.Capacity);
        fseek(fp, 1L, SEEK_CUR);
        fscanf(fp,"%d",p->will.Work);
        fseek(fp, 1L, SEEK_CUR);
        fscanf(fp,"%d",p->will.Adjustice);
        fseek(fp, 1L, SEEK_CUR);
        volunteer->next=p;
        volunteer=p;
    }
    fclose(fp);
}//还需做一个读取比赛相关信息的函数
void VolunteerInfo()
{
    int op;
    char ese;
    char* filename;
    printf("按下ESE键以返回上一界面...\n");
    if(_kbhit())
    {
        ese=getch();
        if(ese!=27)
        {
            printf("请输入志愿者相关信息的文件名：");
            scanf("%s",filename);
            ReadExcel(filename);//读取文件的函数
            printf("需要进行的操作是 登记1/修改2 ：[  ]\b\b\b");
            scanf("%d",op);
            switch (op) {
                case 1:
                    Register();
                    break;
                case 2:
                    Modify();
                    break;
            }
        }
    }
    system("cls");
}
void Register()
{
    char ese;
    char* filename;
    printf("按下ESE键以返回上一界面...\n");
    if(_kbhit())
    {
        ese=getch();
        if(ese!=27)
        {
            printf("新的志愿者信息登记表 ：");
            scanf("%s",filename);
            ReadExcel(filename);
        }
    }
    system("cls");
}
void Modify()
{
    int op;
    char ese;
    char* check;
    char* modify1;
    int modify2;
    printf("按下ESE键以返回上一界面...\n");
    if(_kbhit())
    {
        ese=getch();
        if(ese!=27)
        {
            while(1)
            {
                printf("请输入需要修改信息的志愿者的 姓名/手机号/身份证号(0退出）：");
                scanf("%s",check);
                if(check=='0')
                    break;
                //查找函数,返回对应链表位置
                while(op!=0)
                {
                    printf("请输入需要修改的数据编号与修改后的值(0退出）：");
                    scanf("%d",&op);
                    switch (op) {
                        case 0:
                            break;
                        case 1:
                            scanf("%s",modify1);
                            strcpy(volunteer->name,modify1);
                            break;
                        case 4:
                            scanf("%s",modify1);
                            strcpy(volunteer->number,modify1);
                            break;
                        case 5:
                            scanf("%s",modify1);
                            strcpy(volunteer->ID,modify1);
                            break;
                        case 6:
                            scanf("%s",modify1);
                            strcpy(volunteer->workplace,modify1);
                            break;
                        case 2:
                            scanf("%d",&modify2);
                            volunteer->gender=modify2;
                            break;
                        case 3:
                            scanf("%d",&modify2);
                            volunteer->age=modify2;
                            break;
                        case 7:
                            scanf("%d",&modify2);
                            volunteer->LanguageAbility=modify2;
                            break;
                        case 8:
                            scanf("%d",&modify2);
                            volunteer->experience=modify2;
                            break;
                        case 9:
                            scanf("%d",&modify2);
                            volunteer->servicetime=modify2;
                            break;
                        case 10:
                            scanf("%d",&modify2);
                            volunteer->skills.Interpersonal=modify2;
                            break;
                        case 11:
                            scanf("%d",&modify2);
                            volunteer->skills.Exe=modify2;
                            break;
                        case 12:
                            scanf("%d",&modify2);
                            volunteer->skills.Capacity=modify2;
                            break;
                        case 13:
                            scanf("%d",&modify2);
                            volunteer->will.Work=modify2;
                            break;
                        case 14:
                            scanf("%d",&modify2);
                            volunteer->will.Adjustice=modify2;
                            break;
                    }
                    modify2=0;
                    modify1="";
                }
            }
        }
    }
    system("cls");
}
void CompetitionInfo()
{
    //读取文件的函数
    int op;
    char ese;
    printf("按下ESE键以返回上一界面...\n");
    if(_kbhit())
    {
        ese=getch();
        if(ese!=27)
        {
            printf("是否需要查看比赛信息 需要1/不需要0 ：[  ]\b\b\b");
            scanf("%d",op);
            switch (op) {
                case 1:
                    CheckC();
                    break;
            }
            //系统自动进行匹配
        }
    }
    system("cls");
}
void CheckC()
{

}
void Arrangement()
{

}
void Statistic()
{
    int op;
    char ese;
    printf("按下ESE键以返回上一界面...\n");
    if(_kbhit())
    {
        ese=getch();
        if(ese!=27)
        {
            while(1)
            {
                printf("请选择查看统计数据的方式：");
                scanf("%d",&op);//能够按比赛、按志愿者个体、按志愿者的年龄段等多个维度来统计志愿服务数据,?
                switch (op) {

                }


            }
        }
    }
    system("cls");
}

