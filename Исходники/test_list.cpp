void test_add_head_when_list_is_empty()
{
    List l;
    Node n(11);

    l.add_head(&n);

    // 長さのチェック --- (a)
    TEST_ASSERT(l.length() == 1);
    // add_headで追加した要素が確かに取得できる --- (b)
    TEST_ASSERT(l.get_head()->get() == 11);
    // 11の要素しかふくまれないことを確認するassertion --- (c)
    TEST_ASSERT(l.get_head()->next() == NULL);
}