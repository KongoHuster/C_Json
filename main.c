#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include <string.h>


//任务1 读取文件
static cJSON* read_json_file(char *filename, cJSON* json)//读取json文件，传入文件地址和一个json指针
{
    long len = 0;
    int temp;
    char *JSON_content;

    FILE* fp = fopen(filename, "rb+");
    if(!fp)                           //若指针为空则打开失败

    {
        printf("open file %s failed.\n", filename);
        return NULL;
    }

    fseek(fp, 0, SEEK_END);      //将指针移到最以便得出json大小
    len = ftell(fp);

    if(0 == len)
    {
        return NULL;
    }

    fseek(fp, 0, SEEK_SET);
    JSON_content = (char*) malloc(sizeof(char) * len);
    temp = fread(JSON_content, 1, len, fp);//将内容读入JSON_content,

    fclose(fp);
    json = cJSON_Parse(JSON_content); //解析JSON数据，将数据填入JSON树中
    if (json == NULL)
    {
        return NULL;
    }
    free(JSON_content);

    return json;
}

//任务2.1 新建一个数据表
int makeJson()
 {
         char *char_json = "{}";
          //从缓冲区中解析出JSON结构
          cJSON *json = cJSON_Parse(char_json);
      if (json == NULL)
      {
        return 0;
      }
          //将传入的JSON结构转化为字符串 并打印
          char *buf = NULL;
          buf = cJSON_Print(json);
          //打开一个exec.json文件，并写入json内容
          FILE *fp = fopen("C:\\Users\\yizihong\\Desktop\\test\\exec.json","w");
          fwrite(buf,strlen(buf),1,fp);

          fclose(fp);
         free(buf);
         cJSON_Delete(json);
         return 1;


}

//2.2删除某数据表(未完成)
static cJSON* delete_json_file(char *filename, cJSON* json)
{
    cJSON * cjson;
    cjson = read_json_file(filename, json);
    if (cjson == NULL)
    {
        printf("read_json_file json == NULL\n");
        return -1;
    }
    cJSON *root = cJSON_Parse(cjson);
    cJSON_Delete(root);
    return 0;
//    char *json_data = NULL;
//    printf("data:%s\n",json_data = cJSON_Print(cjson));
//
//    free(json_data);
//    //将JSON结构所占用的数据空间释放
//     cJSON_Delete(json);
//    return 0;
}



////2.3show<打印数据表>
//static cJSON* show_json_file(char *filename)
//{
//    cJSON *json;
//
//    json = read_json_file(filename, json);
//    if (json == NULL)
//    {
//        printf("read_json_file json == NULL\n");
//        return 1;
//    }
//
//    char *json_data = NULL;
//    printf("data:%s\n",json_data = cJSON_Print(json));
//
//    free(json_data);
//    //将JSON结构所占用的数据空间释放
//     cJSON_Delete(json);
//    return 0;
//
//}
//
//
//3.1find<查找>
cJSON* find_Object(cJSON* object, const char* key){
    cJSON* subitem = object->child;
    while(subitem){
        //忽略大小写进行比较
        if(!strcasecmp(subitem->valuestring,key))
            return subitem;
        //有子节点就优先查找子节点
        cJSON* tmp = NULL;
        if(subitem->child)
            tmp = find_Object(subitem,key);
        if(tmp) return tmp;
        //如果子节点没有找到,返回在本层级查找
        subitem = subitem->next;
    }
    return subitem;
}

////3.2count<统计>
int cout_Object(cJSON* object, const char* key){
    int i=0;
    cJSON* subitem = object->child;
    while(subitem){
        //忽略大小写进行比较
        if(!strcasecmp(subitem,key))
            i=i+1;
        //有子节点就优先查找子节点
        cJSON* tmp = NULL;
        if(subitem->child)
            tmp = find_Object(subitem,key);
        if(tmp) i=i+1;
        //如果子节点没有找到,返回在本层级查找
        subitem = subitem->next;
    }
    return i;
}

//任务4.1
int  insert_Object(char *name, char *value,char *txt)
{
         cJSON *json = cJSON_CreateObject();

         //向文档中增加一个键值对{"name":"王大锤"}
         cJSON_AddItemToObject(json,name,cJSON_CreateString(value));

          char *buf = cJSON_Print(json);
        //打开文件写入json内容
          FILE *fp = fopen(txt,"at");
          fwrite(buf,strlen(buf),1,fp);
          free(buf);
          fclose(fp);
        //释放json结构所占用的内存
         cJSON_Delete(json);
         return 1;




}


