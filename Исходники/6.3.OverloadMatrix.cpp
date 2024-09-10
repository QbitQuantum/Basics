int
main()
{
    boost::progress_timer howlong;

    Matrix<double, 2, 2> m;
    m(0, 0) = 1;
    m(0, 1) = 2;
    m(1, 0) = 3;
    m(1, 1) = 4;
    cout << "Determinant " << m.determinant() << endl;
    static double total;
    for(int i = 0; i < 1E9; i++) {
        m(1,1) = i;
        total += m.determinant();
    }
}