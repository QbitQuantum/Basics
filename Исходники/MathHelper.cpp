 float MathHelper::SmoothStep(float val1, float val2, float t)
 {
     t = Clamp(t, 0, 1);
     return Lerp(val1, val2, t*t*(3 - 2 * t));
 }