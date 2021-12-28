#include "handleUserTools.h"
#include "handleUser.h"

int check_repeat_ID(char *user_id){
    FILE *fp;
    USER user_temp;
    if(!(fp = fopen("data/infoUser.csv", "r"))){
        printf("\nerror: cannot open the file\n");
        exit(1);
    }
    fseek(fp, OFFSET_USERLIST, SEEK_SET);
    while(!feof(fp)){
        if(fscanf(fp, "%s %s %s %d", user_temp.ID, user_temp.password, user_temp.name, &user_temp.power) == 4){
            if(!strcmp(user_temp.ID, user_id))
                return 0;
        }
    }
    fclose(fp);
    return 1;
}

int check_password(char *user_id, int user_power){
    int flag_passed = 0;
    int try_time = 0;
    FILE *fp;
    char password[30];
    system("cls");
    while(!flag_passed){
        ++try_time;
        if(try_time == 1){
            printf("请输入密码：");
        }else if(try_time <= 3){
            printf("密码错误，请重新输入(您还有%d次机会)：", 4 - try_time);
        }else{
            printf("输入次数已达上限，请重新登陆！\n");
            break;
        }
        fflush(stdin);
        gets(password);
        if(!(fp = fopen("data/infoUser.csv", "r"))){
            printf("\nerror: cannot open the file\n");
            exit(1);
        }
        fseek(fp, OFFSET_USERLIST, SEEK_SET);
        while(!feof(fp)){
            USER user_temp;
            if(fscanf(fp, "%s %s %s %d", user_temp.ID, user_temp.password, user_temp.name, &user_temp.power) == 4){
                if (!strcmp(user_temp.ID, user_id) && !strcmp(user_temp.password, password) && user_temp.power == user_power){
                    flag_passed = 1;
                    printf("登录成功！");
                    break;
                }
            }
        }
        fclose(fp);
    }
    return flag_passed;
}
