void test_invpcid(uint32_t type, void *descriptor) {
  //CHECK-LABEL: @test_invpcid
  //CHECK: call void @llvm.x86.invpcid(i32 %{{.*}}, i8* %{{.*}})
  _invpcid(type, descriptor);
}