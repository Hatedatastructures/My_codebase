/*双向链表例子*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <windows.h>

#define NAME_MAX 25
#define SEX_MAX 10
#define ADDRESS_MAX 100

#define NAME_MAX_S "%24s"
#define SEX_MAX_S "%9s"
#define ADDRESS_MAX_S "%99s"
static char* SEX_CHINA = "Chian";
// static char* SEX_ENGLISH = "English";
static uint32_t MAX_NUM = 120000;
static uint8_t MAX_AGE = 100;
static float MAX_GRADE_MAIN = 150.0f;
static float MAX_GRADE_SECONDARY =70.0f;
typedef struct subjects
{
    float Chinese;                                    /*语文*/
    float Math;                                       /*数学*/
    float English;                                    /*英语*/
    float politics;                                   /*政治*/
    float history;                                    /*历史*/
    float geography;                                  /*地理*/
    float biology;                                    /*生物*/
    float chemistry;                                  /*化学*/
    float physics;                                    /*物理*/
}subjects;
typedef struct students
{
    uint32_t num;                                         /*学号*/
    char name[NAME_MAX];                                  /*姓名*/
    uint8_t age;                                          /*年龄*/
    char sex[SEX_MAX];                                    /*性别*/
    uint64_t tel;                                         /*电话*/
    char address[ADDRESS_MAX];                            /*地址*/
    uint64_t identity_card;                               /*证号*/
    subjects grades;                                      /*成绩*/
} students;
typedef struct student_node
{
    students* data;
    struct student_node* prev;
    struct student_node* next;
}Sode;
typedef struct input
{
    char* Promptwords;
    char* Placeholders;
    void* address;
    void* limit;
    BOOL(*Enteralimit)(const void*, const void*);
}inputs;
typedef struct str
{
    const char* Placeholding;
    const void* Pointer_field;
    const void* pointer_field_two;
}strlist;
BOOL numjudgment(const void* num, const void* limit)
{
    if (limit != NULL)
    {
        if ((*(uint32_t*)num) <= *(uint32_t*)limit || *(uint32_t*)num != 0)
        {
            return TRUE;
        }
        else
        {
            printf("错误!,人数超过限制，限制人数：%u\n", *(uint32_t*)limit);
            return FALSE;
        }
    }
    else
    {
        if (*(uint32_t*)num == 0)
        {
            printf("错误!,人数不能为0\n");
            return FALSE;
        }
        else
        {
            return TRUE;
        }
    }
}
BOOL namejudgment(const void* name, const void* limit)
{
    char* strname = (char*)name;
    unsigned char strnames = (unsigned char)strname[0];
    if (limit != NULL)
    {
        for (uint8_t i = 0; i < strlen(strname); i++)
        {
            if ((strnames & 0xF0) == 0xE0)
            {
                if (strlen(strname) >= 3)
                {
                    return TRUE;
                }
            }
        }
    }
    else
    {
        for (uint8_t i = 0; i < strlen(strname); i++)
        {
            if ((strnames & 0xF0) == 0xE0)
            {
                if (strlen(strname) >= 3)
                {
                    return TRUE;
                }
            }
        }
    }
    return FALSE;
}
BOOL agejudgment(const void* age, const void* limit)
{
    if (limit != NULL)
    {
        if ((*(uint8_t*)age) <= *(uint8_t*)limit)
        {
            return TRUE;
        }
        else
        {
            printf("错误!,年龄超过限制，限制年龄：%u\n", *(uint8_t*)limit);
            return FALSE;
        }
    }
    else
    {
        if (*(uint8_t*)age == 0)
        {
            printf("错误!,年龄不能为0\n");
            return FALSE;
        }
        else
        {
            return TRUE;
        }
    }
}
BOOL sexjudgment(const void* sex, const void* limit)
{
    if (limit != NULL)
    {
        if (strcmp((char*)limit, "China") == 0)
        {
            if ((strcmp((char*)sex, "男") == 0) || (strcmp((char*)sex, "女") == 0))
            {
                return TRUE;
            }
            else
            {
                printf("错误!,性别只能为男或女\n");
                return FALSE;
            }
        }
        else if (strcmp((char*)limit, "Eenglish") == 0)
        {
            if ((strcmp((char*)sex, "man") == 0) || (strcmp((char*)sex, "woman") == 0))
            {
                return TRUE;
            }
            else
            {
                printf("错误!,性别只能为man或woman\n");
                return FALSE;
            }
        }
    }
    else
    {
        if (strcmp(sex, "男") == 0 || strcmp(sex, "女") == 0 || strcmp(sex, "man") == 0 || strcmp(sex, "woman") == 0)
        {
            return TRUE;
        }
        else
        {
            printf("错误!,性别只能为男或女\n");
            return FALSE;
        }
    }
    return FALSE;
}
BOOL teljudgment(const void* tel, const void* limit)
{
    uint64_t num = *(uint64_t*)tel;
    uint8_t len = 0;
    if (limit != NULL)
    {
        while (num > 0)
        {
            num /= 10;
            len++;
        }
        if (len != 11)
        {
            printf("错误!,电话号码必须为11位,当前%u位\n", len);
            return FALSE;
        }
        else
        {
            return TRUE;
        }
    }
    else
    {
        while (num > 0)
        {
            num /= 10;
            len++;
        }
        if (len != 11)
        {
            printf("错误!,电话号码必须为11位,当前%u位\n", len);
            return FALSE;
        }
        else
        {
            return TRUE;
        }
    }
}

