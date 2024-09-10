Matrix<double> Matrix<double>::Inverse(void) const
{
    if ( GetColumnLength() != GetRowLength() )
    {
        return *this;
    }
    // Calculate Inversed-Matrix<double> by Cofactors.
    const size_t rowCount = GetRowLength();
    const size_t colCount = GetColumnLength();
    Matrix<double> inversed(rowCount, colCount);

#if 0
    double det = Determinant();
    if ( 0 == det )
    {
        return *this;
    }
    for (size_t row = 0; row < rowCount; ++row)
    {
        for (size_t col = 0; col < colCount; ++col)
        {
            int sign = ((row + col) & 1) ? -1 : 1;
            Matrix<double> m(GetCofactorMatrix(row, col));
            inversed[col][row] = GetCofactor(row, col) / det;
        }
    }
#else
    //--------------------------------
    // Gauss-Jordan
    //--------------------------------
    const double threshold = 1.0e-10; // TBD

    Matrix<double> m(rowCount, colCount * 2);
    if ( m.IsNull() )
    {
        return m;
    }
    for (size_t row = 0; row < rowCount; ++row)
    {
        for (size_t col = 0; col < colCount; ++col)
        {
            m[row][col] = (*this)[row][col];
        }
    }
    for (size_t row = 0; row < rowCount; ++row)
    {
        for (size_t col = colCount; col < colCount * 2; ++col)
        {
            if (row == (col - colCount))
            {
                m[row][col] = 1.0;
            }
            else
            {
                m[row][col] = 0.0;
            }
        }
    }

    // 各行を正規化
    for (size_t r = 0; r < m.GetRowLength(); ++r )
    {
        m[r] /= m[r].GetMaximumAbsolute();
    }
    for (size_t r = 0; r < m.GetRowLength(); ++r )
    {
        // 注目している列の中で、最大値を持つ列を探す。
        size_t index = r;
        double maximum = fabs(m[r][r]);
        // "k < m.GetRowLength() - 1" となっていたが、意図不明なので修正。
        for (size_t k = index + 1; k < m.GetRowLength(); ++k )
        {
            if ( fabs(m[k][r]) > maximum )
            {
                index = k;
                maximum = fabs(m[k][r]);
            }
        }
        if ( maximum < threshold )
        {
            // ここに到達することはないはず。
            DEBUG_LOG(" ~ 0 at r=%d\n", static_cast<int>(r));
            m.Resize(0, 0); // NULL を返す。
            return m;
        }
        // 必要なら入れ替える
        if ( r != index )
        {
            const Vectord tmp(m[r]);
            m[r] = m[index];
            m[index] = tmp;
        }
        // 上で入れ替えたので 以降では index は不要、r を使用する。
        // 注目している行の、注目している列の値を 1.0 にする
        m[r] /= m[r][r]; // /= maximum; // maximum では符号が考慮されない。

        // 他の行から引く。
        for (size_t k = 0; k < m.GetRowLength(); ++k )
        {
            if ( k == r )
            {
                continue;
            }
            const Vectord tmp(m[r]);
            m[k] -= (tmp * m[k][r]);
        }
    }
    for (size_t row = 0; row < rowCount; ++row)
    {
        for (size_t col = 0; col < colCount; ++col)
        {
            inversed[row][col] = m[row][col+colCount];
        }
    }
#endif
    return inversed;
}