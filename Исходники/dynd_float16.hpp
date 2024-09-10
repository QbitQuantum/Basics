 bool less_nonan(const dynd_float16& rhs) const {
     if (signbit()) {
         if (rhs.signbit()) {
             return m_bits > rhs.m_bits;
         } else {
             // Signed zeros are equal, have to check for it
             return (m_bits != 0x8000u) || (rhs.m_bits != 0x0000u);
         }
     } else {
         if (rhs.signbit()) {
             return false;
         } else {
             return m_bits < rhs.m_bits;
         }
     }
 }