# C-based management system

Collaborative-development-attempt

#### 项目说明：

##### 	该项目是基于c语言的图书管理系统

#### 	项目结构如下：

![](./doc/img/library_flow_chart.png)


项目文件结构说明：

```c
.
│ .gitignore                         //git push 将会忽略的文件
│  LICENSE                           //版权声明
│  main.c                            //主函数
│  README.md 
│  makefile                        //项目编译文件
├─doc							 //存放了一些关于git和github的说明文档
│  │  git.md
│  │  github.md
│  │  readme.md
│  │
│  └─img
│          library_flow_chart.png     //项目架构图
│
├─moudle                            //将要实现的功能模块化放至module目录
│  ├─book                           //存放所有与书籍操作相关的.c .h文件,handleTools存放二级调用函数
│  │      handleBook.c 
│  │      handleBook.h
│  │      handleBookTools.c 
│  │      handleBookTools.h
│  └─user		//存放所有与用户操作相关的.c .h文件,handleTools存放二级调用函数
│          handleUser.c
│          handleUser.h
│          handleUserTools.c         
│          handleUserTools.h
│
├─data				//所有用户信息和书籍信息存在data目录下
│          infoUser.csv
│          library.csv
│          record_of_borrowing_books.csv
└─view                              //视图的呈现相关放在view目录下
│        menu.c
│        menu.h

```

