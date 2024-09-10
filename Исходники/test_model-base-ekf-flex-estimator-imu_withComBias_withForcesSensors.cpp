Vector computeZmp (unsigned footNumber, IndexedMatrixArray& forces, IndexedMatrixArray& sensorPositions)
{
    double fnormal = 0;
    double sumZmpx = 0;
    double sumZmpy = 0;
    double sumZmpz = 0;
    Vector zmp; zmp.setZero(); zmp.resize (3);

    for (unsigned int i=0; i<footNumber; ++i)
    {
        const Vector& f = forces [i];
        // Check that force is of dimension 6
        if (f.size () != 6)
        {
            zmp.fill (0.);
            return zmp;
        }

        const Matrix& M = sensorPositions[i];
        double fx = M (0,0) * f (0) + M(0,1) * f (1) + M (0,2) * f (2);
        double fy = M (1,0) * f (0) + M(1,1) * f (1) + M (1,2) * f (2);
        double fz = M (2,0) * f (0) + M(2,1) * f (1) + M (2,2) * f (2);

        if (fz > 0)
        {
            double Mx = M (0,0)*f(3) + M (0,1)*f(4) + M (0,2)*f(5) + M (1,3)*fz - M (2,3)*fy;
            double My = M (1,0)*f(3) + M (1,1)*f(4) + M (1,2)*f(5) + M (2,3)*fx - M (0,3)*fz;

            fnormal += fz;
            sumZmpx -= My;
            sumZmpy += Mx;
            sumZmpz += fz * M (2,3);
        }
    }

    if (fnormal != 0)
    {
        zmp (0) = sumZmpx / fnormal;
        zmp (1) = sumZmpy / fnormal;
        zmp (2) = sumZmpz / fnormal;
    }
    else
    {
        zmp.fill (0.);
    }

    return zmp;
}