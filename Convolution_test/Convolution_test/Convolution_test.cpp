﻿
#include <iostream>
#include <string>
#include <type_traits> // Для std::extent
#include <algorithm>
#include <iomanip>
#include <string_view>

template <typename T, size_t Ta >
int level_1(T(&arr1)[Ta], int f) {

    for (size_t i = 0; i < f; i++)
    {
            return arr1[i];
    }
}

template <typename T, size_t Ta, size_t Taa >
void level_2(T(&arr1)[Ta][Taa], int f, int f2) {

    for (size_t i = 0; i < f; i++)
    {
        for (size_t j = 0; j < f2; j++)
        {
           cout << arr1[i][j];
        }
    }
}

template <typename T, size_t Ta, typename D, size_t Da >
void conv2D(T(&arr1)[Ta], D(&arr2)[Da], bool invert) {
    int db[Ta][Da];
    for (int i = 0; i < Ta; ++i) {
        for (int j = 0; j < Da; ++j) {
            db[i][j] = arr1[i] * arr2[j];
        }
    }
    const int size_db = extent<decltype(db), 0>::value;
    const int size_db_2 = extent<decltype(db), 1>::value;
    const int parametr_db_min = min(size_db, size_db_2);
    const int parametr_db_max = max(size_db, size_db_2);
    int sum_k[parametr_db_max]{};
    int sum_z[parametr_db_min]{};
    if (invert) {
        for (int i = 0; i < size_db; i++)
        {
            for (int j = size_db_2 - 1; j >= 0; j--)
            {
                int sum_index = i + j;
                for (int k = 0; k < parametr_db_max; k++)
                {
                    if (sum_index == k) {
                        sum_k[k] += db[i][j];
                    }
                }
                for (int z = 0; z <= parametr_db_min; z++)
                {
                    if (sum_index == size_db + size_db_2 - z) {
                        sum_z[z - 1] += db[i][j];
                    }
                }
            }
        }
        for (int i = 0; i < parametr_db_max; i++) {
            std::cout << sum_k[i] << " ";
        }
        reverse(sum_z, sum_z + parametr_db_min);
        for (int i = 0; i < parametr_db_min - 1; i++) {
            std::cout << sum_z[i] << " ";
        }
    }
    else
    {
        for (int i = 0; i < size_db; i++)
        {
            for (int j = 0; j < size_db_2; j++)
            {
                int difference_index = i - j;
                for (int k = 0; k < parametr_db_max; k++)
                {
                    if (difference_index == -k) {
                        sum_k[k] += db[i][j];
                    }
                }
                for (int z = 1; z <= parametr_db_min; ++z)
                {
                    if (difference_index == z) {
                        sum_z[z - 1] += db[i][j];
                    }
                }
            }
        }
        reverse(sum_k, sum_k + parametr_db_max);
        for (int i = 0; i < parametr_db_max; i++) {
            std::cout << sum_k[i] << " ";
        }
        for (int i = 0; i < parametr_db_min - 1; i++) {
            std::cout << sum_z[i] << " ";
        }
    }
}

int main()
{
    /*
       123    123   123  123  123    123    123
    456     456    456   456   456     456     456
    */

    int conv_1[] = { 1, 2, 3, /*4, 5, 6, 7, 8, 9,*/ };
    int conv_test[] = { /*1, 2, 3,*/ 4, 5, 6,/* 7, 8, 9 */};
    int conv_couting[] = { /*1, 2, 3,4, 5, 6, */ 7, 8, 9, };

    std::cout << "conv2D = ";
    conv2D(conv_1, conv_test, true);
    std::cout << "\n";
    std::cout << "conv2D_invert = ";
    conv2D(conv_1, conv_test, false);

};
