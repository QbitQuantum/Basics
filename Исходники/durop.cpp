 void DurOp::serialize(AlignedBuilder& ab) {
     ab.appendNum(_opcode);
     _serialize(ab);
 }