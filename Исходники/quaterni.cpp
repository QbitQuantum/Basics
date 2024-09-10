csQuaternion csQuaternion::Squad (const csQuaternion & t1, const csQuaternion & t2,
  const csQuaternion & q, float t) const
{
  return SLerp (q, t).SLerp (t1.SLerp (t2, t), 2.0f*t * (1.0f - t));
}