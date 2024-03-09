
#include <iostream>
#include <string>
#include <type_traits> // Для std::extent
using namespace std;

/*

*/
void arc(int arr[]) {
    // cout << extent<decltype(arr), -1>::value;
    for (int i = 0; i < extent<decltype(arr), 0>::value; i++) {
        cout << extent<decltype(arr), 0>::value << endl;
    }

}

void arc_test(int arr[]) { } 

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
    int conv_test[] = {1, 2, 3,4};
    int conv_cout[3] = {};

    
    int sum = 0;
    for (int i = 0; i < extent<decltype(conv_test), 0>::value; i++) {
        for (int j = 0; j < extent<decltype(conv_1), 0>::value; j++) {
            sum += conv_test[i] * conv_1[j];
            cout << sum<< " ";
        }
        cout << endl;
    }

    //arc(conv_1);

        for (int i = 0; i < extent<decltype(conv_2), 0>::value; i++) {
        //cout << "i = " << i << " ";
        int sum = 0;
        for (int j = 0; j < extent<decltype(conv_2), 1>::value; j++)
        {
            cout << "i = " << i << " ";
            //cout << "j = " << j << " " << endl;
            cout << "j = " << j << " ";
            //cout << i << " " << j << " = ";
            sum = conv_2[i][j] * conv_test[j];
            cout << conv_2[i][j] << " ";
            cout << sum << " " << endl;
            //cout << sum << endl;
        }
        //cout << sum << endl;
    }
    // std::cout << "Hello World!\n";
}

