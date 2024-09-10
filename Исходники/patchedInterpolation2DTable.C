Type Foam::interpolation2DTable<Type>::operator()
(
    const scalar valueX,
    const scalar valueY
) const
{
    // Considers all of the list in Y being equal
    label nX = this->size();

    const table& t = *this;

    if (nX == 0)
    {
        WarningIn
        (
            "Type Foam::interpolation2DTable<Type>::operator()"
            "("
                "const scalar, "
                "const scalar"
            ") const"
        )
            << "cannot interpolate a zero-sized table - returning zero" << endl;

        return pTraits<Type>::zero;
    }
    else if (nX == 1)
    {
        // only 1 column (in X) - interpolate to find Y value
        return interpolateValue(t.first().second(), valueY);
    }
    else
    {
        // have 2-D data, interpolate

        // find low and high indices in the X range that bound valueX
        label x0i = Xi(lessOp<scalar>(), valueX, false);
        label x1i = Xi(greaterOp<scalar>(), valueX, true);

        if (x0i == x1i)
        {
            return interpolateValue(t[x0i].second(), valueY);
        }
        else
        {
            Type y0(interpolateValue(t[x0i].second(), valueY));
            Type y1(interpolateValue(t[x1i].second(), valueY));

            // gradient in X
            scalar x0 = t[x0i].first();
            scalar x1 = t[x1i].first();
            Type mX = (y1 - y0)/(x1 - x0);

            // interpolate
            return y0 + mX*(valueX - x0);
        }
    }
}