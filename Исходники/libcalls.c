// CHECK-YES-LABEL: define void @test_fma
// CHECK-NO-LABEL: define void @test_fma
void test_fma(float a0, double a1, long double a2) {
    // CHECK-YES: call float @llvm.fma.f32
    // CHECK-NO: call float @llvm.fma.f32
    float l0 = fmaf(a0, a0, a0);

    // CHECK-YES: call double @llvm.fma.f64
    // CHECK-NO: call double @llvm.fma.f64
    double l1 = fma(a1, a1, a1);

    // CHECK-YES: call x86_fp80 @llvm.fma.f80
    // CHECK-NO: call x86_fp80 @llvm.fma.f80
    long double l2 = fmal(a2, a2, a2);
}