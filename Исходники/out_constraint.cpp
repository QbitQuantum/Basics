    Stmt mutate(const Stmt &s) override {
        CheckLoops c;
        s.accept(&c);

        if (c.count != 1) {
            std::cerr << "expected one loop, found " << c.count << std::endl;
            exit(-1);
        }

        return s;
    }