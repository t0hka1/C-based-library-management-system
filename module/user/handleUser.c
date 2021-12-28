#include "../book/handleBook.h"
#include "handleUser.h"
#include "handleUserTools.h"
#include "../../view/menu.h"
#include <ctype.h>
#define LEN_OF_ID 4
#define MIN_LEN_OF_PASSWORD 8

void sign_up(int power){
    char user_id[20];
    char user_password[30];
    char user_name[30];
    int flag_id, flag_password;
    fflush(stdin);
    printf("������������");
    gets(user_name);
    printf("��������Ҫע����˺�(��%dλ������ɣ���", LEN_OF_ID);
    gets(user_id);
    while(1){
        flag_id = 1;
        for(int i = 0; i < strlen(user_id); ++i){
            if(!isdigit(user_id[i]))
                flag_id = 0;
        }
        if(flag_id == 0 || strlen(user_id) != LEN_OF_ID){
            printf(":( �˺Ÿ�ʽ�������������룺");
            fflush(stdin);
            gets(user_id);
            continue;
        }
        if(!check_repeat_ID(user_id)){
            printf(":( �˺��ѱ�ע��,���������룺");
            fflush(stdin);
            gets(user_id);
        }else{
            break;
        }
    }
    printf("�����õ�¼����(�����ֺ���ĸ���, ����Ҫ��Ϊ%d~20λ)��", MIN_LEN_OF_PASSWORD);
    gets(user_password);
    while(1){
        flag_password= 1;
        for(int i = 0; i < strlen(user_password); ++i){
            if(!isalnum(user_password[i]))
                flag_password = 0;
        }
        if(strlen(user_password) >= MIN_LEN_OF_PASSWORD && flag_password == 1){
            FILE *fp;
            if(!(fp = fopen("data/infoUser.csv", "a"))){
                printf("\nerror: cannot open the file\n");
                exit(1);
            }
            fprintf(fp, "%s %s %s %d\n", user_id, user_password, user_name, power);
            fclose(fp);
            printf(":) ע��ɹ���");
            return;
        }else{
            fflush(stdin);
            printf(":( ���벻����Ҫ�����������ã�");
            gets(user_password);
        }  
    }
}

void sign_in(int power){
    int flag_checked, flag_continue = 1;
    char choice;
    char user_id[20];
    printf("�����������˺�:");
    gets(user_id);
    if(check_password(user_id, power)){
        switch(power){
            case 1:
                while (flag_continue){
                    system("cls");
                    menu3();
                    fflush(stdin);
                    choice=getch();
                    while(choice != '1' && choice != '2' && choice != '3' && choice != '4')
                        choice = getch();
                    if (choice == '1'){
                        list_user();
                        printf("�������������һ��");
                        getch();
                    }
                    else if (choice == '2'){
                        del_user();
                        printf("�������������һ��");   
                        getch();    
                    }
                    else if (choice == '3'){
                        add_system_user();
                        printf("�������������һ��");   
                        getch();
                    }
                    else if (choice == '4'){
                        flag_continue = 0;
                    }    
                }
                break;
            case 2:
                while (flag_continue){
                    system("cls");
                    menu4();
                    fflush(stdin);
                    choice = getch();
                    while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '6' && choice != '7')
                        choice = getch();
                    if (choice == '1') {
                        addBook();
                        printf("�������������һ��");
                        getch();
                    }
                    else if (choice == '2') {
                        delBook();
                        printf("�������������һ��");
                        getch();
                    }
                    else if (choice == '3') {
                        modifyBook();
                        printf("�������������һ��");
                        getch();
                    }
                    else if (choice == '4') {
                        searchBook();
                        printf("�������������һ��");
                        getch();
                    }
                    else if (choice == '5') {
                        listBooks();
                        printf("�������������һ��");
                        getch();
                    }
                    else if (choice == '6') {
                        list_user();
                        printf("�������������һ��");
                        getchar();
                    }
                    else if (choice == '7') {
                        printRecords();
                        printf("�������������һ��");
                        getch();
                    }
                    else if (choice == '8') {
                        flag_continue = 0;
                    }
                }
                break;
            case 3:
                while (flag_continue){
                    system("cls");
                    menu5();
                    fflush(stdin);
                    choice = getch();
                    while(choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != '6' && choice != '7')
                        choice = getch();
                    if (choice == '1'){
                        searchBook();
                        printf("�������������һ��");
                        getch();
                    }
                    else if (choice == '2'){
                        borrowBook(user_id);
                        printf("�������������һ��");   
                        getch();    
                    }
                    else if (choice == '3'){
                        returnBook(user_id);
                        printf("�������������һ��");   
                        getch();
                    }
                    else if (choice == '4'){
                        listBooks();
                        printf("�������������һ��");   
                        getch();
                    }
                    else if (choice == '5'){
                        display_popularity();
                        printf("�������������һ��");   
                        getch();
                    }
                    else if (choice == '6'){
                        checkMyRecord(user_id);
                        printf("�������������һ��");   
                        getch();
                    }
                    else if (choice == '7'){
                        flag_continue = 0;
                    }    
                }
        }
    }
    return;    
}

