 RAJA_HOST_DEVICE RAJA_INLINE atomic_type operator()(ARGS &&... args) const
 {
   return atomic_type(&base_.operator()(std::forward<ARGS>(args)...));
 }