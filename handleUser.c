// 此处添加头文件
#include "handleUser.h"
#include <stdio.h>
#include <string.h>
// 待添加其他头文件


int check_repeat_ID(char *id){
    FILE *fp;
    USER user[100];
    int flag=0,i,number=0;

    fp=fopen("infoUser.txt","r");
    while (!feof(fp)){
        fscanf(fp,"%s %s %s %d\n",user[number].ID,user[number].password,user[number].name,&user[number].power);
        number++;
    }
    fclose(fp);
    for (i = 0; i < number; i++)
    {
        if (strcmp(user[i].ID,id)==0){
            flag=1;
            break;
        }
    }
	if (flag){
		return 1;
    }else{
        return 0;
    }
}

void sign_up(){     // add normal_user
    // 局部变量定义区
    int flag=1;
    FILE *fp;
    USER user;

    while (flag){
    	system("cls");
        printf("请输入你想注册的ID:");
        gets(user.ID);

        // 如果已注册
        // check_repeat_ID待完善
        if (check_repeat_ID(user.ID)){
            printf("该ID已被注册！请重新注册\n");
			printf("按任意键重新注册\n\n");
			getch();
			flag=1;            
        }else{
            flag=0;
            printf("输入您的密码(不要告知他人):");
			gets(user.password);
            printf("输入您的姓名:");
			gets(user.name);
            user.power=3;
            fp=fopen("infoUser.txt","a");
            fprintf(fp,"%s %s %s %d\n",user.ID,user.password,user.name,user.power);
            fclose(fp);
			printf("\n您的账户已注册成功！\n");
            printf("按任意键回到主菜单");
            getchar();
        }
    }
}   

void sign_in(){

}

void list_user(){

}

void del_user(){

}

void add_system_user(){   //super_user have the permission

}   

 