void list_user(){
    FILE *fp;
    USER user_temp;
    system("cls");
    if(!(fp = fopen("data/infoUser.csv", "r"))){
        printf("\nerror: cannot open the file\n");
        exit(1);
    }
    fseek(fp, OFFSET_USERLIST, SEEK_SET);
    while(!feof(fp)){
        if(fscanf(fp, "%s %s %s %d", user_temp.ID, user_temp.password, user_temp.name, &user_temp.power) == 4){
            printf("%s %s %s %d\n", user_temp.ID, user_temp.password, user_temp.name, user_temp.power);
        }
    }
    fclose(fp);
    return;
}

void del_user(){
    FILE *fp;
    USER userinfo[100];
    char del_id[20];
    int n,i;
    int usernumber;
    char choice;
    system("cls");
    while(1){
        fflush(stdin);
        printf("����Ҫɾ�����û�ID:");
        gets(del_id);
        if(!(fp = fopen("data/infoUser.csv", "r"))){
            printf("\nerror: cannot open the file\n");
            exit(1);
        }
        fseek(fp, OFFSET_USERLIST, SEEK_SET);
        usernumber=0;
        while(!feof(fp)){
            fscanf(fp,"%s %s %s %d\n",userinfo[usernumber].ID,userinfo[usernumber].password,userinfo[usernumber].name,&userinfo[usernumber].power);
            usernumber++;
        }
        fclose(fp);
        for ( n = 0; n < usernumber; n++){
            if (strcmp(userinfo[n].ID,del_id)==0){
                break;
            }
        }
        if (n >= usernumber)
            printf(":(û���ҵ����û�����Ϣ!\n");
        else{
            printf("�Ƿ�ȷ����Ҫɾ�����û�(Y/N):");
            while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
                choice = getch();
            printf("%c", choice);
            if (choice == 'Y' || choice == 'y'){
                for (i = n; i < usernumber-1; i++){
                    userinfo[i] = userinfo[i+1];
                }
                usernumber--;
                fp = fopen("data/infoUser.csv", "w");
                fprintf(fp,"�˺�   ����    ���� Ȩ��\n");
                for(n=0;n < usernumber;n++) 
                    fprintf(fp,"%s %s %s %d\n",userinfo[n].ID,userinfo[n].password,userinfo[n].name,userinfo[n].power);
                fclose(fp);
                printf("\n:) ɾ���ɹ�!\n");            
            }else{
                printf("\n:(���û�û�б�ɾ��!");
            }
        }
        printf("�Ƿ��������ɾ������(y/n):");
        choice = getchar();
        while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
            choice = getchar();
        if (choice == 'Y' || choice == 'y')
            continue;
        else
            break;
    }
    return;
}

void add_system_user(){   //super_user have the permission
    system("cls");
    sign_up(2);
}   
