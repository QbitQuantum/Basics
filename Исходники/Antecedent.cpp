    void Antecedent::load(const std::string& antecedent, fl::Rule* rule, const Engine* engine) {
        FL_DBG("Antecedent: " << antecedent);
        unload();
        this->_text = antecedent;
        if (fl::Op::trim(antecedent).empty()) {
            throw fl::Exception("[syntax error] antecedent is empty", FL_AT);
        }
        /*
         Builds an proposition tree from the antecedent of a fuzzy rule.
         The rules are:
         1) After a variable comes 'is',
         2) After 'is' comes a hedge or a term
         3) After a hedge comes a hedge or a term
         4) After a term comes a variable or an operator
         */

        Function function;

        std::string postfix = function.toPostfix(antecedent);
        FL_DBG("Postfix: " << postfix);
        std::stringstream tokenizer(postfix);
        std::string token;

        enum FSM {
            S_VARIABLE = 1, S_IS = 2, S_HEDGE = 4, S_TERM = 8, S_AND_OR = 16
        };
        int state = S_VARIABLE;
        std::stack<Expression*> expressionStack;
        Proposition* proposition = fl::null;
        try {
            while (tokenizer >> token) {
                if (state bitand S_VARIABLE) {
                    Variable* variable = fl::null;
                    if (engine->hasInputVariable(token)) variable = engine->getInputVariable(token);
                    else if (engine->hasOutputVariable(token)) variable = engine->getOutputVariable(token);
                    if (variable) {
                        proposition = new Proposition;
                        proposition->variable = variable;
                        expressionStack.push(proposition);

                        state = S_IS;
                        FL_DBG("Token <" << token << "> is variable");
                        continue;
                    }
                }

                if (state bitand S_IS) {
                    if (token == Rule::isKeyword()) {
                        state = S_HEDGE bitor S_TERM;
                        FL_DBG("Token <" << token << "> is keyword");
                        continue;
                    }
                }

                if (state bitand S_HEDGE) {
                    Hedge* hedge = rule->getHedge(token);
                    if (not hedge) {
                        HedgeFactory* factory = FactoryManager::instance()->hedge();
                        if (factory->hasConstructor(token)) {
                            hedge = factory->constructObject(token);
                            rule->addHedge(hedge);
                        }
                    }
                    if (hedge) {
                        proposition->hedges.push_back(hedge);
                        if (dynamic_cast<Any*> (hedge)) {
                            state = S_VARIABLE bitor S_AND_OR;
                        } else {
                            state = S_HEDGE bitor S_TERM;
                        }
                        FL_DBG("Token <" << token << "> is hedge");
                        continue;
                    }
                }

                if (state bitand S_TERM) {
                    if (proposition->variable->hasTerm(token)) {
                        proposition->term = proposition->variable->getTerm(token);
                        state = S_VARIABLE bitor S_AND_OR;
                        FL_DBG("Token <" << token << "> is term");
                        continue;
                    }
                }

                if (state bitand S_AND_OR) {
                    if (token == Rule::andKeyword() or token == Rule::orKeyword()) {
                        if (expressionStack.size() < 2) {
                            std::ostringstream ex;
                            ex << "[syntax error] logical operator <" << token << "> expects two operands,"
                                    << "but found <" << expressionStack.size() << "> in antecedent";
                            throw fl::Exception(ex.str(), FL_AT);
                        }
                        Operator* fuzzyOperator = new Operator;
                        fuzzyOperator->name = token;
                        fuzzyOperator->right = expressionStack.top();
                        expressionStack.pop();
                        fuzzyOperator->left = expressionStack.top();
                        expressionStack.pop();
                        expressionStack.push(fuzzyOperator);

                        state = S_VARIABLE bitor S_AND_OR;
                        FL_DBG("Subtree: " << fuzzyOperator->toString() <<
                                "(" << fuzzyOperator->left->toString() << ") " <<
                                "(" << fuzzyOperator->right->toString() << ")");
                        continue;
                    }
                }

                //If reached this point, there was an error
                if ((state bitand S_VARIABLE) or (state bitand S_AND_OR)) {
                    std::ostringstream ex;
                    ex << "[syntax error] antecedent expected variable or logical operator, but found <" << token << ">";
                    throw fl::Exception(ex.str(), FL_AT);
                }
                if (state bitand S_IS) {
                    std::ostringstream ex;
                    ex << "[syntax error] antecedent expected keyword <" << Rule::isKeyword() << ">, but found <" << token << ">";
                    throw fl::Exception(ex.str(), FL_AT);
                }
                if ((state bitand S_HEDGE) or (state bitand S_TERM)) {
                    std::ostringstream ex;
                    ex << "[syntax error] antecedent expected hedge or term, but found <" << token << ">";
                    throw fl::Exception(ex.str(), FL_AT);
                }
                std::ostringstream ex;
                ex << "[syntax error] unexpected token <" << token << "> in antecedent";
                throw fl::Exception(ex.str(), FL_AT);
            }

            if (not ((state bitand S_VARIABLE) or (state bitand S_AND_OR))) { //only acceptable final state
                if (state bitand S_IS) {
                    std::ostringstream ex;
                    ex << "[syntax error] antecedent expected keyword <" << Rule::isKeyword() << "> after <" << token << ">";
                    throw fl::Exception(ex.str(), FL_AT);
                }
                if ((state bitand S_HEDGE) or (state bitand S_TERM)) {
                    std::ostringstream ex;
                    ex << "[syntax error] antecedent expected hedge or term after <" << token << ">";
                    throw fl::Exception(ex.str(), FL_AT);
                }
            }

            if (expressionStack.size() != 1) {
                std::vector<std::string> errors;
                while (expressionStack.size() > 1) {
                    Expression* expression = expressionStack.top();
                    expressionStack.pop();
                    errors.push_back(expression->toString());
                    delete expression;
                }
                std::ostringstream ex;
                ex << "[syntax error] unable to parse the following expressions in antecedent <"
                        << Op::join(errors, " ") << ">";
                throw fl::Exception(ex.str(), FL_AT);
            }
        } catch (...) {
            for (std::size_t i = 0; i < expressionStack.size(); ++i) {
                delete expressionStack.top();
                expressionStack.pop();
            }
            throw;
        }
        this->_expression = expressionStack.top();
    }