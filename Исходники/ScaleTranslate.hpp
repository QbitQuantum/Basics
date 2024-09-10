ScaleTranslate<T>
operator*(const ScaleTranslate<T> &a, const ScaleTranslate<T> &b)
{
  ScaleTranslate<T> c;

  //
  // c(p)= a( b(p) )
  //     = a.translation + a.scale*( b.scale*p + b.translation )
  //     = (a.translate + a.scale*b.translation) + (a.scale*b.scale)*p
  //
  //thus:
  //
  // c.scale=a.scale*b.scale
  // c.translation= a.apply_to_point(b.translation)
  c.scale( a.scale() * b.scale());
  c.translation( a.apply_to_point(b.translation()) );

  return c;
}