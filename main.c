// 要包含的头文件
#include <stdio.h>

//#include "handleBook.h"
#include "moudle/user/handleUser.h"
#include "view/menu.h"
#include "toolkit/tool.h"


int main(){
    // 局部变量定义区
    int flag1=1,flag2=1,flag3;
    char choice1,choice2,choice3;


    // 函数调用逻辑区
	SetSize(92,30);

    while (flag1){
        system("cls");   //一个清除屏幕的操作
        menu1();
        choice1=getch();
        while(choice1!='1'&&choice1!='2'&&choice1!='3'&&choice1!='4')
            choice1=getch();

        // 注册模块，该分支只能注册普通用户
        if(choice1=='1'){
            system("cls");
            sign_up();  
        	getchar();
        }

        //登录模块 
        else if(choice1=='2'){
            while (flag2){
                system("cls");
                menu2();
                choice2=getch();
                while (choice2!='1'&&choice2!='2'&&choice2!='3'&&choice2!='4'){
                    // 超级管理员
                    if (choice2=="1"){
                        system("cls");
                        sign_in(1);
                        getchar();
                    }
                    // 管理员
                    else if(choice2=='2'){
                        system("cls");
                        sign_in(2);
                        getchar();
                    }
                    // 普通用户
                    else if (choice2=='3'){
                        system("cls");
                        sign_in(3);
                        getchar();
                    }
                    // 返回上一级
                    else if (choice2=='4'){
                        flag2=0;
                    }               
                }
            }
        }

        // 游客模式
        else if(choice1=='3'){

        }

        // 退出系统
        else if (choice1=='4'){
            flag1=0;
        }
    }    
}

