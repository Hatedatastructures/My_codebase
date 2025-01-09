#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <windows.h>

#define NAME_MAX 20                                     /*姓名*/
#define ADDRESS_MAX 100                                 /*地址*/
#define SEX_MAX 10                                      /*性别*/
#define Capacity_increase_multiple 2                    /*倍数*/
enum medu
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

// 定义函数指针类型
typedef int (*cmp_func_t)(const void*, const void*);


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

static cmp_func_t cmp_funcs[] = 
{
    NULL,           
    cmp_num,        
    cmp_name,      
    cmp_age,        
    cmp_sex,        
    cmp_tel,        
    cmp_address,    
    cmp_identity_card, 
    cmp_Chinese,    
    cmp_Math,       
    cmp_English,    
    cmp_politics,   
    cmp_history,    
    cmp_geography,  
    cmp_biology,    
    cmp_chemistry   
};                                                      //函数指针数组

void initialize(st* s)                                  /*初始化*/
{
    assert(s != NULL);
    const size_t INITIAL_CAPACITY = 10;
    
    s->arr = (stu*)malloc(sizeof(stu) * INITIAL_CAPACITY);
    if (s->arr == NULL)
    {
        fprintf(stderr, "内存分配失败: 无法分配 %zu 字节\n", sizeof(stu) * INITIAL_CAPACITY);
        exit(EXIT_FAILURE);
    }
    
    s->size = 0;
    s->capacity = INITIAL_CAPACITY;
    memset(s->arr, 0, sizeof(stu) * INITIAL_CAPACITY);  // 初始化内存
}


