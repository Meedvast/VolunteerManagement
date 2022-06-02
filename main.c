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
    int Work;//ǰ�����Ǻ���
    int Adjustice;//�Ƿ���ӵ���
}Will;
typedef struct Skills
{
    int Interpersonal;//���������÷�,������1-5��Ϊ5��
    int Exe;//�ж������÷�,������1-5��Ϊ5��
    int Capacity;//���������÷�,������1-5��Ϊ5��
}Skills;
typedef struct Volunteer{
    char* name;
    int gender;
    int age;
    char number[11];//�绰��
    char ID[18];//���֤��
    char* workplace;
    int LanguageAbility;//�������������������̶�,������1-5��Ϊ5��,���Ǽٶ�����Ӣ��Ϊ��
    int experience;//־Ը��������0��ʾ��δ��1��ʾ��1-3�η�������2��ʾ3������
    int servicetime;//�ṩ�����ʱ�䣬0��ʾ���ϣ�1��ʾ���磬2��ʾ���ϡ�
    Skills skills;//�����س�
    Will will;//������Ը��ǰ�����Ǻ��ڣ��Ƿ���ӵ�����
    struct Volunteer* next;
}Volunteer;
typedef struct Competition{
    int id;
    char* name;
    char* time;
    char* place;
    char* type;
}Competition;
Volunteer *volunteer;
Competition competition[20];
void WriteExcel();
void ReadExcel(char *filename);
int Menu(void);//������˵�
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
    printf("\t\t    *               �������˻�־Ը�߹���ϵͳ               *\n");
    SetPosition(POS_X3,++posy);
    printf("\t\t    ********************************************************\n");
    SetPosition(POS_X3,++posy);
    printf("\t\t   ������������������������������������������������������������������������������������������������������������������\n");
    SetPosition(POS_X3,++posy);
    printf("\t\t   ��                                                       ��\n");
    SetPosition(POS_X3,++posy);
    printf("\t\t   ��                   1. �Ǽ�־Ը����Ϣ                   ��\n");
    SetPosition(POS_X3,++posy);
    printf("\t\t   ��                                                       ��\n");
    SetPosition(POS_X3,++posy);
    printf("\t\t   ��                                                       ��\n");
    SetPosition(POS_X3,++posy);
    printf("\t\t   ��                                                       ��\n");
    SetPosition(POS_X3,++posy);
    printf("\t\t   ��                    2. ���������Ϣ                    ��\n");
    SetPosition(POS_X3,++posy);
    printf("\t\t   ��                                                       ��\n");
    SetPosition(POS_X3,++posy);
    printf("\t\t   ��                                                       ��\n");
    SetPosition(POS_X3,++posy);
    printf("\t\t   ��                                                       ��\n");
    SetPosition(POS_X3,++posy);
    printf("\t\t   ��                    3. ־Ը����ͳ��                    ��\n");
    SetPosition(POS_X3,++posy);
    printf("\t\t   ��                                                       ��\n");
    SetPosition(POS_X3,++posy);
    printf("\t\t   ��                                                       ��\n");
    SetPosition(POS_X3,++posy);
    printf("\t\t   ������������������������������������������������������������������������������������������������������������������\n");
    SetPosition(POS_X3,++posy);

    printf("\t\t   ��ѡ������Ҫ���еĲ���[0~3]:[  ]\b\b\b");
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
    fp=fopen(filename,"r");     // fpָ��ָ���ļ�ͷ��
    while (!feof(fp))
    {
        Volunteer *p= (Volunteer *)malloc(sizeof(Volunteer));
        fscanf(fp,"%f",p->name);
        fseek(fp, 1L, SEEK_CUR);   /*fpָ��ӵ�ǰλ������ƶ�*/
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
}//������һ����ȡ���������Ϣ�ĺ���
void VolunteerInfo()
{
    int op;
    char ese;
    char* filename;
    printf("����ESE���Է�����һ����...\n");
    if(_kbhit())
    {
        ese=getch();
        if(ese!=27)
        {
            printf("������־Ը�������Ϣ���ļ�����");
            scanf("%s",filename);
            ReadExcel(filename);//��ȡ�ļ��ĺ���
            printf("��Ҫ���еĲ����� �Ǽ�1/�޸�2 ��[  ]\b\b\b");
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
    printf("����ESE���Է�����һ����...\n");
    if(_kbhit())
    {
        ese=getch();
        if(ese!=27)
        {
            printf("�µ�־Ը����Ϣ�ǼǱ� ��");
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
    printf("����ESE���Է�����һ����...\n");
    if(_kbhit())
    {
        ese=getch();
        if(ese!=27)
        {
            while(1)
            {
                printf("��������Ҫ�޸���Ϣ��־Ը�ߵ� ����/�ֻ���/���֤��(0�˳�����");
                scanf("%s",check);
                if(check=='0')
                    break;
                //���Һ���,���ض�Ӧ����λ��
                while(op!=0)
                {
                    printf("��������Ҫ�޸ĵ����ݱ�����޸ĺ��ֵ(0�˳�����");
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
void CheckS()
{
    int op;
    char ese;
    printf("����ESE���Է�����һ����...\n");
    char* Get;
    if(_kbhit())
    {
        ese=getch();
        if(ese!=27)
        {
            while(op!=0)
            {
                printf("��Ҫ�鿴��Ϣ��־Ը�ߣ���������1/���֤����2/�绰����3����[  ]\b\b\b");
                scanf("%d",op);
                Volunteer *p=volunteer;
                switch (op) {
                    case 1:
                        printf("������Ҫ��ѯ��־Ը�ߵ�������");
                        scanf("%s",Get);

                        while(p->next!=NULL)
                        {
                            if(p->name==Get)
                            {
                                printf("��ѯ����־Ը�ߵ���ϢΪ��%s\t%d\t%d\t%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t\n",p->name,p->gender,p->age,p->number,p->ID,p->workplace,p->LanguageAbility,p->experience,p->servicetime,p->skills.Interpersonal,p->skills.Exe,p->skills.Capacity,p->will.Work,p->will.Adjustice) ;
                                break;
                            }
                            p=p->next;
                        }
                        break;
                    case 2:
                        printf("������Ҫ��ѯ��־Ը�ߵ����֤���룺");
                        scanf("%s",Get);
                        while(p->next!=NULL)
                        {
                            if(p->ID==Get)
                            {
                                printf("��ѯ����־Ը�ߵ���ϢΪ��%s\t%d\t%d\t%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t\n",p->name,p->gender,p->age,p->number,p->ID,p->workplace,p->LanguageAbility,p->experience,p->servicetime,p->skills.Interpersonal,p->skills.Exe,p->skills.Capacity,p->will.Work,p->will.Adjustice) ;
                                break;
                            }
                            p=p->next;
                        }
                        break;
                    case 3:
                        printf("������Ҫ��ѯ��־Ը�ߵĵ绰���룺");
                        scanf("%s",Get);
                        while(p->next!=NULL)
                        {
                            if(p->number==Get)
                            {
                                printf("��ѯ����־Ը�ߵ���ϢΪ��%s\t%d\t%d\t%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t\n",p->name,p->gender,p->age,p->number,p->ID,p->workplace,p->LanguageAbility,p->experience,p->servicetime,p->skills.Interpersonal,p->skills.Exe,p->skills.Capacity,p->will.Work,p->will.Adjustice) ;
                                break;
                            }
                            p=p->next;
                        }
                        break;
                }
            }
        }
    }
    system("cls");
}
void CompetitionInfo()
{
    //��ȡ�ļ��ĺ���
    int op;
    char ese;
    printf("����ESE���Է�����һ����...\n");
    if(_kbhit())
    {
        ese=getch();
        if(ese!=27)
        {
            printf("�Ƿ���Ҫ�鿴������Ϣ ��Ҫ1/����Ҫ0 ��[  ]\b\b\b");
            scanf("%d",op);
            switch (op) {
                case 1:
                    CheckC();
                    break;
            }
            //ϵͳ�Զ�����ƥ��
        }
    }
    system("cls");
}
void CheckC()
{
    //�鿴������Ϣ
    int op;
    char ese;
    printf("����ESE���Է�����һ����...\n");
    if(_kbhit()) {
        ese = getch();
        if (ese != 27) {
            while (op!=0){
                printf("��������Ҫ�鿴�ı�����ţ�");
                scanf("%d", &op);
                printf("�������ƣ�%s\n", competition[op].name);
                printf("����ʱ�䣺%s\n", competition[op].time);
                printf("�����ص㣺%s\n", competition[op].place);
                printf("�������ͣ�%s\n", competition[op].type);
            }
        }
    }
    system("cls");
}
void Arrangement()
{

}
void Statistic()
{
    int op;
    char ese;
    printf("����ESE���Է�����һ����...\n");
    if(_kbhit())
    {
        ese=getch();
        if(ese!=27)
        {
            while(1)
            {
                printf("��ѡ��鿴ͳ�����ݵķ�ʽ��");
                scanf("%d",&op);//�ܹ�����������־Ը�߸��塢��־Ը�ߵ�����εȶ��ά����ͳ��־Ը��������,?
                switch (op) {

                }


            }
        }
    }
    system("cls");
}

