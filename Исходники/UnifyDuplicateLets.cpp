    Expr mutate(const Expr &e) {

        if (e.defined()) {
            map<Expr, string, IRDeepCompare>::iterator iter = scope.find(e);
            if (iter != scope.end()) {
                expr = Variable::make(e.type(), iter->second);
            } else {
                e.accept(this);
            }
        } else {
            expr = Expr();
        }
        stmt = Stmt();
        return std::move(expr);
    }