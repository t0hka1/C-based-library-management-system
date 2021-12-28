#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <conio.h>

/*系统图书信息*/
typedef struct bookinfo {            
    char number[15];        //图书编号
    char name[30];          //图书名称
    char author[20];        //作者
    char press[30];         //出版社 
    char category[20];      //类别 
    float price;            //单价 
    int  quantity;          //馆藏量
 	int  time;              //借阅数
} BOOKINFO;

/*借出的书籍信息*/ 
typedef struct borrowed_book {
	char number[15];        //图书编号
    char name[30];          //图书名称
    char author[20];        //作者
    char press[30];         //出版社
    char category[20];      //类别
    float price;            //单价 
 	char account[30];       //借书者ID
} BORROWED_BOOK;

/*动态数组*/
typedef struct SeqList_info{
    BOOKINFO* books;
    int size;       //有效数据的个数
    int capacity;   //容量
}sl_info;
typedef struct SeqList_record{
    BORROWED_BOOK* books;
    int size;       //有效数据的个数
    int capacity;   //容量
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