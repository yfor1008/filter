// filter.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>

// 交换算法
// iDataA: input/output, 数据A
// iDataB: input/output, 数据B
template <typename T>
void swap(T &iDataA, T &iDataB)
{
    T tmp;
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
template <typename T>
void GetData1D(T *iDataArr, T *iOutArr, int iDataSize, int iIndex, int iHalfLen)
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
// 获取数据, 从数组中获取以iIndex为中心, 长度为iHalfLen*2+1的数据
// iDataArr: input, 数据数组
// iOutArr: output, 获取的数据, 长度为iHalfLen*2+1
// iDataSize: input, 数据长度
// iIndex: input, 当前位置index
// iHalfLen: input, 需要获取数据的长度的半径
template <typename T>
void GetData1D(std::vector<T> iDataArr, std::vector<T> &iOutArr, int iDataSize, int iIndex, int iHalfLen)
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
template <typename T>
void BubbleSort1D(T *iDataArr, int iDataSize, bool bOrder = 1)
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
// 冒泡排序: 一维排序, 时间复杂度O(n^2), 空间复杂度O(1), 稳定
// iDataArr: input/output, 数据数组
// iDataSize: input, 数据长度
// bOrder: input, 排序顺序, 0-从高到低(升序), 1-从低到高(降序)
template <typename T>
void BubbleSort1D(std::vector<T> &iDataArr, int iDataSize, bool bOrder = 1)
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
template <typename T>
void MediumFilter1D(T *iDataArr, T *iFiltered, int iDataSize, int iHalfLen)
{
    int filter_size = iHalfLen * 2 + 1;
    T *filter_data;
    filter_data = (T *)calloc(filter_size, sizeof(T)); // 临时滤波窗口数据
    for (int i = 0; i < iDataSize; i++)
    {
        GetData1D(iDataArr, filter_data, iDataSize, i, iHalfLen); // 获取当前窗口数据
        BubbleSort1D(filter_data, filter_size);                   // 冒泡排序
        iFiltered[i] = filter_data[iHalfLen];                     // 取中间值
    }
    free(filter_data);
}
// 中值滤波
// iDataArr: input, 数据数组
// iFiltered: output, 滤波后的数据
// iDataSize: input, 数据长度
// iHalfLen: input, 滤波窗口半径
template <typename T>
void MediumFilter1D(std::vector<T> iDataArr, std::vector<T> &iFiltered, int iDataSize, int iHalfLen)
{
    int filter_size = iHalfLen * 2 + 1;
    std::vector<T> filter_data(filter_size); // 临时滤波窗口数据
    for (int i = 0; i < iDataSize; i++)
    {
        GetData1D(iDataArr, filter_data, iDataSize, i, iHalfLen); // 获取当前窗口数据
        BubbleSort1D(filter_data, filter_size);                   // 冒泡排序
        iFiltered[i] = filter_data[iHalfLen];                     // 取中间值
    }
}

// 均值滤波
// iDataArr: input, 数据数组
// iFiltered: output, 滤波后的数据
// iDataSize: input, 数据长度
// iHalfLen: input, 滤波窗口半径
template <typename T>
void MeanFilter1D(T *iDataArr, T *iFiltered, int iDataSize, int iHalfLen)
{
    int filter_size = iHalfLen * 2 + 1;
    T *filter_data;
    filter_data = (T *)calloc(filter_size, sizeof(T)); // 临时滤波窗口数据
    for (int i = 0; i < iDataSize; i++)
    {
        T mean_val = 0;
        GetData1D(iDataArr, filter_data, iDataSize, i, iHalfLen); // 获取当前窗口数据
        for (int j = 0; j < filter_size; j++)                     // 计算均值
        {
            mean_val += filter_data[j];
        }
        mean_val /= filter_size;
        iFiltered[i] = mean_val;
    }
    free(filter_data);
}
// 均值滤波
// iDataArr: input, 数据数组
// iFiltered: output, 滤波后的数据
// iDataSize: input, 数据长度
// iHalfLen: input, 滤波窗口半径
template <typename T>
void MeanFilter1D(std::vector<T> iDataArr, std::vector<T> &iFiltered, int iDataSize, int iHalfLen)
{
    int filter_size = iHalfLen * 2 + 1;
    std::vector<T> filter_data(filter_size);
    for (int i = 0; i < iDataSize; i++)
    {
        T mean_val = 0;
        GetData1D(iDataArr, filter_data, iDataSize, i, iHalfLen); // 获取当前窗口数据
        for (int j = 0; j < filter_size; j++)                     // 计算均值
        {
            mean_val += filter_data[j];
        }
        mean_val /= filter_size;
        iFiltered[i] = mean_val;
    }
}

/******************************************************************************
* Function   : 循环迭代滤波
* Parameters :
        - iDataArr:         input   数据数组
        - iFiltered:        output  滤波后数据
        - iDataSize:        input   数据长度
        - filter_init_size: input   滤波窗口初始宽度
        - filter_num:       input   最大滤波次数
        - sample:           input   采样间隔
        - no_sampling_num:  input   不降采样张数
* Returns    :
* Notes      : 循环滤波，直到达到滤波次数或者满足条件
* Changes    : 2020/01/03
******************************************************************************/
template <typename T>
void classified_data_filtered(T *iDataArr, T *iFiltered, int iDataSize, int filter_init_size = 5, int filter_num = 20, int sample = 5, int no_sampling_num = 2000)
{
    if (iDataSize > no_sampling_num)
    {
        int sampled_num = int(ceil((iDataSize - no_sampling_num) * 1.0 / sample)) + no_sampling_num;
        T *filtered = (T *)calloc(sampled_num, sizeof(T));
        T *filtered_copy = (T *)calloc(sampled_num, sizeof(T));

        // 降采样数据
        for (int i = 0; i < sampled_num; i++)
        {
            if (i < no_sampling_num)
            {
                filtered[i] = iDataArr[i];
                filtered_copy[i] = iDataArr[i];
            }
            else
            {
                filtered[i] = iDataArr[(i - no_sampling_num) * sample + no_sampling_num];
                filtered_copy[i] = iDataArr[(i - no_sampling_num) * sample + no_sampling_num];
            }
        }

        // 滤波
        T *class2_idx = (T *)calloc(sampled_num, sizeof(T));
        T *class3_idx = (T *)calloc(sampled_num, sizeof(T));
        for (int i = 0; i < filter_num; i++)
        {
            int filter_win_size = filter_init_size + i * 5;
            MediumFilter1D(filtered_copy, filtered, sampled_num, filter_win_size);

            // 是否滤波干净
            int class2_num = 0;
            int class3_num = 0;
            for (int ii = 0; ii < sampled_num; ii++)
            {
                if (filtered[ii] == 2)
                {
                    class2_idx[class2_num] = ii;
                    class2_num += 1;
                }
                else if (filtered[ii] == 3)
                {
                    class3_idx[class3_num] = ii;
                    class3_num += 1;
                }
            }

            if (class2_num == 0)
            {
                break;
            }
            else
            {
                if (class3_num > 100) // 去除干扰
                {
                    for (int iii = sampled_num - 100; iii < sampled_num; iii++)
                    {
                        filtered[iii] = filtered[class3_idx[class3_num - 1]];
                    }
                }

                // 是否满足条件
                int begin_idx = class2_idx[0];
                int end_idx = class2_idx[class2_num - 1];
                int class2else = 0;
                for (int iii = begin_idx; iii < end_idx; iii++)
                {
                    if (filtered[iii] != 2)
                    {
                        class2else += 1;
                        break;
                    }
                }
                if (class2else == 0)
                {
                    break;
                }
            }

            memcpy(filtered_copy, filtered, sampled_num * sizeof(T));
        }
        free(class2_idx);
        free(class3_idx);

        // 升采样
        for (int i = 0; i < iDataSize; i++)
        {
            if (i < no_sampling_num)
            {
                iFiltered[i] = filtered[i];
            }
            else
            {
                iFiltered[i] = filtered[(i - no_sampling_num) / sample + no_sampling_num];
            }
        }

        free(filtered);
        free(filtered_copy);
    }
    else
    {
        sample = 1;
        T *filtered = (T *)calloc(iDataSize, sizeof(T));
        T *filtered_copy = (T *)calloc(iDataSize, sizeof(T));

        //
        for (int i = 0; i < iDataSize; i++)
        {
            filtered[i] = iDataArr[i];
            filtered_copy[i] = iDataArr[i];
        }

        // 滤波
        for (int i = 0; i < filter_num; i++)
        {
            int filter_win_size = filter_init_size + i * 10;
            MediumFilter1D(filtered_copy, filtered, iDataSize, filter_win_size);

            // 是否滤波干净
            T *class2_idx = (T *)calloc(iDataSize, sizeof(T));
            T *class3_idx = (T *)calloc(iDataSize, sizeof(T));
            int class2_num = 0;
            int class3_num = 0;
            for (int ii = 0; ii < iDataSize; ii++)
            {
                if (filtered[ii] == 2)
                {
                    class2_idx[class2_num] = ii;
                    class2_num += 1;
                }
                else if (filtered[ii] == 3)
                {
                    class3_idx[class3_num] = ii;
                    class3_num += 1;
                }
            }

            if (class2_num == 0)
            {
                break;
            }
            else
            {
                if (class3_num > 100) // 去除干扰
                {
                    for (int iii = iDataSize - 100; iii < iDataSize; iii++)
                    {
                        filtered[iii] = filtered[class3_idx[class3_num - 1]];
                    }
                }

                int begin_idx = class2_idx[0];
                int end_idx = class2_idx[class2_num - 1];
                int class2else = 0;
                for (int iii = begin_idx; iii < end_idx; iii++)
                {
                    if (filtered[iii] != 2)
                    {
                        class2else += 1;
                        break;
                    }
                }
                if (class2else == 0)
                {
                    break;
                }
            }

            memcpy(filtered_copy, filtered, iDataSize * sizeof(T));
            free(class2_idx);
            free(class3_idx);
        }

        //
        for (int i = 0; i < iDataSize; i++)
        {
            iFiltered[i] = filtered[i];
        }

        free(filtered);
        free(filtered_copy);
    }
}

int test1()
{
    int test_data[] = {3, 6, 1, 9, 4, 2, 0, 5, 8, 7, 10};
    int test_size = sizeof(test_data) / sizeof(test_data[0]);
    for (int i = 0; i < test_size; i++)
    {
        printf("%d, ", test_data[i]);
    }
    printf("\n");

    // test GetData1D
    int half = 2;
    int *cur_data;
    cur_data = (int *)calloc(half * 2 + 1, sizeof(int));
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
    if (cur_data)
    {
        free(cur_data);
    }

    // test MediumFilter1D/MeanFilter1D
    int *filtered;
    filtered = (int *)calloc(test_size, sizeof(int));
    MediumFilter1D(test_data, filtered, test_size, half);
    //MeanFilter1D(test_data, filtered, test_size, half);
    for (int i = 0; i < test_size; i++)
    {
        printf("%d, ", filtered[i]);
    }
    printf("\n");
    if (filtered)
    {
        free(filtered);
    }

    printf("test1 down!\n");
    return 0;
}

int test2()
{
    std::vector<int> test_data = {3, 6, 1, 9, 4, 2, 0, 5, 8, 7, 10};
    int test_size = test_data.size();
    for (int i = 0; i < test_size; i++)
    {
        printf("%d, ", test_data[i]);
    }
    printf("\n");

    // test GetData1D
    int half = 2;
    std::vector<int> cur_data(half * 2 + 1);
    for (int i = 0; i < test_size; i++)
    {
        GetData1D(test_data, cur_data, test_size, i, half);
        for (int ii = 0; ii < half * 2 + 1; ii++)
        {
            printf("%d, ", cur_data[ii]);
        }
        printf("\n");
    }

    // test MediumFilter1D/MeanFilter1D
    std::vector<int> filtered(test_size);

    MediumFilter1D(test_data, filtered, test_size, half);
    //MeanFilter1D(test_data, filtered, test_size, half);
    for (int i = 0; i < test_size; i++)
    {
        printf("%d, ", filtered[i]);
    }
    printf("\n");

    printf("test2 down!\n");
    return 0;
}

#include <math.h>
int main(int argc, char *argv[])
{
    //test1();
    //test2();

    // 采样测试
    // int filter_init_size = 21;
    // int num = 20;
    // int sample = 5;
    // int no_sampling_num = 200;

    // int iDataSize = 500;
    // std::vector<int> data(iDataSize);
    // for (int i = 0; i < iDataSize; i++)
    // {
    //     data[i] = i;
    // }

    // int len = int(ceil((iDataSize - no_sampling_num) * 1.0 / sample)) + no_sampling_num;
    // //printf("%d", len);

    // std::vector<int> sampled_data(len);
    // for (int i = 0; i < len; i++)
    // {
    //     if (i < no_sampling_num)
    //     {
    //         sampled_data[i] = data[i];
    //     }
    //     else
    //     {
    //         sampled_data[i] = data[(i - no_sampling_num) * sample + no_sampling_num];
    //     }
    // }

    // std::vector<int> filtered(iDataSize);
    // for (int i = 0; i < iDataSize; i++)
    // {
    //     if (i < no_sampling_num)
    //     {
    //         filtered[i] = sampled_data[i];
    //     }
    //     else
    //     {
    //         filtered[i] = sampled_data[(i - no_sampling_num) / sample + no_sampling_num];
    //     }
    // }

    // for (int i = 0; i < iDataSize; i++)
    // {
    //     printf("%d, %d\n", data[i], filtered[i]);
    // }

    // 读取文本
    FILE *pFileRead = fopen("zz.log", "r");
    if (NULL == pFileRead)
    {
        printf("open %s failed!", "zz.log");
        return -1;
    }

    std::vector<int> datas;
    int data;
    while (!feof(pFileRead))
    {
        fscanf(pFileRead, "%d\n", &data);
        datas.push_back(data);
    }

    // 滤波测试
    int iSize = datas.size();
    int *iDataList = (int *)calloc(iSize, sizeof(int));
    for (int i = 0; i < iSize; i++)
    {
        iDataList[i] = datas[i];
    }

    // 保存滤波前数据
    FILE *pFile1 = fopen("filter_before.txt", "w");
    if (NULL == pFile1)
    {
        printf("open %s failed!", "filter_before.txt");
    }
    for (int i = 0; i < iSize; i++)
    {
        fprintf(pFile1, "%d\n", iDataList[i]);
    }
    fclose(pFile1);

    // 滤波
    int *iFiltered = (int *)calloc(iSize, sizeof(int));
    classified_data_filtered(iDataList, iFiltered, iSize);

    // 保存滤波后数据
    FILE *pFile2 = fopen("filter_after.txt", "w");
    if (NULL == pFile2)
    {
        printf("open %s failed!", "filter_after.txt");
    }
    for (int i = 0; i < iSize; i++)
    {
        fprintf(pFile2, "%d\n", iFiltered[i]);
    }
    fclose(pFile2);

    free(iDataList);
}
