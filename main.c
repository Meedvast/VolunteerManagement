#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <conio.h>
#include <mysql.h>
#define POS_X3 50

MYSQL_RES *res;
MYSQL_RES *res2;
MYSQL_ROW row;
MYSQL_ROW row2;
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
    char v_id[5];//־Ը�߱��
    char* name;
    int gender;
    int age;
    char* number;//�绰��
    char* ID;//���֤��
    char* workplace;
    int LanguageAbility;//�������������������̶�,������1-5��Ϊ5��,���Ǽٶ�����Ӣ��Ϊ��
    int experience;//־Ը������,0��ʾ��δ,1��ʾ��1-3�η�����,2��ʾ3������
    int servicetime;//�ṩ�����ʱ��,0��ʾ����,1��ʾ����,2��ʾ���ϡ�
    Skills skills;//�����س�
    Will will;//������Ը,ǰ�����Ǻ���,�Ƿ���ӵ�����
}Volunteer;
typedef struct Competition{
    char id[5];
    char name[100];
    char time[100];
    int time_num;
    char type[100];
}Competition;
Volunteer volunteer;

int Menu(void);//������˵�
void SetPosition(int x,int y);
void VolunteerInfo(MYSQL *mysql);
void Register(MYSQL* mysql);
void Modify(MYSQL *mysql);
void CompetitionInfo(MYSQL *mysql);
void CheckC(MYSQL *mysql);
void Arrange(MYSQL *mysql);
void Statistic(MYSQL* mysql);
void CompetitionClass(MYSQL* mysql);
void VolunteerClass(MYSQL* mysql);
void AgeClass(MYSQL* mysql);


