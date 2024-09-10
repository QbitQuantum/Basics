bool
TargetNVC0::isPostMultiplySupported(operation op, float f, int& e) const
{
   if (op != OP_MUL)
      return false;
   f = fabsf(f);
   e = static_cast<int>(log2f(f));
   if (e < -3 || e > 3)
      return false;
   return f == exp2f(static_cast<float>(e));
}