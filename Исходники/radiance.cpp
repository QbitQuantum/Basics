 packed_colour::packed_colour(const V3 &col) {
   float d;
   
   d = std::max(std::max(col.r, col.g), col.b);
   
   r = g = b = e = 0;
   if (d > 1e-30f) {
     int exp;
     d = frexpf(d, &exp) * 255.0f / d;
     
     if (col.r > 0.0) r = (uint8_t)(col.r * d + 0.5f);
     if (col.g > 0.0) g = (uint8_t)(col.g * d + 0.5f);
     if (col.b > 0.0) b = (uint8_t)(col.b * d + 0.5f);
     
     e = (uint8_t)exp + excess;
   }
 }