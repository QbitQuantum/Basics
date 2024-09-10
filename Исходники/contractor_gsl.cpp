static double eval(Enode * const e, double const values[], double const params[],
                   unordered_map<Enode *, unsigned> const & value_lookup,
                   unordered_map<Enode *, unsigned> const & param_lookup) {
    if (e->isNumb()) {
        return e->getNumb();
    } else if (e->isVar()) {
        auto it = value_lookup.find(e);
        if (it != value_lookup.end()) {
            return values[it->second];
        }
        it = param_lookup.find(e);
        if (it != param_lookup.end()) {
            return params[it->second];
        }
        DREAL_LOG_FATAL << "Can't find variable " << e;
        throw runtime_error("GSL eval: unmatched variable");
    } else if (e->isTerm()) {
        switch (e->getCar()->getId()) {
        case ENODE_ID_PLUS: {
            Enode * p = e->getCdr();
            double ret = eval(p->getCar(), values, params, value_lookup, param_lookup);
            p = p->getCdr();
            while (!p->isEnil()) {
                ret += eval(p->getCar(), values, params, value_lookup, param_lookup);
                p = p->getCdr();
            }
            return ret;
        }
        case ENODE_ID_MINUS: {
            Enode * p = e->getCdr();
            double ret = eval(p->getCar(), values, params, value_lookup, param_lookup);
            p = p->getCdr();
            while (!p->isEnil()) {
                ret -= eval(p->getCar(), values, params, value_lookup, param_lookup);
                p = p->getCdr();
            }
            return ret;
        }
        case ENODE_ID_TIMES: {
            Enode * p = e->getCdr();
            double ret = eval(p->getCar(), values, params, value_lookup, param_lookup);
            p = p->getCdr();
            while (!p->isEnil()) {
                ret *= eval(p->getCar(), values, params, value_lookup, param_lookup);
                p = p->getCdr();
            }
            return ret;
        }
        case ENODE_ID_DIV: {
            Enode * p = e->getCdr();
            double ret = eval(p->getCar(), values, params, value_lookup, param_lookup);
            p = p->getCdr();
            while (!p->isEnil()) {
                ret /= eval(p->getCar(), values, params, value_lookup, param_lookup);
                p = p->getCdr();
            }
            return ret;
        }
        case ENODE_ID_POW: {
            if (e->getArity() != 2) {
                throw runtime_error("GSL eval: pow not implemented");
            }
            double const arg1 = eval(e->get1st(), values, params, value_lookup, param_lookup);
            double const arg2 = eval(e->get2nd(), values, params, value_lookup, param_lookup);
            return pow(arg1, arg2);
        }
        case ENODE_ID_ATAN2: {
            double const arg1 = eval(e->get1st(), values, params, value_lookup, param_lookup);
            double const arg2 = eval(e->get2nd(), values, params, value_lookup, param_lookup);
            return atan2(arg1, arg2);
        }
        case ENODE_ID_UMINUS: {
            assert(e->getArity() == 1);
            double const arg = eval(e->get1st(), values, params, value_lookup, param_lookup);
            return -arg;
        }
        case ENODE_ID_SIN: {
            assert(e->getArity() == 1);
            double const arg = eval(e->get1st(), values, params, value_lookup, param_lookup);
            return sin(arg);
        }
        case ENODE_ID_COS: {
            assert(e->getArity() == 1);
            double const arg = eval(e->get1st(), values, params, value_lookup, param_lookup);
            return cos(arg);
        }
        case ENODE_ID_TAN: {
            assert(e->getArity() == 1);
            double const arg = eval(e->get1st(), values, params, value_lookup, param_lookup);
            return tan(arg);
        }
        case ENODE_ID_SQRT: {
            assert(e->getArity() == 1);
            double const arg = eval(e->get1st(), values, params, value_lookup, param_lookup);
            return sqrt(arg);
        }
        case ENODE_ID_SAFESQRT: {
            assert(e->getArity() == 1);
            double const arg = eval(e->get1st(), values, params, value_lookup, param_lookup);
            assert(arg >= 0);
            return sqrt(arg);
        }
        case ENODE_ID_EXP: {
            assert(e->getArity() == 1);
            double const arg = eval(e->get1st(), values, params, value_lookup, param_lookup);
            return exp(arg);
        }
        case ENODE_ID_LOG: {
            assert(e->getArity() == 1);
            double const arg = eval(e->get1st(), values, params, value_lookup, param_lookup);
            return log(arg);
        }
        case ENODE_ID_ASIN: {
            assert(e->getArity() == 1);
            double const arg = eval(e->get1st(), values, params, value_lookup, param_lookup);
            return asin(arg);
        }
        case ENODE_ID_ACOS: {
            assert(e->getArity() == 1);
            double const arg = eval(e->get1st(), values, params, value_lookup, param_lookup);
            return acos(arg);
        }
        case ENODE_ID_ATAN: {
            assert(e->getArity() == 1);
            double const arg = eval(e->get1st(), values, params, value_lookup, param_lookup);
            return atan(arg);
        }
        case ENODE_ID_SINH: {
            assert(e->getArity() == 1);
            double const arg = eval(e->get1st(), values, params, value_lookup, param_lookup);
            return sinh(arg);
        }
        case ENODE_ID_COSH: {
            assert(e->getArity() == 1);
            double const arg = eval(e->get1st(), values, params, value_lookup, param_lookup);
            return cosh(arg);
        }
        case ENODE_ID_TANH: {
            assert(e->getArity() == 1);
            double const arg = eval(e->get1st(), values, params, value_lookup, param_lookup);
            return tanh(arg);
        }
        default:
            return eval(e->getCar(), values, params, value_lookup, param_lookup);
        }
    } else if (e->isList()) {
        throw runtime_error("GSL eval: list");
    } else if (e->isDef()) {
        throw runtime_error("GSL eval: def");
    } else if (e->isEnil()) {
        throw runtime_error("GSL eval: enil");
    }
    throw runtime_error("GSL eval: unknown");
}