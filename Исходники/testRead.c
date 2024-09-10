void TestSwapC() {
    value v1;
    GetIthCentroid(1, &v1);
    value v2;
    GetIthData(5, &v2);
    SwapCentroid(5,1);
    value v3;
    GetIthCentroid(1, &v3);
    value v4;
    GetIthData(5, &v4);
    CU_ASSERT(0 == data.distance(&v1,&v4));
    CU_ASSERT(0 == data.distance(&v2,&v3));

}