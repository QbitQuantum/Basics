Number shunting_yard(std::vector<std::string> & tokens, std::vector<std::string> & out_ops, bool boolean_exp = false) {
    prepare();
    std::string previous_token;
    Operator * op;
    Operator * previous_op = new Sum();
    std::string last_token = "";
    std::string token;

    for(auto s = tokens.begin(); s != tokens.end(); ++s) {
        token = *s;
        //std::cout<<token<<std::endl;
        if(is_number(token)) {
            if(is_number(previous_token)) {
                throw std::string("Too many operands");
            }
            if(previous_op && previous_op->sign() == ")") {
                throw std::string("Missing operation between paretheses");
            }
            Number i = parse_number(token);
            if(i >= Number("10", "99") || i <= Number("-10", "99")) {
                //std::cout<<i<<'\n';
                throw std::string("Number out of valid range");
            }

            if(is_variable(token)) {
                std::stringstream g;
                g << i;
                out_ops.push_back(token + "= " + g.str());
            }
            output_stack.push(i);
            previous_op = nullptr;
        }
        else if((op = get_function_op(token)) != nullptr) {
            operator_stack.push(op);
        }

        else if (token == ",") {
            while(!operator_stack.empty() && operator_stack.top()->sign() != "(") {
                evaluate(operator_stack.top(), out_ops);
                operator_stack.pop();
            }
            // error
            if(operator_stack.empty()) {
                throw std::string("mismatched parens");
            }
            // dirty fix, the problem is that in get_operator we only return a
            // negative if there was an operator before, so root(3, -27) was being
            // treated as a substraction
            previous_op = new Sum();
        }

        else if((op = get_operator(token, previous_op, boolean_exp)) != nullptr) {
            if(op->sign() == "(") {
                if(!previous_op || (previous_op && previous_op->sign() == ")" )) {
                    throw std::string("Missing operation between paretheses");
                }
                operator_stack.push(op);
            } else if(op->sign() == ")") {
                while(!operator_stack.empty() && operator_stack.top()->sign() != "(") {
                    evaluate(operator_stack.top(), out_ops);
                    operator_stack.pop();
                }
                // error
                if(operator_stack.empty()) {
                    throw std::string("mismatched parens");
                }
                operator_stack.pop();
                if(!operator_stack.empty() && operator_stack.top()->sign() == "r") {
                    evaluate_function(operator_stack.top(), out_ops);
                    operator_stack.pop();
                }
            }
            else {
                while(!operator_stack.empty() &&
                        ( (op->associativity() == assoc::LEFT && op->precedence() <= operator_stack.top()->precedence())
                          ||
                          (op->associativity() == assoc::RIGHT && op->precedence() < operator_stack.top()->precedence())))
                {
                    evaluate(operator_stack.top(), out_ops);
                    operator_stack.pop();
                }
                operator_stack.push(op);
            }
            previous_op = op;
        }

        else if(token == "=" && !boolean_exp) {
            if(s+1 != tokens.end())
                last_token = *(s+1);
            break;
        }
        // unknown token
        else {
            throw std::string("Unexpected Token '" + token + "'");
        }
        previous_token = token;
    }

    while(!operator_stack.empty()) {
        op = operator_stack.top();
        if(op->sign() == "(") {
            throw std::string("mismatched parens");
        }
        operator_stack.pop();
        evaluate(op, out_ops);
    }

    if(token != "=" && !boolean_exp) {
        throw std::string("Missing =");
    }

    if(!last_token.empty() && !boolean_exp) {
        if(var_map.find(last_token) != var_map.end()) {
            var_map[last_token] = output_stack.top();
            if(tokens[tokens.size()-1] != last_token) {
                throw std::string("Warning, no more expressions after variable assignment");
            }
            // out ops A=
            std::stringstream ss;
            ss << output_stack.top();
            out_ops.push_back(last_token + "= " + ss.str());
            //std::cout << var_map[last_token] << '\n';
        }
        else {
            throw std::string("Warning, no more expressions after =");
        }

    }
    if(output_stack.empty()) return Number ("0","0");

    Number ans = output_stack.top();
    output_stack.pop();
    if(!output_stack.empty()) throw std::string("too many arguments to function");
    return ans;

}