/*
 * @Author: karin
 * @Date: 2020-01-18 12:57:35
 * @LastEditors  : karin
 * @LastEditTime : 2020-01-18 13:18:49
 * @Description:
 * 买股票的最佳时机,
 * 给定一个数组，它的第 *i* 个元素是一支给定股票第 i 天的价格。设计一个算法来计算你所能获取的最大利润。你可以尽可能地完成更多的交易（多次买卖一支股票）。
 * 注意：你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。
 * 但是，由于交易次数没有限制，可以在同一天进行多笔交易比如在当天卖出手上的股票（此时当前拥有股票数目为零），然后再买进；这样可以利用连续求解的方法得到最优解。
 * @TimeComplexity: O(n)
 * @FilePath: \datastructure\leetcode\shuzu2.c
 */
#include<stdio.h>

int maxProfit(int* prices, int pricesSize){
    if(pricesSize == 0) return 0;
    int p = 0, q = 1;//p,q 可以看做两个指针，q 是快指针，p 是当前指针

    int profit = 0;
    for (;q < pricesSize ;q++){
        if(prices[q] >= prices[p]){
            profit += prices[q] - prices[p];
            p = q;
        }
        else{
            p++;
        }
    }
    return profit;

}

int main(){
	int prices[5] = {4,2,3,4,5};
	int pricesSize = 5;
	int profit = maxProfit(prices,pricesSize);
	printf("%d",profit);
	getchar();
	return 0;
}