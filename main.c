#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <mysql.h>
#define POS_X1 35
#define POS_X2 40
#define POS_X3 50
#define POS_X4 65
#define POS_Y 3
MYSQL_RES *res;
MYSQL_ROW row;
char sql[100];
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
    int v_id;//־Ը�߱��
    char* name;
    int gender;
    int age;
    char* number;//�绰��
    char* ID;//���֤��
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
Competition competition[20];
void WriteExcel();
void ReadExcel(char *filename);
int Menu(void);//������˵�
void SetPosition(int x,int y);
void VolunteerInfo(MYSQL *mysql);
void Register();
void CheckS();//
void Modify(MYSQL *mysql);
void CompetitionInfo();
void CheckC();
void Arrangement();
void Statistic();
void CompetitionClass();
void VolunteerClass();
void AgeClass();

char v_id[5];char* name;int age;char number[11];char ID[18];char* workplace;int LanguageAbility;int experience;int servicetime;int gender;Will will;//������Ը��ǰ�����Ǻ��ڣ��Ƿ���ӵ�����

int main() {
    MYSQL mysql;
    mysql_init(&mysql);
    mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
    if(NULL == mysql_real_connect(&mysql,"127.0.0.1","root","123456","mysql",3306,NULL,0))
    {
        printf("MySQL connect fail.\n");
        mysql_close(&mysql);
        return -1;
    }
    else
        printf("MySQL connect sucessed!\n");
    int ch;
    system("mode con cols=130 lines=60");
    system("color 0A");
    ch=Menu();
    while (ch)
    {
        switch (ch) {
            case 1:
                VolunteerInfo(&mysql);
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
        }
        ch=Menu();
    }
    mysql_close(&mysql);
    return 0;
}


int Menu()
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
    scanf("%d",&option);
    system("cls");
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
void Modify(MYSQL *mysql){
    printf("����ESC���Է�����һ����...\n");
    while(1)
    {
        printf("������־Ը�߱�ţ�");
        fflush(stdin);
        int check;
        char ch;
        int i=0;
        while(1)
        {
            ch = getch();                         /*�����ַ�������*/

            if(ch == 27) {                        /*����Esc��*/
                v_id[0] = '\0';                        /*�ַ����������*/
                system("cls");
                check=0; /*����ѭ��*/
                goto start;
            }
            else if(ch == '\r' || ch == '\n') { /*����Enter����*/
                v_id[i] = '\0';                        /*���ַ������������ַ�������־*/
                i = 0;
                break;                             /*��������ɹ���־*/
            }
            else {
                v_id[i++] = ch;                /*���򽫵õ��� ch �����ַ�������*/
            }
            putchar(ch);                          /*��Ļ����*/
        }
        check=1;
        start:
        if(!check)
            break;
        sprintf(sql,"select v_id from volunteer where v_id='%s';",v_id);
        if(mysql_query(mysql,sql)) {
            fprintf(stderr,"%s\n",mysql_error(mysql));
            return ;
        }
        else {
            res=mysql_use_result(mysql);
            if((row=mysql_fetch_row(res))==NULL)
            {
                printf("��ѧ����Ч��\n");
                continue;
            }
        }
        mysql_free_result(res);
        printf("\n");

        printf("(1)���� (2)�Ա� ��3������ (4)�绰���� ��5�����֤�� ��6��������λ ��7��������Ը ��8���Ƿ���ӵ��� (0)�˳�\n");
        int select=1;
        while(select!=0) {
            printf("������ѡ��");
            fflush(stdin);
            scanf("%d",&select);
            switch (select) {
                case 0:
                    continue;
                case 1:
                    printf("������ѧ����������");
                    scanf("%s",name);
                    sprintf(sql, " update volunteer set name='%s' where v_id='%s';", name, v_id);
                    break;
                case 2:
                    printf("������ѧ�����Ա�");
                    scanf("%d",gender);
                    sprintf(sql, " update volunteer set gender='%d' where v_id='%s';", gender, v_id);
                    break;
                case 3:
                    printf("������ѧ�������䣺");
                    scanf("%d",age);
                    sprintf(sql, " update volunteer set age='%d' where v_id='%s';", age, v_id);
                    break;
                case 5:
                    printf("������ѧ�������֤�ţ�");
                    scanf("%s",ID);
                    sprintf(sql, "update volunteer set id='%s' where v_id='%s';", ID, v_id);
                    break;
                case 4:
                    printf("������ѧ���ĵ绰���룺");
                    scanf("%s",number);
                    sprintf(sql, "update volunteer set number=%d where v_id='%s';", number, v_id);
                    break;
                case 6:
                    printf("������ѧ���Ĺ�����λ��");
                    scanf("%s",workplace);
                    sprintf(sql, " update volunteer set workplace='%s' where v_id='%s';", workplace, v_id);
                    break;
                case 7:
                    printf("������ѧ���Ĺ�����Ը��");
                    scanf("%d",will.Work);
                    sprintf(sql, " update volunteer set work='%d' where v_id='%s';",will.Work, v_id);
                    break;
                case 8:
                    printf("�Ƿ���ӵ�������");
                    scanf("%d",will.Adjustice);
                    sprintf(sql, " update volunteer set adjustice='%d' where v_id='%s';", will.Adjustice, v_id);
                    break;
                default:
                    break;
                }
            if (!mysql_query(mysql, sql)) {
                printf("ѧ����Ϣ�޸ĳɹ���\n");
            }
            else {
                printf("ѧ����Ϣ�޸�ʧ�ܣ�\n");
                fprintf(stderr, "%s\n", mysql_error(mysql));
                system("pause");
            }
        }
    }
    system("cls");
}
void Register()
{
    char op;
    printf("����ESC���Է�����һ����...\n");
    while(op!='0'){
        printf("��Ҫ���еĲ����� �Ǽ� ��[  ]\b\b\b");
        op=getch();
        putchar(op);                          /*��Ļ����*/
        if(op==27)
            break;
        printf("�µ�־Ը����Ϣ�ǼǱ� ��");
    }
    system("cls");
}
void VolunteerInfo(MYSQL *mysql)
{
    char op;
    printf("����ESC���Է�����һ����...\n");
    while(op!='0'){
        printf("��Ҫ���еĲ����� �Ǽ�1/�޸�2 ��[  ]\b\b\b");
        op=getch();
        putchar(op);                          /*��Ļ����*/
        printf("\n");
        if(op==27)
            break;
        switch (atoi(&op)) {
            case 1:
                Register(mysql);
                break;
            case 2:
                Modify(mysql);
                break;
        }
    }
    system("cls");
}
/*void CheckS()
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
}*/
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
void Arrangement(MYSQL *mysql)
{
    //���ݱ�����Ž��б�������

}
//�����ݿ��в�ѯ��Ϣ