BOOL IDnumberjudgment(const void* identity_card, const void* limit)
{
    uint64_t num = *(uint64_t*)identity_card;
    uint8_t len = 0;
    while (num > 0)
    {
        num /= 10;
        len++;
    }
    if (limit != NULL)
    {
        if (len != 18)
        {
            printf("错误!,身份证号必须为18位,当前%u位\n", len);
            return FALSE;
        }
        else
        {
            return TRUE;
        }
    }
    else
    {
        if (len != 18)
        {
            printf("错误!,身份证号必须为18位,当前%u位\n", len);
            return FALSE;
        }
        else
        {
            return TRUE;
        }
    }
}

BOOL MainSubjectjudgment(const void* grade, const void* limit)
{
    if (limit != NULL)
    {
        if ((*(float*)grade) <= *(float*)limit || *(float*)grade >= 0)
        {
            return TRUE;
        }
        else
        {
            printf("错误!,成绩超过限制，限制成绩：%.2f\n", *(float*)limit);
            return FALSE;
        }
    }
    else
    {
        if (*(float*)grade <= 0)
        {
            printf("错误!,成绩非法0\n");
            return FALSE;
        }
        else
        {
            return TRUE;
        }
    }
}
BOOL stuinputs(char* Promptwords, char* Placeholders, void* address)
{
    while (1)
    {
        printf("%s", Promptwords);
        int result = scanf(Placeholders, address);
        if (result == 1)
        {
            while (getchar() != '\n');
            return TRUE;
        }
        else
        {
            printf("输入错误!\n");
            while (getchar() != '\n');
            continue;
        }
    }
}
void stuinput(students* input)                            /*输入*/
{
    inputs inputs[] =
    {
        {"请输入学号：",    "%u",          &input->num,       &MAX_NUM              , numjudgment },
        {"请输入姓名：",    NAME_MAX_S,    input->name,        NULL                 , namejudgment},
        {"请输入年龄：",    "%hhu",        &input->age,       &MAX_AGE              , agejudgment},
        {"请输入性别：",    SEX_MAX_S,     input->sex,        SEX_CHINA             , sexjudgment},
        {"请输入电话：",    "%llu",        &input->tel,        NULL                 , teljudgment},
        {"请输入地址：",    ADDRESS_MAX_S, input->address,     NULL                 , NULL},
        {"请输入证号：",    "%llu",  &input->identity_card,    NULL                 , IDnumberjudgment},
        {"请输入语文成绩：", "%f",    &input->grades.Chinese,  &MAX_GRADE_MAIN      , MainSubjectjudgment},
        {"请输入数学成绩：", "%f",    &input->grades.Math,     &MAX_GRADE_MAIN      , MainSubjectjudgment},
        {"请输入英语成绩：", "%f",    &input->grades.English,  &MAX_GRADE_MAIN      , MainSubjectjudgment},
        {"请输入政治成绩：", "%f",    &input->grades.politics, &MAX_GRADE_SECONDARY , MainSubjectjudgment},
        {"请输入历史成绩：", "%f",    &input->grades.history,  &MAX_GRADE_SECONDARY , MainSubjectjudgment},
        {"请输入地理成绩：", "%f",    &input->grades.geography,&MAX_GRADE_SECONDARY , MainSubjectjudgment},
        {"请输入生物成绩：", "%f",    &input->grades.biology,  &MAX_GRADE_SECONDARY , MainSubjectjudgment},
        {"请输入化学成绩：", "%f",    &input->grades.chemistry,&MAX_GRADE_SECONDARY , MainSubjectjudgment},
        {"请输入物理成绩：", "%f",    &input->grades.physics,  &MAX_GRADE_SECONDARY , MainSubjectjudgment},
    };
    for (uint8_t i = 0; i < sizeof(inputs) / sizeof(inputs[0]); i++)
    {
        while (1)
        {
            if (stuinputs(inputs[i].Promptwords, inputs[i].Placeholders, (void*)inputs[i].address) != FALSE)
            {
                if (inputs[i].Enteralimit != NULL)
                {
                    if (inputs[i].Enteralimit(inputs[i].address, inputs[i].limit) == FALSE)
                    {
                        printf("输入无效！\n");
                        continue;
                    }
                }
                else
                {
                    break;
                }
            }
            break;
        }
    }
}

