int main()
{
    // initialization test
    ArrayList<int> a;
    assert(a.isEmpty());
    assert(a.size() == 0);
    a.add(1);
    assert(!a.isEmpty());
    assert(a.size() == 1);
    a.clear();
    assert(a.isEmpty());
    a.add(1);
    assert(a.size() == 1);

    a.fromArray(source, lengthOfSource);
    assert(a.size() == lengthOfSource);
    a.toArray(destination);
    for (int i = 0; i < lengthOfSource; i++) {
        assert(source[i] == destination[i]);
    }

    // get and set test
    a.clear();
    for (int i = 1; i < 100; i += 2) {
        a.add(i);
    }
    for (int i = 0; i < a.size(); i++) {
        a.set(i, a.get(i) - 1);
    }
    for (int i = 0; i < a.size(); i++) {
        assert(a.get(i) == i * 2);
    }
    for (int i = 0; i < 100; i++) {
        if (i % 2 == 1) {
            assert(!a.contains(i));
        } else {
            assert(a.contains(i));
        }
    }

    // add and remove test
    a.fromArray(source, lengthOfSource);
    for (int i = 0; i < 3; i++)
        a.add(0, 0);
    for (int i = 0; i < 5; i++) 
        a.add(5, 5);
    for (int i = 0; i < 8; i++)
        a.add(98);
    a.output();
    // (0 0 0 0 1 4 5 5 5 5 5 8 16 22 41 56 98 98 98 98 98 98 98 98)
    assert(a.indexOf(0) == 0);
    assert(a.lastIndexOf(0) == 2);
    assert(a.indexOf(5) == 5);
    assert(a.lastIndexOf(5) == 9);
    assert(a.indexOf(98) == 15);
    assert(a.lastIndexOf(98) == 22);
    for (int i = 0; i < 5; i++)
        a.removeByIndex(5);
    for (int i = 0; i < 3; i++)
        a.removeByIndex(0);
    // should be (1 4 8 16 22 41 56 98 98 98 98 98 98 98 98)
    while (a.remove(98))
        ;  // empty loop body!
    a.output();
    // should be (1 4 8 16 22 41 56)
    a.removeRange(1, 5);
    a.output();
    // should be (1 41 56)


    return 0;
}