#include "tools.h"
#include<iostream>
#include <random> 
#include<ctime>
#include<iomanip>

int edge(int a, int min, int max)
{
    if(a<min)
        a=min;
    if(a>max)
        a=max;
    return a;
}

int edgeleft(int a, int min)
{
    if(a<min) a=min;
    return a;
}

int edgeright(int a, int max)
{
    if(a>max) a=max;
    return a;
}

int switching(int *a)
{
    if(*a==0)
        *a=1;
    else
        *a=0;
    return *a;
}

int getSwitchNum(int a)
{
    if(a==1)
        a=0;
    else a=1;
    return a;
}

int random(int min, int max)
{
    // 定义静态随机数生成器和分布
    static std::mt19937 rng(std::time(nullptr)); // 使用静态变量保持随机数种子
    static std::uniform_int_distribution<int> uni;

    // 设置分布的范围
    uni.param(std::uniform_int_distribution<int>::param_type(min, max));

    // 返回生成的随机数
    return uni(rng);
}

int *FindMinPosition(int a[2][5], int low, int high)
{
    int min=high;
    int i,j;
    int* tem=new int[3];
    for(i=0;i<2;i++)
        for(j=0;j<5;j++)
            if(a[i][j]<min&&a[i][j]>low)
                min=a[2][5];
    for(i=0;i<2;i++)
        for(j=0;j<5;j++)
            if(a[i][j]==min)
            {
                tem[0]=min,tem[1]=i,tem[2]=j;return tem;
            }
    return nullptr;
}

float cifang(float x, int cifang)
{
    float tem=1;
    if(cifang==0)
        return 1;
    else 
    {
        for(int i=0;i<cifang;i++)
            tem*=x;
        return tem;
    }

}

int Up_quzheng(float x)
{
    int tem=x;
    if(tem==x)
    return tem;
    else
    return ++tem;;
}

void toEnter(int x)
{
    for(int i=0;i<x;i++)
        std::cout<<std::endl;
}

char lower(char a)
{
    if(a<='Z'&&a>='A')
        a+='a'-'A';
    return a;
}

void fengexian(int start, int end, int step, int internal)
{
    toEnter(internal-1);
    for(int i=0;i<(end-start)/step;i++)
    {
        std::cout<<"_";
        for(int j=0;j<step-1;j++)
            std::cout<<" ";
    }
    toEnter(internal);
}