void Capacity(st* p)                                    /*增容*/
{
    assert(p != NULL);
    
    if (p->size < p->capacity) {
        return;
    }

    size_t new_capacity = p->capacity * Capacity_increase_multiple;
    if (new_capacity <= p->capacity) 
    {  // 检查溢出
        fprintf(stderr, "容量溢出: 当前容量 %zu, 新容量 %zu\n",p->capacity, new_capacity);
        exit(EXIT_FAILURE);
    }

    stu* new_arr = (stu*)realloc(p->arr, sizeof(stu) * new_capacity);
    if (new_arr == NULL)
    {
        fprintf(stderr, "内存重分配失败: 无法分配 %zu 字节\n",
                sizeof(stu) * new_capacity);
        exit(EXIT_FAILURE);
    }

    p->arr = new_arr;
    p->capacity = new_capacity;
    
    // 初始化新分配的内存
    memset(p->arr + p->size, 0, sizeof(stu) * (new_capacity - p->size));
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
    if (pos < 0 || pos > p->size) {
        printf("插入位置无效!\n");
        free(x);
        return;
    }
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
    if (pos < 0 || pos >= p->size) {
        printf("删除位置无效!\n");
        return;
    }
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
    assert(p != NULL);
    assert(fp != NULL);
    
    initialize(p);
    
    stu stg;
    int line_num = 1;
    char line[256];
    
    while (fgets(line, sizeof(line), fp)) 
    {
        // 跳过空行和注释行
        if (line[0] == '\n' || line[0] == '#') 
        {
            line_num++;
            continue;
        }

        int result = sscanf(line, "%d %19s %d %9s %lld %99s %lld %hhu %hhu %hhu %hhu %hhu %hhu %hhu %hhu",
            &stg.num, stg.name, &stg.age, stg.sex, &stg.tel, stg.address, &stg.identity_card,
            &stg.wing.Chinese, &stg.wing.Math, &stg.wing.English, &stg.wing.politics,
            &stg.wing.history, &stg.wing.geography, &stg.wing.biology, &stg.wing.chemistry);

        if (result != 15) 
        {
            fprintf(stderr, "文件格式错误: 第 %d 行\n", line_num);
            continue;
        }

        // 验证数据
        if (stg.age < 0 || stg.age > 150) 
        {
            fprintf(stderr, "年龄无效: 第 %d 行\n", line_num);
            continue;
        }

        p->arr[p->size] = stg;
        p->size++;
        Capacity(p);
        line_num++;
    }

    if (ferror(fp)) 
    {
        fprintf(stderr, "文件读取错误: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    printf("成功读取 %zu 条记录\n", p->size);
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
int safe_input(const char* prompt, const char* format, void* value) 
{
    while (1) {
        printf("%s", prompt);
        if (scanf(format, value) == 1) 
        {
            while (getchar() != '\n');
            return 1;
        }
        printf("输入无效，请重新输入!\n");

        while (getchar() != '\n');
    }
}

int validate_string(const char* str, size_t max_len) 
{
    return str && strlen(str) > 0 && strlen(str) < max_len;
}

stu* stuinport() 
{
    stu* stg = (stu*)malloc(sizeof(stu));
    if (!stg) 
    {
        perror("malloc");
        printf("内存申请失败!\n");
        system("pause");
        return NULL;
    }
    memset(stg, 0, sizeof(stu));
    printf("请输入学生信息:\n\a");
    struct {
        const char* prompt;
        const char* format;
        void* value;
        int (*validator)(void*);
        } fields[] = 
                {
                    {"学号:", "%d", &stg->num, NULL},
                    {"姓名:", "%19s", stg->name, (int(*)(void*))validate_string},
                    {"年龄:", "%d", &stg->age, NULL},
                    {"性别:", "%9s", stg->sex, (int(*)(void*))validate_string},
                    {"电话:", "%lld", &stg->tel, NULL},
                    {"地址:", "%99s", stg->address, (int(*)(void*))validate_string},
                    {"证号:", "%lld", &stg->identity_card, NULL},
                    {"语文:", "%hhu", &stg->wing.Chinese, NULL},
                    {"数学:", "%hhu", &stg->wing.Math, NULL},
                    {"英语:", "%hhu", &stg->wing.English, NULL},
                    {"政治:", "%hhu", &stg->wing.politics, NULL},
                    {"历史:", "%hhu", &stg->wing.history, NULL},
                    {"地理:", "%hhu", &stg->wing.geography, NULL},
                    {"生物:", "%hhu", &stg->wing.biology, NULL},
                    {"化学:", "%hhu", &stg->wing.chemistry, NULL}
                };
    for (size_t i = 0; i < sizeof(fields)/sizeof(fields[0]); i++) 
    {
        while (1) 
        {
            if (!safe_input(fields[i].prompt, fields[i].format, fields[i].value)) 
            {
                continue;
            }
            if (strcmp(fields[i].prompt, "年龄:") == 0) 
            {
                if (stg->age < 0 || stg->age > 150) 
                {
                    printf("年龄必须在0到150之间!\n");
                    continue;
                }
            }
            if (fields[i].validator && !fields[i].validator(fields[i].value)) 
            {
                printf("输入无效，请重新输入!\n");
                continue;
            }
            
            break;
        }
    }
    
    printf("输入成功!\n");
    return stg;
}
size_t sorts()
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
    size_t inport = 0;
    scanf("%zu", &inport);
    return inport;
}




void my_sort(st* p, size_t index)                          /*排序*/
{
    assert(p!= NULL);
    if(p->size == 0)
    {
        printf("当前没有学生信息,请先输入学生信息!\n");
        exit(-1);
    }
    
    // 检查索引是否有效
    if (index >= 1 && index <= 15 && cmp_funcs[index] != NULL) 
    {
        qsort(p->arr, p->size, sizeof(stu), cmp_funcs[index]);
        printf("排序成功!\n");
    } 
    else 
    {
        printf("输入错误，返回!\n");
    }
}


void display_menu() 
{
    printf("========== 学生管理系统 ==========\n");
    printf("1. 删除头部学生\n");
    printf("2. 插入学生到指定位置\n");
    printf("3. 删除指定位置学生\n");
    printf("4. 添加学生到末尾\n");
    printf("5. 删除末尾学生\n");
    printf("6. 显示所有学生信息\n");
    printf("7. 从文件加载数据\n");
    printf("8. 保存数据到文件\n");
    printf("9. 排序学生信息\n");
    printf("0. 退出系统\n");
    printf("==================================\n");
    printf("请选择操作 (0-9): ");
}
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    st p;
    initialize(&p);
    int pos = 0;
    FILE* fp = fopen("C:\\Users\\C1373\\Desktop\\students_data.txt", "r");
    if (fp == NULL)
    {
        printf("文件不存在,请创建文件!\n");
        system("pause");
    }
    if(setvbuf(fp, NULL, _IOFBF, 8192)!= 0) 
    { 
        perror("setvbuf");
        printf("缓存申请失败!\n");
        system("pause");
    }
    int inport = 0;
    display_menu();
    while (scanf("%d", &inport) != EOF)
    {
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
                {
                    fclose(fp);
                    fp = fopen("students_data.txt", "w");
                    if (fp == NULL)
                    {
                        perror("fopen");
                        printf("无法打开文件进行写入!\n");
                        system("pause");
                        break;
                    }
                    Write_file(fp, &p);
                    fclose(fp);
                    fp = NULL;
                }
                break;
            case NINE:
                my_sort(&p, sorts());
                break;
            default:
                printf("输入错误，请重新输入!\n\a");
        }
        display_menu();
    }
    fclose(fp);
    fp = NULL;
    free(p.arr);
    p.arr = NULL;
    printf("文件地址:students_data.txt");
    system("pause");
    return 0;
}