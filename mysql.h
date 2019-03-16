#pragma once
#include <iostream>
#include<string.h>
#include<mysql/mysql.h>
#define N 100
using namespace std ; 

class mysql
{

public :
    MYSQL sql ;
public :
    mysql() ;
    ~mysql() {}

public :
    void print_user_info(const char* table_name) ;
    int send_mysql_request(const char* request, int len) ;
};

//初始化mysql句柄
mysql :: mysql()
{
    
    if(mysql_init(&sql) == NULL)
    {

        cout << "初始化失败～！" << endl ;   
        exit(1) ;
    }

    //连接数据库
    if(mysql_real_connect(&sql, "localhost", "root", "mysql", "user_info", 0, NULL, 0) == 0)
    {

        cout << "连接数据库失败" << endl ;
        exit(1) ;
    }
}

int mysql :: send_mysql_request(const char* request, int len) 
{
    
    while(mysql_real_query(&sql, request, len))
    {
        cout << mysql_error(&sql) <<endl ;
        return 0 ;
    }
    return 1 ;
}

//打印所有指定表中的成员信息
void mysql :: print_user_info(const char* table_name)
{
    
    char info[N] ;
    bzero(info, sizeof(info)) ;
    sprintf(info, "select id,u_name from %s", table_name) ;
    
    if(mysql_real_query(&sql, info, strlen(info)) != 0)
    {
        cout << "select error!" << endl ;
        exit(1) ;
    }

    
    MYSQL_RES* res = mysql_store_result(&sql) ;
    //输出内容
    MYSQL_ROW row ;
    cout << "all user_info in "<< table_name << "is here" <<endl ;
    while((row = mysql_fetch_row(res)))
    {
        cout << "id:" << atoi(row[0]) << "  name:" << row[1] << endl ;
    }
    cout << "--------------------------------------------"<< endl ;
    mysql_free_result(res) ;
}
