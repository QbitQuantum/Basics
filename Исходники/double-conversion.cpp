 static double RadixStringToDouble(const char* current,
                                   const char* end,
                                   bool sign,
                                   bool allow_trailing_junk,
                                   double junk_string_value,
                                   const char** trailing_pointer) {
     ASSERT(current != end);
     
     // Skip leading 0s.
     while (*current == '0') {
         ++current;
         if (current == end) {
             *trailing_pointer = end;
             return SignedZero(sign);
         }
     }
     
     int64_t number = 0;
     int exponent = 0;
     const int radix = (1 << radix_log_2);
     
     do {
         int digit;
         if (*current >= '0' && *current <= '9' && *current < '0' + radix) {
             digit = static_cast<char>(*current) - '0';
         } else if (radix > 10 && *current >= 'a' && *current < 'a' + radix - 10) {
             digit = static_cast<char>(*current) - 'a' + 10;
         } else if (radix > 10 && *current >= 'A' && *current < 'A' + radix - 10) {
             digit = static_cast<char>(*current) - 'A' + 10;
         } else {
             if (allow_trailing_junk || !AdvanceToNonspace(&current, end)) {
                 break;
             } else {
                 return junk_string_value;
             }
         }
         
         number = number * radix + digit;
         int overflow = static_cast<int>(number >> 53);
         if (overflow != 0) {
             // Overflow occurred. Need to determine which direction to round the
             // result.
             int overflow_bits_count = 1;
             while (overflow > 1) {
                 overflow_bits_count++;
                 overflow >>= 1;
             }
             
             int dropped_bits_mask = ((1 << overflow_bits_count) - 1);
             int dropped_bits = static_cast<int>(number) & dropped_bits_mask;
             number >>= overflow_bits_count;
             exponent = overflow_bits_count;
             
             bool zero_tail = true;
             while (true) {
                 ++current;
                 if (current == end || !isDigit(*current, radix)) break;
                 zero_tail = zero_tail && *current == '0';
                 exponent += radix_log_2;
             }
             
             if (!allow_trailing_junk && AdvanceToNonspace(&current, end)) {
                 return junk_string_value;
             }
             
             int middle_value = (1 << (overflow_bits_count - 1));
             if (dropped_bits > middle_value) {
                 number++;  // Rounding up.
             } else if (dropped_bits == middle_value) {
                 // Rounding to even to consistency with decimals: half-way case rounds
                 // up if significant part is odd and down otherwise.
                 if ((number & 1) != 0 || !zero_tail) {
                     number++;  // Rounding up.
                 }
             }
             
             // Rounding up may cause overflow.
             if ((number & ((int64_t)1 << 53)) != 0) {
                 exponent++;
                 number >>= 1;
             }
             break;
         }