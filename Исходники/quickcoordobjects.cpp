QSObject QSRectClass::normalize(QSEnv *env)
{
  QSObject t = env->thisValue();
  QSRectClass *cl = (QSRectClass *)t.objectType();
  QRect *r = cl->rect(&t);
  return cl->construct(r->normalize());
}