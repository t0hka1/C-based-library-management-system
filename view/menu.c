#include<stdio.h>
#include "menu.h"

// 首页菜单
void menu1(){
    printf("--------------------------------------------------------------------------------------------");
    printf("\n\n\n");
    printf("欢迎您，亲爱的用户！                                                                        ");
    printf("                                                                                            ");
    printf("                         欢迎使用图书管理系统                                               ");
    printf("                                                                                            ");
    printf("                                                                                            ");
    printf("                               1、注册                                                      ");
    printf("                               2、登录                                                      ");
    printf("                               3、随便逛逛                                                  ");
    printf("                               4、退出                                                      ");
    printf("                      请输入选项前的编号，按回车键结束                                      ");
    printf("--------------------------------------------------------------------------------------------");
}
// 登录界面菜单，后续自动判断身份
void menu2(){
    printf("--------------------------------------------------------------------------------------------");
    printf("\n\n\n");
    printf("欢迎您，亲爱的用户！                                                                        ");
    printf("                         请选择你的身份                                                     ");
    printf("                                                                                            ");
    printf("                                                                                            ");
    printf("                               1、超级管理员登录                                              ");
    printf("                               2、管理员登录                                                 ");
    printf("                               3、普通用户登录                                              ");
    printf("                               4、返回上一级                                                 ");
    printf("                      请输入选项前的编号，按回车键结束                                       ");
    printf("--------------------------------------------------------------------------------------------");
}
// root用户界面
void menu3(){

}
// manager用户界面
void menu4(){

}
// user用户界面
void menu5(){

}
// 游客菜单，暂不做
void menu6(){

}