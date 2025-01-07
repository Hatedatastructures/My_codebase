#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <windows.h>

#define NAME_MAX 20                                     /*姓名*/
#define ADDRESS_MAX 100                                 /*地址*/
#define SEX_MAX 10                                      /*性别*/
#define Capacity_increase_multiple 2                    /*倍数*/
enum menu
{
    EXITS,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    ELEVEN,
    TWELVE,
    THIRTEEN,
    FOURTEEN,
    FIFTEEN,
};                                              

typedef struct student
{
    unsigned char Chinese;                              /*语文*/
    unsigned char Math;                                 /*数学*/
    unsigned char English;                              /*英语*/
    unsigned char politics;                             /*政治*/
    unsigned char history;                              /*历史*/
    unsigned char geography;                            /*地理*/
    unsigned char biology;                              /*生物*/
    unsigned char chemistry;                            /*化学*/
} s;
typedef struct students
{
    int num;                                            /*学号*/
    char name[NAME_MAX];                                /*姓名*/
    int age;                                            /*年龄*/
    char sex[SEX_MAX];                                  /*性别*/
    long long tel;                                      /*电话*/
    char address[ADDRESS_MAX];                          /*地址*/
    long long identity_card;                            /*证号*/
    s wing;                                             /*成绩*/
} stu;

typedef struct studentss
{
    stu* arr;
    size_t size;                                        /*当前元素个数*/
    size_t capacity;                                    /*当前容量*/
} st;

void initialize(st* s);                                 /*初始*/

void stuHead_insertion(st* p, stu* x);                  /*头插*/

void stuHeader_removal(st* p);                          /*头删*/

void stuInsert_in_the_middle(st* p, stu* x, int pos);   /*中插*/

void stuIntermediate_deletion(st* p, int pos);          /*中删*/

void stuTail_insertion(st* p, stu* x);                  /*尾插*/

void stuTail_deletion(st* p);                           /*尾删*/

void stuprint(const st* p);                             /*打印*/

void Capacity(st* p);                                   /*增容*/


int cmp_num(const void* a, const void* b)                
{
    return ((stu*)a)->num - ((stu*)b)->num;
}
int cmp_name(const void* a, const void* b)
{
    return strcmp(((stu*)a)->name, ((stu*)b)->name);
}
int cmp_age(const void* a, const void* b)
{
    return ((stu*)a)->age - ((stu*)b)->age;
}
int cmp_sex(const void* a, const void* b)
{
    return strcmp(((stu*)a)->sex, ((stu*)b)->sex);
}
int cmp_tel(const void* a, const void* b)
{
    return ((stu*)a)->tel - ((stu*)b)->tel;
}
int cmp_address(const void* a, const void* b)
{
    return strcmp(((stu*)a)->address, ((stu*)b)->address);
}
int cmp_identity_card(const void* a, const void* b)
{
    return ((stu*)a)->identity_card - ((stu*)b)->identity_card;
}
int cmp_Chinese(const void* a, const void* b)
{
    return ((stu*)a)->wing.Chinese - ((stu*)b)->wing.Chinese;
}
int cmp_Math(const void* a, const void* b)
{
    return ((stu*)a)->wing.Math - ((stu*)b)->wing.Math;
}
int cmp_English(const void* a, const void* b)
{
    return ((stu*)a)->wing.English - ((stu*)b)->wing.English;
}
int cmp_politics(const void* a, const void* b)
{
    return ((stu*)a)->wing.politics - ((stu*)b)->wing.politics;
}
int cmp_history(const void* a, const void* b)
{
    return ((stu*)a)->wing.history - ((stu*)b)->wing.history;
}
int cmp_geography(const void* a, const void* b)
{
    return ((stu*)a)->wing.geography - ((stu*)b)->wing.geography;
}
int cmp_biology(const void* a, const void* b)
{
    return ((stu*)a)->wing.biology - ((stu*)b)->wing.biology;
}
int cmp_chemistry(const void* a, const void* b)
{
    return ((stu*)a)->wing.chemistry - ((stu*)b)->wing.chemistry;
}


void initialize(st* s)                                  /*初始化*/
{
    assert(s!= NULL);
    s->arr = (stu*)malloc(sizeof(stu) * 10);
    if (s->arr == NULL)
    {
        printf("申请内存失败！\n");
        exit(-1);
    }
    s->size = 0;
    s->capacity = 10;
}


void Capacity(st* p)                                    /*增容*/
{
    assert(p!= NULL);
    if (p->size == p->capacity)
    {
        p->capacity *= Capacity_increase_multiple;
        stu* tmp = (stu*)realloc(p->arr, sizeof(stu) * p->capacity);
        if (tmp == NULL)
        {
            printf("增容申请内存失败！\n");
            exit(-1);
        }
        p->arr = tmp;
    }
}


// 修改 Delete 函数，不分配内存，只进行元素的删除操作
void Delete(st* p, int index)
{
    assert(p!= NULL);
    if (p->size == 0)
    {
        printf("当前人数为 0,无法删除!\n");
        exit(-1);
    }
    // 可根据具体需求添加更复杂的删除逻辑，这里简单将最后一个元素覆盖要删除的元素
    if (index < p->size - 1) 
    {
        p->arr[index] = p->arr[p->size - 1];
    }
    p->size--;
}


