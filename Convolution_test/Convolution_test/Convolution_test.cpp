
#include <iostream>
#include <string>
#include <type_traits> // Для std::extent
#include <algorithm>
#include <iomanip>
#include <string_view>

using namespace std;

template <typename T, size_t Ta >
int level_1(T(&arr1)[Ta], int f) {

    for (size_t i = 0; i < f; i++)
    {
            return arr1[i];
    }
}

template <typename T,size_t Ta, size_t Taa >
void level_2(T(&arr1)[Ta][Taa], int f, int f2) {

    for (size_t i = 0; i < f; i++)
    {
        for (size_t j = 0; j < f2; j++)
        {
           cout << arr1[i][j];
        }
    }
}
void arc(int arr[]) {
    // cout << extent<decltype(arr), -1>::value;
    for (int i = 0; i < extent<decltype(arr), 0>::value; i++) {
        cout << extent<decltype(arr), 0>::value << endl;
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

    int db_null[3][3] = {
        {},
        {},
        {},
    };
   
    int iteration_1 = conv_1[0] * conv_test[2];
    int iteration_2 = conv_1[0] * conv_test[1] + conv_1[1] * conv_test[2];
    int iteration_3 = conv_1[0] * conv_test[0] + conv_1[1] * conv_test[1] + conv_1[2] * conv_test[2];
    int iteration_4 = conv_1[1] * conv_test[0] + conv_1[2] * conv_test[1];
    int iteration_5 = conv_1[2] * conv_test[0];
    cout << "-----------------------------------------" << endl;
    /*
    cout << iteration_1 << endl;
    cout << iteration_2 << endl;
    cout << iteration_3 << endl;
    cout << iteration_4 << endl;
    cout << iteration_5 << endl;
    */
    
                //Смог получить доступ к элементам и рализорвать цикл
                    /*
                for (int y = 0; y < size_db + size_db_2 - 1; y++)
                {
                    if (i - j == -2) {
                        //sum += db[i-1][j];
                        cout << "db[i][j-1] = " << db[i][j] << endl;
                    }
                    if (i - j == 0)
                    {
                        //sum += db[i][j];
                        //cout << "db[i][j] = "<< db[i][j]<<endl;
                    }
                    if (i - j == 3) {
                        //sum += db[i-1][j];
                        //cout << "db[i-1][j] = " << db[i][j] << endl;;
                    }
                }
                */
    
    

    cout << "-----------------------------------------" << endl;

    /*
    const int db[3][3] = {
        {4,   5 ,   6},
        {8,   10,   12},
        {12,  15,   18},
    };

    const int size_db = extent<decltype(db), 0>::value;
    const int size_db_2 = extent<decltype(db), 1>::value;
    const int parametr_db_min = min(size_db, size_db_2);
    const int parametr_db_max = max(size_db, size_db_2);

    int couts = 0;
    int coutss = 0;
    int sum_k[parametr_db_max]{};
    int sum_z[parametr_db_min]{};

    for (int i = 0; i < size_db; i++)
    {
        for (int j = 0; j < size_db_2; j++)
        {   // max value
            
            for (int k = 0; k < parametr_db_max; k++)
            {
                if (i - j == -k) {
                    cout << "Index k = " << k << endl;
                    //cout << "\033[44m";
                    //cout << "db[" + to_string(i) + "][" + to_string(j) + "] = " << db[i][j] << endl;
                    //cout << "\033[0m";
                    sum_k[k] += db[i][j];
                    //couts++;
                }
            }            
            for (int z = 1; z <= parametr_db_min; ++z)
            {
                if (i - j == z) {
                    cout << "Index z = " << z << endl;
                    //cout << "\033[41m";
                    //cout << "db[" + to_string(i) + "][" + to_string(j) + "] = " << db[i][j] << endl;
                    //cout << "\033[0m";
                    sum_z[z-1] += db[i][j];
                    //couts++;
                }
            }
            //coutss++;
        }
    }
    cout << endl;
    cout << "massiv k:" << endl;
    reverse(sum_k, sum_k + parametr_db_max);
    for (int i = 0; i < parametr_db_max; i++) {
        cout << "\033[44m";
        std::cout << sum_k[i] << " "; // Выводим каждый элемент массива
        cout << "\033[0m";
    }
    cout << endl;
    cout << "massiv z:" << endl;
    for (int i = 0; i < parametr_db_min-1; i++) {
        cout << "\033[41m";
        std::cout << sum_z[i] << " "; // Выводим каждый элемент массива
        cout << "\033[0m";
    }

    //cout << "Elem = " + couts << endl;
    //cout << "Iteration = " + coutss << endl;
    */
    const int arr1[]{ 1, 2, 3 };
    const int arr2[]{ 4, 5, 6 };
    const int sizes_1 = size(arr1);
    const int sizes_2 = size(arr2);
    int db[sizes_1][sizes_2]; 

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            db[i][j] = arr1[i] * arr2[j];
        }
    }

    const int size_db = extent<decltype(db), 0>::value;
    const int size_db_2 = extent<decltype(db), 1>::value;
    const int parametr_db_min = min(size_db, size_db_2);
    const int parametr_db_max = max(size_db, size_db_2);
    int sum_k[parametr_db_max]{};
    int sum_z[parametr_db_min]{};

    for (int i = 0; i < size_db; i++)
    {
        for (int j = 0; j < size_db_2; j++)
        { 
            for (int k = 0; k < parametr_db_max; k++)
            {
                if (i - j == -k) {
                    sum_k[k] += db[i][j];
                }
            }
            for (int z = 1; z <= parametr_db_min; ++z)
            {
                if (i - j == z) {
                    sum_z[z - 1] += db[i][j];
                }
            }
        }
    }
    reverse(sum_k, sum_k + parametr_db_max);
    for (int i = 0; i < parametr_db_max; i++) {
        std::cout << sum_k[i] << " "; // Выводим каждый элемент массива
    }
    for (int i = 0; i < parametr_db_min - 1; i++) {
        std::cout << sum_z[i] << " "; // Выводим каждый элемент массива
    }
};
