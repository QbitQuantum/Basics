bool  PositionBasedElasticRod::ProjectEdgeConstraints(
    const Vector3r& pA, const float wA,
    const Vector3r& pB, const float wB,
    const Vector3r& pG, const float wG,
    const float edgeKs, const float edgeRestLength, const float ghostEdgeRestLength,
    Vector3r& corrA, Vector3r&  corrB, Vector3r&  corrC)
{
    corrA.setZero();
    corrB.setZero();
    corrC.setZero();

    //Edge distance constraint
    Vector3r dir = pA - pB;
    float len = dir.norm();

    float wSum = wA + wB;
    if (len > EPSILON && wSum > EPSILON)
    {
        Vector3r dP = (1.0f / wSum) * (len - edgeRestLength) * (dir / len) * edgeKs;

        corrA -= dP * wA;
        corrB += dP * wB;
        corrC = Vector3r(0, 0, 0);
    }

    //Bisector constraint
    Vector3r pm = 0.5f * (pA + pB);
    Vector3r p0p2 = pA - pG;
    Vector3r p2p1 = pG - pB;
    Vector3r p1p0 = pB - pA;
    Vector3r p2pm = pG - pm;
    float lambda;

    wSum = wA * p0p2.squaredNorm() + wB * p2p1.squaredNorm() + wG * p1p0.squaredNorm();
    if (wSum > EPSILON)
    {
        lambda = p2pm.dot(p1p0) / wSum * edgeKs;

        corrA -= p0p2 * lambda * wA;
        corrB -= p2p1 * lambda * wB;
        corrC -= p1p0 * lambda * wG;
    }

    ////Ghost-Edge constraint
    wSum = 0.25f * wA + 0.25f * wB + 1.0f * wG;

    if (wSum > EPSILON)
    {
        //need to use updated positions
        pm = 0.5f * (pA + corrA + pB + corrB);
        p2pm = pG + corrC - pm;

        float p2pm_mag = p2pm.norm();
        p2pm *= 1.0f / p2pm_mag;

        lambda = (p2pm_mag - ghostEdgeRestLength) / wSum * edgeKs;

        corrA += 0.5f * wA * lambda * p2pm;
        corrB += 0.5f * wB * lambda * p2pm;
        corrC -= 1.0f * wG * lambda * p2pm;
    }


    return true;
}