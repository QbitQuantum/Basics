  string NetworkDriverRewriteVisitor::GetSharedStructStrInFunctionBody(Stmt *body, bool doLog)
  {
    string shared_struct_str = "";

    for (auto i = body->child_begin(), e = body->child_end(); i != e; ++i)
    {
      if (isa<DeclStmt>(*i))
      {
        DeclStmt *declStmt = cast<DeclStmt>(*i);
        if (!declStmt->isSingleDecl() && !isa<VarDecl>(declStmt->getSingleDecl()))
          continue;

        VarDecl *varDecl = cast<VarDecl>(declStmt->getSingleDecl());
        if (!isa<ValueDecl>(varDecl))
          continue;

        ValueDecl *value = cast<ValueDecl>(varDecl);

        if (value->getType().getAsString(Context->getPrintingPolicy()) != "struct net_device *")
          continue;
        if (!isa<NamedDecl>(varDecl))
          continue;

        if (varDecl->getInit() == 0 || !isa<CallExpr>(varDecl->getInit()))
          continue;

        CallExpr *callExpr = cast<CallExpr>(varDecl->getInit());
        shared_struct_str = GetSharedStructStr(callExpr);
        if (shared_struct_str != "")
        {
          if (doLog)
          {
            Expr *callee = callExpr->getCallee();
            ImplicitCastExpr *calleeImplExpr = cast<ImplicitCastExpr>(callee);
            DeclRefExpr *calleeDeclExpr = cast<DeclRefExpr>(calleeImplExpr->getSubExpr());
            DI->getInstance().AddSharedStructInformation("whoop_network_shared_struct",
              calleeDeclExpr->getNameInfo().getAsString());
          }

          break;
        }
      }
      else if (isa<BinaryOperator>(*i))
      {
        BinaryOperator *binOp = cast<BinaryOperator>(*i);
        if (!isa<CallExpr>(binOp->getRHS()))
          continue;

        CallExpr *callExpr = cast<CallExpr>(binOp->getRHS());
        shared_struct_str = GetSharedStructStr(callExpr);
        if (shared_struct_str != "")
        {
          if (doLog)
          {
            Expr *callee = callExpr->getCallee();
            ImplicitCastExpr *calleeImplExpr = cast<ImplicitCastExpr>(callee);
            DeclRefExpr *calleeDeclExpr = cast<DeclRefExpr>(calleeImplExpr->getSubExpr());
            DI->getInstance().AddSharedStructInformation("whoop_network_shared_struct",
              calleeDeclExpr->getNameInfo().getAsString());
          }

          break;
        }
      }
    }

    return shared_struct_str;
  }