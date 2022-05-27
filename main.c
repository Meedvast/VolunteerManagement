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
    while()
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
    printf("按下ESE键以返回上一界面...");
}
void Modify()