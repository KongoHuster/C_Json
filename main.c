#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include <string.h>


//����1 ��ȡ�ļ�
static cJSON* read_json_file(char *filename, cJSON* json)//��ȡjson�ļ��������ļ���ַ��һ��jsonָ��
{
    long len = 0;
    int temp;
    char *JSON_content;

    FILE* fp = fopen(filename, "rb+");
    if(!fp)                           //��ָ��Ϊ�����ʧ��

    {
        printf("open file %s failed.\n", filename);
        return NULL;
    }

    fseek(fp, 0, SEEK_END);      //��ָ���Ƶ����Ա�ó�json��С
    len = ftell(fp);

    if(0 == len)
    {
        return NULL;
    }

    fseek(fp, 0, SEEK_SET);
    JSON_content = (char*) malloc(sizeof(char) * len);
    temp = fread(JSON_content, 1, len, fp);//�����ݶ���JSON_content,

    fclose(fp);
    json = cJSON_Parse(JSON_content); //����JSON���ݣ�����������JSON����
    if (json == NULL)
    {
        return NULL;
    }
    free(JSON_content);

    return json;
}

//����2.1 �½�һ�����ݱ�
int makeJson()
 {
         char *char_json = "{}";
          //�ӻ������н�����JSON�ṹ
          cJSON *json = cJSON_Parse(char_json);
      if (json == NULL)
      {
        return 0;
      }
          //�������JSON�ṹת��Ϊ�ַ��� ����ӡ
          char *buf = NULL;
          buf = cJSON_Print(json);
          //��һ��exec.json�ļ�����д��json����
          FILE *fp = fopen("C:\\Users\\yizihong\\Desktop\\test\\exec.json","w");
          fwrite(buf,strlen(buf),1,fp);

          fclose(fp);
         free(buf);
         cJSON_Delete(json);
         return 1;


}

//2.2ɾ��ĳ���ݱ�(δ���)
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
//    //��JSON�ṹ��ռ�õ����ݿռ��ͷ�
//     cJSON_Delete(json);
//    return 0;
}



////2.3show<��ӡ���ݱ�>
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
//    //��JSON�ṹ��ռ�õ����ݿռ��ͷ�
//     cJSON_Delete(json);
//    return 0;
//
//}
//
//
//3.1find<����>
cJSON* find_Object(cJSON* object, const char* key){
    cJSON* subitem = object->child;
    while(subitem){
        //���Դ�Сд���бȽ�
        if(!strcasecmp(subitem->valuestring,key))
            return subitem;
        //���ӽڵ�����Ȳ����ӽڵ�
        cJSON* tmp = NULL;
        if(subitem->child)
            tmp = find_Object(subitem,key);
        if(tmp) return tmp;
        //����ӽڵ�û���ҵ�,�����ڱ��㼶����
        subitem = subitem->next;
    }
    return subitem;
}

////3.2count<ͳ��>
int cout_Object(cJSON* object, const char* key){
    int i=0;
    cJSON* subitem = object->child;
    while(subitem){
        //���Դ�Сд���бȽ�
        if(!strcasecmp(subitem,key))
            i=i+1;
        //���ӽڵ�����Ȳ����ӽڵ�
        cJSON* tmp = NULL;
        if(subitem->child)
            tmp = find_Object(subitem,key);
        if(tmp) i=i+1;
        //����ӽڵ�û���ҵ�,�����ڱ��㼶����
        subitem = subitem->next;
    }
    return i;
}

//����4.1
int  insert_Object(char *name, char *value,char *txt)
{
         cJSON *json = cJSON_CreateObject();

         //���ĵ�������һ����ֵ��{"name":"����"}
         cJSON_AddItemToObject(json,name,cJSON_CreateString(value));

          char *buf = cJSON_Print(json);
        //���ļ�д��json����
          FILE *fp = fopen(txt,"at");
          fwrite(buf,strlen(buf),1,fp);
          free(buf);
          fclose(fp);
        //�ͷ�json�ṹ��ռ�õ��ڴ�
         cJSON_Delete(json);
         return 1;




}


//4.2update <����>
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


//����6
int login()
{
    int i = 0;

    char password[10] = { 0 };
    char name[10] = { 0 };
    printf("�������û���:");
    scanf("%s", name);

    printf("����������:");
    while (i < 3)
    {
        scanf("%s", password);
        printf("\n");
        if (strcmp(password, "yzh") == 0)
        {
            printf("��¼�ɹ�\n");
            break;
        }
        else
        {
            i++;
            if (i != 3)
                printf("������һ��");
        }
    }
    if (i == 3)
        printf("������������˳���¼����\n");
    system("pause");
    return 0;
}



int main() {
    printf("�û�����yzh\n���룺yzh\n�������1������2.1������2.3������3.1,����3.2,����4.1,����3.1,����6\n���\n1.����print�ɴ�ӡ��Ϣ��\n2.����makejson�����½�һ������\n3.����show,�س���������C:\\\\Users\\\\yizihong\\\\Desktop\\\\test\\\\list.data��ַ�����Դ�ӡ���ݱ�\n4.����count���������ԲԲ�����Բ��Ҹ������ж�����\n");
    printf("6.����insert,�س���������name���س���������jake�����Բ�����Ϣ\n7.��������˳�����������break\n8.���Ѿ������ˣ�������\n");

    login();

    while(1) {
        int result = -1;
        char a[4][20] = {0};
        printf("�����������֣�");
        scanf("%s", a);


        //����1
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
            //��JSON�ṹ��ռ�õ����ݿռ��ͷ�
            cJSON_Delete(json);
            return 0;
        }

        //����2.1
        if (strcmp(a[0], "makejson") == 0) {
            result = makeJson();
            if (result == 1)
                printf("�ɹ��� OK");
            else if (result == 0)
                printf("ʧ�ܣ� ERROR�� <failed message>");
        }



        //����2.3
        if (strcmp(a[0], "show") == 0) {
            cJSON *json;
            printf("���ӡ���ļ���ַ��");
            scanf("%s", a + 1);
            json = read_json_file(a + 1, json);

            if (json == NULL) {
                printf("read_json_file json == NULL\n");
                return -1;
            }

            char *json_data = NULL;
            printf("data:%s\n", json_data = cJSON_Print(json));

            free(json_data);
            //��JSON�ṹ��ռ�õ����ݿռ��ͷ�
            cJSON_Delete(json);
            return 0;
        }

        //����3.1//������
        if (strcmp(a[0], "find") == 0) {
            printf("���ҵ���Ϣ��");
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
            printf("���ҵ���Ϣ��");
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
                printf("������Ϣ������");

        }

        //4.1insert
        if (strcmp(a[0], "insert") == 0) {
            printf("�������Ϣ1��");
            scanf("%s", a + 1);
            printf("�������Ϣ2��");
            scanf("%s", a + 2);
            printf("������ļ���");
            scanf("%s", a + 3);
            result = insert_Object(a + 1, a + 2, a + 3);
            if (result >= 0)
                printf("OK");
            else
                printf("ʧ�ܣ� ERROR �� < failed message >");

            

        }

//      if (strcmp(a[0], "break") == 0)
//          break;
    }
}


