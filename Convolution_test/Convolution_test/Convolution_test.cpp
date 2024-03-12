
#include <iostream>
#include <string>
#include <type_traits> // Для std::extent

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

int size(int arr[]) { return sizeof(arr) / sizeof(arr[0]) + 1; }

static int arc_test(int arr[]) {
        return size(arr);
}

int main()
{

    
    int matrix[] = {
            4,  5,  6,

        1,  4,   5,  6,

        2,  8,  10,  12,

        3,  12, 15,  18

    };


    //Балуемся
    int couting1[][1] =
    {
     {1}
    //couting[]
    };

    int conv_2[][3] = {
        {1, 2, 3},
        {4, 5, 6},
        //{7, 8, 9}
    };
    auto m = "d";

    int conv_cout[3] = {};




    int conv_1[] = { 1, 2, 3, /*4, 5, 6, 7, 8, 9,*/ };
    int conv_test[] = { /*1, 2, 3,*/ 4, 5, 6,/* 7, 8, 9 */};
    int conv_couting[] = { /*1, 2, 3,4, 5, 6, */ 7, 8, 9, };
    /*
       123
    456

      123
    456

     123
    456

    123
    456

    123
     456

    123
      456

    123
       456
    */

    //создаём нормальную сборку ))    //свёртку*
    int size_conv_1 = size(conv_1);
    //cout << size_conv_1 << endl;
    int size_conv_2 = size(conv_test);
    //cout << size_conv_2 << endl;
    int parametr = size_conv_1 + size_conv_2 - 1;

    for (int i = 1; i <= size(conv_1) + size(conv_2) - 1 /*6*/; i++) {
        //Код;
    }
    int iteration_1 = conv_1[0] * conv_test[2];
    int iteration_2 = conv_1[0] * conv_test[1] + conv_1[1] * conv_test[2];
    int iteration_3 = conv_1[0] * conv_test[0] + conv_1[1] * conv_test[1]+ conv_1[2] * conv_test[2];
    int iteration_4 = conv_1[1] * conv_test[0] + conv_1[2] * conv_test[1];
    int iteration_5 = conv_1[2] * conv_test[0];

    cout << iteration_1 << endl;
    cout << iteration_2 << endl;
    cout << iteration_3 << endl;
    cout << iteration_4 << endl;
    cout << iteration_5 << endl;
    int n = sizeof(conv_1) / sizeof(conv_1[0]); // Количество элементов в массивах
    for (int i = 0; i < i <= n-1; i++) {
        int sum = 0;
        for (int j = 0; j <= i; j++) {
            sum += conv_1[j] * conv_test[i - j];
        }
        std::cout << "iteration_" << (i + 1) << " = " << sum << std::endl;
    }


    for (size_t i = 1; i <= size_conv_1; i++)
    {
        for (size_t i = 1; i <= size_conv_2; i++)
        {
            int a = 0;
        }
    }

    int sum = 0;
    
    int a = 0;
    for (size_t i = 0; i < size(conv_test); i++)
    {
        //cout << ++a;
    }
    //cout << arc_test(conv_1);

    //level_2(conv_2, 2, 2);
    //arc(conv_1);
    
};
