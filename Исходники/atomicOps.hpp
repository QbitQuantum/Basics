 AE_FORCEINLINE void compiler_fence(memory_order order)
 {
   switch (order) {
   case memory_order_relaxed: break;
   case memory_order_acquire: _ReadBarrier(); break;
   case memory_order_release: _WriteBarrier(); break;
   case memory_order_acq_rel: _ReadWriteBarrier(); break;
   case memory_order_seq_cst: _ReadWriteBarrier(); break;
   default: assert(false);
   }
 }