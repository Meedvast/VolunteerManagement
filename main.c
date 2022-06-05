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
    int v_id;//志愿者编号
    char* name;
    int gender;
    int age;
    char* number;//电话号
    char* ID;//身份证号
    char* workplace;
    int LanguageAbility;//掌握外语种类与熟练程度,评分由1-5分为5档,我们假定仅以英语为例
    int experience;//志愿服务经历，0表示从未，1表示有1-3次服务经历，2表示3次以上
    int servicetime;//提供服务的时间，0表示早上，1表示下午，2表示晚上。
    Skills skills;//个人特长
    Will will;//个人意愿，前场还是后勤，是否服从调剂等
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
int Menu(void);//主界面菜单
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

char v_id[5];char* name;int age;char number[11];char ID[18];char* workplace;int LanguageAbility;int experience;int servicetime;int gender;Will will;//个人意愿，前场还是后勤，是否服从调剂等

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
void Modify(MYSQL *mysql){
    printf("按下ESC键以返回上一界面...\n");
    while(1)
    {
        printf("请输入志愿者编号：");
        fflush(stdin);
        int check;
        char ch;
        int i=0;
        while(1)
        {
            ch = getch();                         /*单个字符串输入*/

            if(ch == 27) {                        /*若是Esc键*/
                v_id[0] = '\0';                        /*字符缓冲区清空*/
                system("cls");
                check=0; /*跳出循环*/
                goto start;
            }
            else if(ch == '\r' || ch == '\n') { /*若是Enter键，*/
                v_id[i] = '\0';                        /*在字符缓冲区加入字符结束标志*/
                i = 0;
                break;                             /*返回输入成功标志*/
            }
            else {
                v_id[i++] = ch;                /*否则将得到的 ch 放入字符缓冲区*/
            }
            putchar(ch);                          /*屏幕回显*/
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
                    scanf("%s",name);
                    sprintf(sql, " update volunteer set name='%s' where v_id='%s';", name, v_id);
                    break;
                case 2:
                    printf("请输入学生的性别：");
                    scanf("%d",gender);
                    sprintf(sql, " update volunteer set gender='%d' where v_id='%s';", gender, v_id);
                    break;
                case 3:
                    printf("请输入学生的年龄：");
                    scanf("%d",age);
                    sprintf(sql, " update volunteer set age='%d' where v_id='%s';", age, v_id);
                    break;
                case 5:
                    printf("请输入学生的身份证号：");
                    scanf("%s",ID);
                    sprintf(sql, "update volunteer set id='%s' where v_id='%s';", ID, v_id);
                    break;
                case 4:
                    printf("请输入学生的电话号码：");
                    scanf("%s",number);
                    sprintf(sql, "update volunteer set number=%d where v_id='%s';", number, v_id);
                    break;
                case 6:
                    printf("请输入学生的工作单位：");
                    scanf("%s",workplace);
                    sprintf(sql, " update volunteer set workplace='%s' where v_id='%s';", workplace, v_id);
                    break;
                case 7:
                    printf("请输入学生的工作意愿：");
                    scanf("%d",will.Work);
                    sprintf(sql, " update volunteer set work='%d' where v_id='%s';",will.Work, v_id);
                    break;
                case 8:
                    printf("是否服从调剂？：");
                    scanf("%d",will.Adjustice);
                    sprintf(sql, " update volunteer set adjustice='%d' where v_id='%s';", will.Adjustice, v_id);
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
void Register()
{
    char op;
    printf("按下ESC键以返回上一界面...\n");
    while(op!='0'){
        printf("需要进行的操作是 登记 ：[  ]\b\b\b");
        op=getch();
        putchar(op);                          /*屏幕回显*/
        if(op==27)
            break;
        printf("新的志愿者信息登记表 ：");
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
}
/*void CheckS()
{
    int op;
    char ese;
    printf("按下ESE键以返回上一界面...\n");
    char* Get;
    if(_kbhit())
    {
        ese=getch();
        if(ese!=27)
        {
            while(op!=0)
            {
                printf("需要查看信息的志愿者（根据姓名1/身份证号码2/电话号码3）：[  ]\b\b\b");
                scanf("%d",op);
                Volunteer *p=volunteer;
                switch (op) {
                    case 1:
                        printf("请输入要查询的志愿者的姓名：");
                        scanf("%s",Get);

                        while(p->next!=NULL)
                        {
                            if(p->name==Get)
                            {
                                printf("查询到的志愿者的信息为：%s\t%d\t%d\t%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t\n",p->name,p->gender,p->age,p->number,p->ID,p->workplace,p->LanguageAbility,p->experience,p->servicetime,p->skills.Interpersonal,p->skills.Exe,p->skills.Capacity,p->will.Work,p->will.Adjustice) ;
                                break;
                            }
                            p=p->next;
                        }
                        break;
                    case 2:
                        printf("请输入要查询的志愿者的身份证号码：");
                        scanf("%s",Get);
                        while(p->next!=NULL)
                        {
                            if(p->ID==Get)
                            {
                                printf("查询到的志愿者的信息为：%s\t%d\t%d\t%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t\n",p->name,p->gender,p->age,p->number,p->ID,p->workplace,p->LanguageAbility,p->experience,p->servicetime,p->skills.Interpersonal,p->skills.Exe,p->skills.Capacity,p->will.Work,p->will.Adjustice) ;
                                break;
                            }
                            p=p->next;
                        }
                        break;
                    case 3:
                        printf("请输入要查询的志愿者的电话号码：");
                        scanf("%s",Get);
                        while(p->next!=NULL)
                        {
                            if(p->number==Get)
                            {
                                printf("查询到的志愿者的信息为：%s\t%d\t%d\t%s\t%s\t%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t\n",p->name,p->gender,p->age,p->number,p->ID,p->workplace,p->LanguageAbility,p->experience,p->servicetime,p->skills.Interpersonal,p->skills.Exe,p->skills.Capacity,p->will.Work,p->will.Adjustice) ;
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
    //查看比赛信息
    int op;
    char ese;
    printf("按下ESE键以返回上一界面...\n");
    if(_kbhit()) {
        ese = getch();
        if (ese != 27) {
            while (op!=0){
                printf("请输入需要查看的比赛编号：");
                scanf("%d", &op);
                printf("比赛名称：%s\n", competition[op].name);
                printf("比赛时间：%s\n", competition[op].time);
                printf("比赛地点：%s\n", competition[op].place);
                printf("比赛类型：%s\n", competition[op].type);
            }
        }
    }
    system("cls");
}
void Arrangement(MYSQL *mysql)
{
    //根据比赛编号进行比赛安排

}
//从数据库中查询信息

void Statistic()
{
    char op;
    printf("按下ESC键以返回上一界面...\n");
    while(op!='0'){
        printf("请选择查看统计数据的方式 ：[  ]\b\b\b");
        op=getch();
        putchar(op);                          /*屏幕回显*/
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
    printf("接下来将以比赛形式输出志愿者服务信息");//通过数据库查看比赛信息，同时根据志愿者的比赛编号找到志愿者的信息并输出志愿服务数据
    for(int i=0;i<20;i++)
    {
        Volunteer *p=volunteer;
        printf("比赛名称：%s\n", competition[i].name);
        printf("比赛时间：%s\n", competition[i].time);
        printf("比赛地点：%s\n", competition[i].place);
        printf("比赛类型：%s\n", competition[i].type);
        printf("该场比赛的志愿者为：\n");
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
    printf("接下来将以志愿者形式输出志愿者服务信息");//通过数据库查看志愿者信息，同时根据志愿者的比赛编号找到志愿者的信息并输出志愿服务数据
    sprintf(sql,"select v_id,name from volunteer,competition where volunteer.work.competition=competition.id");

    //select v_id,name from volunteer,competition where volunteer.work.competition=competition.id
    //需要建立一个competition表，包含比赛编号，比赛内容（名字），比赛时间，比赛地点，比赛类型，在这场比赛工作的志愿者的编号，同时志愿者表需要加上实际工作岗位与比赛编号
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
        printf("志愿者服务于%s %s",competition[i].name,competition[i].type);
        printf("职务为%s",p->work.position);
        p=p->next;
    }

}
void AgeClass()
{
    printf("接下来将以志愿者年龄形式输出志愿者服务信息");
    Volunteer *p=volunteer;
    sort_Volunteer(volunteer,get_last_Volunteer(volunteer));
    while (p->next!=NULL)
    {
        printf("大一学生的志愿服务信息：\n");
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
            printf("%d %s 服务于 %s %s做%s",p->v_id,p->name,competition[mid].name,competition[mid].type,p->work.position);
            p=p->next;
        }
        printf("大二学生的志愿服务信息：\n");
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
            printf("%d %s 服务于 %s %s做%s",p->v_id,p->name,competition[mid].name,competition[mid].type,p->work.position);
            p=p->next;
        }
        printf("大三学生的志愿服务信息：\n");
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
            printf("%d %s 服务于 %s %s做%s",p->v_id,p->name,competition[mid].name,competition[mid].type,p->work.position);
            p=p->next;
        }
        printf("大四学生的志愿服务信息：\n");
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
            printf("%d %s 服务于 %s %s做%s",p->v_id,p->name,competition[mid].name,competition[mid].type,p->work.position);
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

        if(pfast->age <= phead->age) //phead作为支点
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
    sort_Volunteer(phead, ptemp);//ptemp为左右两部分分割点的前一个节点
    sort_Volunteer(pslow->next, pend);
}