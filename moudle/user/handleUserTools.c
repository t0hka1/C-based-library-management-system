// 此处添加头文件
#include "handleUserTools.h"
#include "handleUser.h"
#include <stdio.h>
#include <string.h>
// 待添加其他头文件

int check_repeat_ID(char *id){
    FILE *fp;
    USER user[100];
    int flag=0,i,number=0;

    fp=fopen("../../src/infoUser.txt","r");
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