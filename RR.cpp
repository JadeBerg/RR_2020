/**
* @file rr_struna.c
* @author Струна В.Р., гр. 515б, вариант 15
* @date 18 мая 2020
* @brief Расчетная работа
*
* База данных людей
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<locale.h>
#include<conio.h>
#include<string>
#include<string.h>
#include<stdlib.h>
#include<Windows.h>
#define PASS "5TNN61337"
typedef struct {
unsigned int serial;
char name[50] = { 0 };
char pass[50] = { 0 };
int card;
int number[3];
bool deleted;
} people;
bool pass(char*, FILE*);
void osn1(FILE*);
void osn2(FILE*);
void osn3(FILE*);
void osn4(FILE*);
void spec1(FILE*);
void spec2(FILE*);
void dop1(FILE*);
void dop2(FILE*);
int main(void)
{
int m, n = 0;
bool pas;
char* DB = (char*)calloc(30, sizeof(char)), * kluch = (char*)calloc(30, sizeof(char)), *
str = (char*)calloc(30, sizeof(char));
FILE* fp, * upass;
if ((upass = (FILE*)fopen("pass.txt", "r")) == NULL)
{
upass = (FILE*)fopen("pass.txt", "w");
printf(": ");
gets_s(DB, 30);
printf(": ");
gets_s(str, 30);
strcat(kluch, str);
if (!strcmp(kluch, PASS))
{
pas = true;
}
else
{
pas = false;
}
fprintf(upass, "DB = ");
fputs(DB, upass);
fprintf(upass, ";\nKEY = ");
fputs(kluch, upass);
fprintf(upass, ";\n");
fclose(upass);
}
else
{
pas = pass(DB, upass);
}
setlocale(LC_ALL, "Russian");
SetConsoleCP(1251);
SetConsoleOutputCP(1251);
if ((fp = (FILE*)fopen(DB, "wb+")) == NULL)
{
printf("Открыть файл невозможно");
_getch();
return 0;
}
free(DB);
if (pas)
{
for (; ; )
{
restart:
printf("\nМеню: \n0-Выход \n1-Добавить
запись в базу данных\n2-Удалить запись из базы данных "
"\n3-Просмотр записей\n4-Изменить запись\n5-Поиск людей по
фамилии\n"
"6-Поиск людей в списке по месяцу рождения\n7-Сохранение базы
данных в файле с заданным именем\n8-Экспорт базы данных в текстовый файл с заданным
именем\n\nВведите: ");
scanf("%d", &m);
switch (m)
{
case 0: fclose(fp);
fclose(upass); return 0;
case 1:
osn1(fp); break;
case 2: osn3(fp);
break;
case 3: osn2(fp);
break;
case 4: osn4(fp); break;
case 5:
spec2(fp); break;
case 6: spec1(fp);
break;
case 7: dop1(fp); break;
case 8: dop2(fp); break;
default: goto restart;
}
m = NULL;
}
}
else
{
for (; ; )
{
restart2:
printf("Меню: \n0-Выход \n1-Добавить запись в базу данных\n2-
Удалить запись из базы данных "
"\n3-Просмотр записей\n 4-Изменить запись\n"
"Введен неверный ключ конфигурационного файла\n");
scanf("%d", &m);
switch (m)
{
case 0: fclose(fp); fclose(upass);
return 0;
case 1: osn1(fp);
break;
case 2:
osn3(fp); break;
case 3: osn2(fp); break;
case 4: osn4(fp);
break;
default:
goto restart2;
}
m = NULL;
}
}
}
bool pass(char* DB, FILE* upass)
{
char* stroka = (char*)calloc(30, sizeof(char)), * strocka = (char*)calloc(30,
sizeof(char));
fgets(stroka, 30, upass);
fgets(strocka, 30, upass);
char* pas = (char*)calloc(11, sizeof(char));
int x = 0;
while (strocka[x + 6] != ';')
{
pas[x] = strocka[x + 6];
x++;
}
x = 0;
while (stroka[x + 5] != ';')
{
DB[x] = stroka[x + 5];
x++;
}
free(stroka);
free(strocka);
return !strcmp(pas, PASS);
}
void osn1(FILE* fp)
{
people route;
char musor;
int n, c = sizeof(route), l = 0, res, res1[3];
fseek(fp, 0, SEEK_SET);
while (true)
{
people route1;
n = fread(&route1, sizeof(route1), 1, fp);
if (n == 0)
{
break;
}
l = route1.serial;
if (route1.deleted)
{
fseek(fp, -c, SEEK_CUR);
route.serial = route1.serial;
goto s_l;
}
};
route.serial = l + 1;
s_l:
printf("Внесите следующие значения (каждое в новую строку): Фамилия имя и отчество ,
Номер пасспорта, Дата рождения , Номер карты плательщика\n");
musor = getchar();
gets_s(route.name);
gets_s(route.pass);
for (int i = 0; i < 3; i++) {
scanf("%d ", &res1[i]);
route.number[i] = res1[i];
}
printf("\n");
scanf("%d", &res);
route.card = res;
route.deleted = false;
fwrite(&route, sizeof(route), 1, fp);
}
void osn3(FILE* fp)
{
people route;
int ua, nal;
printf("Номер записи которую нужно удалить: ");
scanf("%d", &nal);
fseek(fp, sizeof(route) * (nal - 1), SEEK_SET);
ua = fread(&route, sizeof(route), 1, fp);
if (ua == 0) {
printf("Ошибка\n");
}
else if (route.deleted) {
printf("Эта запись уже была удалена\n");
}
else {
route.deleted = true;
fseek(fp, sizeof(route) * (nal - 1), SEEK_SET);
fwrite(&route, sizeof(route), 1, fp);
printf("Запись удалена\n");
}
}
void osn2(FILE* fp)
{
fseek(fp, 0, SEEK_SET);
int kkk;
while (true)
{
people route;
kkk = fread(&route, sizeof(route), 1, fp);
if (kkk == 0) {
break;
}
if (!route.deleted) {
printf("\nНомер записи:%d\n", route.serial);
printf("ФИО: ");
puts(route.name);
printf("Номер пасспорта: ");
puts(route.pass);
printf("Номер карты: %d\n", route.card);
printf("Дата Рождения: ");
for (int i = 0; i < 3; i++) {
printf("%d ", route.number[i]);
}
printf("\n");
}
};
}
void osn4(FILE* fp)
{
people route;
int n, nal, k;
char musor;
char* ton = (char*)malloc(50);
printf("Номер записи: ");
scanf("%d", &nal);
fseek(fp, sizeof(route) * (nal - 1), SEEK_SET);
n = fread(&route, sizeof(route), 1, fp);
if (n == 0)
{
printf("Ошибка");
goto exit;
}
restart:
printf("Что вы хотите изменить?: \n1.ФИО\n2.Номер пасспорта\n3.Дату рождения\n4.Номер
карты\n");
scanf("%d", &k);
int sum, sum1[3];
switch (k)
{
case 1: printf("Введите ФИО: ");
musor = getchar();
gets_s(ton, 50);
strcpy(route.name, ton);
break;
case 2: printf("Введите номер пасспорта: ");
musor = getchar();
gets_s(ton, 50);
strcpy(route.pass, ton);
break;
case 3: printf("Введите дату рождения: ");
for (int i = 0; i < 3; i++) {
scanf("%d", &sum1[i]);
route.number[i] = sum1[i];
}
break;
case 4: printf("Введите номер карты: ");
scanf("%d", &sum);
route.card = sum;
break;
default: goto restart;
break;
}
fseek(fp, sizeof(route) * (nal - 1), SEEK_SET);
fwrite(&route, sizeof(route), 1, fp);
exit:
free(ton);
}
void spec2(FILE* fp)
{
float res = 0;
int giv;
char ton1[50];
char musor;
char* ton = (char*)malloc(50);
fseek(fp, 0, SEEK_SET);
printf("Введите фамилию: ");
musor = getchar();
gets_s(ton, 50);
do
{
people route;
giv = fread(&route, sizeof(route), 1, fp);
if (giv == 0)
{
break;
}
strcpy(ton1, route.name);
for (int i = 0; *(ton1 + i) != '\0'; i++)
{
if (*(ton1 + i) == ' ')
{
ton1[i] = '\0';
i--;
}
}
if (!route.deleted && !strcmp(ton1, ton))
{
printf("%d\n", route.serial);
puts(route.name);
puts(route.pass);
printf("%d\n", route.card);
for (int i = 0; i < 3; i++) {
printf("%d\n", route.number[i]);
}
}
} while (true);
free(ton);
}
void spec1(FILE* fp)
{
int res;
int rex;
char musor;
char* ton = (char*)malloc(50);
fseek(fp, 0, SEEK_SET);
musor = getchar();
printf("Введите месяц: ");
scanf("%d", &res);
do
{
people route;
rex = fread(&route, sizeof(route), 1, fp);
if (rex == 0)
{
printf("\nНет\n"); break;
}
if (!route.deleted && route.number[1] == res)
{
printf("\nНомер записи: %d\n", route.serial);
puts(route.name);
puts(route.pass);
printf("Номер карты: %d\n", route.card);
printf("Дата рождения: ");
for (int i = 0; i < 3; i++) {
printf("%d\n", route.number[i]);
}
}
} while (true);
free(ton);
}
void dop1(FILE* fp)
{
char* name = (char*)calloc(30, sizeof(char)), musor2;
FILE* mux;
int mux2;
printf("Введите название файла: ");
musor2 = getchar();
gets_s(name, 25);
strcat(name, ".dat");
mux = fopen(name, "wb");
fseek(fp, 0, SEEK_SET);
do
{
people route;
mux2 = fread(&route, sizeof(route), 1, fp);
if (mux2 == 0)
{
break;
}
fwrite(&route, sizeof(route), 1, mux);
} while (true);
fclose(mux);
free(name);
}
void dop2(FILE* fp)
{
char* name = (char*)calloc(30, sizeof(char)), musor2;
FILE* mux;
int mux2;
printf("Введите название файла: ");
musor2 = getchar();
gets_s(name, 25);
strcat(name, ".txt");
mux = fopen(name, "w");
fseek(fp, 0, SEEK_SET);
while (true)
{
people route;
mux2 = fread(&route, sizeof(route), 1, fp);
if (mux2 == 0) {
break;
}
fprintf(mux, "\n%d;\n", route.serial);
fputs(route.name, mux);
fprintf(mux, ";\n");
fputs(route.pass, mux);
fprintf(mux, ";\n%d;\n", route.card);
for (int i = 0; i < 3; i++) {
fprintf(mux, "%d ", route.number[i]);
}
};
fclose(mux);
free(name);
}
