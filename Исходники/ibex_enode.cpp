ExprNode const * translate_enode_to_exprnode(unordered_map<string, Variable const> & var_map, Enode const * e) {
    // TODO(soonhok): for the simple case such as 0 <= x or x <= 10.
    // Handle it as a domain specification instead of constraints.
    if (e->isVar()) {
        string const & var_name = e->getCar()->getName();
        auto it = var_map.find(var_name);
        if (it == var_map.end()) {
            // The variable is new, we need to make one.
            Variable v(var_name.c_str());
            // double const lb = e->getLowerBound();
            // double const ub = e->getUpperBound();
            var_map.emplace(var_name, v);
            return v.symbol;
        } else {
            // Variable is found in var_map
            Variable const & v = it->second;
            return v.symbol;
        }

    } else if (e->isConstant()) {
        // TODO(soonhok): handle number c as an interval [lb(c), ub(c)]
        return &ExprConstant::new_scalar(e->getValue());
    } else if (e->isSymb()) {
        throw logic_error("translateEnodeExprNode: Symb");
    } else if (e->isNumb()) {
        throw logic_error("translateEnodeExprNode: Numb");
    } else if (e->isTerm()) {
        assert(e->getArity() >= 1);
        ExprNode const * ret = translate_enode_to_exprnode(var_map, e->get1st());
        enodeid_t id = e->getCar()->getId();
        switch (id) {
        case ENODE_ID_PLUS:
            e = e->getCdr()->getCdr();  // e is pointing to the 2nd arg
            while (!e->isEnil()) {
                ret = &(*ret + *translate_enode_to_exprnode(var_map, e->getCar()));
                e = e->getCdr();
            }
            return ret;
        case ENODE_ID_MINUS:
            e = e->getCdr()->getCdr();  // e is pointing to the 2nd arg
            while (!e->isEnil()) {
                ret = &(*ret - *translate_enode_to_exprnode(var_map, e->getCar()));
                e = e->getCdr();
            }
            return ret;
        case ENODE_ID_UMINUS:
            assert(e->getArity() == 1);
            return &(- *ret);
        case ENODE_ID_TIMES:
            e = e->getCdr()->getCdr();  // e is pointing to the 2nd arg
            while (!e->isEnil()) {
                ret = &(*ret * *translate_enode_to_exprnode(var_map, e->getCar()));
                e = e->getCdr();
            }
            return ret;
        case ENODE_ID_DIV:
            e = e->getCdr()->getCdr();  // e is pointing to the 2nd arg
            while (!e->isEnil()) {
                ret = &(*ret / *translate_enode_to_exprnode(var_map, e->getCar()));
                e = e->getCdr();
            }
            return ret;
        case ENODE_ID_ACOS:
            assert(e->getArity() == 1);
            return &acos(*translate_enode_to_exprnode(var_map, e->get1st()));
        case ENODE_ID_ASIN:
            assert(e->getArity() == 1);
            return &asin(*translate_enode_to_exprnode(var_map, e->get1st()));
        case ENODE_ID_ATAN:
            assert(e->getArity() == 1);
            return &atan(*translate_enode_to_exprnode(var_map, e->get1st()));
        case ENODE_ID_ATAN2:
            assert(e->getArity() == 2);
            return &atan2(*translate_enode_to_exprnode(var_map, e->get1st()), *translate_enode_to_exprnode(var_map, e->get2nd()));
        case ENODE_ID_MIN:
            assert(e->getArity() == 2);
            return &min(*translate_enode_to_exprnode(var_map, e->get1st()), *translate_enode_to_exprnode(var_map, e->get2nd()));
        case ENODE_ID_MAX:
            assert(e->getArity() == 2);
            return &max(*translate_enode_to_exprnode(var_map, e->get1st()), *translate_enode_to_exprnode(var_map, e->get2nd()));
        case ENODE_ID_MATAN:
            // TODO(soonhok): MATAN
            throw logic_error("translateEnodeExprNode: MATAN");
        case ENODE_ID_SAFESQRT:
            // TODO(soonhok): SAFESQRT
            throw logic_error("translateEnodeExprNode: SAFESQRT");
        case ENODE_ID_SQRT:
            assert(e->getArity() == 1);
            return &sqrt(*translate_enode_to_exprnode(var_map, e->get1st()));
        case ENODE_ID_EXP:
            assert(e->getArity() == 1);
            return &exp(*translate_enode_to_exprnode(var_map, e->get1st()));
        case ENODE_ID_LOG:
            assert(e->getArity() == 1);
            return &log(*translate_enode_to_exprnode(var_map, e->get1st()));
        case ENODE_ID_POW: {
            assert(e->getArity() == 2);
            bool   is_1st_constant = false;
            bool   is_1st_int      = false;
            bool   is_2nd_constant = false;
            bool   is_2nd_int      = false;
            double dbl_1st = 0.0;
            int    int_1st = 0;
            double dbl_2nd = 0.0;
            int    int_2nd = 0;
            if (e->get1st()->isConstant()) {
                dbl_1st = e->get1st()->getValue();
                is_1st_constant = true;
                double tmp;
                if (modf(dbl_1st, &tmp) == 0.0) {
                    is_1st_int = true;
                    int_1st = static_cast<int>(tmp);
                }
            }
            if (e->get2nd()->isConstant()) {
                dbl_2nd = e->get2nd()->getValue();
                is_2nd_constant = true;
                double tmp;
                if (modf(dbl_2nd, &tmp) == 0.0) {
                    is_2nd_int = true;
                    int_2nd = static_cast<int>(tmp);
                }
            }
            if (is_1st_constant && is_2nd_constant) {
                // Both of them are constant, just compute and return a number
                return &ExprConstant::new_scalar(pow(dbl_1st, dbl_2nd));
            }
            // Now, either of them is non-constant.
            if (is_1st_int) {
                return &pow(int_1st, *translate_enode_to_exprnode(var_map, e->get2nd()));
            }
            if (is_1st_constant) {
                return &pow(dbl_1st, *translate_enode_to_exprnode(var_map, e->get2nd()));
            }
            if (is_2nd_int) {
                return &pow(*translate_enode_to_exprnode(var_map, e->get1st()), int_2nd);
            }
            if (is_2nd_constant) {
                return &pow(*translate_enode_to_exprnode(var_map, e->get1st()), dbl_2nd);
            }
            return &pow(*translate_enode_to_exprnode(var_map, e->get1st()), *translate_enode_to_exprnode(var_map, e->get2nd()));
        }
        case ENODE_ID_ABS:
            assert(e->getArity() == 1);
            return &abs(*translate_enode_to_exprnode(var_map, e->get1st()));
        case ENODE_ID_SIN:
            assert(e->getArity() == 1);
            return &sin(*translate_enode_to_exprnode(var_map, e->get1st()));
        case ENODE_ID_COS:
            assert(e->getArity() == 1);
            return &cos(*translate_enode_to_exprnode(var_map, e->get1st()));
        case ENODE_ID_TAN:
            assert(e->getArity() == 1);
            return &tan(*translate_enode_to_exprnode(var_map, e->get1st()));
        case ENODE_ID_SINH:
            assert(e->getArity() == 1);
            return &sinh(*translate_enode_to_exprnode(var_map, e->get1st()));
        case ENODE_ID_COSH:
            assert(e->getArity() == 1);
            return &cosh(*translate_enode_to_exprnode(var_map, e->get1st()));
        case ENODE_ID_TANH:
            assert(e->getArity() == 1);
            return &tanh(*translate_enode_to_exprnode(var_map, e->get1st()));
        default:
            throw logic_error("translateEnodeExprNode: Unknown Term");
        }
    } else if (e->isList()) {
        throw logic_error("translateEnodeExprNode: List");
    } else if (e->isDef()) {
        throw logic_error("translateEnodeExprNode: Def");
    } else if (e->isEnil()) {
        throw logic_error("translateEnodeExprNode: Nil");
    } else {
        throw logic_error("translateEnodeExprNode: unknown case");
    }
    throw logic_error("Not implemented yet: translateEnodeExprNode");
}