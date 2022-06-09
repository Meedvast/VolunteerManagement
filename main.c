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
    char v_id[5];//志愿者编号
    char* name;
    int gender;
    int age;
    char* number;//电话号
    char* ID;//身份证号
    char* workplace;
    int LanguageAbility;//掌握外语种类与熟练程度,评分由1-5分为5档,我们假定仅以英语为例
    int experience;//志愿服务经历,0表示从未,1表示有1-3次服务经历,2表示3次以上
    int servicetime;//提供服务的时间,0表示早上,1表示下午,2表示晚上。
    Skills skills;//个人特长
    Will will;//个人意愿,前场还是后勤,是否服从调剂等
}Volunteer;
typedef struct Competition{
    char id[5];
    char name[100];
    char time[100];
    int time_num;
    char type[100];
}Competition;
Volunteer volunteer;

int Menu(void);//主界面菜单
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
void Modify(MYSQL *mysql){//修改志愿者信息
    char ch;
    int i=0;
    system("cls");
    printf("按下ESC键以返回上一界面...\n");
    while(1)
    {
        printf("请输入志愿者编号：");

        while(1)
        {
            fflush(stdin);
            ch = getch();                         /*单个字符串输入*/


            if(ch == 27) {                        /*若是Esc键*/
                volunteer.v_id[0] = '\0';                        /*字符缓冲区清空*/
                system("cls");          /*跳出循环*/
                return;
            }
            else if(ch == '\r' || ch == '\n') { /*若是Enter键,*/
                volunteer.v_id[i] = '\0';                        /*在字符缓冲区加入字符结束标志*/
                i = 0;
                break;                             /*返回输入成功标志*/
            }
            else {
                volunteer.v_id[i++] = ch;                /*否则将得到的 ch 放入字符缓冲区*/
            }
            putchar(ch);          /*屏幕回显*/
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
                printf("该学号无效！\n");
                continue;
            }
        }
        mysql_free_result(res);
        printf("\n");

        printf("(1)姓名 (2)性别 （3）年龄 (4)电话号码 （5）身份证号 （6）工作单位 （7）工作意愿 （8）是否服从调剂 (0)退出\n");
        int select=1;
        while(select!=0) {
            printf("请输入选择：");
            fflush(stdin);
            scanf("%d",&select);
            switch (select) {
                case 0:
                    continue;
                case 1:
                    printf("请输入学生的姓名：");
                    scanf("%s",volunteer.name);
                    sprintf(sql, " update volunteer set name='%s' where v_id='%s';",volunteer.name, volunteer.v_id);
                    break;
                case 2:
                    printf("请输入学生的性别：");
                    scanf("%d",&volunteer.gender);
                    sprintf(sql, " update volunteer set gender='%d' where v_id='%s';", volunteer.gender, volunteer.v_id);
                    break;
                case 3:
                    printf("请输入学生的年龄：");
                    scanf("%d",&volunteer.age);
                    sprintf(sql, " update volunteer set age='%d' where v_id='%s';", volunteer.age, volunteer.v_id);
                    break;
                case 5:
                    printf("请输入学生的身份证号：");
                    scanf("%s",volunteer.ID);
                    sprintf(sql, "update volunteer set id='%s' where v_id='%s';", volunteer.ID, volunteer.v_id);
                    break;
                case 4:
                    printf("请输入学生的电话号码：");
                    scanf("%s",volunteer.number);
                    sprintf(sql, "update volunteer set phoneNumber='%d' where v_id='%s';", volunteer.number,volunteer.v_id);
                    break;
                case 6:
                    printf("请输入学生的工作单位：");
                    scanf("%s",volunteer.workplace);
                    sprintf(sql, " update volunteer set workplace='%s' where v_id='%s';", volunteer.workplace,volunteer.v_id);
                    break;
                case 7:
                    printf("请输入学生的工作意愿：");
                    scanf("%d",&volunteer.will.Work);
                    sprintf(sql, " update volunteer set work='%d' where v_id='%s';",volunteer.will.Work, volunteer.v_id);
                    break;
                case 8:
                    printf("是否服从调剂？：");
                    scanf("%d",&volunteer.will.Adjustice);
                    sprintf(sql, " update volunteer set adjustice='%d' where v_id='%s';",volunteer.will.Adjustice, volunteer.v_id);
                    break;
                default:
                    break;
                }
            if (!mysql_query(mysql, sql)) {
                printf("学生信息修改成功！\n");
            }
            else {
                printf("学生信息修改失败！\n");
                fprintf(stderr, "%s\n", mysql_error(mysql));
                system("pause");
            }
        }
    }
    system("cls");
}
void Insert(MYSQL* mysql)//往表中插入数据,数据为变量的写法
{
    system("cls");
    char ch;
    int rc,i;
    int check;
    char op;
    printf("按下ESC键以返回上一界面...\n");

    while(1)
    {
        printf("请输入要添加的志愿者学号：");
        while(1)
        {
            fflush(stdin);
            ch = getch();                         /*单个字符串输入*/

            if(ch == 27) {                        /*若是Esc键*/
                volunteer.v_id[0] = '\0';                        /*字符缓冲区清空*/
                system("cls");
                check=0; /*跳出循环*/
                goto start;
            }
            else if(ch == '\r' || ch == '\n') { /*若是Enter键,*/
                volunteer.v_id[i] = '\0';                        /*在字符缓冲区加入字符结束标志*/
                i = 0;
                break;                             /*返回输入成功标志*/
            }
            else {
                volunteer.v_id[i++] = ch;                /*否则将得到的 ch 放入字符缓冲区*/
            }
            putchar(ch);                          /*屏幕回显*/
        }
        check=1;
        start:
        if(!check)
            break;
        //省略以下好多输入,开摆！
        printf("\n请输入需要添加的志愿者姓名：");
        scanf("%s",volunteer.name);
        fflush(stdin);
        printf("\n请输入需要添加的志愿者性别：");
        scanf("%d",&volunteer.gender);
        printf("\n请输入需要添加的志愿者年龄：");
        scanf("%d",&volunteer.age);
        printf("\n请输入需要添加的志愿者电话号码：");
        scanf("%s",volunteer.number);
        fflush(stdin);
        printf("\n请输入需要添加的志愿者身份证号：");
        scanf("%s",volunteer.ID);
        fflush(stdin);
        printf("\n请输入需要添加的志愿者工作单位：");
        scanf("%s",volunteer.workplace);
        fflush(stdin);
        printf("\n请输入需要添加的志愿者言语能力（由1——5从低到高）：");
        scanf("%d",&volunteer.LanguageAbility);
        printf("\n请输入需要添加的志愿者的志愿经历：");
        scanf("%d",&volunteer.experience);
        printf("\n请输入需要添加的志愿者的服务时间：");
        scanf("%d",&volunteer.servicetime);
        printf("\n请输入需要添加的志愿者的交际能力：");
        scanf("%d",&volunteer.skills.Interpersonal);
        printf("\n请输入需要添加的志愿者的执行力：");
        scanf("%d",&volunteer.skills.Exe);
        printf("\n请输入需要添加的志愿者管理能力：");
        scanf("%d",&volunteer.skills.Capacity);
        printf("\n请输入需要添加的志愿者的工作意愿：");
        scanf("%d",&volunteer.will.Work);
        printf("\n请输入需要添加的志愿者是否接受调剂：");
        scanf("%d",&volunteer.will.Adjustice);

        sprintf(sql, "insert into volunteer (v_id,name,gender,age,phoneNumber,id,workplace,LanguageAbility,experience,serviceTime,interpersonal,exe,capacity,work,adjustice,ability) values ('%s', '%s', '%d', '%d','%s','%s','%s','%d','%d','%d','%d','%d','%d','%d','%d','%lf')", volunteer.v_id, volunteer.name, volunteer.gender, volunteer.age,volunteer.number,volunteer.ID,volunteer.workplace,volunteer.LanguageAbility,volunteer.experience,volunteer.servicetime,volunteer.skills.Interpersonal,volunteer.skills.Exe,volunteer.skills.Capacity,volunteer.will.Work,volunteer.will.Adjustice,volunteer.skills.Interpersonal*0.25+volunteer.skills.Exe*0.5+volunteer.skills.Capacity*0.25);
        rc = mysql_real_query(mysql, sql, strlen(sql));
        if (0 != rc) {
            printf("mysql_real_query(): %s\n", mysql_error(mysql));
            return ;
        }
        printf("插入成功！\n");
    }
    mysql_close(mysql);
}
void Delete(MYSQL* mysql)
{
    system("cls");
    char ch;
    int rc,i;
    int check;
    printf("按下ESC键以返回上一界面...\n");
    while(1)
    {
        printf("请输入要删除的学生学号：");
        while(1)
        {
            ch = getch();                         /*单个字符串输入*/

            if(ch == 27) {                        /*若是Esc键*/
                volunteer.v_id[0] = '\0';                        /*字符缓冲区清空*/
                system("cls");
                check=0; /*跳出循环*/
                goto start;
            }
            else if(ch == '\r' || ch == '\n') { /*若是Enter键,*/
                volunteer.v_id[i] = '\0';                        /*在字符缓冲区加入字符结束标志*/
                i = 0;
                break;                             /*返回输入成功标志*/
            }
            else {
                volunteer.v_id[i++] = ch;                /*否则将得到的 ch 放入字符缓冲区*/
            }
            putchar(ch);                          /*屏幕回显*/
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
            printf("\n该学号无效！\n");
            continue;
        }
        printf("\n确定要删除该学生吗？（1）确定（0）取消\n");
        scanf("%d",&check);
        if(check==1)
        {
            sprintf(sql, "delete from volunteer where v_id='%s';", volunteer.v_id);
            rc = mysql_real_query(mysql, sql, strlen(sql));
            if (0 != rc) {
                printf("mysql_real_query(): %s\n", mysql_error(mysql));
                return ;
            }
            printf("删除成功！\n");
        }
        else
        {
            printf("取消删除！\n");
        }
    }
    mysql_close(mysql);
    return ;

}
void Register(MYSQL* mysql)//登记新的志愿者信息
{
    system("cls");
    char op;
    printf("按下ESC键以返回上一界面...\n");
    while(op!='0'){
        printf("需要进行的操作是 登记1/删除记录2 ：[  ]\b\b\b");
        fflush(stdin);
        op = getch();                         /*单个字符串输入*/

        if(op == 27) {                        /*若是Esc键*/
            //volunteer.v_id[0] = '\0';                        /*字符缓冲区清空*/
            system("cls");          /*跳出循环*/
            return;
        }
        putchar(op);          /*屏幕回显*/
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
    printf("按下ESC键以返回上一界面...\n");
    while(op!='0'){
        printf("需要进行的操作是 登记1/修改2 ：[  ]\b\b\b");
        op=getch();
        putchar(op);                          /*屏幕回显*/
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
}//志愿者信息模块
void CompetitionInfo(MYSQL* mysql)//比赛信息模块
{
    char op,ch;
    printf("按下ESC键以返回上一界面...\n");
    while(op!='0'){
        printf("您需要查看比赛信息吗 (1)是 (2)安排比赛 (0)退出:[  ]\b\b\b");
        op=getch();
        putchar(op);                          /*屏幕回显*/
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
                printf("已完成自动分配！是否需要进行手动修改？(1)是 （0）否：[  ]\b\b\b");
                ch=getch();
                putchar(ch);                          /*屏幕回显*/
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
void CheckC(MYSQL* mysql)//查询比赛信息
{
    //查看比赛信息
    char ch;
    int rc,fields;
    int i=0;
    Competition Check;
    while (1)
    {
        printf("请输入需要查询的比赛编号：");//通过数据库查看比赛信息,同时根据志愿者的比赛编号找到志愿者的信息并输出志愿服务数据
        memset(Check.id,'\0',sizeof(Check.id));
        fflush(stdin);
        i=0;
        while(1)
        {
            fflush(stdin);
            ch = getch();                         /*单个字符串输入*/

            if(ch == 27) {                        /*若是Esc键*/
                Check.id[0] = '\0';                        /*字符缓冲区清空*/
                system("cls");          /*跳出循环*/
                return;
            }
            else if(ch == '\r' || ch == '\n') { /*若是Enter键,*/
                Check.id[i] = '\0';                        /*在字符缓冲区加入字符结束标志*/
                i = 0;
                break;                             /*返回输入成功标志*/
            }
            else {
                Check.id[i++] = ch;                /*否则将得到的 ch 放入字符缓冲区*/
            }
            putchar(ch);          /*屏幕回显*/
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
void Arrange(MYSQL *mysql)//自动进行志愿者与比赛匹配,要求：SELECT MAX(student_name) FROM tb_students_score;分成两个组愿意调剂和不愿意的,然后分别进行排序,对不愿意调剂的按能力值由高到低分配,对愿意调剂的按能力值由低到高分配,一场比赛2个前场两个后场
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

    sprintf(sql,"select * from competition order by type desc,id;");//读取比赛信息,按语言能力要求降序排列
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
    }//获取数据到比赛数组
    i=0;
    j=0;
    mysql_free_result(res);

    sprintf(sql,"select v_id,LanguageAbility,experience,serviceTime,work,adjustice,ability from volunteer where adjustice=0 order by ability desc,v_id;");//读取志愿者信息
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
    }//第一次分配,分配不接受调剂的志愿者,按照志愿者意愿
    mysql_free_result(res);

    sprintf(sql,"select v_id,LanguageAbility,experience,serviceTime,work,adjustice,ability from volunteer where adjustice=1 order by ability,v_id;");//重置
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
    }//第二次分配,分配部分接受调剂的志愿者,依旧按照志愿者意愿,且不设上限
    mysql_free_result(res);

    sprintf(sql,"select v_id,LanguageAbility,experience,serviceTime,work,adjustice,ability from volunteer where adjustice=0 order by ability,v_id;");//重置
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
    }//第三次分配,分配剩余不接受调剂的志愿者,要求强制分配

    sprintf(sql,"select v_id,LanguageAbility,experience,serviceTime,work,adjustice,ability from volunteer where adjustice=1 order by ability desc,v_id;");//重置
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
    }//第四次分配,分配剩余接受调剂的志愿者,要求强制分配
    mysql_free_result(res);

    sprintf(sql,"select v_id,LanguageAbility,experience,serviceTime,work,adjustice,ability from volunteer where adjustice=1 order by ability desc,v_id;");//重置
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
    while(i<101)//检查未分配工作的志愿者,分配为公共场所志愿者
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
    }//选取小组长
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
    }//将志愿者编号输入对应的比赛信息中,为后面读取连接方便
}

