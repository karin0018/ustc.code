/*
 * @Author: karin
 * @Date: 2020-01-30 16:37:59
 * @LastEditors  : karin
 * @LastEditTime : 2020-02-04 19:44:07
 * @Description: Quick sort
 * @TimeComplexity: O(nlogn)
 * @FilePath: \datastructure\ustc.code\sort\quicksort1.cpp
 */

#include<stdio.h>
#include<stdlib.h>

int partition(char *a,int lo,int hi){
    int i = lo;
    int j = hi+1;
    char temp;//交换中介
    //设 a[lo] 为参考值
    while (true){
        while (a[++i] < a[lo])//找到左边待交换的值
            if(i == hi) break;
        while (a[lo] < a[--j])//找到右边待交换的值
            if(j == lo) break;
        if (i > j || i == j) break;
        temp = a[i];//交换 a[i] 与 a[j]
        a[i] = a[j];
        a[j] = temp;
        printf("exchange %s",a);
        getchar();
    }
    temp = a[j];
    a[j] = a[lo];
    a[lo] = temp;
    return j;//排序后参考值的位置
}

void quickSort(char *a,int lo,int hi){
    if(lo > hi || lo == hi) return;
    int j = partition(a,lo,hi);
    quickSort(a,lo,j-1);
    printf("%d %s",j,a);
    getchar();
    quickSort(a,j+1,hi);
}

int main(){
	char a[5] = {'a','s','f','g','h'};
	printf("%s",a);
	getchar();
	quickSort(a,0,4);
	printf("%s",a);
	getchar();
}
