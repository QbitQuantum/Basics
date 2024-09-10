void SnakeGameView::render(Graphics2D& g)
{
#if 0
    g.clearScreen(g.makeRGB(0xFF,0xFF,0xFF));

    for(int y = 0; y < mBoard.height(); ++y) {
        for(int x = 0; x < mBoard.width(); ++x) {
            GameBoard::BoardState st = mBoard.boardStateAt(x,y);
            switch (st) {
            case GameBoard::BoardStateSnake:
                g.fillRect(x << 3, y << 3, 8, 8, g.makeRGB(0, 255, 0));
                break;
            case GameBoard::BoardStateFood:
                g.fillRect(x << 3, y << 3, 8, 8, g.makeRGB(0, 0, 255));
                break;
            case GameBoard::BoardStateBlock:
                g.fillRect(x << 3, y << 3, 8, 8, g.makeRGB(0, 0, 0));
                break;
            default:
                break;
            }
        }
    }
#endif

}