void Statistic()
{
    char op;
    printf("����ESC���Է�����һ����...\n");
    while(op!='0'){
        printf("��ѡ��鿴ͳ�����ݵķ�ʽ ��[  ]\b\b\b");
        op=getch();
        putchar(op);                          /*��Ļ����*/
        printf("\n");
        if(op==27)
            break;
        switch (atoi(&op)) {
            case 1:
                CompetitionClass();
                break;
            case 2:
                VolunteerClass();
                break;
            case 3:
                AgeClass();
                break;
        }
    }
    system("cls");
}
void CompetitionClass()
{
    printf("���������Ա�����ʽ���־Ը�߷�����Ϣ");//ͨ�����ݿ�鿴������Ϣ��ͬʱ����־Ը�ߵı�������ҵ�־Ը�ߵ���Ϣ�����־Ը��������
    for(int i=0;i<20;i++)
    {
        Volunteer *p=volunteer;
        printf("�������ƣ�%s\n", competition[i].name);
        printf("����ʱ�䣺%s\n", competition[i].time);
        printf("�����ص㣺%s\n", competition[i].place);
        printf("�������ͣ�%s\n", competition[i].type);
        printf("�ó�������־Ը��Ϊ��\n");
        while(p->next!=NULL)
        {
            if(p->work.competition == competition[i].id)
            {
                printf("%d %s %s\n",p->v_id,p->name,p->work.position);
            }
            p=p->next;
        }
    }
}
void VolunteerClass(MYSQL *mysql)
{
    MYSQL_RES *res;
    MYSQL_ROW row;
    mysql_init(&mysql);
    char *sql="select from volunteer";
    mysql_real_query(mysql,sql,strlen(sql));
    res = mysql_store_result(mysql);
    row = mysql_fetch_row(res);
    printf("����������־Ը����ʽ���־Ը�߷�����Ϣ");//ͨ�����ݿ�鿴־Ը����Ϣ��ͬʱ����־Ը�ߵı�������ҵ�־Ը�ߵ���Ϣ�����־Ը��������
    sprintf(sql,"select v_id,name from volunteer,competition where volunteer.work.competition=competition.id");

    //select v_id,name from volunteer,competition where volunteer.work.competition=competition.id
    //��Ҫ����һ��competition������������ţ��������ݣ����֣�������ʱ�䣬�����ص㣬�������ͣ����ⳡ����������־Ը�ߵı�ţ�ͬʱ־Ը�߱���Ҫ����ʵ�ʹ�����λ��������
    //


    while(p->next!=NULL)
    {
        printf("%s ",p->v_id);
        printf("%s ",p->name);
        int i=0;
        while(competition[i].id!=p->work.competition)
        {
            i++;
        }
        printf("־Ը�߷�����%s %s",competition[i].name,competition[i].type);
        printf("ְ��Ϊ%s",p->work.position);
        p=p->next;
    }

}
void AgeClass()
{
    printf("����������־Ը��������ʽ���־Ը�߷�����Ϣ");
    Volunteer *p=volunteer;
    sort_Volunteer(volunteer,get_last_Volunteer(volunteer));
    while (p->next!=NULL)
    {
        printf("��һѧ����־Ը������Ϣ��\n");
        while(p->age == 19)
        {
            int i = 0;
            int high = 19;
            int mid = (i + high) / 2;
            while (i<=high) {
                if (competition[mid].id > p->work.competition) {
                    high = mid - 1;
                }
                else if (competition[mid].id < p->work.competition) {
                    i = mid + 1;
                }
                else break;
                mid = (i + high) / 2;
            }
            printf("%d %s ������ %s %s��%s",p->v_id,p->name,competition[mid].name,competition[mid].type,p->work.position);
            p=p->next;
        }
        printf("���ѧ����־Ը������Ϣ��\n");
        while(p->age == 20)
        {
            int i = 0;
            int high = 19;
            int mid = (i + high) / 2;
            while (i<=high) {
                if (competition[mid].id > p->work.competition) {
                    high = mid - 1;
                }
                else if (competition[mid].id < p->work.competition) {
                    i = mid + 1;
                }
                else break;
                mid = (i + high) / 2;
            }
            printf("%d %s ������ %s %s��%s",p->v_id,p->name,competition[mid].name,competition[mid].type,p->work.position);
            p=p->next;
        }
        printf("����ѧ����־Ը������Ϣ��\n");
        while(p->age == 21)
        {
            int i = 0;
            int high = 19;
            int mid = (i + high) / 2;
            while (i<=high) {
                if (competition[mid].id > p->work.competition) {
                    high = mid - 1;
                }
                else if (competition[mid].id < p->work.competition) {
                    i = mid + 1;
                }
                else break;
                mid = (i + high) / 2;
            }
            printf("%d %s ������ %s %s��%s",p->v_id,p->name,competition[mid].name,competition[mid].type,p->work.position);
            p=p->next;
        }
        printf("����ѧ����־Ը������Ϣ��\n");
        while(p->age == 22 || p->age==23)
        {
            int i = 0;
            int high = 19;
            int mid = (i + high) / 2;
            while (i<=high) {
                if (competition[mid].id > p->work.competition) {
                    high = mid - 1;
                }
                else if (competition[mid].id < p->work.competition) {
                    i = mid + 1;
                }
                else break;
                mid = (i + high) / 2;
            }
            printf("%d %s ������ %s %s��%s",p->v_id,p->name,competition[mid].name,competition[mid].type,p->work.position);
            p=p->next;
        }
    }
}
Volunteer* get_last_Volunteer(Volunteer* phead)

{
    Volunteer* ptr = phead;
    while(ptr->next)
    {
        ptr = ptr->next;
    }
    return ptr;
}
void sort_Volunteer(Volunteer * phead, Volunteer* pend)

{

    if(phead == NULL || pend == NULL) return;
    if(phead == pend) return;
    Volunteer* pslow = phead;
    Volunteer* pfast = phead->next;
    Volunteer* ptemp = phead;
    while(pfast && pfast != pend->next)
    {

        if(pfast->age <= phead->age) //phead��Ϊ֧��
        {
            ptemp = pslow;
            pslow = pslow->next;
            pslow->age=pfast->age+pslow->age;
            pfast->age=pslow->age-pfast->age;
            pslow->age=pslow->age-pfast->age;
        }
        pfast = pfast->next;
    }
    pslow->age=phead->age+pslow->age;
    phead->age=pslow->age-phead->age;
    pslow->age=pslow->age-phead->age;
    sort_Volunteer(phead, ptemp);//ptempΪ���������ַָ���ǰһ���ڵ�
    sort_Volunteer(pslow->next, pend);
}