void stuHead_insertion(st* p, stu* x)                    /*头插*/
{
    assert(p!= NULL);
    Capacity(p);
    for (int i = p->size - 1; i >= 0; i--)
    {
        p->arr[i + 1] = p->arr[i];
    }
    p->arr[0] = *x;
    p->size++;
    free(x);
}


void stuHeader_removal(st* p)                            /*头删*/
{
    assert(p!= NULL);
    Delete(p, 0);
}


void stuInsert_in_the_middle(st* p, stu* x, int pos)     /*中插*/
{
    assert(p!= NULL);
    Capacity(p);
    for (int i = p->size; i > pos; i--)
    {
        p->arr[i] = p->arr[i - 1];
    }
    p->arr[pos] = *x;
    p->size++;
    free(x);
}


void stuIntermediate_deletion(st* p, int pos)           /*中删*/
{
    assert(p!= NULL);
    Delete(p, pos);
}


void stuTail_insertion(st* p, stu* x)                   /*尾插*/
{
    assert(p!= NULL);
    Capacity(p);
    p->arr[p->size] = *x;
    p->size++;
    free(x);
}


void stuTail_deletion(st* p)                            /*尾删*/
{
    assert(p!= NULL);
    Delete(p, p->size - 1);
}


void stuprint(const st* p)                              /*打印*/
{
    assert(p!= NULL);
    printf("当前人数:%zu\n", p->size);
    for (size_t i = 0; i < p->size; i++)
    {
        printf("学号%d 姓名：%s 年龄：%d 性别：%s 电话：%lld 地址：%s 证号：%lld"
        "语文：%d 数学:%d 英语:%d 政治:%d 历史:%d 地理:%d 生物:%d 化学：%d\n",
        p->arr[i].num, p->arr[i].name, p->arr[i].age, p->arr[i].sex, p->arr[i].tel,
        p->arr[i].address, p->arr[i].identity_card, p->arr[i].wing.Chinese,
        p->arr[i].wing.Math, p->arr[i].wing.English, p->arr[i].wing.politics,
        p->arr[i].wing.history, p->arr[i].wing.geography, p->arr[i].wing.biology,
        p->arr[i].wing.chemistry);
    }
}


void Read_file(FILE* fp, st* p)                         /*读取*/
{
    assert(p!= NULL);
    initialize(p);
    stu stg;
    while (fscanf(fp, "%d %s %d %s %lld %s %lld %d %d %d %d %d %d %d %d",
        &stg.num,&stg.name,&stg.age,&stg.sex,&stg.tel,&stg.address,&stg.identity_card,
        &stg.wing.Chinese,&stg.wing.Math,&stg.wing.English,&stg.wing.politics,
        &stg.wing.history,&stg.wing.geography,&stg.wing.biology,&stg.wing.chemistry) == 15)
    {
        p->arr[p->size] = stg;
        p->size++;
        Capacity(p);
    }
    // 检查文件读取是否成功
    if (ferror(fp))
    {
        printf("文件读取错误！\n");
        exit(-1);
    }
    printf("\n读取成功!\n");
}
void Write_file(FILE* fp, st* p)                       /*写入*/
{
    assert(p!= NULL);
    if(p->size == 0)
    {
        printf("当前人数为 0,无法写入!\n");
        exit(-1);
    }
    else
    {
        for (size_t i = 0; i < p->size; i++)
        {
            fprintf(fp, "%d %s %d %s %lld %s %lld %d %d %d %d %d %d %d %d\n",
            p->arr[i].num,p->arr[i].name,p->arr[i].age,p->arr[i].sex,p->arr[i].tel,
            p->arr[i].address,p->arr[i].identity_card,p->arr[i].wing.Chinese,
            p->arr[i].wing.Math,p->arr[i].wing.English,p->arr[i].wing.politics,
            p->arr[i].wing.history,p->arr[i].wing.geography,p->arr[i].wing.biology,
            p->arr[i].wing.chemistry
            );
        }
        printf("\n写入成功!\n");
        printf("当前写入人数:%zu\n", p->size);
    }
}
stu* stuinport()                                        /*输入*/
{ 
    stu* stg= (stu*)malloc(sizeof(stu));
    if(stg == NULL)
    {
        perror("malloc");
        exit(-1);
    }
    printf("请输入学生信息:\n\a");
    printf("学号:");
    scanf("%d", &stg->num);
    printf("姓名:");
    scanf("%s", stg->name);
    printf("年龄:");
    scanf("%d", &stg->age);
    printf("性别:");
    scanf("%s", stg->sex);
    printf("电话:");
    scanf("%lld", &stg->tel);
    printf("地址:");
    scanf("%s", stg->address);
    printf("证号:");
    scanf("%lld", &stg->identity_card);
    printf("语文:");
    scanf("%d", &stg->wing.Chinese);
    printf("数学:");
    scanf("%d", &stg->wing.Math);
    printf("英语:");
    scanf("%d", &stg->wing.English);
    printf("政治:");
    scanf("%d", &stg->wing.politics);
    printf("历史:");
    scanf("%d", &stg->wing.history);
    printf("地理:");
    scanf("%d", &stg->wing.geography);
    printf("生物:");
    scanf("%d", &stg->wing.biology);
    printf("化学:");
    scanf("%d", &stg->wing.chemistry);
    printf("输入成功!\n");
    return stg;
}
int sorts()
{
    printf("请选择排序方式:\n\a");
    printf("1  按学号排序\n");
    printf("2. 按姓名排序\n");
    printf("3. 按年龄排序\n");
    printf("4. 按性别排序\n");
    printf("5. 按电话排序\n");
    printf("6. 按地址排序\n");
    printf("7. 按证号排序\n");
    printf("8. 按语文排序\n");
    printf("9. 按数学排序\n");
    printf("10.按英语排序\n");
    printf("11.按政治排序\n");
    printf("12.按历史排序\n");
    printf("13.按地理排序\n");
    printf("14.按生物排序\n");
    printf("15.按化学排序\n");
    int inport = 0;
    scanf("%d", &inport);
    return inport;
}

