    Stmt mutate(Stmt s) {
        CountBarriers c;
        s.accept(&c);

        if (c.count != correct) {
            printf("There were %d barriers. There were supposed to be %d\n", c.count, correct);
            exit(-1);
        }

        return s;
    }