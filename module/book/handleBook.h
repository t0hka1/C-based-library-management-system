#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <conio.h>

/*ϵͳͼ����Ϣ*/
typedef struct bookinfo {            
    char number[15];        //ͼ����
    char name[30];          //ͼ������
    char author[20];        //����
    char press[30];         //������ 
    char category[20];      //��� 
    float price;            //���� 
    int  quantity;          //�ݲ���
 	int  time;              //������
} BOOKINFO;

/*������鼮��Ϣ*/ 
typedef struct borrowed_book {
	char number[15];        //ͼ����
    char name[30];          //ͼ������
    char author[20];        //����
    char press[30];         //������
    char category[20];      //���
    float price;            //���� 
 	char account[30];       //������ID
} BORROWED_BOOK;

/*��̬����*/
typedef struct SeqList_info{
    BOOKINFO* books;
    int size;       //��Ч���ݵĸ���
    int capacity;   //����
}sl_info;
typedef struct SeqList_record{
    BORROWED_BOOK* books;
    int size;       //��Ч���ݵĸ���
    int capacity;   //����
}sl_record;


/*normal user*/
sl_info getBooklist();
sl_record getRecord();
void updata_booklist(sl_info new_booklist);
void updata_recordlist(sl_record new_recordlist);
void listBooks();
void printRecords();
void checkMyRecord(char *account);
void borrowBook(char *account);
void returnBook(char *account);
void searchBook();
void display_popularity();

/*system user*/
void modifyBook();
void addBook();
void delBook();