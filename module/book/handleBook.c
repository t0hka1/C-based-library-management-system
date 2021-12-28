#include "handleBook.h"
#include "handleBookTools.h"
#define OFFSET_BOOKLIST 45
#define OFFSET_RECORDLIST 40

/*�����鴢���鵥*/
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

/*�����鴢����ļ�¼*/
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

/*�����鵥��Ϣ*/
void updata_booklist(sl_info new_booklist){
    FILE *fp = NULL;
    if(!(fp = fopen("data/library.csv", "w"))){
        printf("error: cannot open the file\n");
        exit(1);
    }
    fprintf(fp, "��� ���� ���� ������ ���� �۸� �ݲ��� ������\n");
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

/*���½��ļ�¼��Ϣ*/
void updata_recordlist(sl_record new_recordlist){
    FILE *fp = NULL;
    if(!(fp = fopen("data/record_of_borrowing_books.csv", "w"))){
        printf("error: cannot open the file\n");
        exit(1);
    }
    fprintf(fp, "��� ���� ���� ������ ���� �۸� ������ID\n");
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

/*�о������鼮��Ϣ*/
void listBooks(){
    sl_info booklist = getBooklist();
    system("cls");
    if(booklist.size == 0){
        printf("\n����ͼ����Ϣ!");
        return;
    }
    printf("|---------------------------------ͼ����Ϣ---------------------------------|\n");
    printf("| ���    ����     ����      ������       ���      ����    �ݲ���    ������ |\n");
    printf("|                                                                         |\n");
    for(int i = 0; i < booklist.size; ++i){
        printf("|%s��%s��%s��%s��%s��%.1f��%d��%d|\n",
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

/*������еĽ�����Ϣ*/
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

/*�鿴���˵Ľ��ļ�¼*/
void checkMyRecord(char *account){
    sl_record recordlist = getRecord();
    int cnt = 0;
    system("cls");
    printf("--���----����----����----������----���----����--\n");
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
        printf("----------------�� �� �� �� �� ¼-----------------\n");
    }else{
        printf("------------�� �� �� %d �� �� �� �� ¼-------------\n", cnt);
    }
    return;
}

/*�������*/
void borrowBook(char *account){
    sl_info booklist = getBooklist();
    char target[30];
    FILE* fp = NULL;
    int flag_continue = 1;
    int flag_borrowed = 0;
    char judge;
    system("cls");
    while(flag_continue){
        printf("����Ҫ���ĵ�ͼ���Ż�����:");
        fflush(stdin);
        scanf("%s", target);
        for(int i = 0;i < booklist.size; ++i){
            if((!strcmp(booklist.books[i].number, target) || !strcmp(booklist.books[i].name, target)) && booklist.books[i].quantity > 0){
                --booklist.books[i].quantity;
                ++booklist.books[i].time;
                updata_booklist(booklist); //�����鵥��Ϣ
                if(!(fp = fopen("data/record_of_borrowing_books.csv", "a"))){ //��ӽ�����Ϣ
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
                printf(":) ����ɹ���\n");
                flag_borrowed = 1;
                break;
            }
        } 
        if(!flag_borrowed)
            printf(":( ����ʧ�ܣ�\n");
        printf("�Ƿ�������飿(����'y'��'n'):");
        LOOP:fflush(stdin);
        judge = getchar();
        if(judge == 'n'){
            flag_continue = 0;
        }else if(judge == 'y'){
            flag_borrowed = 0;
        }else{
            printf(":( ��Ч���룡���������룺");
            goto LOOP;
        }   
    }
    return;
}

/*�������*/
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
        printf("����������Ҫ�黹��ͼ����:");
        fflush(stdin);
        scanf("%s", target_number);
        for(int i = 0; i < recordlist.size; ++i){ //�ڽ�����Ϣ�в�ɾ
            if(!strcmp(recordlist.books[i].account, account) && !strcmp(recordlist.books[i].number, target_number)){
                for(int j = i; j < recordlist.size - 1; ++j){
                    recordlist.books[j] = recordlist.books[j + 1];
                }
                recordlist.size--;
                updata_recordlist(recordlist);
                flag_returned = 1;
                printf(":) ����ɹ���\n");
                break;
            }
        }
        if(flag_returned){ //���Ӹ���Ŀ����
            for(int i = 0; i < booklist.size; ++i){
                if(!strcmp(target_number, booklist.books[i].number)){
                    booklist.books[i].quantity++;
                    updata_booklist(booklist);
                }
            }
        }else{
            printf(":( �Ҳ������Ľ����¼��\n");
        }
        printf("�Ƿ�������飿(����'y'��'n'):");
        LOOP:fflush(stdin);
        judge = getchar();
        if(judge == 'n'){
            flag_continue = 0;
        }else if(judge == 'y'){
            flag_returned = 0;
        }else{
            printf(":( ��Ч���룡���������룺");
            goto LOOP;
        }
    }       
    return;
}

/*����ͼ��*/
void searchBook(){
    sl_info booklist = getBooklist();
    char target[30];
    int flag_searched = 0;
    int flag_continue = 1;
    char judge;
    system("cls");
    while(flag_continue){
        printf("��������Ҫ��ѯ��ͼ���Ż�������");
        fflush(stdin);
        scanf("%s", target);
        for(int i = 0; i < booklist.size; ++i){
            if(!strcmp(target, booklist.books[i].name) || !strcmp(target, booklist.books[i].number)){
                printf("|���     ����     ����     ������     ���     ����   �ݲ���   ������|\n");
                printf("|%s��%s��%s��%s��%s��%.1f��%d��%d|\n",
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
            printf(":( ��Ǹ��û���ҵ�������Ҫ����鼮!\n");
        printf("�Ƿ�������ң�(����'y'��'n'):");
        LOOP:fflush(stdin);
        judge = getchar();
        if(judge == 'n'){
            flag_continue = 0;
        }else if(judge == 'y'){
            flag_searched = 0;
        }else{
            printf(":( ��Ч���룡���������룺");
            goto LOOP;
        }
    }
    return;
}

/*ͼ���ܻ�ӭ�����а�*/
int timeCompare(const void* book_1, const void* book_2){ //����qsort()�еıȽϺ���
    BOOKINFO *temp_1 = (BOOKINFO *) book_1;
    BOOKINFO *temp_2 = (BOOKINFO *) book_2;
    return temp_1->time - temp_2->time;
}
void display_popularity(){
    sl_info booklist = getBooklist();
    system("cls");
    qsort((void *)booklist.books, booklist.size, sizeof(BOOKINFO), timeCompare);
    printf("|���     ����     ����     ������     ���     ����   �ݲ���   ������|\n");
    for(int i = 0; i < booklist.size; ++i){
        printf("|%s��%s��%s��%s��%s��%.1f��%d��%d|\n",
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

/*ɾ���鱾��Ϣ*/
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
        printf("����Ҫɾ�����鱾����:");
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
            printf("�����û���κ���Ϣ!\n");
            printf("��������ص����˵�!\n");
            getch();
            break;
        }else{
            for (n = 0; n < booknumber; n++)
                if (strcmp(bookinfo[n].name, search) == 0){
                    break;
                }
            if (n >= booknumber)
                printf(":( û�в��Ҹ�����κ���Ϣ!\n");
            else{
                printf("�Ƿ�ȷ����Ҫɾ��������Ŀ(Y/N):");
                choice = getch();
                while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
                    choice = getch();
                printf("%c", choice);
                if (choice == 'Y' || choice == 'y'){
                    for (i = n; i < booknumber - 1; i++)
                        bookinfo[i] = bookinfo[i + 1];
                    booknumber--;
                    p1 = fopen("data/library.csv", "w");
                    fprintf(p1, "��� ���� ���� ������ ���� �۸� ������ID\n");
                    for (n = 0; n < booknumber; n++)
                        fprintf(p1, "%s %s %s %s %s %.1f %d %d \n",
                            bookinfo[n].number, bookinfo[n].name, bookinfo[n].author,
                            bookinfo[n].press, bookinfo[n].category, bookinfo[n].price, bookinfo[n].quantity, bookinfo[n].time);
                    fclose(p1);
                    printf("\n:) ɾ���ɹ�!\n");
                }
                else
                    printf("\n������Ŀû�б�ɾ��!\n");
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
    }
    return;
}

/*�޸�ͼ����Ϣ*/
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
        printf("����Ҫ���ĵ��鱾���ƣ�");
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
            printf("�����û���κ���Ϣ!\n\n");
            printf("��������ص����˵�!\n\n");
            getch();
            break;
        }else{
            for (n = 0; n < booknumber; n++)
                if (strcmp(bookinfo[n].name, change) == 0){
                    break;
                }
            if (n >= booknumber)
                printf(":( û�и�����κ���Ϣ!\n");
            else{
                fflush(stdin);
                printf("�������鱾���;");
                gets(changebook.number);
                printf("��������ĺ������:");
                gets(changebook.name);
                printf("����������:");
                gets(changebook.author);
                printf("�����������:");
                gets(changebook.press);
                printf("���������:");
                gets(changebook.category);
                printf("������۸�:");
                scanf("%f", &changebook.price);
                printf("������ݲ���:");
                scanf("%d", &changebook.quantity);
                printf("��������Ĵ���:");
                scanf("%d", &changebook.time);
                fflush(stdin);
                printf("�Ƿ���ĸ�����Ŀ(y/n):");
                choice = getchar();
                while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
                    choice = getchar();
                if (choice == 'Y' || choice == 'y'){
                    bookinfo[n] = changebook;
                    p1 = fopen("data/library.csv", "w");
                    fprintf(p1, "��� ���� ���� ������ ���� �۸� ������ID\n");
                    for (n = 0; n < booknumber; n++)
                        fprintf(p1, "%s %s %s %s %s %.1f %d %d \n",
                            bookinfo[n].number, bookinfo[n].name, bookinfo[n].author,
                            bookinfo[n].press, bookinfo[n].category, bookinfo[n].price, bookinfo[n].quantity, bookinfo[n].time);
                    fclose(p1);
                    printf(":) ���ĳɹ���\n");
                }else
                    printf("\n������Ŀû�б�����!\n");
                printf("�Ƿ��������ɾ������(y/n):");
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

/*����ͼ��*/
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
        printf("������ͼ����:");
        scanf("%s", newbook.number);
        while(1){
            if(!check_repeat_number(newbook.number)){
                printf(":( ͼ�����Ѵ���,���������룺");
                fflush(stdin);
                gets(newbook.number);
            }else{
                break; 
            } 
        }
        fflush(stdin);
        printf("����������:");
        scanf("%s", newbook.name);
        printf("����������:");
        scanf("%s", newbook.author);
        printf("�����������:");
        scanf("%s", newbook.press);
        printf("���������:");
        scanf("%s", newbook.category);
        printf("������۸�:");
        scanf("%f", &newbook.price);
        printf("������ݲ���:");
        scanf("%d", &newbook.quantity);
        printf("��������Ĵ���(��������0):");
        scanf("%d", &newbook.time);
        fflush(stdin);
        printf("�Ƿ񱣴������Ŀ(y/n):");
        choice = getchar();
        while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n')
            choice = getchar();
        if (choice == 'Y' || choice == 'y'){
            p1 = fopen("data/library.csv", "a");
            fprintf(p1, "%s %s %s %s %s %.1f %d %d \n",
                newbook.number, newbook.name, newbook.author, newbook.press,
                newbook.category, newbook.price, newbook.quantity, newbook.time);
            fclose(p1);
            printf(":) ��ӳɹ�!\n");
        }else{
            printf("\n������Ŀδ����!\n");
        }
        printf("�Ƿ���������Ŀ(y/n):");
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