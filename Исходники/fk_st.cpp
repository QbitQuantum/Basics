int main() {
    int n = 1000;
    int capacity = 2000000;
    vector<int> weights (n);
    vector<int> values (n);
    for (int i=0;i<n;i++) {
        weights[i] = rand()%capacity;
        values[i] = rand()%capacity;
    }

    double optimal_value = get_optimal_value(capacity, weights, values);

    std::cout.precision(10);
    std::cout << optimal_value << std::endl;
    return 0;
}