//4.2update <更新>
//void  update_Object(char *filename)
//{
//    FILE *f;
//    long len;
//    char *data;
//    cJSON *json,*ret;
//
//    f=fopen(filename,"rb");
//    fseek(f,0,SEEK_END);
//    len=ftell(f);
//    fseek(f,0,SEEK_SET);
//    data=(char*)malloc(len+1);
//    fread(data,1,len,f);
//    data[len]='\0';
//    json=cJSON_Parse(data);
//    if (!json)
//    {
//        printf("Error before: [%s]\n",cJSON_GetErrorPtr());
//        ret = NULL;
//        goto EXIT;
//    }
//    else
//    {
//        //printf("%s\n",data);
//        ret = json;
//
//    }


//任务6
int login()
{
    int i = 0;

    char password[10] = { 0 };
    char name[10] = { 0 };
    printf("请输入用户名:");
    scanf("%s", name);

    printf("请输入密码:");
    while (i < 3)
    {
        scanf("%s", password);
        printf("\n");
        if (strcmp(password, "yzh") == 0)
        {
            printf("登录成功\n");
            break;
        }
        else
        {
            i++;
            if (i != 3)
                printf("再输入一次");
        }
    }
    if (i == 3)
        printf("密码错误三次退出登录界面\n");
    system("pause");
    return 0;
}



int main() {
    printf("用户名：yzh\n密码：yzh\n完成任务1，任务2.1，任务2.3，任务3.1,任务3.2,任务4.1,任务3.1,任务6\n命令：\n1.输入print可打印信息；\n2.输入makejson可以新建一个链表\n3.输入show,回车，在输入C:\\\\Users\\\\yizihong\\\\Desktop\\\\test\\\\list.data地址，可以打印数据表\n4.输入count，在输入高圆圆，可以查找该人名有多少人\n");
    printf("6.输入insert,回车，再输入name，回车，在输入jake，可以插入信息\n7.最后，若想退出程序请输入break\n8.我已经尽力了，呜呜呜\n");

    login();

    while(1) {
        int result = -1;
        char a[4][20] = {0};
        printf("请输入命令字：");
        scanf("%s", a);


        //任务1
        if (strcmp(a[0], "print") == 0) {
            cJSON *json;
            json = read_json_file("C:\\Users\\yizihong\\Desktop\\test\\list.data", json);

            if (json == NULL) {
                printf("read_json_file json == NULL\n");
                return -1;
            }

            char *json_data = NULL;
            printf("data:%s\n", json_data = cJSON_Print(json));

            free(json_data);
            //将JSON结构所占用的数据空间释放
            cJSON_Delete(json);
            return 0;
        }

        //任务2.1
        if (strcmp(a[0], "makejson") == 0) {
            result = makeJson();
            if (result == 1)
                printf("成功： OK");
            else if (result == 0)
                printf("失败： ERROR： <failed message>");
        }



        //任务2.3
        if (strcmp(a[0], "show") == 0) {
            cJSON *json;
            printf("请打印的文件地址：");
            scanf("%s", a + 1);
            json = read_json_file(a + 1, json);

            if (json == NULL) {
                printf("read_json_file json == NULL\n");
                return -1;
            }

            char *json_data = NULL;
            printf("data:%s\n", json_data = cJSON_Print(json));

            free(json_data);
            //将JSON结构所占用的数据空间释放
            cJSON_Delete(json);
            return 0;
        }

        //任务3.1//有问题
        if (strcmp(a[0], "find") == 0) {
            printf("查找的信息：");
            scanf("%s", a + 1);
            cJSON *json;
            json = read_json_file("C:\\Users\\yizihong\\Desktop\\test\\list.data", json);
            if (json == NULL) {
                printf("read_json_file json == NULL\n");
                return -1;
            }
            char *json_data = NULL;

            json_data = find_Object(json, a + 1);
            printf("data:%s\n", json_data = cJSON_Print(json));


        }


        //3.2count
        if (strcmp(a[0], "count") == 0) {
            printf("查找的信息：");
            scanf("%s", a + 1);
            cJSON *json;
            json = read_json_file("C:\\Users\\yizihong\\Desktop\\test\\list.data", json);
            if (json == NULL) {
                printf("read_json_file json == NULL\n");
                return -1;
            }
            char *json_data = NULL;

            result = cout_Object(json, a + 1);
            if (result >= 0)
                printf("data:%d\n", result);
            else
                printf("所查信息不存在");

        }

        //4.1insert
        if (strcmp(a[0], "insert") == 0) {
            printf("插入的信息1：");
            scanf("%s", a + 1);
            printf("插入的信息2：");
            scanf("%s", a + 2);
            printf("插入的文件：");
            scanf("%s", a + 3);
            result = insert_Object(a + 1, a + 2, a + 3);
            if (result >= 0)
                printf("OK");
            else
                printf("失败： ERROR ： < failed message >");

            

        }

//      if (strcmp(a[0], "break") == 0)
//          break;
    }
}


