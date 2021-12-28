#include "handleBook.h"
#include "handleBookTools.h"
#define OFFSET_BOOKLIST 45
#define OFFSET_RECORDLIST 40

/*用数组储存书单*/
sl_info getBooklist(){
    sl_info booklist;
    SLInit_info(&booklist);
    FILE *fp = NULL;
    BOOKINFO temp;
    if(!(fp = fopen("data/library.csv", "r"))){
        printf("error: cannot open the file\n");
        exit(1);
    }
    fseek(fp, OFFSET_BOOKLIST, SEEK_SET);
    while(!feof(fp)){
        if(fscanf(fp,"%s %s %s %s %s %f %d %d",
                temp.number,
                temp.name,
                temp.author,
                temp.press,
                temp.category,
                &temp.price,
                &temp.quantity,
                &temp.time) == 8)
        SLPushBack_info(&booklist, temp);
    }
    fclose(fp);
    return booklist;
}

/*用数组储存借阅记录*/
sl_record getRecord(){
    sl_record recordlist;
    SLInit_record(&recordlist);
    FILE *fp = NULL;
    BORROWED_BOOK temp;
    if(!(fp = fopen("data/record_of_borrowing_books.csv", "r"))){
        printf("error: cannot open the file\n");
        exit(1);
    }
    fseek(fp, OFFSET_RECORDLIST, SEEK_SET);
    while(!feof(fp)){
        if(fscanf(fp,"%s %s %s %s %s %f %s",
                temp.number,
                temp.name,
                temp.author,
                temp.press,
                temp.category,
                &temp.price,
                temp.account) == 7)
        SLPushBack_record(&recordlist, temp);
    }
    fclose(fp);
    return recordlist;
}

/*更新书单信息*/
void updata_booklist(sl_info new_booklist){
    FILE *fp = NULL;
    if(!(fp = fopen("data/library.csv", "w"))){
        printf("error: cannot open the file\n");
        exit(1);
    }
    fprintf(fp, "编号 书名 作者 出版社 类型 价格 馆藏量 借阅数\n");
    for(int i = 0; i < new_booklist.size; ++i){
        fprintf(fp, "%s %s %s %s %s %.1f %d %d\n",
                new_booklist.books[i].number,
                new_booklist.books[i].name,
                new_booklist.books[i].author,
                new_booklist.books[i].press,
                new_booklist.books[i].category,
                new_booklist.books[i].price,
                new_booklist.books[i].quantity,
                new_booklist.books[i].time);
    }
    fclose(fp);
    return;
}

/*更新借阅记录信息*/
void updata_recordlist(sl_record new_recordlist){
    FILE *fp = NULL;
    if(!(fp = fopen("data/record_of_borrowing_books.csv", "w"))){
        printf("error: cannot open the file\n");
        exit(1);
    }
    fprintf(fp, "编号 书名 作者 出版社 类型 价格 借书者ID\n");
    for(int i = 0; i < new_recordlist.size; ++i){
        fprintf(fp, "%s %s %s %s %s %.1f %s\n",
                new_recordlist.books[i].number,
                new_recordlist.books[i].name,
                new_recordlist.books[i].author,
                new_recordlist.books[i].press,
                new_recordlist.books[i].category,
                new_recordlist.books[i].price,
                new_recordlist.books[i].account);
    }
    fclose(fp);
    return;
}

/*列举所有书籍信息*/
void listBooks(){
    sl_info booklist = getBooklist();
    system("cls");
    if(booklist.size == 0){
        printf("\n暂无图书信息!");
        return;
    }
    printf("|---------------------------------图书信息---------------------------------|\n");
    printf("| 编号    书名     作者      出版社       类别      单价    馆藏量    借阅数 |\n");
    printf("|                                                                         |\n");
    for(int i = 0; i < booklist.size; ++i){
        printf("|%s，%s，%s，%s，%s，%.1f，%d，%d|\n",
            booklist.books[i].number,
            booklist.books[i].name, 
            booklist.books[i].author, 
            booklist.books[i].press,
            booklist.books[i].category, 
            booklist.books[i].price, 
            booklist.books[i].quantity,
            booklist.books[i].time);
    }
    return;
}

/*输出所有的借阅信息*/
void printRecords(){
    sl_record recordlist = getRecord();
    system("cls");
    for(int i = 0; i < recordlist.size; ++i){
        printf("%s %s %s %s %s %.1f %s\n",
                recordlist.books[i].number,
                recordlist.books[i].name,
                recordlist.books[i].author,
                recordlist.books[i].press,
                recordlist.books[i].category,
                recordlist.books[i].price,
                recordlist.books[i].account);
    }
    return;
}

