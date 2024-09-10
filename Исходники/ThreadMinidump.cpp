RegisterContextSP
ThreadMinidump::CreateRegisterContextForFrame(StackFrame *frame) {
  RegisterContextSP reg_ctx_sp;
  uint32_t concrete_frame_idx = 0;

  if (frame)
    concrete_frame_idx = frame->GetConcreteFrameIndex();

  if (concrete_frame_idx == 0) {
    if (m_thread_reg_ctx_sp)
      return m_thread_reg_ctx_sp;

    ProcessMinidump *process =
        static_cast<ProcessMinidump *>(GetProcess().get());
    ArchSpec arch = process->GetArchitecture();
    RegisterInfoInterface *reg_interface = nullptr;

    // TODO write other register contexts and add them here
    switch (arch.GetMachine()) {
    case llvm::Triple::x86: {
      reg_interface = new RegisterContextLinux_i386(arch);
      lldb::DataBufferSP buf =
          ConvertMinidumpContext_x86_32(m_gpregset_data, reg_interface);
      DataExtractor gpregset(buf, lldb::eByteOrderLittle, 4);
      m_thread_reg_ctx_sp.reset(new RegisterContextCorePOSIX_x86_64(
          *this, reg_interface, gpregset, {}));
      break;
    }
    case llvm::Triple::x86_64: {
      reg_interface = new RegisterContextLinux_x86_64(arch);
      lldb::DataBufferSP buf =
          ConvertMinidumpContext_x86_64(m_gpregset_data, reg_interface);
      DataExtractor gpregset(buf, lldb::eByteOrderLittle, 8);
      m_thread_reg_ctx_sp.reset(new RegisterContextCorePOSIX_x86_64(
          *this, reg_interface, gpregset, {}));
      break;
    }
    case llvm::Triple::aarch64: {
      DataExtractor data(m_gpregset_data.data(), m_gpregset_data.size(),
                         lldb::eByteOrderLittle, 8);
      m_thread_reg_ctx_sp.reset(new RegisterContextMinidump_ARM64(*this, data));
      break;
    }
    case llvm::Triple::arm: {
      DataExtractor data(m_gpregset_data.data(), m_gpregset_data.size(),
                         lldb::eByteOrderLittle, 8);
      const bool apple = arch.GetTriple().getVendor() == llvm::Triple::Apple;
      m_thread_reg_ctx_sp.reset(
          new RegisterContextMinidump_ARM(*this, data, apple));
      break;
    }
    default:
      break;
    }

    reg_ctx_sp = m_thread_reg_ctx_sp;
  } else if (m_unwinder_ap) {
    reg_ctx_sp = m_unwinder_ap->CreateRegisterContextForFrame(frame);
  }

  return reg_ctx_sp;
}