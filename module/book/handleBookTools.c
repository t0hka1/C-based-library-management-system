#include "handleBook.h"

/*建立动态数组*/
void SLInit_info(sl_info* ps){ //初始化数组
    assert(ps);
    ps->books = (BOOKINFO*)malloc(sizeof(BOOKINFO)*10);
    ps->size = 0;
    ps->capacity = 10;
}
void SLPushBack_info(sl_info* ps,BOOKINFO x){ //在数组末尾进行添加
    assert(ps); 
    if(ps->size == ps->capacity){ //若数组大小达到最大容量，则需要进行扩容
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