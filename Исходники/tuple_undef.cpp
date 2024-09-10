    Stmt mutate(const Stmt &s) override {
        CountStores c;
        s.accept(&c);

        if (c.count != correct) {
            printf("There were %d stores. There were supposed to be %d\n", c.count, correct);
            exit(-1);
        }

        return s;
    }