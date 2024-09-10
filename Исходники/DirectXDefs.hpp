XMVECTOR XMVector3Avg(R ... args)
{
  auto total = _Vector3AvgUINT(args ...);

  return XMVectorScale(total, 1.0f / sizeof...(args));
}