int comp (const point &A, const point &B)
{
    int cnt = A.ccw(B, reference_point);

    if (cnt == 0)
    {
        float dist_B = reference_point.distance (B);
        float dist_A = reference_point.distance (A);

        return (dist_A < dist_B);
    }

    return (cnt > 0);
}