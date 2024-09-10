 constexpr static Dim to(const Range<1, Float>& other) {
     return {other.min()[0],
             /* Doing it this way to preserve constexpr */
             other.max()[0] - other.min()[0]};
 }