double computeAverageDouble(Vec<double> &result){

    RR average = 0;

    for (int i = 1; i <= result.length() ; i++){
        average += result(i);
    }

    return to_double(average/result.length());
}