/*查看本人的借阅记录*/
void checkMyRecord(char *account){
    sl_record recordlist = getRecord();
    int cnt = 0;
    system("cls");
    printf("--编号----书名----作者----出版社----类别----单价--\n");
    for(int i = 0; i < recordlist.size; ++i){
        if(!strcmp(recordlist.books[i].account, account)){
            ++cnt;
            printf("%s, %s, %s, %s, %s, %.1f\n",
                    recordlist.books[i].number,
                    recordlist.books[i].name,
                    recordlist.books[i].author,
                    recordlist.books[i].press,
                    recordlist.books[i].category,
                    recordlist.books[i].price);
        }
    }
    if(cnt == 0){
        printf("----------------暂 无 借 阅 记 录-----------------\n");
    }else{
        printf("------------您 共 有 %d 条 借 阅 记 录-------------\n", cnt);
    }
    return;
}

/*借书操作*/
void borrowBook(char *account){
    sl_info booklist = getBooklist();
    char target[30];
    FILE* fp = NULL;
    int flag_continue = 1;
    int flag_borrowed = 0;
    char judge;
    system("cls");
    while(flag_continue){
        printf("输入要借阅的图书编号或书名:");
        fflush(stdin);
        scanf("%s", target);
        for(int i = 0;i < booklist.size; ++i){
            if((!strcmp(booklist.books[i].number, target) || !strcmp(booklist.books[i].name, target)) && booklist.books[i].quantity > 0){
                --booklist.books[i].quantity;
                ++booklist.books[i].time;
                updata_booklist(booklist); //更新书单信息
                if(!(fp = fopen("data/record_of_borrowing_books.csv", "a"))){ //添加借阅信息
                    printf("error: cannot open the file\n");
                    exit(1);
                }
                fprintf(fp,"%s %s %s %s %s %.1f %s\n",
                            booklist.books[i].number,
                            booklist.books[i].name,
                            booklist.books[i].author,
                            booklist.books[i].press,
                            booklist.books[i].category,
                            booklist.books[i].price,
                            account);
                fclose(fp);
                printf(":) 借书成功！\n");
                flag_borrowed = 1;
                break;
            }
        } 
        if(!flag_borrowed)
            printf(":( 借书失败！\n");
        printf("是否继续借书？(输入'y'或'n'):");
        LOOP:fflush(stdin);
        judge = getchar();
        if(judge == 'n'){
            flag_continue = 0;
        }else if(judge == 'y'){
            flag_borrowed = 0;
        }else{
            printf(":( 无效输入！请重新输入：");
            goto LOOP;
        }   
    }
    return;
}

/*还书操作*/
void returnBook(char *account){
    sl_info booklist = getBooklist();
    sl_record recordlist = getRecord();
    char target_number[15];
    int flag_returned = 0;
    int flag_continue = 1;
    char judge;
    system("cls");
    fflush(stdin);
    while(flag_continue){
        printf("请输入您需要归还的图书编号:");
        fflush(stdin);
        scanf("%s", target_number);
        for(int i = 0; i < recordlist.size; ++i){ //在借阅信息中查删
            if(!strcmp(recordlist.books[i].account, account) && !strcmp(recordlist.books[i].number, target_number)){
                for(int j = i; j < recordlist.size - 1; ++j){
                    recordlist.books[j] = recordlist.books[j + 1];
                }
                recordlist.size--;
                updata_recordlist(recordlist);
                flag_returned = 1;
                printf(":) 还书成功！\n");
                break;
            }
        }
        if(flag_returned){ //增加该书的库存数
            for(int i = 0; i < booklist.size; ++i){
                if(!strcmp(target_number, booklist.books[i].number)){
                    booklist.books[i].quantity++;
                    updata_booklist(booklist);
                }
            }
        }else{
            printf(":( 找不到您的借书记录！\n");
        }
        printf("是否继续还书？(输入'y'或'n'):");
        LOOP:fflush(stdin);
        judge = getchar();
        if(judge == 'n'){
            flag_continue = 0;
        }else if(judge == 'y'){
            flag_returned = 0;
        }else{
            printf(":( 无效输入！请重新输入：");
            goto LOOP;
        }
    }       
    return;
}

