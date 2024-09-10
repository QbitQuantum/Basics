/**
 * Retrieving end result. Calculating elements of queue
 * @param postfixNotat - Queue of operators and operands in postfix notation
 * @return - Result of user's expression
 */
double processingQueueOfPostfixNotation(Queue<string> postfixNotat) {
    double res;
    Vector<string> vec;
    while(!postfixNotat.isEmpty()) {
        vec.add(postfixNotat.dequeue());
    }
    for(int i = 0; i < vec.size(); i++) {
        if(vec.size() == 1) {
            break;
        }
        string tmp = vec[i];
        if(isOperator(tmp[0]) && i >= 2) {
            string tok = vec[i];
            double secondOperand = atof(vec[i-1].c_str());
            double firstOperand = atof(vec[i-2].c_str());
            double calcResult =  executeOperation(firstOperand,secondOperand,tok[0]);
            string r2 = to_string(calcResult);
            vec.set(i-2, r2);
            vec.remove(i-1);
            vec.remove(i-1);
            i = 0;
        }
    }
    return res = atof(vec[0].c_str());
}