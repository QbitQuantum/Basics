void MatrixTest::test_polar_decomposition(Matrix const &matrix, int rotations, Real accuracy)
{
    Matrix R;
    Matrix S;
    matrix.do_polar_decomposition(R, S, rotations, 2*rotations, accuracy);
    
    EXPECT_EQ( matrix, R*S );
    
    if ( !equal(0, matrix.determinant()) )
    {
        EXPECT_NEAR(1, abs(R.determinant()), accuracy);
    }
    
    Matrix S_simmetrized = S;
    simmetrize(S_simmetrized);
    EXPECT_EQ( S, S_simmetrized );
}