void Pointer_judgment(const void* judgment,const char* name)
{
    if (judgment == NULL)
    {
        if (name != NULL)
        {
            printf("%s 传入无效！\n", name);
        }
        else
        {
            printf(" 空指针错误！\n");
        }
        system("pause");
        exit(-1);
    }
}/*检查空指针*/
Sode* New_node()
{
    Sode* Node = (Sode*)malloc(sizeof(Sode));
    if(Node == NULL)
    {
        printf("内存分配失败！\n");
        exit(-1);
    }
    Node->data = (students*)malloc(sizeof(students));
    if (Node->data == NULL)
    {
        printf("内存分配失败！\n");
        exit(-1);
    }
    memset(Node->data, 0, sizeof(students));
    Node->prev = NULL;
    Node->next = NULL;
    return Node;
}/*新节点*/
void Head_insertion(Sode** head, Sode* Node)/*头插*/
{
    Pointer_judgment(head, "头插");
    Pointer_judgment(Node, "头插");
    if (*head == NULL)
    {
        *head = Node;
        Node->prev = NULL;
        Node->next = NULL;
    }
    else
    {
        (*head)->prev = Node;
        Node->next = *head;
        Node->prev = NULL;
        (*head) = Node;
    }
}/*头插*/
void Head_deletion(Sode** head)
{
    Pointer_judgment(head, "头删");
    if (*head != NULL)
    {
        (*head)->next->prev = NULL;
        Sode* Old_Nodes = (*head)->next;
        (*head)->next = NULL;
        free(*head);
        *head = Old_Nodes;
        printf("删除成功！\n");
    }
    else
    {
        printf("该链表为空,删除无效！\n");
        return;
    }
}/*头删*/
void Tail_insertion(Sode** head, Sode* Node)
{
    Pointer_judgment(head, "尾插");
    Pointer_judgment(Node, "尾插");
    if (*head == NULL)
    {
        *head = Node;
        Node->prev = NULL;
        Node->next = NULL;
    }
    else
    {
        Sode* current = *head;
        while (current->next != NULL)
        {
            current = current->next;
        }
        current->next = Node;
        Node->prev = current;
        Node->next = NULL;
    }
    printf("尾部插入成功！\n");
}/*尾插*/
void Tail_deletion(Sode** head)
{
    Pointer_judgment(head, "尾删");
    if (*head != NULL)
    {
        if ((*head)->next == NULL)
        {
            free(*head);
            *head = NULL;
        }
        else
        {
            Sode* Old_Nodes = *head;
            while (Old_Nodes->next->next != NULL)
            {
                Old_Nodes = Old_Nodes->next;
            }
            Old_Nodes->next->prev = NULL;
            free(Old_Nodes->next);
            Old_Nodes->next = NULL;
        }
        printf("删除成功！\n");
    }
    else
    {
        printf("该链表为空,无效删除！\n");
    }
}/*尾删*/

