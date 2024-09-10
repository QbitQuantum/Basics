/**
 * @brief GetLength return arc length.
 * @return length.
 */
qreal VArc::GetLength() const
{
    return (M_PI * d->radius)/180 * AngleArc();
}