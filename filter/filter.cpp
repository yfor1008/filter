// filter.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>

// 交换算法
// iDataA: input/output, 数据A
// iDataB: input/output, 数据B
void swap(int& iDataA, int& iDataB)
{
    int tmp;
    tmp = iDataA;
    iDataA = iDataB;
    iDataB = tmp;
}

// 获取数据, 从数组中获取以iIndex为中心, 长度为iHalfLen*2+1的数据
// iDataArr: input, 数据数组
// iOutArr: output, 获取的数据, 长度为iHalfLen*2+1
// iDataSize: input, 数据长度
// iIndex: input, 当前位置index
// iHalfLen: input, 需要获取数据的长度的半径
void GetData1D(int* iDataArr, int* iOutArr, int iDataSize, int iIndex, int iHalfLen)
{
    iOutArr[iHalfLen] = iDataArr[iIndex]; // 中心直接为当前index的值

    for (int i = 1; i < iHalfLen + 1; i++)
    {
        // 当前index前面的数据, 超过数据长度取数组第一个数据
        int tmp_idx = iIndex - i;
        if (tmp_idx < 0)
        {
            tmp_idx = 0;
        }
        iOutArr[iHalfLen - i] = iDataArr[tmp_idx];
        // 当前index后面的数据, 超过数据长度取数组最后一个数据
        tmp_idx = iIndex + i;
        if (tmp_idx > iDataSize - 1)
        {
            tmp_idx = iDataSize - 1;
        }
        iOutArr[iHalfLen + i] = iDataArr[tmp_idx];
    }
}

// 冒泡排序: 一维排序, 时间复杂度O(n^2), 空间复杂度O(1), 稳定
// iDataArr: input/output, 数据数组
// iDataSize: input, 数据长度
// bOrder: input, 排序顺序, 0-从高到低(升序), 1-从低到高(降序)
void BubbleSort1D(int* iDataArr, int iDataSize, bool bOrder = 1)
{
    int i = 0, j = 0;
    for (i = 0; i < iDataSize; i++)
    {
        for (j = 0; j < iDataSize - i - 1; j++)
        {
            if (bOrder) // 升序
            {
                if (iDataArr[j] > iDataArr[j + 1])
                {
                    swap(iDataArr[j], iDataArr[j + 1]);
                }
            }
            else // 降序
            {
                if (iDataArr[j] < iDataArr[j + 1])
                {
                    swap(iDataArr[j], iDataArr[j + 1]);
                }
            }
        }
    }
}

// 中值滤波
// iDataArr: input, 数据数组
// iFiltered: output, 滤波后的数据
// iDataSize: input, 数据长度
// iHalfLen: input, 滤波窗口半径
void MediumFilter1D(int* iDataArr, int* iFiltered, int iDataSize, int iHalfLen)
{
    int filter_size = iHalfLen * 2 + 1;
    int* filter_data;
    filter_data = (int*)calloc(filter_size, sizeof(int)); // 临时滤波窗口数据
    for (int i = 0; i < iDataSize; i++)
    {
        GetData1D(iDataArr, filter_data, iDataSize, i, iHalfLen); // 获取当前窗口数据
        BubbleSort1D(filter_data, filter_size); // 冒泡排序
        iFiltered[i] = filter_data[iHalfLen]; // 取中间值
    }
    free(filter_data);
}

// 均值滤波
// iDataArr: input, 数据数组
// iFiltered: output, 滤波后的数据
// iDataSize: input, 数据长度
// iHalfLen: input, 滤波窗口半径
void MeanFilter1D(int* iDataArr, int* iFiltered, int iDataSize, int iHalfLen)
{
    int filter_size = iHalfLen * 2 + 1;
    int* filter_data;
    filter_data = (int*)calloc(filter_size, sizeof(int)); // 临时滤波窗口数据
    for (int i = 0; i < iDataSize; i++)
    {
        int mean_val = 0;
        GetData1D(iDataArr, filter_data, iDataSize, i, iHalfLen); // 获取当前窗口数据
        for (int j = 0; j < filter_size; j++) // 计算均值
        {
            mean_val += filter_data[j];
        }
        mean_val /= filter_size;
        iFiltered[i] = mean_val;
    }
    free(filter_data);
}

int main()
{
    int test_data[] = { 3,6,1,9,4,2,0,5,8,7,10 };
    int test_size = sizeof(test_data) / sizeof(test_data[0]);
    for (int i = 0; i < test_size; i++)
    {
        printf("%d, ", test_data[i]);
    }
    printf("\n");
    
    // test GetData1D
    /*
    int half = 2;
    int* cur_data;
    cur_data = (int*)calloc(half * 2 + 1, sizeof(int));
    memset(cur_data, 0, sizeof(int) * (half * 2 + 1));
    for (int i = 0; i < test_size; i++)
    {
        GetData1D(test_data, cur_data, test_size, i, half);
        for (int ii = 0; ii < half * 2 + 1; ii++)
        {
            printf("%d, ", cur_data[ii]);
        }
        printf("\n");
    }
    free(cur_data);
    */

    // test MediumFilter1D/MeanFilter1D
    int half = 2;
    int* filtered;
    filtered = (int*)calloc(test_size, sizeof(int));
    //MediumFilter1D(test_data, filtered, test_size, half);
    MeanFilter1D(test_data, filtered, test_size, half);
    for (int i = 0; i < test_size; i++)
    {
        printf("%d, ", filtered[i]);
    }
    printf("\n");
    free(filtered);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
