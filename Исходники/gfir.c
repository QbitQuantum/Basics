void InitializeGame()
{
    game.Initialize();
    srand(time(NULL));
    game.playerIDList.push_back(2);
    game.SetGamerAI(2, 10);
    DrawBoard();
}