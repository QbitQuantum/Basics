llvm::Constant *irgen::emitConstantInt(IRGenModule &IGM,
                                       IntegerLiteralInst *ILI) {
  APInt value = ILI->getValue();
  BuiltinIntegerWidth width
    = ILI->getType().castTo<BuiltinIntegerType>()->getWidth();

  // The value may need truncation if its type had an abstract size.
  if (!width.isFixedWidth()) {
    assert(width.isPointerWidth() && "impossible width value");

    unsigned pointerWidth = IGM.getPointerSize().getValueInBits();
    assert(pointerWidth <= value.getBitWidth()
           && "lost precision at AST/SIL level?!");
    if (pointerWidth < value.getBitWidth())
      value = value.trunc(pointerWidth);
  }

  return llvm::ConstantInt::get(IGM.LLVMContext, value);
}