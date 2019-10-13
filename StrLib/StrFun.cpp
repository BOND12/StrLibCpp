/*
 * StrFun.cpp
 *
 *  Created on: 3 янв. 2019 г.
 *      Author: BOND
 *      License: M.I.T.
 *      v0.2
 */

#include "Defaults.h"
#include <stdlib.h>

/*
 * Исключительно в целях отладки
 *
 */
#define debug 0

#if(debug)
#include <iostream>
using namespace std;
#endif


int length(char *s){//Символ завершения строки имеет код 0, поэтому, его и ищем
	//Строго записывается как "\0"
	int i=0;
	for (i=0; s[i] != 0; i++);

	return i;
}


int posc(char* s1, char c){
	int l = length(s1);
	for (int v = 0;(v<l&&v<StrLenDef);v++){
		if (s1[v] == c){
			return v;
		}
	}
	return -1;
}

void copy(char* s1, char* s2,int n, int m){

int v = length(s2);
int i=0;

	for (i=0; i<m && (i+n)<v;i++){
		s1[i] = s2[i+n];
	}
	s1[i] = 0;
}


void copy (char *s1,char*s2){
	copy(s1,s2,0,length(s2));
	return;
}

void insert(char* s1, char* s2,int n){
	char cc[StrLenDef]= "";//Вспомогательная строка, для хранения одной из запчастей строк
	int i =0;

	copy(cc,s1,n,StrLenDef);
	int l2 = length(s2);//Кол-во символов в строке s2
	int r=0;//Вспомогательный счётчик для счёта символов из s2
	for (i = n;r<l2 && i<StrLenDef;i++){
		s1[i]=s2[r];
		r++;
	}

	r=0;
	l2 = length(cc);

	for (l2 = length(cc); r<l2 && i<StrLenDef; i++){
			s1[i]=cc[r];
			r++;
		}

	s1[i]='\0';//Оканчиваем символом завершения строки
return;
}



void del(char* s1,int n, int m){
	char s2[StrLenDef] = "";
	char s3[StrLenDef] = "";
	copy(s2,s1,0,n);//Копируем строку до символа n
	copy(s3,s1,n+m,length(s1));//Копируем то, что после n+m символов
	copy(s1,s2);
	insert(s1,s3,n);
	return;
}

bool compare(char *s1,char*s2){
	int i = length(s1);
	int i1 = length(s2);
	if (i!=i1)
		return 0;

	for (int n = 0;n<i;n++){
		if (s1[n] != s2[n])
			return 0;
	}
	return 1;

}

//Можно оптимизировать
int pos(char* s1,char* s2){
	char s[StrLenDef]="";
	int z=0;
	copy(s,s1);
	int len2 = length(s2);
	while (length(s)){
		int x = posc(s,s2[0]);//Позиция первого вхождения символа
		if (x==-1)//Если такого символа нет
			return -1;
		//Если есть:
		char sr1[StrLenDef]="";
		copy(sr1,s,x,len2);
		if (compare(sr1,s2))
		{
			return x+z;
		}
		else {
			z+=1;
			del(s,0,1);//Удаляем символ до...
			//По хорошему, этот момент можно оптимизировать, т.е. удалять все символы до x сразу, а не по одному...
			//Но это потом как-нибудь, ибо при моей попытке сделать это у меня подвисала прога.
		}
	}

	return -1;
}


void dela(char*s1,char a){
	int i = posc(s1,a);
	while (i !=-1){
		del(s1,i,1);
		i = posc(s1,a);
	}
	return;
}

int replace(char*s1,char*s2,char*s3){
	int  v;
		if ((v = pos(s1,s2)) != -1){
			int l=length(s2);
			del(s1,v,l);
			insert(s1,s3,v);
		}
		else
			return -1;

		return 0;
}

int replacea(char*s1,char*s2, char *s3){
	int i=0;
	if (compare(s2,s3))//Защита от дурака
		return -2;
	if ((pos(s1,s2)==-1))
		return -1;
	while (pos(s1,s2)!=-1){
		i++;
		replace(s1,s2,s3);
	}
	return i;
}

int replacec(char *s1,char a, char b){
	int  v;
	if ((v = posc(s1,a)) != -1){
		del(s1,v,1);
		char l[2];
		l[0]=b;
		l[1] = 0;
		insert(s1,l,v);
	}
	else
		return -1;

	return 0;
}


int replaceca(char *s1,char a, char b){
	int i=0;
	if (a==b)
		return -2;
	if ((posc(s1,a)==-1))
		return -1;

	while (posc(s1,a)!=-1){
		i++;
		replacec(s1,a,b);
	}
	return i;

}

void strrev(char *s){//Могут быть глюки...
int l = length(s);
char s1[StrLenDef];

copy(s1,s);

for (int i = 0;i<l;i++){
	s[i]=s1[l-i-1];
}
}



void itoa(int n, char*s){
	int i,sign;
		if((sign=n)<0)//Присваиваем переменной sign значение n и
			//сравниваем его с 0 для определения знака числа n
		n=-n;
		i=0;
		do {
			s[i++]=n%10+'0';//Вычленяем число разряда и прибавляем его к
			//коду символа 0
		} while ((n/=10)>0);//Если ещё число не сократилось до 0
		//циклим дальше
		if(sign<0)
		s[i++]='-';//Если число было отрицательным, добавляем минус в конце
		s[i]=0;//Добавляем символ конца строки
		strrev(s);//Инверсируем строку
}

int atoi(char *s)//Потом немного переделать...
{
int n,i,sign;//Дополнительные переменный
for(i=0;s[i]==' '||s[i]=='\t';i++);
sign=1;//Знак положительный по умолчанию
if(s[i]=='\0'||s[i]=='-' || s[i] == '+')
sign=(s[i++]=='+')?1:-1;//Если число отрицательное, нужно
//установить значения знака = -1
for(n=0;s[i]>='0'&& s[i]<='9';++i)//Проверка на недопустимые символы
	//И преобразования строки в число
n=10*n+s[i]-'0';//Преобразуем символ цифры в разряд челого числа со сдвигом
//бывшего значения на одит порядок
return(sign*n);//Возвращаем результат с учётом знака
}


bool comparel(char*s1,char*s2,bool params = 0){
	switch (params) {//Для дальнейшей доработки функции...
	case 0:
		int l1 = length(s1);//Получаем длины строк
		int l2 = length(s2);
		int i=0;//Счётчик цикла
		while ((s1[i]==s2[i])&&(i<l1)&&(i<l2)){//Проверка строк на одинаковость...
			//и на непревышение циклом длин строк
			i++;
		}
	if (i == l1)//Если строка 1 короче 2 и при этом они одинаковы на длине l1 то
		return 0;//s1 лексиграфически меньше s2
	if (i == l2)
		return 1;// и наоборот
	if (s1[i] > s2[i])//Условие: если найдено различие:
		return 1;//s1 > s2 лексиграфически
	else
		return 0;//И наоборот
	break;
}
	return 0;
}


