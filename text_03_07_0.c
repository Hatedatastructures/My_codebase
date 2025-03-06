//二叉树
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define NAME_MAX 20

typedef struct students
{
    uint32_t num;                                         /*学号*/
    char name[NAME_MAX];                                  /*姓名*/
} students;

typedef struct TreeNode 
{
    students data;
    struct TreeNode *_left_treeNode;
    struct TreeNode *_right_treeNode;
}TreeNode;


//计算二叉树的深度

//先序遍历二叉树

//中序遍历二叉树

//后序遍历二叉树

//计算二叉树的节点个数

//计算二叉树的叶子节点个数

//计算二叉树的第k层节点个数

//层序遍历二叉树

//判断是不是完全二叉树

//判断是不是满二叉树

//计算二叉树的最长路径长度

//镜像二叉树

//判断是不是一个二叉树是不是另一个二叉树的子树

//二叉树的合并

//检查二叉树是不是单值二叉树

int main()
{
    return 0;
}