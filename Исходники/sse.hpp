 // -- //
 static Float4x4 VFunction MultiplyTranspose(const Float4x4& matrixA, const Float4x4& matrixB)
 {
     return Transpose(Multiply(matrixA, matrixB));
 }