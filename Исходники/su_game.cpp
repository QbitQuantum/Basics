QSet<int> SuGame::getBlockOfField_(std::vector<SuFieldCell> &field, int x, int y)
{
    QSet<int> block;

    int beginCol = (x / 3) * 3;
    int beginRow = (y / 3) * 3;

    for(int row = 0; row < 3; row++)
    {
        for(int col = 0; col < 3; col++)
        {
            block.insert(field[(beginRow + row) * LEN_SIDE_OF_FIELD + beginCol + col].value);
        }
    }

    block.remove(0);

    return block;
}