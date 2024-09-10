 void operator()(std::nullptr_t)
 {
   operator()(static_cast<Pointee *>(nullptr));
 }