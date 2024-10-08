int main()
{
    enum Status {CONTINUE, WON, LOST};

    int myPoint;
    Status gameStatus;

    srand(time(0));

    int sumOfDice = rollDice();

    switch (sumOfDice)
    {
        case 7:
        case 11:
            gameStatus = WON;
            break;
        case 2:
        case 3:
        case 12:
            gameStatus = LOST;
            break;
        default:
            gameStatus = CONTINUE;
            myPoint = sumOfDice;
            cout << "Point is " << myPoint << endl;
            break;
    }

    while (gameStatus == CONTINUE)
    {
        sumOfDice = rollDice();

        if (sumOfDice == myPoint)
            gameStatus = WON;
        else if(sumOfDice == 7)
            gameStatus = LOST;
    }

    if (gameStatus == WON)
        cout << "Player wins" << endl;
    else
        cout << "Player loses" << endl;

    return 0;
}