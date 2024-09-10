extern "C" void test_math(DataStruct* data)
{
  float f = data->f;
  float fi = data->i;
  data->fa[0] = expf(f);
  data->fa[1] = logf(f);
  data->fa[2] = exp2f(f);
  data->fa[3] = log2f(f);
  data->fa[4] = sinf(f);
  data->fa[5] = cosf(f);
  data->fa[6] = sqrtf(f);
  data->fa[7] = tanf(f);
//  data->fa[8] = rsqrtf(f);
//  data->fa[9] = rcpf(f); // 1/x
  data->fa[10] = floorf(f);
  data->fa[11] = atanf(f);
  data->fa[12] = powf(f,fi);
//  data->fa[13] = powi(f,data->i);


}