      /*
       * Free function. Saves the current context in @p from
       * and restores the context in @p to. On windows the from
       * parameter is ignored. The current context is saved on the
       * current fiber.
       * Note that if the current thread is not a fiber, it will be
       * converted to fiber on the fly on call and unconverted before
       * return. This is expensive. The user should convert the
       * current thread to a fiber once on thread creation for better performance.
       * Note that we can't leave the thread unconverted on return or else we
       * will leak resources on thread destruction. Do the right thing by
       * default.
       */
      friend
      void
      swap_context(fibers_context_impl_base& from,
                   const fibers_context_impl_base& to,
                   default_hint)
      {
        if(!is_fiber()) {
          HPX_ASSERT(from.m_ctx == 0);
          from.m_ctx = ConvertThreadToFiber(0);
          HPX_ASSERT(from.m_ctx != 0);

#if HPX_HAVE_SWAP_CONTEXT_EMULATION != 0
          switch_to_fiber(to.m_ctx);
#else
          SwitchToFiber(to.m_ctx);
#endif
          BOOL result = ConvertFiberToThread();
          HPX_ASSERT(result);
          HPX_UNUSED(result);
          from.m_ctx = 0;
        } else {
          bool call_from_main = from.m_ctx == 0;
          if(call_from_main)
            from.m_ctx = GetCurrentFiber();
#if HPX_HAVE_SWAP_CONTEXT_EMULATION != 0
          switch_to_fiber(to.m_ctx);
#else
          SwitchToFiber(to.m_ctx);
#endif
          if(call_from_main)
            from.m_ctx = 0;
        }
      }