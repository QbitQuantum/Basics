    bool testBasics() {
        typedef HashMap<AString, int, StringPolicy> Map;
        Map map;

        if (!check(map.init(), "initialized"))
            return false;

        Map::Result r = map.find("cat");
        if (!check(!r.found(), "cat not found"))
            return false;

        Map::Insert i = map.findForAdd("cat");
        if (!check(!i.found(), "cat not found for add"))
            return false;
        if (!check(map.add(i, AString("cat"), 5), "cat added"))
            return false;
        if (!check(r->value == 5, "cat is 5"))
            return false;

        Map::iterator iter = map.iter();
        if (!check(iter->key.compare("cat") == 0, "iterator got key cat"))
            return false;
        if (!check(iter->value == 5, "iterator got value 5"))
            return false;
        iter.next();
        if (!check(iter.empty(), "iterator should be finished"))
            return false;

        i = map.findForAdd("cat");
        if (!check(i.found(), "cat found through insert"))
            return false;

        r = map.find("dog");
        if (!check(!r.found(), "dog not found"))
            return false;

        r = map.find("cat");
        if (!check(r.found(), "cat found"))
            return false;
        if (!check(r->value == 5, "cat is 5"))
            return false;
        map.remove(r);

        r = map.find("cat");
        if (!check(!r.found(), "cat ran away"))
            return false;

        return true;
    }