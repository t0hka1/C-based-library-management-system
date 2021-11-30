// 此处添加头文件
// 待添加其他头文件


typedef struct bookinfo               //系统图书信息
{
    char number[15];                  //图书编号
    char name[30];                    //图书名称
    char author[20];                  //作者
    char press[30];                   //出版社 
    char category[20];                //类别 
    float price;                      //单价 
    int  quantity;                    //馆藏量
 	int  time;                        //借书次数 
    int  flag;                        //是否在借
    char account[30];                 //在借人ID
}BOOKINFO;


void listBooks();

void modifyBook();

void delBook();

void addBook();

void borrowBook();

void returnBook();

void searchBook();