/*查找图书*/
void searchBook(){
    sl_info booklist = getBooklist();
    char target[30];
    int flag_searched = 0;
    int flag_continue = 1;
    char judge;
    system("cls");
    while(flag_continue){
        printf("请输入您要查询的图书编号或书名：");
        fflush(stdin);
        scanf("%s", target);
        for(int i = 0; i < booklist.size; ++i){
            if(!strcmp(target, booklist.books[i].name) || !strcmp(target, booklist.books[i].number)){
                printf("|编号     书名     作者     出版社     类别     单价   馆藏量   借阅数|\n");
                printf("|%s，%s，%s，%s，%s，%.1f，%d，%d|\n",
                        booklist.books[i].number,
                        booklist.books[i].name, 
                        booklist.books[i].author, 
                        booklist.books[i].press,
                        booklist.books[i].category, 
                        booklist.books[i].price, 
                        booklist.books[i].quantity,
                        booklist.books[i].time);
                flag_searched = 1;
            }
        }
        if(!flag_searched)
            printf(":( 抱歉，没有找到符合您要求的书籍!\n");
        printf("是否继续查找？(输入'y'或'n'):");
        LOOP:fflush(stdin);
        judge = getchar();
        if(judge == 'n'){
            flag_continue = 0;
        }else if(judge == 'y'){
            flag_searched = 0;
        }else{
            printf(":( 无效输入！请重新输入：");
            goto LOOP;
        }
    }
    return;
}

/*图书受欢迎度排行榜*/
int timeCompare(const void* book_1, const void* book_2){ //定义qsort()中的比较函数
    BOOKINFO *temp_1 = (BOOKINFO *) book_1;
    BOOKINFO *temp_2 = (BOOKINFO *) book_2;
    return temp_1->time - temp_2->time;
}
void display_popularity(){
    sl_info booklist = getBooklist();
    system("cls");
    qsort((void *)booklist.books, booklist.size, sizeof(BOOKINFO), timeCompare);
    printf("|编号     书名     作者     出版社     类别     单价   馆藏量   借阅数|\n");
    for(int i = 0; i < booklist.size; ++i){
        printf("|%s，%s，%s，%s，%s，%.1f，%d，%d|\n",
                booklist.books[i].number,
                booklist.books[i].name, 
                booklist.books[i].author, 
                booklist.books[i].press,
                booklist.books[i].category, 
                booklist.books[i].price, 
                booklist.books[i].quantity,
                booklist.books[i].time);
    }
    return;    
}

/*删除书本信息*/
void delBook(){
    char search[20];
    int n, i;
    FILE* p1;
    char choice;
    BOOKINFO bookinfo[100];
    int booknumber;
    system("cls");
    while (1){
        fflush(stdin);
        printf("输入要删除的书本名称:");
        gets(search);
        p1 = fopen("data/library.csv", "r");
        fseek(p1, OFFSET_BOOKLIST, SEEK_SET);
        booknumber = 0;
        while (!feof(p1)){
            fscanf(p1, "%s %s %s %s %s %f %d %d\n",
                bookinfo[booknumber].number, bookinfo[booknumber].name, bookinfo[booknumber].author,
                bookinfo[booknumber].press, bookinfo[booknumber].category,
                &bookinfo[booknumber].price, &bookinfo[booknumber].quantity, &bookinfo[booknumber].time);
            booknumber++;
        }
        fclose(p1);
        if (bookinfo[0].quantity == 0){
            printf("书库中没有任何信息!\n");
            printf("按任意键回到主菜单!\n");
            getch();
            break;
        }else{
            for (n = 0; n < booknumber; n++)
                if (strcmp(bookinfo[n].name, search) == 0){
                    break;
                }
            if (n >= booknumber)
                printf(":( 没有查找该书的任何信息!\n");
            else{
                printf("是否确认需要删除该条书目(Y/N):");
                choice = getch();
                while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
                    choice = getch();
                printf("%c", choice);
                if (choice == 'Y' || choice == 'y'){
                    for (i = n; i < booknumber - 1; i++)
                        bookinfo[i] = bookinfo[i + 1];
                    booknumber--;
                    p1 = fopen("data/library.csv", "w");
                    fprintf(p1, "编号 书名 作者 出版社 类型 价格 借书者ID\n");
                    for (n = 0; n < booknumber; n++)
                        fprintf(p1, "%s %s %s %s %s %.1f %d %d \n",
                            bookinfo[n].number, bookinfo[n].name, bookinfo[n].author,
                            bookinfo[n].press, bookinfo[n].category, bookinfo[n].price, bookinfo[n].quantity, bookinfo[n].time);
                    fclose(p1);
                    printf("\n:) 删除成功!\n");
                }
                else
                    printf("\n该条书目没有被删除!\n");
            }
            printf("是否继续进行删除操作(y/n):");
            choice = getchar();
            while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
                choice = getchar();
            if (choice == 'Y' || choice == 'y')
                continue;
            else
                break;
        }
    }
    return;
}

