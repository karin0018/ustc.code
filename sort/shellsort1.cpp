/*
 * @Author: karin
 * @Date: 2020-02-01 13:53:31
 * @LastEditors  : karin
 * @LastEditTime : 2020-02-04 19:45:34
 * @Description: Shell sort -- Insert sort 2.0
 * @TimeComplexity: O(n^2)
 * @FilePath: \datastructure\ustc.code\sort\shellsort1.cpp
 */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void exch(char* a, int i, int j){
    char temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void shellSort(char* a){
    int len = strlen(a);
    int h = 1;
    while(h < len/3) h = 3*h + 1;//先找到小于数组长度的最大增量值
    while(h > 0){//hsort -- the array
        for(int i = h;i<len;i++){
            for(int j = i;j>0 && a[j] < a[j-h];j = j-h){
                exch(a,j,j-h);
            }
        }
        h = h/3;
    }
}


void shuffle(char* a){
    int len = strlen(a);
    int r;
    for (int i = 0;i<len;i++){
 		r = rand()%(i+1);//生成的随机数在0~i之间十分重要；
        exch(a,i,r);
    }
}


int main(){
	char a[10] = "sedfrtgcd";
	printf("raw %s",a);
	getchar();
	shellSort(a);
	printf("sort1 %s",a);
	getchar();
	shuffle(a);
	printf("shuffle %s",a);
	getchar();
	return 0;
}
