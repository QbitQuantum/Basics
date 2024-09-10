Cell ProcessorTS::BAm1(const Cell & A, const Cell & B) const
{
    if (N.iszero())
        return BAtt(A, B);

    if (0) // old impl
    {
        // Step 1 prepare old values
        Unumber x = B.x();
        Unumber Ax = A.x();

        // Step 2 do old operation
        Unumber xm1, a(Ax);
        bool k = ma::invert(a, N2, &xm1);
        if ( !k )
        {
            Unumber g = ma::gcd(a, x);
            if ( g == 1 ) return Cell();
            x /= g;
            a /= g;
            bool k = ma::invert(a, N2, &xm1);
            if ( !k ) return Cell();
        }
        x = x.mul(xm1, N2);

        // Step 3 convert old values to Ts
        x -= 1;
        Unumber t, s;
        s = x.div(N, t);

        return Cell(t, s);
    }
    else
    {
        if (0)
        {
            Cell ai = A.invert();
            Unumber x = B.x().mul(ai.x(), N2);
            return Cell(x, Cell::X);
        }
        else
            return A.invert() * B;
    }
}