void Statistic(MYSQL* mysql)//志愿服务统计模块
{
    char op;
    printf("按下ESC键以返回上一界面...\n");
    while(op!='0'){
        printf("请选择查看统计数据的方式(1)按比赛统计 (2)按志愿者统计 (3)按年龄段统计 ：[  ]\b\b\b");
        op=getch();
        putchar(op);                          /*屏幕回显*/
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

    printf("接下来将以比赛形式输出志愿者服务信息\n");//通过数据库查看比赛信息,同时根据志愿者的比赛编号找到志愿者的信息并输出志愿服务数据
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
                printf("志愿者为：");
                while((row2 = mysql_fetch_row(res2)))
                {
                    printf("%s\t", row2[0]);//完成这一次的输出
                    printf("%s\t", row2[1]);
                }
            }
        }
        printf("\n");
    }
    printf("显示已完成,按下任意键以返回上一界面...\n");
    op=getch();
    system("cls");
}
void VolunteerClass(MYSQL *mysql)
{
    char op;
    int rc,fields,fields2;

    printf("接下来将以志愿者个人形式输出志愿者服务信息\n");//通过数据库查看比赛信息,同时根据志愿者的比赛编号找到志愿者的信息并输出志愿服务数据
    sprintf(sql, "select v_id,name,position,c_id from volunteer");//缺少比赛编号与工作岗位,把比赛编号放后面
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
                printf("工作职务为：\t");
                if(atoi(row[i])==1)
                    printf("前场志愿者  \t");
                else if(atoi(row[i])==0)
                    printf( "后场志愿者  \t");
                else if(atoi(row[i])==10)
                    printf( "小组长       \t");
                else if(atoi(row[i])==-1)
                    printf( "公共场所志愿者\t\n");
            }
            else if(i==0)
                printf("%-8s", row[i]);

            if(i==fields-1)//缺少比赛编号才写得fields-1,别以为以前的你错了
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
                    printf("工作地点为：");
                    for (int l = 0; l < fields2; l++) {
                        printf("%s\t", row2[l]);//完成这一次的输出
                    }
                    printf("\n");
                }
            }
        }
        printf("\n");
    }


    printf("显示已完成,按下任意键以返回上一界面...\n");
    op=getch();;
    system("cls");
}
void AgeClass(MYSQL *mysql)
{
    char op;
    int rc,fields,fields2;
    printf("接下来将以志愿者年龄(年级）形式输出志愿者服务信息\n");

    printf("大一学生的志愿服务信息：\n");
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
                printf("工作职务为：\t");
                if(atoi(row[i])==1)
                    printf("前场志愿者  \t");
                else if(atoi(row[i])==0)
                    printf( "后场志愿者  \t");
                else if(atoi(row[i])==10)
                    printf( "小组长       \t");
                else if(atoi(row[i])==-1)
                {
                    printf( "公共场所志愿者\t\n");
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
                printf("工作地点为：");
                fields2 = mysql_num_fields(res2);
                while((row2 = mysql_fetch_row(res2)))
                {
                    for (int j = 0; j < fields2; j++) {
                        printf("%s\t", row2[j]);//完成这一次的输出
                    }
                }
                mysql_free_result(res2);
            }
        }
        printf("\n");
    }
    printf("\n");

    printf("大二学生的志愿服务信息：\n");
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
                printf("工作职务为：\t");
                if(atoi(row[i])==1)
                    printf("前场志愿者  \t");
                else if(atoi(row[i])==0)
                    printf( "后场志愿者  \t");
                else if(atoi(row[i])==10)
                    printf( "小组长       \t");
                else if(atoi(row[i])==-1)
                    printf( "公共场所志愿者\t\n");
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
                printf("工作地点为：");
                fields2 = mysql_num_fields(res2);
                while((row2 = mysql_fetch_row(res2)))
                {
                    for (int j = 0; j < fields2; j++) {
                        printf("%s\t", row2[j]);//完成这一次的输出
                    }
                }
            }
        }
        printf("\n");
    }
    printf("\n");

    printf("大三学生的志愿服务信息：\n");
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
                printf("工作职务为：\t");
                if(atoi(row[i])==1)
                    printf("前场志愿者  \t");
                else if(atoi(row[i])==0)
                    printf( "后场志愿者  \t");
                else if(atoi(row[i])==10)
                    printf( "小组长       \t");
                else if(atoi(row[i])==-1)
                    printf( "公共场所志愿者\t\n");
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
                printf("工作地点为：");
                fields2 = mysql_num_fields(res2);
                while((row2 = mysql_fetch_row(res2)))
                {
                    for (int j = 0; j < fields2; j++) {
                        printf("%s\t", row2[j]);//完成这一次的输出
                    }
                }
            }
        }
        printf("\n");
    }
    printf("\n");

    printf("大四学生的志愿服务信息：\n");
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
                printf("工作职务为：\t");
                if(atoi(row[i])==1)
                    printf("前场志愿者  \t");
                else if(atoi(row[i])==0)
                    printf( "后场志愿者  \t");
                else if(atoi(row[i])==10)
                    printf( "小组长       \t");
                else if(atoi(row[i])==-1)
                    printf( "公共场所志愿者\t\n");
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
                printf("工作地点为：");
                fields2 = mysql_num_fields(res2);
                while((row2 = mysql_fetch_row(res2)))
                {
                    for (int j = 0; j < fields2; j++) {
                        printf("%s\t", row2[j]);//完成这一次的输出
                    }
                }
            }
        }
        printf("\n");
    }

    printf("显示已完成,按下任意键以返回上一界面...\n");
    op=getch();
    system("cls");
}
