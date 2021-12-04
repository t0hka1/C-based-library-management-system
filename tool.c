// 此处添加头文件
// 待添加其他头文件
#include "tool.h"
#include <stdlib.h>
#include <windows.h>

// 设置输出窗口大小
void SetSize(unsigned uCol,unsigned uLine){
 char cmd[64];
 sprintf(cmd,"mode con cols=%d lines=%d",uCol,uLine);
 system(cmd);
}