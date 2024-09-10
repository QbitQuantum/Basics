uint32_t test_enclv(uint32_t leaf, size_t data[3]) {
// CHECK-64: call { i32, i64, i64, i64 } asm "enclv", "={ax},={bx},={cx},={dx},{ax},{bx},{cx},{dx},~{cc},~{dirflag},~{fpsr},~{flags}"(i32 %{{.*}}, i64 %{{.*}}, i64 %{{.*}}, i64 %{{.*}})
// CHECK-32: call { i32, i32, i32, i32 } asm "enclv", "={ax},={bx},={cx},={dx},{ax},{bx},{cx},{dx},~{cc},~{dirflag},~{fpsr},~{flags}"(i32 %{{.*}}, i32 %{{.*}}, i32 %{{.*}}, i32 %{{.*}})

  return _enclv_u32(leaf, data);
}