// -----------------------------------------------------------------------------------------
CPepeEngineQuaternion CPepeEngineQuaternion::squad(
    float fT, const CPepeEngineQuaternion& rkP, const CPepeEngineQuaternion& rkA,
    const CPepeEngineQuaternion& rkB, const CPepeEngineQuaternion& rkQ, bool shortestPath)
{
    float fSlerpT = 2.0f * fT * (1.0f - fT);
    CPepeEngineQuaternion kSlerpP = slerp(fT, rkP, rkQ, shortestPath);
    CPepeEngineQuaternion kSlerpQ = slerp(fT, rkA, rkB);
    return slerp(fSlerpT, kSlerpP , kSlerpQ);
}