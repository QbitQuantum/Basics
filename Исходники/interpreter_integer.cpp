// Count Leading Zeroes Word
static void
cntlzw(ThreadState *state, Instruction instr)
{
   unsigned long a;
   uint32_t s;

   s = state->gpr[instr.rS];

   if (!_BitScanReverse(&a, s)) {
      a = 32;
   } else {
      a = 31 - a;
   }

   state->gpr[instr.rA] = a;

   if (instr.rc) {
      updateConditionRegister(state, a);
   }
}