/*修改图书信息*/
void modifyBook(){
    char change[20];
    int n, i;
    FILE* p1;
    char choice;
    int booknumber;
    BOOKINFO changebook;
    BOOKINFO bookinfo[100];
    system("cls");
    while (1){
        fflush(stdin);
        printf("输入要更改的书本名称：");
        gets(change);
        p1 = fopen("data/library.csv", "r");
        fseek(p1, OFFSET_BOOKLIST, SEEK_SET);
        booknumber = 0;
        while (!feof(p1)) {
            fscanf(p1, "%s %s %s %s %s %f %d %d \n",
                bookinfo[booknumber].number, bookinfo[booknumber].name, bookinfo[booknumber].author,
                bookinfo[booknumber].press, bookinfo[booknumber].category,
                &bookinfo[booknumber].price, &bookinfo[booknumber].quantity, &bookinfo[booknumber].time);
            booknumber++;
        }
        fclose(p1);
        if (bookinfo[0].quantity == 0){
            printf("书库中没有任何信息!\n\n");
            printf("按任意键回到主菜单!\n\n");
            getch();
            break;
        }else{
            for (n = 0; n < booknumber; n++)
                if (strcmp(bookinfo[n].name, change) == 0){
                    break;
                }
            if (n >= booknumber)
                printf(":( 没有该书的任何信息!\n");
            else{
                fflush(stdin);
                printf("请输入书本编号;");
                gets(changebook.number);
                printf("请输入更改后的书名:");
                gets(changebook.name);
                printf("请输入作者:");
                gets(changebook.author);
                printf("请输入出版社:");
                gets(changebook.press);
                printf("请输入类别:");
                gets(changebook.category);
                printf("请输入价格:");
                scanf("%f", &changebook.price);
                printf("请输入馆藏量:");
                scanf("%d", &changebook.quantity);
                printf("请输入借阅次数:");
                scanf("%d", &changebook.time);
                fflush(stdin);
                printf("是否更改该条书目(y/n):");
                choice = getchar();
                while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
                    choice = getchar();
                if (choice == 'Y' || choice == 'y'){
                    bookinfo[n] = changebook;
                    p1 = fopen("data/library.csv", "w");
                    fprintf(p1, "编号 书名 作者 出版社 类型 价格 借书者ID\n");
                    for (n = 0; n < booknumber; n++)
                        fprintf(p1, "%s %s %s %s %s %.1f %d %d \n",
                            bookinfo[n].number, bookinfo[n].name, bookinfo[n].author,
                            bookinfo[n].press, bookinfo[n].category, bookinfo[n].price, bookinfo[n].quantity, bookinfo[n].time);
                    fclose(p1);
                    printf(":) 更改成功！\n");
                }else
                    printf("\n该条书目没有被更改!\n");
                printf("是否继续进行删除操作(y/n):");
                choice = getchar();
                while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
                    choice = getchar();
                if (choice == 'Y' || choice == 'y'){
                    getch();
                    continue; 
                }else
                    break;
            }
        }
    }
    return;
}

/*增加图书*/
int check_repeat_number(char *book_number){
    sl_info booklist = getBooklist();
    int i;
    for(i = 0; i < booklist.size;++i){
        if(!strcmp(book_number, booklist.books[i].number)){
            break;
        }
    }
    if(i == booklist.size){
        return 1;
    }else{
        return 0;
    }
}
void addBook(){
    char choice;
    FILE* p1;
    BOOKINFO newbook;
    int flag;
    system("cls");
    while (1){
        flag = 0;
        fflush(stdin);
        printf("请输入图书编号:");
        scanf("%s", newbook.number);
        while(1){
            if(!check_repeat_number(newbook.number)){
                printf(":( 图书编号已存在,请重新输入：");
                fflush(stdin);
                gets(newbook.number);
            }else{
                break; 
            } 
        }
        fflush(stdin);
        printf("请输入书名:");
        scanf("%s", newbook.name);
        printf("请输入作者:");
        scanf("%s", newbook.author);
        printf("请输入出版社:");
        scanf("%s", newbook.press);
        printf("请输入类别:");
        scanf("%s", newbook.category);
        printf("请输入价格:");
        scanf("%f", &newbook.price);
        printf("请输入馆藏量:");
        scanf("%d", &newbook.quantity);
        printf("请输入借阅次数(新书输入0):");
        scanf("%d", &newbook.time);
        fflush(stdin);
        printf("是否保存该条书目(y/n):");
        choice = getchar();
        while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
            choice = getchar();
        if (choice == 'Y' || choice == 'y'){
            p1 = fopen("data/library.csv", "a");
            fprintf(p1, "%s %s %s %s %s %.1f %d %d \n",
                newbook.number, newbook.name, newbook.author, newbook.press,
                newbook.category, newbook.price, newbook.quantity, newbook.time);
            fclose(p1);
            printf(":) 添加成功!\n");
        }else{
            printf("\n本条书目未保存!\n");
        }
        printf("是否继续添加书目(y/n):");
        choice = getchar();
        while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
            choice = getchar();
        if (choice == 'Y' || choice == 'y' || flag == 1)
            continue;
        else
            break;
    }
    return;
}