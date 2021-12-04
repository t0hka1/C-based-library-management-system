// 此处添加头文件
#include <stdio.h>
// 待添加其他头文件

typedef struct user
{
    char name[30];
    char ID[20];
    char password[30];
    int power; //power: 1=>super_user 2=>system_user 3=>normal_user 
}USER;


void sign_up();   //equal add normal_user

void sign_in(int power);

void list_user();

void del_user();

void add_system_user();   //super_user have the permission

