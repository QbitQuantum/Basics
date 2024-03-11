
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
    int conv_1[] = {
    1, 2, 3, /*4, 5, 6, 7, 8, 9,*/
    };
    int conv_2[][3] = {
        {1, 2, 3},
        {4, 5, 6},
        //{7, 8, 9}
    };
    auto m = "d";
    int conv_test[] = { 1, 2, 3, 4 };
    int conv_cout[3] = {};

    int sum = 0;
    
    int a = 0;
    for (size_t i = 0; i < size(conv_test); i++)
    {
        //cout << ++a;
    }

    cout << arc_test(conv_1);

    //level_2(conv_2, 2, 2);
    //arc(conv_1);
    
};
