vector<int> find_repeated_sqrt(int num) {
    /* Return a vector in the form of [m, a0, a1, ... an]
     * where m is the first square less than sqrt(num) and
     * a_n is the sequence of repeated terms in the continued fraction
     * If num is square, return a single element vector containing num
     * E.g: sqrt(2) = 2 + 1
     *                    -----------
     *                    2 + 1
     *                        -------
     *                        2 + ...
     *
     * find_repeated_sqrt(2) -> [1, 2]
     */
    // initialize terms with the first number
    vector<int> terms{int(sqrt(num))};
    if (terms[0] * terms[0] == num)
        return terms;
    int d(1), m(0), a(terms[0]);
    while (a != 2*terms[0]) {
        m = d * a - m;
        d = (num - m * m) / d;
        a = (terms[0] + m) / d;
        terms.push_back(a);
    }
    return terms;
}