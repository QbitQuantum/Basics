int test_map() {
    string a = "hello.",
           b = "how.",
           c = "are.",
           d = "you.",
           e = "my.",
           f = "name.",
           g = "is.",
           t1, t2;

    /** test collision */
    Map<string, string> map(1);
    test(map.hash(a), map.hash(a));
    test(map.hash(b), map.hash(b));
    test(map.hash(g), map.hash(g));
    map["greeting"] = "hello";
    map["phrase"] = "how are you";
    map["phrase_two"] = "but I\'m hopin\' all the same";
    t1 = map["greeting"];
    t2 = map["greeting"];
    map["phrase"] = "I don\'t even know your name";
    test(t1, t2);
    t2 = "I don\'t even know your name";
    test(map["phrase"], t2);

    /** test with higher size */
    Map<int, string> map2(128);
    test(map2.hash(1), map2.hash(1));
    test(map2.hash(2), map2.hash(2));
    test(map2.hash(3), map2.hash(3));
    map2[1] = "hello";
    map2[2] = "how are you";
    map2[3] = "but I\'m hopin\' all the same";
    t1 = map2[1];
    t2 = map2[1];
    map2[2] = "I don\'t even know your name";
    test(t1, t2);
    t2 = "I don\'t even know your name";
    test(map2[2], t2);

    /** test with object keys */
    Thing l1, l2, l3;
    Map<Thing, string> map3(1024);
    test(map3.hash(l1), map3.hash(l1));
    test(map3.hash(l2), map3.hash(l2));
    test(map3.hash(l3), map3.hash(l3));
    map3[l1] = "hello";
    map3[l2] = "how are you";
    map3[l3] = "but I\'m hopin\' all the same";
    t1 = map3[l1];
    t2 = map3[l1];
    map3[l2] = "I don\'t even know your name";
    test(t1, t2);
    t2 = "I don\'t even know your name";
    test(map3[l2], t2);

    /** test overloaded hash key */
    Map<int, int> dictionary;
    int k = 100;
    while (k-- > 0) {
        dictionary[k] = 3;
    }

    dictionary[101] = 5;
    k = 100;
    while (k-- > 0) {
        if (dictionary[k] != 3) {
            test(dictionary[k], 3);
        } else {
            if (k % 10 == 0) {
                test(dictionary[k], 3);
            }
        }
    }
    test(dictionary[101], 5);

    auto keys1 = dictionary.keys();
    test(keys1.size(), 101);
    keys1.clear();

    auto keys2 = dictionary.keys();
    test(keys2.size(), 101);

    /** test hash set */
    Map<int, bool> bMap;
    bMap[0] = true;
    bMap[1] = false;
    test(bMap[0], true);
    test(bMap[1], false);

    bool test1, test2;
    Set<int> s1;
    test1 = s1.contains(false);
    test2 = s1.contains(true);
    test(test1, false);
    test(test2, false);

    s1.add(0);
    test1 = s1.contains(0);
    test2 = s1.contains(1);
    test(test1, 1);
    test(test2, 0);

    s1.add(1);
    test1 = s1.contains(0);
    test2 = s1.contains(1);
    test(test1, 1);
    test(test2, 1);

    s1.remove(0);
    test1 = s1.contains(0);
    test2 = s1.contains(1);
    test(test1, 0);
    test(test2, 1);

    s1.remove(1);
    test1 = s1.contains(0);
    test2 = s1.contains(1);
    test(test1, 0);
    test(test2, 0);

    s1.add(0);
    s1.add(1);
    test1 = s1.contains(0);
    test2 = s1.contains(1);
    test(test1, 1);
    test(test2, 1);

    s1.clear();
    test1 = s1.contains(0);
    test2 = s1.contains(1);
    test(test1, 0);
    test(test2, 0);

    {
        int A = 5, B = 6;
        Set<int> S;
        S.add(A);
        S.add(A);
        S.add(A);
        console_test(S.contains(A));
        console_test(!S.contains(B));
        console_test(S.size(), 1);
        console_test(S.values().size(), 1);
        console_test(S.values().contains(A));
        S.add(B);
        console_test(S.size(), 2);
        console_test(S.values().size(), 2);
        console_test(S.values().contains(A));
        S.remove(A);
        console_test(S.size(), 1);
        console_test(S.values().size(), 1);
        console_test(S.values().contains(B));
    }

    {
        Set<string> words;
        words.add("hello");
        words.add("world");
        console_test(words.contains("hello"));
        console_test(words.contains("world"));
        console_test(!words.contains("blam!"));
    }

    {
        // deletion of keys
        Map<int, int> ii;
        ii[0] = 10;
        ii[-0] = 12;
        ii[false] = 14;
        console_test(1, ii.size());
        ii[1] = 9;
        console_test(2, ii.size());
        ii[2] = 8;
        console_test(3, ii.size());
        ii[3] = 7;
        console_test(4, ii.size());
        ii[4] = 6;
        console_test(5, ii.size());
        ii - 1;
        ii - 3;
        console_test(3, ii.size());
        ii[1] = 12;
        console_test(4, ii.size());
    }

    cout << endl;
    return 0;
};