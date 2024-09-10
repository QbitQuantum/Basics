QualType CallOrObjCMessage::getResultType(ASTContext &ctx) const {
  QualType resultTy;
  bool isLVal = false;

  if (isObjCMessage()) {
    isLVal = isa<ObjCMessageExpr>(Msg.getOriginExpr()) &&
             Msg.getOriginExpr()->isLValue();
    resultTy = Msg.getResultType(ctx);
  } else if (const CXXConstructExpr *Ctor =
              CallE.dyn_cast<const CXXConstructExpr *>()) {
    resultTy = Ctor->getType();
  } else {
    const CallExpr *FunctionCall = CallE.get<const CallExpr *>();

    isLVal = FunctionCall->isLValue();
    const Expr *Callee = FunctionCall->getCallee();
    if (const FunctionDecl *FD = State->getSVal(Callee).getAsFunctionDecl())
      resultTy = FD->getResultType();
    else
      resultTy = FunctionCall->getType();
  }

  if (isLVal)
    resultTy = ctx.getPointerType(resultTy);

  return resultTy;
}