void RunQuaternionTests()
{
    RunCommonVectorOrQuaternionTests<quaternion>("quaternion");

    RunPerfTest<quaternion, quaternion>("quaternion conjugate", [](quaternion* value, quaternion& param)
    {
        auto t = param;
        param = *value;
        *value = conjugate(t);
    });

    RunPerfTest<quaternion, quaternion>("quaternion inverse", [](quaternion* value, quaternion& param)
    {
        auto t = param;
        param = *value;
        *value = inverse(t);
    });

    RunPerfTest<quaternion, quaternion>("quaternion slerp", [](quaternion* value, quaternion const& param)
    {
        *value = slerp(*value, param, 0.5f);
    });

    RunPerfTest<quaternion, quaternion>("quaternion concatenate", [](quaternion* value, quaternion const& param)
    {
        *value = concatenate(*value, param);
    });
}