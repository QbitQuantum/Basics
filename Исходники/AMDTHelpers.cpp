 void WriteMsrReg(uint reg, uint64 val)
 {
     __writemsr(static_cast<ulong>(reg), val);
 }