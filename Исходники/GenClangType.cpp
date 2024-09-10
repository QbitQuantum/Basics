static clang::CanQualType getClangSelectorType(
    const clang::ASTContext &clangCtx) {
    return clangCtx.getPointerType(clangCtx.ObjCBuiltinSelTy);
}