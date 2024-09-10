void Map_Test::Map_remove()
{
    Map<int, int> M;
    M.add(2,3);
    M.remove(2);
    QCOMPARE(M.find(2),false);
}