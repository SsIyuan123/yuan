#ifndef TOOLS_H
#define TOOLS_H
#include<vector>

int edge(int a, int min, int max);

int edgeleft(int a, int min);

int edgeright(int a,int max);

int switching(int *a);

int getSwitchNum(int a);

int random(int min = 0, int max = 100);

int* FindMinPosition(int a[2][5], int low = 0, int high = 100);//记录二维数组有x行y列，只考虑（low，high）开区间里的数的最小值位置

float cifang(float x, int cishu);

int Up_quzheng(float x);

template <typename T>
int Include(T& x, std::vector<T>& a) {
    for (int i = 0; i < a.size(); ++i) {
        if (x == a[i]) {
            return 1; // 如果找到 x，返回 true
        }
    }
    return 0; // 如果未找到 x，返回 false
}

void toEnter(int x);

char lower(char a);

void fengexian(int start, int end, int step, int internal);

#endif