void Insert_middle(Sode** head, Sode* Node, uint32_t num)
{
    Pointer_judgment(head, "中间插入");
    Pointer_judgment(Node, "中间插入");
    if (*head == NULL)
    {
        *head = Node;
        Node->prev = NULL;
        Node->next = NULL;
    }
    else
    {
        Sode* current = *head;
        for (uint32_t i = 0; i < num; i++)
        {
            if (current->next == NULL)
            {
                printf("插入位置无效！\n");
                return;
            }
            current = current->next;
        }
        Node->next = current;
        Node->prev = current->prev;
        current->prev->next = Node;
        current->prev = Node;
    }
    printf("插入成功！\n");
}/*中间插入*/

void Delete_middle(Sode** head, uint32_t num)
{
    Pointer_judgment(head, "中间删除");
    if (*head == NULL)
    {
        printf("该链表为空,删除无效！\n");
    }
    else
    {
        Sode* current = *head;
        for (uint32_t i = 0; i < num; i++)
        {
            if (current->next == NULL)
            {
                printf("删除位置无效！\n");
                return;
            }
            current = current->next;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;
        free(current);
        current = NULL;
        printf("删除成功！\n");
    }
}/*中间删除*/

Sode* Sode_Find(Sode* head, uint32_t num)
{
    Pointer_judgment(head, "查找");
    Sode* current = head;
    for (uint32_t i = 0; i < num; i++)
    {
        if (current->next == NULL)
        {
            printf("查找位置无效！\n");
            return NULL;
        }
        current = current->next;
    }
    printf("查找成功！\n");
    return current;
}/*查找目标位置地址*/

BOOL Sode_printf(const Sode* head)
{
    if(head == NULL)
    {
        return FALSE;
    }
    int32_t result = 0;
    result = printf("学号:%u "
                    "姓名：%s"
                    "年龄：%u"
                    "性别：%s"
                    "电话：%llu"
                    "地址：%s"
                    "证号：%llu"
                    "语文：%.2f"
                    "数学：%.2f"
                    "英语：%.2f" 
                    "政治：%.2f" 
                    "历史：%.2f" 
                    "地理：%.2f" 
                    "生物：%.2f"
                    "化学：%.2f" 
                    "物理：%.2f\n",
                    head->data->num,
                    head->data->name,
                    head->data->age,
                    head->data->sex,
                    head->data->tel,
                    head->data->address,
                    head->data->identity_card,
                    head->data->grades.Chinese,
                    head->data->grades.Math,
                    head->data->grades.English,
                    head->data->grades.politics,
                    head->data->grades.history,
                    head->data->grades.geography,
                    head->data->grades.biology,
                    head->data->grades.chemistry,
                    head->data->grades.physics);
    if(result == 0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}/*打印*/

BOOL Sode_revise(Sode** head, uint32_t num)
{
    Pointer_judgment(head, "修改");
    Pointer_judgment(*head, "修改");
    Sode* current = *head;
    for (uint32_t i = 0; i < num; i++)
    {
        if (current->next == NULL)
        {
            printf("修改位置无效！\n");
            return FALSE;
        }
        current = current->next;
    }
    students* temporary = (students*)malloc(sizeof(students));
    Pointer_judgment(temporary, "修改");
    free(current->data);
    current->data = temporary;
    printf("修改成功！\n");
    return TRUE;
}/*修改指定位置数据*/

int64_t compare (const void* a, const void* b ,const char* c)
{
    strlist list[] = 
        {
            {"学号", &((students*)a)->num,              &((students*)b)->num},
            {"年龄", &((students*)a)->age,              &((students*)b)->age},
            {"性别", &((students*)a)->sex,              &((students*)b)->sex},
            {"证号", &((students*)a)->identity_card,    &((students*)b)->identity_card},
            {"语文", &((students*)a)->grades.Chinese,   &((students*)b)->grades.Chinese},
            {"数学", &((students*)a)->grades.Math,      &((students*)b)->grades.Math},
            {"英语", &((students*)a)->grades.English,   &((students*)b)->grades.English},
            {"政治", &((students*)a)->grades.politics,  &((students*)b)->grades.politics},
            {"历史", &((students*)a)->grades.history,   &((students*)b)->grades.history},
            {"地理", &((students*)a)->grades.geography, &((students*)b)->grades.geography},
            {"生物", &((students*)a)->grades.biology,   &((students*)b)->grades.biology},
            {"化学", &((students*)a)->grades.chemistry, &((students*)b)->grades.chemistry},
            {"物理", &((students*)a)->grades.physics,   &((students*)b)->grades.physics}
        };
    for (uint8_t i = 0; i < sizeof(list) / sizeof(list[0]); i++)
    {
        if (strcmp(list[i].Placeholding, c) == 0)
        {
            return (*(int64_t*)list[i].Pointer_field - *(uint64_t*)list[i].pointer_field_two);
        }
    }
    printf("输入排序字符不合法！\n");
    return INT64_MAX;
}
BOOL Insert_sorting(Sode** head, char* data)
{
    Pointer_judgment(head, "插入排序");
    if(*head == NULL)
    {
        return FALSE;
    }
    uint64_t list_count = 0;
    uint64_t list_counts = 0;
    Sode* Ephemeral_nodes = NULL;
    Sode* current = *head;
    uint8_t number = 0;
    Sode* count = *head;
    while(count->next != NULL)
    {
        count = count->next;
        list_count++;
    }
    while(current != NULL)
    {
        Sode* temp = Ephemeral_nodes;
        Sode* slow = NULL;
        if(Ephemeral_nodes == NULL ||compare(Ephemeral_nodes->data, current->data, data)!= INT64_MAX|| compare(Ephemeral_nodes->data, current->data, data) >= 0) /*头插*/
        {
            if(Ephemeral_nodes == NULL)
            {
                Ephemeral_nodes = current;
                Ephemeral_nodes->next = NULL;
                Ephemeral_nodes->prev = NULL;
                number = 1;
                list_counts++;
            }
            else
            {
                while(temp != NULL)
                {
                    slow = temp;
                    temp = temp->prev;
                    if(compare(temp->data, current->data, data) >= 0||compare(Ephemeral_nodes->data, current->data, data)!= INT64_MAX)
                    {
                        temp->prev = current;
                        temp->next = slow;
                        temp = temp->prev;/*防止重复插入*/
                        number = 1;
                        list_counts++;
                        break;
                    }
                }
                temp->prev = NULL;
            }
            if(number == 1)
            {
                printf("插入前部失败！\n");
                return FALSE;
            }
        }
        else
        {
            while(temp != NULL)
            {
                slow = temp ;
                temp = temp->next;
                if(compare(Ephemeral_nodes->next->data, current->data, data) <= 0||compare(Ephemeral_nodes->data, current->data, data)!= INT64_MAX)
                {
                    temp->next = current;
                    temp->prev = slow;
                    temp = temp->next;/*防止重复插入*/
                    list_counts++;
                    number = 1;
                    break;
                }
            }
            temp->next = NULL;
            if(number == 1)
            {
                printf("插入后部失败！\n");
                return FALSE;
            }
        }
        if(current->next != NULL)
        {
           current = current->next;
        }
    }
    if(list_counts != list_count)
    {
        printf("插入排序中bug！\n");
        return FALSE;
    }
    else
    {
        printf("插入排序成功！\n");
        *head = Ephemeral_nodes;
        return TRUE;
    }
    printf("插入排序成功！\n");
}/*插入排序*/


int main()
{
    uint64_t sum = sizeof(Sode);
    printf("sum = %llu\n", sum);
    return 0;
}