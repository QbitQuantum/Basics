 inline Index jump(const Matrix<Index, N, 1>& offset,
                   const Matrix<Index, N, 1>& strides)
 {
   static_assert(
     std::numeric_limits<Index>::is_integer,
     "Index must be integral");
   return offset.dot(strides);
 }