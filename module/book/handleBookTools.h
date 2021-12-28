#pragma once
#include "handleBook.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void SLInit_info(sl_info* ps);
void SLPushBack_info(sl_info* ps,BOOKINFO x); 
void SLInit_record(sl_record* ps);
void SLPushBack_record(sl_record* ps,BORROWED_BOOK x);