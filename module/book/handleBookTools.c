#include "handleBook.h"

/*������̬����*/
void SLInit_info(sl_info* ps){ //��ʼ������
    assert(ps);
    ps->books = (BOOKINFO*)malloc(sizeof(BOOKINFO)*10);
    ps->size = 0;
    ps->capacity = 10;
}
void SLPushBack_info(sl_info* ps,BOOKINFO x){ //������ĩβ�������
    assert(ps); 
    if(ps->size == ps->capacity){ //�������С�ﵽ�������������Ҫ��������
        ps->capacity *= 2;
        ps->books = (BOOKINFO*)realloc(ps->books, sizeof(BOOKINFO)*ps->capacity);
    }
    ps->books[ps->size] = x;
    ps->size++;
}
void SLInit_record(sl_record* ps){
    assert(ps);
    ps->books = (BORROWED_BOOK*)malloc(sizeof(BORROWED_BOOK)*10);
    ps->size = 0;
    ps->capacity = 10;
}
void SLPushBack_record(sl_record* ps, BORROWED_BOOK x){
    assert(ps); 
    if(ps->size == ps->capacity){
        ps->capacity *= 2;
        ps->books = (BORROWED_BOOK*)realloc(ps->books, sizeof(BORROWED_BOOK)*ps->capacity);
    }
    ps->books[ps->size] = x;
    ps->size++;
}