void AMDGPUTargetStreamer::emitRuntimeMetadata(const Function &F) {
  if (!F.getMetadata("kernel_arg_type"))
    return;
  auto &S = getStreamer();
  S.EmitIntValue(RuntimeMD::KeyKernelBegin, 1);
  emitRuntimeMDStringValue(RuntimeMD::KeyKernelName, F.getName());

  const DataLayout &DL = F.getParent()->getDataLayout();
  for (auto &Arg : F.args()) {
    unsigned I = Arg.getArgNo();
    Type *T = Arg.getType();
    auto TypeName = dyn_cast<MDString>(F.getMetadata(
        "kernel_arg_type")->getOperand(I))->getString();
    auto BaseTypeName = cast<MDString>(F.getMetadata(
        "kernel_arg_base_type")->getOperand(I))->getString();
    StringRef ArgName;
    if (auto ArgNameMD = F.getMetadata("kernel_arg_name"))
      ArgName = cast<MDString>(ArgNameMD->getOperand(I))->getString();
    auto TypeQual = cast<MDString>(F.getMetadata(
        "kernel_arg_type_qual")->getOperand(I))->getString();
    auto AccQual = cast<MDString>(F.getMetadata(
        "kernel_arg_access_qual")->getOperand(I))->getString();
    RuntimeMD::KernelArg::Kind Kind;
    if (TypeQual.find("pipe") != StringRef::npos)
      Kind = RuntimeMD::KernelArg::Pipe;
    else Kind = StringSwitch<RuntimeMD::KernelArg::Kind>(BaseTypeName)
      .Case("sampler_t", RuntimeMD::KernelArg::Sampler)
      .Case("queue_t",   RuntimeMD::KernelArg::Queue)
      .Cases("image1d_t", "image1d_array_t", "image1d_buffer_t",
             "image2d_t" , "image2d_array_t",  RuntimeMD::KernelArg::Image)
      .Cases("image2d_depth_t", "image2d_array_depth_t",
             "image2d_msaa_t", "image2d_array_msaa_t",
             "image2d_msaa_depth_t",  RuntimeMD::KernelArg::Image)
      .Cases("image2d_array_msaa_depth_t", "image3d_t",
             RuntimeMD::KernelArg::Image)
      .Default(isa<PointerType>(T) ?
                   (T->getPointerAddressSpace() == AMDGPUAS::LOCAL_ADDRESS ?
                   RuntimeMD::KernelArg::DynamicSharedPointer :
                   RuntimeMD::KernelArg::GlobalBuffer) :
                   RuntimeMD::KernelArg::ByValue);
    emitRuntimeMetadataForKernelArg(DL, T,
        Kind, BaseTypeName, TypeName, ArgName, TypeQual, AccQual);
  }

  // Emit hidden kernel arguments for OpenCL kernels.
  if (F.getParent()->getNamedMetadata("opencl.ocl.version")) {
    auto Int64T = Type::getInt64Ty(F.getContext());
    emitRuntimeMetadataForKernelArg(DL, Int64T,
                                    RuntimeMD::KernelArg::HiddenGlobalOffsetX);
    emitRuntimeMetadataForKernelArg(DL, Int64T,
                                    RuntimeMD::KernelArg::HiddenGlobalOffsetY);
    emitRuntimeMetadataForKernelArg(DL, Int64T,
                                    RuntimeMD::KernelArg::HiddenGlobalOffsetZ);
    if (F.getParent()->getNamedMetadata("llvm.printf.fmts")) {
      auto Int8PtrT = Type::getInt8PtrTy(F.getContext(),
          RuntimeMD::KernelArg::Global);
      emitRuntimeMetadataForKernelArg(DL, Int8PtrT,
                                      RuntimeMD::KernelArg::HiddenPrintfBuffer);
    }
  }

  // Emit KeyReqdWorkGroupSize, KeyWorkGroupSizeHint, and KeyVecTypeHint.
  if (auto RWGS = F.getMetadata("reqd_work_group_size")) {
    emitRuntimeMDThreeIntValues(RuntimeMD::KeyReqdWorkGroupSize,
                                RWGS, 4);
  }

  if (auto WGSH = F.getMetadata("work_group_size_hint")) {
    emitRuntimeMDThreeIntValues(RuntimeMD::KeyWorkGroupSizeHint,
                                WGSH, 4);
  }

  if (auto VTH = F.getMetadata("vec_type_hint")) {
    auto TypeName = getOCLTypeName(cast<ValueAsMetadata>(
      VTH->getOperand(0))->getType(), mdconst::extract<ConstantInt>(
      VTH->getOperand(1))->getZExtValue());
    emitRuntimeMDStringValue(RuntimeMD::KeyVecTypeHint, TypeName);
  }

  // Emit KeyKernelEnd
  S.EmitIntValue(RuntimeMD::KeyKernelEnd, 1);
}