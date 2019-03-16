#include"mysql.h"
#define N 100

int main()
{
    //创建mysql类
    mysql db ;
    char info[N] ;
    //添加信息
///////////////////////////////////////////
    //将想要执行的命令放到info中
    sprintf(info, "insert users(u_name,password)value(\'%s\',\'%s\');","liu","ck") ;
    //将数据信息插入到数据库中
    db.send_mysql_request(info, strlen(info)) ;
    //遍历数据库中的指定表信息
///////////////////////////////////////////
    db.print_user_info("users") ;

    //查询数据库中的指定信息,示例查询数据库中u_name为chang的用户密码
////////////////////////////////////////////
    
    bzero(info, sizeof(info)) ;
    const char* name ="chang" ;
    sprintf(info, "select password from  users where u_name=\'%s\'",name) ;
    db.send_mysql_request(info, strlen(info)) ;

    MYSQL_RES* res = mysql_store_result(&db.sql) ;
    MYSQL_ROW row ;
    while((row = mysql_fetch_row(res)))
    {
        cout << "password:" <<row[0] <<endl ;
    }
    mysql_free_result(res);

    //更改数据库中的信息，示例：将数据库中的u_name为chang的用户密码改为xixi
//////////////////////////////////////////////
    bzero(info, sizeof(info)) ;
    const char* u_name = "chang" ;
    const char* password = "xixi" ;
    sprintf(info, "update users set password=\'%s\' where u_name=\'%s\'", password, u_name) ;
    db.send_mysql_request(info, strlen(info)) ;
    
    //删除表中指定用户的信息,实例：将表中u_name为chang的用户去掉
///////////////////////////////////////////////////
    bzero(info, sizeof(info));
    const char* del_name = "chang" ;
    const char *table = "users" ;
    sprintf(info, "delete from %s where u_name=\'%s\'",table, del_name) ;
    db.send_mysql_request(info, strlen(info)) ;
    db.print_user_info(table) ;

    //删除数据表中的列
/////////////////////////////////////////////////////////////////
   const char* del_column = "score" ;
    const char* del_table = "users" ;  
    bzero(info, sizeof(info)) ;
    sprintf(info, "alter table %s drop %s", del_table, del_column) ;
    db.send_mysql_request(info, strlen(info)) ;
    
    //修改表的结构,示例给users表中添加score列
////////////////////////////////////////////////////////
    const char* column_name = "score" ;
    const char* table_name = "users" ;  
    bzero(info, sizeof(info)) ;
    sprintf(info, "alter table  %s add %s varchar(20) first ", table_name, column_name) ;
    db.send_mysql_request(info, strlen(info)) ;
    mysql_close(&db.sql) ;

  
    mysql_close(&db.sql) ;
    return 0;
}

