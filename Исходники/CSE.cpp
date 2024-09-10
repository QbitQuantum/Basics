    void include(const Expr &e) {
        if (result.defined()) return;

        set<const IRNode *>::iterator iter = visited.find(e.ptr);

        if (iter != visited.end()) {
            if (e.as<Variable>() || is_const(e)) {
                return;
            }

            result = e;
        } else {
            e.accept(this);
            visited.insert(e.ptr);
        }
    }