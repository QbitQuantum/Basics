CA_FLOAT nuc_func_norm (CA_FLOAT Unuc, CA_FLOAT p1, CA_FLOAT p2, CA_FLOAT p3)
{
  CA_FLOAT result;

  result = p2 * 1 / (p1 * SQRT (2.0 * 3.14159)) * EXP (-((Unuc - p3) * (Unuc - p3)) / (2 * p1 * p1));
  return (result);
}