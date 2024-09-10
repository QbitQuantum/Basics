 /**
  * Get the direction from 1 point to another
  * Thanks to "Snarkbait" for this little code snippit
  * @return Angle of difference
  */
 float Vector2::GetDirection( float fromx, float fromy, float tox, float toy )
 {
     // arcus tangens, convert to degrees, add 450 and normalize to 360.
     return fmodf((atan2f(toy - fromy, tox - fromx) / (float)M_PI * 180.0f + 450.0f), 360.0f);
 }