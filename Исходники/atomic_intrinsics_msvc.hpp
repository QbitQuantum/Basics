 inline void store(T value, MemoryOrder order = MEMORY_ORDER_SEQ_CST) volatile {
   assert(order != MEMORY_ORDER_ACQUIRE);
   assert(order != MEMORY_ORDER_CONSUME);
   assert(order != MEMORY_ORDER_ACQ_REL);
   if (order != MEMORY_ORDER_SEQ_CST) {
     _ReadWriteBarrier();
     value_ = static_cast<ImplType>(value);
     _ReadWriteBarrier();
   } else {
     Impl::exchange(value_, static_cast<ImplType>(value));
   }
 }