int main() {
    MYSQL mysql;
    mysql_init(&mysql);
    mysql_options(&mysql, MYSQL_SET_CHARSET_NAME, "gbk");
    if(NULL == mysql_real_connect(&mysql,"127.0.0.1","root","123456","mysql",3306,NULL,CLIENT_MULTI_STATEMENTS))
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
                CompetitionInfo(&mysql);
                break;
            case 3:
                Statistic(&mysql);
                break;
            default:
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
void Modify(MYSQL *mysql){//�޸�־Ը����Ϣ
    char ch;
    int i=0;
    system("cls");
    printf("����ESC���Է�����һ����...\n");
    while(1)
    {
        printf("������־Ը�߱�ţ�");

        while(1)
        {
            fflush(stdin);
            ch = getch();                         /*�����ַ�������*/


            if(ch == 27) {                        /*����Esc��*/
                volunteer.v_id[0] = '\0';                        /*�ַ����������*/
                system("cls");          /*����ѭ��*/
                return;
            }
            else if(ch == '\r' || ch == '\n') { /*����Enter��,*/
                volunteer.v_id[i] = '\0';                        /*���ַ������������ַ�������־*/
                i = 0;
                break;                             /*��������ɹ���־*/
            }
            else {
                volunteer.v_id[i++] = ch;                /*���򽫵õ��� ch �����ַ�������*/
            }
            putchar(ch);          /*��Ļ����*/
        }
        sprintf(sql,"select v_id from volunteer where v_id='%s';",volunteer.v_id);
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
                    scanf("%s",volunteer.name);
                    sprintf(sql, " update volunteer set name='%s' where v_id='%s';",volunteer.name, volunteer.v_id);
                    break;
                case 2:
                    printf("������ѧ�����Ա�");
                    scanf("%d",&volunteer.gender);
                    sprintf(sql, " update volunteer set gender='%d' where v_id='%s';", volunteer.gender, volunteer.v_id);
                    break;
                case 3:
                    printf("������ѧ�������䣺");
                    scanf("%d",&volunteer.age);
                    sprintf(sql, " update volunteer set age='%d' where v_id='%s';", volunteer.age, volunteer.v_id);
                    break;
                case 5:
                    printf("������ѧ�������֤�ţ�");
                    scanf("%s",volunteer.ID);
                    sprintf(sql, "update volunteer set id='%s' where v_id='%s';", volunteer.ID, volunteer.v_id);
                    break;
                case 4:
                    printf("������ѧ���ĵ绰���룺");
                    scanf("%s",volunteer.number);
                    sprintf(sql, "update volunteer set phoneNumber='%d' where v_id='%s';", volunteer.number,volunteer.v_id);
                    break;
                case 6:
                    printf("������ѧ���Ĺ�����λ��");
                    scanf("%s",volunteer.workplace);
                    sprintf(sql, " update volunteer set workplace='%s' where v_id='%s';", volunteer.workplace,volunteer.v_id);
                    break;
                case 7:
                    printf("������ѧ���Ĺ�����Ը��");
                    scanf("%d",&volunteer.will.Work);
                    sprintf(sql, " update volunteer set work='%d' where v_id='%s';",volunteer.will.Work, volunteer.v_id);
                    break;
                case 8:
                    printf("�Ƿ���ӵ�������");
                    scanf("%d",&volunteer.will.Adjustice);
                    sprintf(sql, " update volunteer set adjustice='%d' where v_id='%s';",volunteer.will.Adjustice, volunteer.v_id);
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
void Insert(MYSQL* mysql)//�����в�������,����Ϊ������д��
{
    system("cls");
    char ch;
    int rc,i;
    int check;
    char op;
    printf("����ESC���Է�����һ����...\n");

    while(1)
    {
        printf("������Ҫ��ӵ�־Ը��ѧ�ţ�");
        while(1)
        {
            fflush(stdin);
            ch = getch();                         /*�����ַ�������*/

            if(ch == 27) {                        /*����Esc��*/
                volunteer.v_id[0] = '\0';                        /*�ַ����������*/
                system("cls");
                check=0; /*����ѭ��*/
                goto start;
            }
            else if(ch == '\r' || ch == '\n') { /*����Enter��,*/
                volunteer.v_id[i] = '\0';                        /*���ַ������������ַ�������־*/
                i = 0;
                break;                             /*��������ɹ���־*/
            }
            else {
                volunteer.v_id[i++] = ch;                /*���򽫵õ��� ch �����ַ�������*/
            }
            putchar(ch);                          /*��Ļ����*/
        }
        check=1;
        start:
        if(!check)
            break;
        //ʡ�����ºö�����,���ڣ�
        printf("\n��������Ҫ��ӵ�־Ը��������");
        scanf("%s",volunteer.name);
        fflush(stdin);
        printf("\n��������Ҫ��ӵ�־Ը���Ա�");
        scanf("%d",&volunteer.gender);
        printf("\n��������Ҫ��ӵ�־Ը�����䣺");
        scanf("%d",&volunteer.age);
        printf("\n��������Ҫ��ӵ�־Ը�ߵ绰���룺");
        scanf("%s",volunteer.number);
        fflush(stdin);
        printf("\n��������Ҫ��ӵ�־Ը�����֤�ţ�");
        scanf("%s",volunteer.ID);
        fflush(stdin);
        printf("\n��������Ҫ��ӵ�־Ը�߹�����λ��");
        scanf("%s",volunteer.workplace);
        fflush(stdin);
        printf("\n��������Ҫ��ӵ�־Ը��������������1����5�ӵ͵��ߣ���");
        scanf("%d",&volunteer.LanguageAbility);
        printf("\n��������Ҫ��ӵ�־Ը�ߵ�־Ը������");
        scanf("%d",&volunteer.experience);
        printf("\n��������Ҫ��ӵ�־Ը�ߵķ���ʱ�䣺");
        scanf("%d",&volunteer.servicetime);
        printf("\n��������Ҫ��ӵ�־Ը�ߵĽ���������");
        scanf("%d",&volunteer.skills.Interpersonal);
        printf("\n��������Ҫ��ӵ�־Ը�ߵ�ִ������");
        scanf("%d",&volunteer.skills.Exe);
        printf("\n��������Ҫ��ӵ�־Ը�߹���������");
        scanf("%d",&volunteer.skills.Capacity);
        printf("\n��������Ҫ��ӵ�־Ը�ߵĹ�����Ը��");
        scanf("%d",&volunteer.will.Work);
        printf("\n��������Ҫ��ӵ�־Ը���Ƿ���ܵ�����");
        scanf("%d",&volunteer.will.Adjustice);

        sprintf(sql, "insert into volunteer (v_id,name,gender,age,phoneNumber,id,workplace,LanguageAbility,experience,serviceTime,interpersonal,exe,capacity,work,adjustice,ability) values ('%s', '%s', '%d', '%d','%s','%s','%s','%d','%d','%d','%d','%d','%d','%d','%d','%lf')", volunteer.v_id, volunteer.name, volunteer.gender, volunteer.age,volunteer.number,volunteer.ID,volunteer.workplace,volunteer.LanguageAbility,volunteer.experience,volunteer.servicetime,volunteer.skills.Interpersonal,volunteer.skills.Exe,volunteer.skills.Capacity,volunteer.will.Work,volunteer.will.Adjustice,volunteer.skills.Interpersonal*0.25+volunteer.skills.Exe*0.5+volunteer.skills.Capacity*0.25);
        rc = mysql_real_query(mysql, sql, strlen(sql));
        if (0 != rc) {
            printf("mysql_real_query(): %s\n", mysql_error(mysql));
            return ;
        }
        printf("����ɹ���\n");
    }
    mysql_close(mysql);
}
void Delete(MYSQL* mysql)
{
    system("cls");
    char ch;
    int rc,i;
    int check;
    printf("����ESC���Է�����һ����...\n");
    while(1)
    {
        printf("������Ҫɾ����ѧ��ѧ�ţ�");
        while(1)
        {
            ch = getch();                         /*�����ַ�������*/

            if(ch == 27) {                        /*����Esc��*/
                volunteer.v_id[0] = '\0';                        /*�ַ����������*/
                system("cls");
                check=0; /*����ѭ��*/
                goto start;
            }
            else if(ch == '\r' || ch == '\n') { /*����Enter��,*/
                volunteer.v_id[i] = '\0';                        /*���ַ������������ַ�������־*/
                i = 0;
                break;                             /*��������ɹ���־*/
            }
            else {
                volunteer.v_id[i++] = ch;                /*���򽫵õ��� ch �����ַ�������*/
            }
            putchar(ch);                          /*��Ļ����*/
        }
        check=1;
        start:
        if(!check)
            break;
        sprintf(sql, "select * from volunteer where v_id='%s';", volunteer.v_id);
        rc = mysql_real_query(mysql, sql, strlen(sql));
        if (0 != rc) {
            printf("mysql_real_query(): %s\n", mysql_error(mysql));
            return ;
        }
        res = mysql_store_result(mysql);
        if (NULL == res) {
            printf("mysql_store_result(): %s\n", mysql_error(mysql));
            return ;
        }
        if (mysql_num_rows(res) == 0) {
            printf("\n��ѧ����Ч��\n");
            continue;
        }
        printf("\nȷ��Ҫɾ����ѧ���𣿣�1��ȷ����0��ȡ��\n");
        scanf("%d",&check);
        if(check==1)
        {
            sprintf(sql, "delete from volunteer where v_id='%s';", volunteer.v_id);
            rc = mysql_real_query(mysql, sql, strlen(sql));
            if (0 != rc) {
                printf("mysql_real_query(): %s\n", mysql_error(mysql));
                return ;
            }
            printf("ɾ���ɹ���\n");
        }
        else
        {
            printf("ȡ��ɾ����\n");
        }
    }
    mysql_close(mysql);
    return ;

}
void Register(MYSQL* mysql)//�Ǽ��µ�־Ը����Ϣ
{
    system("cls");
    char op;
    printf("����ESC���Է�����һ����...\n");
    while(op!='0'){
        printf("��Ҫ���еĲ����� �Ǽ�1/ɾ����¼2 ��[  ]\b\b\b");
        fflush(stdin);
        op = getch();                         /*�����ַ�������*/

        if(op == 27) {                        /*����Esc��*/
            //volunteer.v_id[0] = '\0';                        /*�ַ����������*/
            system("cls");          /*����ѭ��*/
            return;
        }
        putchar(op);          /*��Ļ����*/
        switch(atoi(&op)){
            case 1:
                Insert(mysql);
                break;
            case 2:
                Delete(mysql);
                break;
            default:
                break;
        }
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
}//־Ը����Ϣģ��
void CompetitionInfo(MYSQL* mysql)//������Ϣģ��
{
    char op,ch;
    printf("����ESC���Է�����һ����...\n");
    while(op!='0'){
        printf("����Ҫ�鿴������Ϣ�� (1)�� (2)���ű��� (0)�˳�:[  ]\b\b\b");
        op=getch();
        putchar(op);                          /*��Ļ����*/
        printf("\n");
        if(op==27)
            break;
        switch (atoi(&op)) {
            case 1:
                CheckC(mysql);
                break;
            case 0:
                break;
            case 2:
                Arrange(mysql);
                printf("������Զ����䣡�Ƿ���Ҫ�����ֶ��޸ģ�(1)�� ��0����[  ]\b\b\b");
                ch=getch();
                putchar(ch);                          /*��Ļ����*/
                printf("\n");
                if(ch==27)
                    break;
                switch (atoi(&ch)) {
                    case 1:
                        Modify(mysql);
                        break;
                    case 0:
                        Statistic(mysql);
                        break;
                }
        }

    }
    system("cls");
}
void CheckC(MYSQL* mysql)//��ѯ������Ϣ
{
    //�鿴������Ϣ
    char ch;
    int rc,fields;
    int i=0;
    Competition Check;
    while (1)
    {
        printf("��������Ҫ��ѯ�ı�����ţ�");//ͨ�����ݿ�鿴������Ϣ,ͬʱ����־Ը�ߵı�������ҵ�־Ը�ߵ���Ϣ�����־Ը��������
        memset(Check.id,'\0',sizeof(Check.id));
        fflush(stdin);
        i=0;
        while(1)
        {
            fflush(stdin);
            ch = getch();                         /*�����ַ�������*/

            if(ch == 27) {                        /*����Esc��*/
                Check.id[0] = '\0';                        /*�ַ����������*/
                system("cls");          /*����ѭ��*/
                return;
            }
            else if(ch == '\r' || ch == '\n') { /*����Enter��,*/
                Check.id[i] = '\0';                        /*���ַ������������ַ�������־*/
                i = 0;
                break;                             /*��������ɹ���־*/
            }
            else {
                Check.id[i++] = ch;                /*���򽫵õ��� ch �����ַ�������*/
            }
            putchar(ch);          /*��Ļ����*/
        }

        sprintf(sql, "select name,time,place from competition where id = '%s'", Check.id);
        rc = mysql_real_query(mysql, sql, strlen(sql));
        if (0 != rc) {
            printf("mysql_real_query(): %s\n", mysql_error(mysql));
            return ;
        }
        res = mysql_store_result(mysql);
        if (NULL == res) {
            printf("mysql_restore_result(): %s\n", mysql_error(mysql));
            return;
        }
        fields = mysql_num_fields(res);
        printf("\n");
        while ((row = mysql_fetch_row(res))) {
            for (i = 0; i < fields; i++) {
                    printf("%s\t", row[i]);
            }
            printf("\n");
        }
        mysql_free_result(res);
    }
}
void Arrange(MYSQL *mysql)//�Զ�����־Ը�������ƥ��,Ҫ��SELECT MAX(student_name) FROM tb_students_score;�ֳ�������Ը������Ͳ�Ը���,Ȼ��ֱ��������,�Բ�Ը������İ�����ֵ�ɸߵ��ͷ���,��Ը������İ�����ֵ�ɵ͵��߷���,һ������2��ǰ��������
{
    Competition competition[25];
    for (int i = 0; i < 25; ++i) {
        memset(competition[i].id,'\0',sizeof(competition[i].id));
        memset(competition[i].name,'\0',sizeof(competition[i].name));
        memset(competition[i].type,'\0',sizeof(competition[i].type));
        memset(competition[i].time,'\0',sizeof(competition[i].time));
    }
    int rc;
    int CVolunteer0[25]={0},CVolunteer1[25]={0},IsArranged[102]={0};
    int i=0,j=0,limit[26]={0};

    sprintf(sql,"select * from competition order by type desc,id;");//��ȡ������Ϣ,����������Ҫ��������
    rc = mysql_real_query(mysql, sql, strlen(sql));
    if (0 != rc) {
        printf("mysql_real_query(): %s\n", mysql_error(mysql));
        return ;
    }
    res = mysql_store_result(mysql);
    if (NULL == res) {
        printf("mysql_restore_result(): %s\n", mysql_error(mysql));
        return;
    }
    while ((row = mysql_fetch_row(res))) {
        i=0;
        strcpy(competition[j].id,row[i]);
        //printf("%s\t",competition[j].id);
        i++;
        strcpy(competition[j].name,row[i]);
        //printf("%s\t",competition[j].name);
        i++;
        strcpy(competition[j].time,row[i]);
        //printf("%s\t",competition[j].time);
        if(strstr(competition[j].time,"08:00:00")!=NULL)
            competition[j].time_num=0;
        else if(strstr(competition[j].time,"13:00:00")!=NULL)
            competition[j].time_num=1;
        else if(strstr(competition[j].time,"18:00:00")!=NULL)
            competition[j].time_num=2;
        i+=2;
        strcpy(competition[j].type,row[i]);
        //printf("%s\t",competition[j].type);

        CVolunteer0[j]=2;
        CVolunteer1[j]=2;
        limit[j]=2;
        j++;
    }//��ȡ���ݵ���������
    i=0;
    j=0;
    mysql_free_result(res);

    sprintf(sql,"select v_id,LanguageAbility,experience,serviceTime,work,adjustice,ability from volunteer where adjustice=0 order by ability desc,v_id;");//��ȡ־Ը����Ϣ
    rc = mysql_real_query(mysql, sql, strlen(sql));
    if (0 != rc) {
        printf("mysql_real_query(): %s\n", mysql_error(mysql));
        return ;
    }
    res = mysql_store_result(mysql);
    if (NULL == res) {
        printf("mysql_restore_result(): %s\n", mysql_error(mysql));
        return;
    }
    while ((row = mysql_fetch_row(res)))
    {
        for (j = 0; j < 25; ++j) {
            if (strtol(row[3],NULL,10)==competition[j].time_num && strtol(row[1],NULL,10)>=strtol(competition[j].type,NULL,10) && limit[j]>0)
            {
                if(strtol(row[4],NULL,10)==0 && CVolunteer0[j]>0 || strtol(row[4],NULL,10) == 1 && CVolunteer1[j] > 0) {

                    sprintf(sql,"update volunteer set c_id='%s',position='%s' where v_id='%s'",competition[j].id,row[4],row[0]);
                    mysql_query(mysql,sql);
                    switch (strtol(row[4],NULL,10)) {
                        case 0:
                            CVolunteer0[j]--;
                            break;
                        case 1:
                            CVolunteer1[j]--;
                            break;
                        default:
                            break;
                    }
                    IsArranged[strtol(row[0],NULL,10)-10000]=1;
                    limit[j]--;
                    break;
                }
            }
        }
    }//��һ�η���,���䲻���ܵ�����־Ը��,����־Ը����Ը
    mysql_free_result(res);

    sprintf(sql,"select v_id,LanguageAbility,experience,serviceTime,work,adjustice,ability from volunteer where adjustice=1 order by ability,v_id;");//����
    rc = mysql_real_query(mysql, sql, strlen(sql));
    if (0 != rc) {
        printf("mysql_real_query(): %s\n", mysql_error(mysql));
        return ;
    }
    res = mysql_store_result(mysql);
    if (NULL == res) {
        printf("mysql_restore_result(): %s\n", mysql_error(mysql));
        return;
    }
    while ((row = mysql_fetch_row(res)))
    {
        for (j = 0; j < 25; ++j) {
            if (atoi(row[3])==competition[j].time_num && row[1]>=competition[j].type && IsArranged[atoi(row[0])-10000]==0)
            {
                if(atoi(row[4])==0 &&CVolunteer0[j]!=0 || atoi(row[4])==1 &&CVolunteer1[j]!=0) {
                    sprintf(sql, " update volunteer set c_id='%s',position='%s' where v_id='%s';", competition[j].id,row[4],row[0]);
                    mysql_query(mysql,sql);
                    switch (atoi(row[4])) {
                        case 0:
                            CVolunteer0[j]--;
                            break;
                        case 1:
                            CVolunteer1[j]--;
                            break;
                        default:
                            break;
                    }
                    IsArranged[atoi(row[0])-10000]=1;
                    break;
                }
            }
        }
    }//�ڶ��η���,���䲿�ֽ��ܵ�����־Ը��,���ɰ���־Ը����Ը,�Ҳ�������
    mysql_free_result(res);

    sprintf(sql,"select v_id,LanguageAbility,experience,serviceTime,work,adjustice,ability from volunteer where adjustice=0 order by ability,v_id;");//����
    rc = mysql_real_query(mysql, sql, strlen(sql));
    if (0 != rc) {
        printf("mysql_real_query(): %s\n", mysql_error(mysql));
        return ;
    }
    res = mysql_store_result(mysql);
    if (NULL == res) {
        printf("mysql_restore_result(): %s\n", mysql_error(mysql));
        return;
    }
    while ((row = mysql_fetch_row(res)))
    {
        for (j = 0; j < 25; ++j) {
            if (atoi(row[3])==competition[j].time_num && row[1]>=competition[j].type && IsArranged[atoi(row[0])-10000]==0)
            {
                if(CVolunteer0[j]!=0)
                {
                    sprintf(sql, " update volunteer set c_id='%s',position=0 where v_id='%s';", competition[j].id,row[0]);
                    mysql_query(mysql,sql);
                    switch (atoi(row[4])) {
                        case 0:
                            CVolunteer0[j]--;
                            break;
                        case 1:
                            CVolunteer1[j]--;
                            break;
                        default:
                            break;
                    }
                    IsArranged[atoi(row[0])-10000]=1;
                    break;
                }
                else if(CVolunteer1[j]!=0)
                {
                    sprintf(sql, " update volunteer set c_id='%s',position=1 where v_id='%s';", competition[j].id,row[0]);
                    mysql_query(mysql,sql);
                    switch (atoi(row[4])) {
                        case 0:
                            CVolunteer0[j]--;
                            break;
                        case 1:
                            CVolunteer1[j]--;
                            break;
                        default:
                            break;
                    }
                    IsArranged[atoi(row[0])-10000]=1;
                    break;
                }
            }
        }
    }//�����η���,����ʣ�಻���ܵ�����־Ը��,Ҫ��ǿ�Ʒ���

    sprintf(sql,"select v_id,LanguageAbility,experience,serviceTime,work,adjustice,ability from volunteer where adjustice=1 order by ability desc,v_id;");//����
    rc = mysql_real_query(mysql, sql, strlen(sql));
    if (0 != rc) {
        printf("mysql_real_query(): %s\n", mysql_error(mysql));
        return ;
    }
    res = mysql_store_result(mysql);
    if (NULL == res) {
        printf("mysql_restore_result(): %s\n", mysql_error(mysql));
        return;
    }
    while ((row = mysql_fetch_row(res)))
    {
        for (j = 0; j < 25; ++j) {
            if (atoi(row[3])==competition[j].time_num && row[1]>=competition[j].type && IsArranged[atoi(row[0])-10000]==0)
            {
                if(CVolunteer1[j]!=0)
                {
                    sprintf(sql, " update volunteer set c_id='%s',position=0 where v_id='%u';", competition[j].id,row[0]);
                    mysql_query(mysql, sql);
                    switch (atoi(row[4])) {
                        case 0:
                            CVolunteer0[j]--;
                            break;
                        case 1:
                            CVolunteer1[j]--;
                            break;
                        default:
                            break;
                    }
                    IsArranged[atoi(row[0])-10000]=1;
                    break;
                }
                else if(CVolunteer0[j]!=0)
                {
                    sprintf(sql, " update volunteer set c_id='%s',position=1 where v_id='%u';", competition[j].id,row[0]);
                    mysql_query(mysql, sql);
                    switch (atoi(row[4])) {
                        case 0:
                            CVolunteer0[j]--;
                            break;
                        case 1:
                            CVolunteer1[j]--;
                            break;
                        default:
                            break;
                    }
                    IsArranged[atoi(row[0])-10000]=1;
                    break;
                }
            }
        }
    }//���Ĵη���,����ʣ����ܵ�����־Ը��,Ҫ��ǿ�Ʒ���
    mysql_free_result(res);

    sprintf(sql,"select v_id,LanguageAbility,experience,serviceTime,work,adjustice,ability from volunteer where adjustice=1 order by ability desc,v_id;");//����
    rc = mysql_real_query(mysql, sql, strlen(sql));
    if (0 != rc) {
        printf("mysql_real_query(): %s\n", mysql_error(mysql));
        return ;
    }
    res = mysql_store_result(mysql);
    if (NULL == res) {
        printf("mysql_restore_result(): %s\n", mysql_error(mysql));
        return;
    }
    i=0;
    while(i<101)//���δ���乤����־Ը��,����Ϊ��������־Ը��
    {
        if(IsArranged[i]==0)
        {
            sprintf(sql, " update volunteer set c_id='0',position='-1' where v_id='%u';", i+10000);
            mysql_query(mysql, sql);
        }
        i++;
    }
    mysql_free_result(res);

    for (int k = 0; k < 25; ++k) {
        int MaxExperience=0;
        double MaxAbility=0;
        char* v_id;
        sprintf(sql, "select v_id,ability,experience from volunteer where c_id='%d';", atoi(competition[k].id));
        rc = mysql_real_query(mysql, sql, strlen(sql));
        if (0 != rc) {
            printf("mysql_real_query(): %s\n", mysql_error(mysql));
            return ;
        }
        res = mysql_store_result(mysql);
        if (NULL == res) {
            printf("mysql_restore_result(): %s\n", mysql_error(mysql));
            return;
        }

        while ((row = mysql_fetch_row(res)))
        {
            if(atoi(row[2])>MaxExperience)
            {
                MaxAbility=atof(row[1]);
                MaxExperience=atoi(row[2]);
                v_id=row[0];
            }
            else if (atoi(row[2])==MaxExperience && atof(row[1])>MaxAbility)
            {
                MaxAbility=atof(row[1]);
                v_id=row[0];
            }
            else if (atoi(row[2])==MaxExperience && atof(row[1])==MaxAbility && atoi(row[0])< atoi(v_id))
            {
                v_id=row[0];
            }
        }
        sprintf(sql, " update volunteer set position=10 where v_id='%u';", atoi(v_id));
        mysql_query(mysql, sql);
    }//ѡȡС�鳤
    mysql_free_result(res);

    for (int k = 0; k < 25; ++k) {
        char v_id[26];
        memset(v_id,'\0',sizeof(v_id));
        int l=0,fields=0;
        sprintf(sql, "select v_id,c_id from volunteer where c_id='%d';",atoi(competition[k].id));
        rc = mysql_real_query(mysql, sql, strlen(sql));
        if (0 != rc) {
            printf("mysql_real_query(): %s\n", mysql_error(mysql));
            return ;
        }
        res = mysql_store_result(mysql);
        if (NULL == res) {
            printf("mysql_restore_result(): %s\n", mysql_error(mysql));
            return;
        }
        while ((row = mysql_fetch_row(res)))
        {
            int num=0;
            strcat(v_id,row[0]);
            num=strlen(v_id);
            v_id[num]=',';
            v_id[num+1]='\0';
        }
        sprintf(sql, " update competition set volunteer_id='%s' where id='%d';", v_id,atoi(competition[k].id));
        mysql_query(mysql, sql);
    }//��־Ը�߱�������Ӧ�ı�����Ϣ��,Ϊ�����ȡ���ӷ���
}

void Statistic(MYSQL* mysql)//־Ը����ͳ��ģ��
{
    char op;
    printf("����ESC���Է�����һ����...\n");
    while(op!='0'){
        printf("��ѡ��鿴ͳ�����ݵķ�ʽ(1)������ͳ�� (2)��־Ը��ͳ�� (3)�������ͳ�� ��[  ]\b\b\b");
        op=getch();
        putchar(op);                          /*��Ļ����*/
        printf("\n");
        if(op==27)
            break;
        switch (atoi(&op)) {
            case 1:
                CompetitionClass(mysql);
                break;
            case 2:
                VolunteerClass(mysql);
                break;
            case 3:
                AgeClass(mysql);
                break;
        }
    }
    system("cls");
}
void CompetitionClass(MYSQL* mysql)
{
    char op;
    int rc,fields;

    printf("���������Ա�����ʽ���־Ը�߷�����Ϣ\n");//ͨ�����ݿ�鿴������Ϣ,ͬʱ����־Ը�ߵı�������ҵ�־Ը�ߵ���Ϣ�����־Ը��������
    sprintf(sql, "select id,name,time,place,volunteer_id from competition;");
    rc = mysql_real_query(mysql, sql, strlen(sql));
    if (0 != rc) {
        printf("mysql_real_query(): %s\n", mysql_error(mysql));
        return ;
    }
    res = mysql_store_result(mysql);
    if (NULL == res) {
        printf("mysql_restore_result(): %s\n", mysql_error(mysql));
        return;
    }
    fields = mysql_num_fields(res);
    while ((row = mysql_fetch_row(res))) {
        for (int i = 0; i < fields; i++) {
            if(i<fields-1)
            {
                if(i==fields-2)
                    printf("%-26s\t", row[i]);
                else
                    printf("%-8s  ", row[i]);
            }
            else if(i==fields-1)
            {
                sprintf(sql, "select v_id,name from volunteer where c_id='%s';", row[0]);
                rc = mysql_real_query(mysql, sql, strlen(sql));
                if (0 != rc) {
                    printf("mysql_real_query(): %s\n", mysql_error(mysql));
                    return ;
                }
                res2 = mysql_store_result(mysql);
                if (NULL == res2) {
                    printf("mysql_restore_result(): %s\n", mysql_error(mysql));
                    return;
                }
                printf("־Ը��Ϊ��");
                while((row2 = mysql_fetch_row(res2)))
                {
                    printf("%s\t", row2[0]);//�����һ�ε����
                    printf("%s\t", row2[1]);
                }
            }
        }
        printf("\n");
    }
    printf("��ʾ�����,����������Է�����һ����...\n");
    op=getch();
    system("cls");
}
void VolunteerClass(MYSQL *mysql)
{
    char op;
    int rc,fields,fields2;

    printf("����������־Ը�߸�����ʽ���־Ը�߷�����Ϣ\n");//ͨ�����ݿ�鿴������Ϣ,ͬʱ����־Ը�ߵı�������ҵ�־Ը�ߵ���Ϣ�����־Ը��������
    sprintf(sql, "select v_id,name,position,c_id from volunteer");//ȱ�ٱ�������빤����λ,�ѱ�����ŷź���
    rc = mysql_real_query(mysql, sql, strlen(sql));
    if (0 != rc) {
        printf("mysql_real_query(): %s\n", mysql_error(mysql));
        return ;
    }
    res = mysql_store_result(mysql);
    if (NULL == res) {
        printf("mysql_restore_result(): %s\n", mysql_error(mysql));
        return;
    }
    fields = mysql_num_fields(res);
    while ((row = mysql_fetch_row(res))) {
        for (int i = 0; i < fields; i++) {
            if(i==1)
                printf("%-12s\t", row[i]);
            else if(i==2)
            {
                printf("����ְ��Ϊ��\t");
                if(atoi(row[i])==1)
                    printf("ǰ��־Ը��  \t");
                else if(atoi(row[i])==0)
                    printf( "��־Ը��  \t");
                else if(atoi(row[i])==10)
                    printf( "С�鳤       \t");
                else if(atoi(row[i])==-1)
                    printf( "��������־Ը��\t\n");
            }
            else if(i==0)
                printf("%-8s", row[i]);

            if(i==fields-1)//ȱ�ٱ�����Ų�д��fields-1,����Ϊ��ǰ�������
            {
                sprintf(sql, "select name,time from competition where id='%d';", atoi(row[i]));
                rc = mysql_real_query(mysql, sql, strlen(sql));
                if (0 != rc) {
                    printf("mysql_real_query(): %s\n", mysql_error(mysql));
                    return ;
                }
                res2 = mysql_store_result(mysql);
                if (NULL == res2) {
                    printf("mysql_restore_result(): %s\n", mysql_error(mysql));
                    return;
                }
                fields2 = mysql_num_fields(res2);
                while((row2 = mysql_fetch_row(res2)))
                {
                    printf("�����ص�Ϊ��");
                    for (int l = 0; l < fields2; l++) {
                        printf("%s\t", row2[l]);//�����һ�ε����
                    }
                    printf("\n");
                }
            }
        }
        printf("\n");
    }


    printf("��ʾ�����,����������Է�����һ����...\n");
    op=getch();;
    system("cls");
}
void AgeClass(MYSQL *mysql)
{
    char op;
    int rc,fields,fields2;
    printf("����������־Ը������(�꼶����ʽ���־Ը�߷�����Ϣ\n");

    printf("��һѧ����־Ը������Ϣ��\n");
    sprintf(sql, "select v_id,name,position,c_id from volunteer where age = 19 ");
    rc = mysql_real_query(mysql, sql, strlen(sql));
    if (0 != rc) {
        printf("mysql_real_query(): %s\n", mysql_error(mysql));
        return ;
    }
    res = mysql_store_result(mysql);
    if (NULL == res) {
        printf("mysql_restore_result(): %s\n", mysql_error(mysql));
        return;
    }
    fields = mysql_num_fields(res);
    while ((row = mysql_fetch_row(res))) {
        for (int i = 0; i < fields; i++) {
            if(i==1)
                printf("%-12s\t", row[i]);
            else if(i==2)
            {
                printf("����ְ��Ϊ��\t");
                if(atoi(row[i])==1)
                    printf("ǰ��־Ը��  \t");
                else if(atoi(row[i])==0)
                    printf( "��־Ը��  \t");
                else if(atoi(row[i])==10)
                    printf( "С�鳤       \t");
                else if(atoi(row[i])==-1)
                {
                    printf( "��������־Ը��\t\n");
                    break;
                }

            }
            else if(i==0)
                printf("%-8s",row[i]);


            if(i==fields-1 && atoi(row[2])!=-1)
            {
                sprintf(sql, "select name,time from competition where competition.id='%s';", row[i]);
                rc = mysql_real_query(mysql, sql, strlen(sql));
                if (0 != rc) {
                    printf("mysql_real_query(): %s\n", mysql_error(mysql));
                    return ;
                }
                res2 = mysql_store_result(mysql);
                if (NULL == res2) {
                    printf("mysql_restore_result(): %s\n", mysql_error(mysql));
                    return;
                }
                printf("�����ص�Ϊ��");
                fields2 = mysql_num_fields(res2);
                while((row2 = mysql_fetch_row(res2)))
                {
                    for (int j = 0; j < fields2; j++) {
                        printf("%s\t", row2[j]);//�����һ�ε����
                    }
                }
                mysql_free_result(res2);
            }
        }
        printf("\n");
    }
    printf("\n");

    printf("���ѧ����־Ը������Ϣ��\n");
    sprintf(sql, "select v_id,name,position,c_id from volunteer where age = 20 ");
    rc = mysql_real_query(mysql, sql, strlen(sql));
    if (0 != rc) {
        printf("mysql_real_query(): %s\n", mysql_error(mysql));
        return ;
    }
    res = mysql_store_result(mysql);
    if (NULL == res) {
        printf("mysql_restore_result(): %s\n", mysql_error(mysql));
        return;
    }
    fields = mysql_num_fields(res);
    while ((row = mysql_fetch_row(res))) {
        for (int i = 0; i < fields; i++) {
            if(i==1)
                printf("%-12s\t", row[i]);
            else if(i==2)
            {
                printf("����ְ��Ϊ��\t");
                if(atoi(row[i])==1)
                    printf("ǰ��־Ը��  \t");
                else if(atoi(row[i])==0)
                    printf( "��־Ը��  \t");
                else if(atoi(row[i])==10)
                    printf( "С�鳤       \t");
                else if(atoi(row[i])==-1)
                    printf( "��������־Ը��\t\n");
            }
            else if(i==0)
                printf("%-8s",row[i]);
            if(i==fields-1 && atoi(row[2])!=-1)
            {
                sprintf(sql, "select name,time from competition where competition.id='%s';", row[i]);
                rc = mysql_real_query(mysql, sql, strlen(sql));
                if (0 != rc) {
                    printf("mysql_real_query(): %s\n", mysql_error(mysql));
                    return ;
                }
                res2 = mysql_store_result(mysql);
                if (NULL == res2) {
                    printf("mysql_restore_result(): %s\n", mysql_error(mysql));
                    return;
                }
                printf("�����ص�Ϊ��");
                fields2 = mysql_num_fields(res2);
                while((row2 = mysql_fetch_row(res2)))
                {
                    for (int j = 0; j < fields2; j++) {
                        printf("%s\t", row2[j]);//�����һ�ε����
                    }
                }
            }
        }
        printf("\n");
    }
    printf("\n");

    printf("����ѧ����־Ը������Ϣ��\n");
    sprintf(sql, "select v_id,name,position,c_id from volunteer where age = 21 ");
    rc = mysql_real_query(mysql, sql, strlen(sql));
    if (0 != rc) {
        printf("mysql_real_query(): %s\n", mysql_error(mysql));
        return ;
    }
    res = mysql_store_result(mysql);
    if (NULL == res) {
        printf("mysql_restore_result(): %s\n", mysql_error(mysql));
        return;
    }
    fields = mysql_num_fields(res);
    while ((row = mysql_fetch_row(res))) {
        for (int i = 0; i < fields; i++) {
            if(i==1)
                printf("%-12s\t", row[i]);
            else if(i==2)
            {
                printf("����ְ��Ϊ��\t");
                if(atoi(row[i])==1)
                    printf("ǰ��־Ը��  \t");
                else if(atoi(row[i])==0)
                    printf( "��־Ը��  \t");
                else if(atoi(row[i])==10)
                    printf( "С�鳤       \t");
                else if(atoi(row[i])==-1)
                    printf( "��������־Ը��\t\n");
            }
            else if(i==0)
                printf("%-8s",row[i]);
            if(i==fields-1 && atoi(row[2])!=-1)
            {
                sprintf(sql, "select name,time from competition where competition.id='%s';", row[i]);
                rc = mysql_real_query(mysql, sql, strlen(sql));
                if (0 != rc) {
                    printf("mysql_real_query(): %s\n", mysql_error(mysql));
                    return ;
                }
                res2 = mysql_store_result(mysql);
                if (NULL == res2) {
                    printf("mysql_restore_result(): %s\n", mysql_error(mysql));
                    return;
                }
                printf("�����ص�Ϊ��");
                fields2 = mysql_num_fields(res2);
                while((row2 = mysql_fetch_row(res2)))
                {
                    for (int j = 0; j < fields2; j++) {
                        printf("%s\t", row2[j]);//�����һ�ε����
                    }
                }
            }
        }
        printf("\n");
    }
    printf("\n");

    printf("����ѧ����־Ը������Ϣ��\n");
    sprintf(sql, "select v_id,name,position,c_id from volunteer where (age between 22 and 23) ");
    rc = mysql_real_query(mysql, sql, strlen(sql));
    if (0 != rc) {
        printf("mysql_real_query(): %s\n", mysql_error(mysql));
        return ;
    }
    res = mysql_store_result(mysql);
    if (NULL == res) {
        printf("mysql_restore_result(): %s\n", mysql_error(mysql));
        return;
    }
    fields = mysql_num_fields(res);
    while ((row = mysql_fetch_row(res))) {
        for (int i = 0; i < fields; i++) {
            if(i==1)
                printf("%-12s\t", row[i]);
            else if(i==2)
            {
                printf("����ְ��Ϊ��\t");
                if(atoi(row[i])==1)
                    printf("ǰ��־Ը��  \t");
                else if(atoi(row[i])==0)
                    printf( "��־Ը��  \t");
                else if(atoi(row[i])==10)
                    printf( "С�鳤       \t");
                else if(atoi(row[i])==-1)
                    printf( "��������־Ը��\t\n");
            }
            else if(i==0)
                printf("%-8s",row[i]);
            if(i==fields-1 && atoi(row[2])!=-1)
            {
                sprintf(sql, "select name,time from competition where competition.id='%s';", row[i]);
                rc = mysql_real_query(mysql, sql, strlen(sql));
                if (0 != rc) {
                    printf("mysql_real_query(): %s\n", mysql_error(mysql));
                    return ;
                }
                res2 = mysql_store_result(mysql);
                if (NULL == res2) {
                    printf("mysql_restore_result(): %s\n", mysql_error(mysql));
                    return;
                }
                printf("�����ص�Ϊ��");
                fields2 = mysql_num_fields(res2);
                while((row2 = mysql_fetch_row(res2)))
                {
                    for (int j = 0; j < fields2; j++) {
                        printf("%s\t", row2[j]);//�����һ�ε����
                    }
                }
            }
        }
        printf("\n");
    }

    printf("��ʾ�����,����������Է�����һ����...\n");
    op=getch();
    system("cls");
}
