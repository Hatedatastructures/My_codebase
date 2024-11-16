#include <stdio.h>
#include <windows.h>
//猜数字


void maeu()
{
    printf("—————— 猜数字 ———————");
    printf("_____1.开始游戏——————");
    printf("_____0.退出游戏——————");

}
int main()
{
    SetConsoleOutputCP(936);
    int inport = 0;
    do
    {
        maeu();
        scanf("%d ",&inport);
    } while (inport);
    return 0;
}