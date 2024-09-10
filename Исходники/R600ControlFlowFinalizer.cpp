 MachineBasicBlock::iterator insertLiterals(
     MachineBasicBlock::iterator InsertPos,
     const std::vector<unsigned> &Literals) const {
   MachineBasicBlock *MBB = InsertPos->getParent();
   for (unsigned i = 0, e = Literals.size(); i < e; i+=2) {
     unsigned LiteralPair0 = Literals[i];
     unsigned LiteralPair1 = (i + 1 < e)?Literals[i + 1]:0;
     InsertPos = BuildMI(MBB, InsertPos->getDebugLoc(),
         TII->get(AMDGPU::LITERALS))
         .addImm(LiteralPair0)
         .addImm(LiteralPair1);
   }
   return InsertPos;
 }