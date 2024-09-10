void benchmark( )
{
    for (size_t i = 1; i < 12; i++) 
    {
        const size_t N = (size_t)pow(2, i);
        Eigen::MatrixXd m = MatrixXd::Random(N, N);

        clock_t t0 = clock();
        auto mInv = m.inverse();
        clock_t t1 = clock();
        double eigenT = (double)(t1-t0)/CLOCKS_PER_SEC;

        t0 = clock();
        auto m1 = m;
        invert( m1 );
        t1 = clock();

        if( (m1-mInv).norm() > 1e-6 )
        {
            cout << "Got " << endl << m1 << endl;
            cout << "Expected " << endl << mInv << endl;
            cout << "Original matrix was " << endl << m << endl;
            cout<< "Error : " << endl << (m1 - mInv).norm() << endl;
            throw;
        }

        cout << N << ' ' << (double)(t1-t0) / CLOCKS_PER_SEC <<  ' ' << eigenT << endl;
    }

}