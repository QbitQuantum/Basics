#include <functional>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <map>
#include <type_traits>
#include <variant>
#include <stdarg.h>

class cP {
public:
    int health = 100;
    int epoch = 10;
    struct _Brain
    {

        int massiv[8][8] = {
    {  2,  5, 11, 17,  6, 20, 12,  0 },
    { 18,  9,  7, 19,  7,  8,  3,  1 },
    { 14, 20, 15, 10,  6,  2, 16, 21 },
    { 22, 10,  0, 23, 16,  5,  4, 14 },
    {  8,  3,  4, 13,  1, 12,  9, 11 },
    {  9, 18,  4, 15, 17, 19, 13,  3 },
    { 23, 13,  1,  2, 22,  8, 16, 21 },
    { 22,  7, 18, 15, 14, 17,  0, 24 }
        };

        void Run(int array[8][8]) {

        }
    };
    struct _Action
    {
        void MoveNorthwest() { std::cout << "MoveNorthwest"; };
        void MoveNorth() { std::cout << "MoveNorth"; }
        void MoveNortheast() { std::cout << "MoveNortheast"; }
        void MoveEast() { std::cout << "MoveEast"; }
        void MoveSoutheast() { std::cout << "MoveSoutheast"; }
        void MoveSouth() { std::cout << "MoveSouth"; }
        void MoveSouthwest() { std::cout << "MoveSouthwest"; }
        void MoveWest() { std::cout << "MoveWest"; }

        void TurnNorthwest() { std::cout << "TurnNorthwest"; };
        void TurnNorth() { std::cout << "TurnNorth"; }
        void TurnNortheast() { std::cout << "TurnNortheast"; }
        void TurnEast() { std::cout << "TurnEast"; }
        void TurnSoutheast() { std::cout << "TurnSoutheast"; }
        void TurnSouth() { std::cout << "TurnSouth"; }
        void TurnSouthwest() { std::cout << "TurnSouthwest"; }
        void TurnWest() { std::cout << "TurnWest"; }

        std::map<int, std::function<void()>> actionMap;


    };

    struct _State
    {
        std::string Default = "north";

        void StateNorthwest() { Default = "northwest"; std::cout << Default; };
        void StateNorth() { Default = "north"; std::cout << Default; }
        void StateNortheast() { Default = "northeast"; std::cout << Default; }
        void StateEast() { Default = "east"; std::cout << Default; }
        void StateSoutheast() { Default = "southeast"; std::cout << Default; }
        void StateSouth() { Default = "south"; std::cout << Default; }
        void StateSouthwest() { Default = "southwest"; std::cout << Default; }
        void StateWest() { Default = "west"; std::cout << Default; }

        std::map<int, std::function<void()>> stateMap;
    };
    _Brain brain;
    _Action action;
    _State state;
};

int main() {
    cP cp;
    cp.action.actionMap[0] = [&cp]() { cp.action.MoveNorthwest(); };
    cp.action.actionMap[1] = [&cp]() { cp.action.MoveNorth(); };
    cp.action.actionMap[2] = [&cp]() { cp.action.MoveNortheast(); };
    cp.action.actionMap[3] = [&cp]() { cp.action.MoveEast(); };
    cp.action.actionMap[4] = [&cp]() { cp.action.MoveSoutheast(); };
    cp.action.actionMap[5] = [&cp]() { cp.action.MoveSouth(); };
    cp.action.actionMap[6] = [&cp]() { cp.action.MoveSouthwest(); };
    cp.action.actionMap[7] = [&cp]() { cp.action.MoveWest(); };

    cp.action.actionMap[8] = [&cp]() { cp.action.TurnNorthwest(); };
    cp.action.actionMap[9] = [&cp]() { cp.action.TurnNorth(); };
    cp.action.actionMap[10] = [&cp]() { cp.action.TurnNortheast(); };
    cp.action.actionMap[11] = [&cp]() { cp.action.TurnEast(); };
    cp.action.actionMap[12] = [&cp]() { cp.action.TurnSoutheast(); };
    cp.action.actionMap[13] = [&cp]() { cp.action.TurnSouth(); };
    cp.action.actionMap[14] = [&cp]() { cp.action.TurnSouthwest(); };
    cp.action.actionMap[15] = [&cp]() { cp.action.TurnWest(); };

    cp.state.stateMap[16] = [&cp]() { cp.state.StateNorthwest(); };
    cp.state.stateMap[17] = [&cp]() { cp.state.StateNorth(); };
    cp.state.stateMap[18] = [&cp]() { cp.state.StateNortheast(); };
    cp.state.stateMap[19] = [&cp]() { cp.state.StateEast(); };
    cp.state.stateMap[20] = [&cp]() { cp.state.StateSoutheast(); };
    cp.state.stateMap[21] = [&cp]() { cp.state.StateSouth(); };
    cp.state.stateMap[22] = [&cp]() { cp.state.StateSouthwest(); };
    cp.state.stateMap[23] = [&cp]() { cp.state.StateWest(); };
    
    for (int i = 0; ; ++i) {
        cp.health--;
        if (cp.health == 0) {
            cp.health = 100;
        }
        for (int j = 0; j < 8; ++j) {
            cp.health--;
            std::cout << cp.health << std::endl;
            std::cout << " " << cp.brain.massiv[i % 8][j % 8] << " ";
            if (cp.brain.massiv[i % 8][j % 8] >= 0 && cp.brain.massiv[i % 8][j % 8] <= 15) {
                cp.action.actionMap[cp.brain.massiv[i % 8][j % 8]]();
                std::cout << std::endl;
            }
            else
                if (cp.brain.massiv[i % 8][j % 8] >= 16 && cp.brain.massiv[i % 8][j % 8] <= 23) {
                    cp.state.stateMap[cp.brain.massiv[i % 8][j % 8]]();
                    std::cout << std::endl;
                }
        }
    } 
}
/*
void printArray(int massiv[8][8]) {
    // Перебор всех элементов массива
    std::cout << " massiv[8][8] = {";
    std::cout << std::endl;
    for (int i = 0; i < 8; ++i) {
        std::cout << "{ ";
        for (int j = 0; j < 8; ++j) {
            // Вывод элемента массива с запятой и пробелом, кроме последнего элемента в строке
            if (j != 7)
                std::cout << massiv[i][j] << ", ";
            else
                std::cout << massiv[i][j];
        }
        std::cout << " }," << std::endl;
    }
    std::cout << " }";

}
*/

/*
int summer(int arr[5]) {
    int sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += arr[i];
    }
    return sum;
}
void fignya(int x) {
    int mass[5] = {};
    int pop = 0;
    for (int D=0;; D++) {
        pop++;
        int sum = summer(mass);
        if (sum == x) {
            std::cout << "Popitka = " << pop;
            break;
        }
        for (int i = 0; i < std::size(mass); i++) {
            if (sum != x) {
                mass[i] = (rand() % x) + 1 - 1 + 1;
            }
            std::cout << mass[i] << " ";
        }
        std::cout << std::endl;
    }
};
*/

/*
20:
5 7 2 5 1
Popitka = 787

х4,64

200:
11 8 77 72 32
Popitka = 3657

х0,67

2000:
250 308 453 613 376
Popitka = 2456

x168

20000:
374 290 11385 1457 6494
Popitka = 413309
*/

/*
    //printArray(cp.brain.massiv);
    //int a = 2000;
    //fignya(a);