void my_sort(st* p, int index)                          /*排序*/
{
    assert(p!= NULL);
    if(p->size == 0)
    {
        printf("当前没有学生信息,请先输入学生信息!\n");
        exit(-1);
    }
    switch (index)
    {
        case ONE:
            qsort(p->arr, p->size, sizeof(stu), cmp_num);
            break;
        case TWO:
            qsort(p->arr, p->size, sizeof(stu), cmp_name);
            break;
        case THREE:
            qsort(p->arr, p->size, sizeof(stu), cmp_age);
            break;
        case FOUR:
            qsort(p->arr, p->size, sizeof(stu), cmp_sex);
            break;
        case FIVE:
            qsort(p->arr, p->size, sizeof(stu), cmp_tel);
            break;
        case SIX:
            qsort(p->arr, p->size, sizeof(stu), cmp_address);
            break;
        case SEVEN:
            qsort(p->arr, p->size, sizeof(stu), cmp_identity_card);
            break;
        case EIGHT:
            qsort(p->arr, p->size, sizeof(stu), cmp_Chinese);
            break;
        case NINE:
            qsort(p->arr, p->size, sizeof(stu), cmp_Math);
            break;
        case TEN:
            qsort(p->arr, p->size, sizeof(stu), cmp_English);
            break;
        case ELEVEN:
            qsort(p->arr, p->size, sizeof(stu), cmp_politics);
            break;
        case TWELVE:
            qsort(p->arr, p->size, sizeof(stu), cmp_history);
            break;
        case THIRTEEN:
            qsort(p->arr, p->size, sizeof(stu), cmp_geography);
            break;
        case FOURTEEN:
            qsort(p->arr, p->size, sizeof(stu), cmp_biology);
            break;
        case FIFTEEN:
            qsort(p->arr, p->size, sizeof(stu), cmp_chemistry);
            break;
        default:
            printf("输入错误!\n");
            break;
    }
    printf("排序成功!\n\a");
}
void meau()
{
    printf("0:退出\n");
    printf("1:头删\n");
    printf("2:中插\n");
    printf("3:中删\n");
    printf("4:尾插\n");
    printf("5:尾删\n");
    printf("6:打印\n");
    printf("7:读取文件\n");
    printf("8:写入文件\n");
    printf("9:排序\n\a");
}
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    st p;
    initialize(&p);
    int pos = 0;
    FILE* fp = fopen("students_data.txt", "r");
    if (fp == NULL)
    {
        perror("fopen");
        return 0;
    }
    if(setvbuf(fp, NULL, _IOFBF, 8192)!= 0) 
    { 
        perror("setvbuf");
        return -1;
    }
    int inport = 0;
    meau();
    while (scanf("%d", &inport) != EOF)
    {
        meau();
        switch (inport)
        {
            case EXITS:
                printf("退出成功!\n");
                return 0;
            case ONE:
                stuHeader_removal(&p);  
                break;
            case TWO:
                printf("请输入插入位置:"); scanf("%d", &pos);
                stuInsert_in_the_middle(&p, stuinport(), pos);
                break;
            case THREE:
                printf("请输入删除位置:"); scanf("%d", &pos);
                stuIntermediate_deletion(&p, pos);
                break;
            case FOUR:
                stuTail_insertion(&p, stuinport());
                break;
            case FIVE:
                stuTail_deletion(&p);
                break;
            case SIX:
                stuprint(&p);
                break;
            case SEVEN:
                Read_file(fp,&p);
                break;
            case EIGHT:
                fclose(fp);
                fp = NULL;
                FILE* fp = fopen("students_data.txt", "w");
                if (fp == NULL)
                {
                    perror("fopen");
                    return -1;
                }
                Write_file(fp, &p);
                break;
            case NINE:
                my_sort(&p, sorts());
                break;
            default:
                printf("输入错误，请重新输入!\n\a");
        }
    }
    fclose(fp);
    fp = NULL;
    free(p.arr);
    p.arr = NULL;
    printf("文件地址:students_data.txt");
    system("pause");
    return 0;
}