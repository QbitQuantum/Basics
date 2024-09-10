int test_setjmpex() {
  return _setjmpex(jb);
  // X64-LABEL: define i32 @test_setjmpex
  // X64:       %[[addr:.*]] = call i8* @llvm.frameaddress(i32 0)
  // X64:       %[[call:.*]] = call i32 @_setjmpex(i8* getelementptr inbounds ([1 x i8], [1 x i8]* @jb, i32 0, i32 0), i8* %[[addr]])
  // X64-NEXT:  ret i32 %[[call]]
}