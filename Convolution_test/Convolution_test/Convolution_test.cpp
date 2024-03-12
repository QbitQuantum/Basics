
#include <iostream>
#include <string>
#include <type_traits> // Для std::extent
#include <algorithm>
#include <iomanip>
#include <iostream>
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
    
                //Смог получить доступ к жементам и рализорвать цикл
                    /*
                for (int y = 0; y < size_db+ size_db_2-1; y++)
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

    const int db[4][3] = {
    {4, 5 ,6},
    {8, 10, 12},
    {12, 15, 18},
    {16, 20, 24},
    };

    const int size_db = extent<decltype(db), 0>::value;
    const int size_db_2 = extent<decltype(db), 1>::value;
    int parametr_db = max(size_db, size_db_2);

    int couts = 0;
    int coutss = 0;
    for (int i = 0; i < size_db; i++)
    {
        for (int j = 0; j < size_db_2; j++)
        {

            for (int z = 0; z > -size_db; --z)
            {
                if (i - j == z) {
                    //sum += db[i-1][j];
                    cout << "db[i][j-1] = " << db[i][j] << endl;
                    couts++;
                }
            }
            coutss++;
            for (int z = 0; z < size_db_2 - 1; z++)
            {
                    if (i - j == z) {
                        //sum += db[i-1][j];
                        cout << "db[i][j-1] = " << db[i][j] << endl;
                        couts++;
                    }    
            }
        }
    }
    cout << "Elem = "<<couts << endl;
    cout << "Iteration = " << coutss << endl;

};
