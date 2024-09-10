  virtual void WritePatch() override
  {
    hadesmem::detail::AcquireSRWLock const lock(
      &GetSrwLock(), hadesmem::detail::SRWLockType::Exclusive);

    auto& veh_hooks = GetVehHooks();

    HADESMEM_DETAIL_ASSERT(veh_hooks.find(target_) == std::end(veh_hooks));
    veh_hooks[target_] = this;

    auto const veh_cleanup_hook = [&]()
    {
      auto const veh_hooks_removed = veh_hooks.erase(target_);
      (void)veh_hooks_removed;
      HADESMEM_DETAIL_ASSERT(veh_hooks_removed);
    };
    auto scope_veh_cleanup_hook =
      hadesmem::detail::MakeScopeWarden(veh_cleanup_hook);

    HADESMEM_DETAIL_TRACE_A("Setting DR hook.");

    auto& dr_hooks = GetDrHooks();
    auto const thread_id = ::GetCurrentThreadId();
    HADESMEM_DETAIL_ASSERT(dr_hooks.find(thread_id) == std::end(dr_hooks));

    Thread const thread(thread_id);
    auto context = GetThreadContext(thread, CONTEXT_DEBUG_REGISTERS);

    std::uint32_t dr_index = static_cast<std::uint32_t>(-1);
    for (std::uint32_t i = 0; i < 4; ++i)
    {
      // Check whether the DR is available according to the control register
      bool const control_available = !(context.Dr7 & (1ULL << (i * 2)));
      // Check whether the DR is zero. Pobably not actually necessary, but
      // it's a nice additional sanity check. This may require a
      // user-controlable flag in future though if the code being hooked is
      // 'hostile'.
      bool const dr_available = !(&context.Dr0)[i];
      if (control_available && dr_available)
      {
        dr_index = i;
        break;
      }
    }

    if (dr_index == static_cast<std::uint32_t>(-1))
    {
      HADESMEM_DETAIL_THROW_EXCEPTION(
        Error{} << ErrorString{"No free debug registers."});
    }

    dr_hooks[ ::GetCurrentThreadId()] = dr_index;

    auto const dr_cleanup_hook = [&]()
    {
      auto const dr_hooks_removed = dr_hooks.erase(::GetCurrentThreadId());
      (void)dr_hooks_removed;
      HADESMEM_DETAIL_ASSERT(dr_hooks_removed);
    };
    auto scope_dr_cleanup_hook =
      hadesmem::detail::MakeScopeWarden(dr_cleanup_hook);

    (&context.Dr0)[dr_index] = reinterpret_cast<std::uintptr_t>(target_);
    // Set appropriate L0-L3 flag
    context.Dr7 |= static_cast<std::uintptr_t>(1ULL << (dr_index * 2));
    // Set appropriate RW0-RW3 field (Execution)
    std::uintptr_t break_type = 0;
    context.Dr7 |= (break_type << (16 + 4 * dr_index));
    // Set appropriate LEN0-LEN3 field (1 byte)
    std::uintptr_t break_len = 0;
    context.Dr7 |= (break_len << (18 + 4 * dr_index));
    // Set LE flag
    std::uintptr_t local_enable = 1 << 8;
    context.Dr7 |= local_enable;

    SetThreadContext(thread, context);

    scope_veh_cleanup_hook.Dismiss();
    scope_dr_cleanup_hook.Dismiss();
  }