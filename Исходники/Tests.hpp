void TestList() {
    List<int> a;
    a.Add(3);
    a.Add(5);
    assert(a.Count() == 2);
    assert(a.Contains(3));
    assert(a.Contains(5));
    assert(a[0] == 3);

    List<int> b(a);
    b.Add(a);
    assert(b.Count() == 4);
    a.Remove(3);
    assert(a.Count() == 1);
    assert(a.Contains(3) == false);
    assert(a[0] = 5);
    
    a.Insert(4, 0);
    a.Insert(6, 1);
    a.Insert(7, a.Count() - 1);
    assert(a[0] == 4);
    assert(a[1] == 6);
    assert(a[2] == 7);

    a.Remove(6);
    assert(a[2] == 5);
}