bool SuperastCPP::TraverseCXXOperatorCallExpr(clang::CXXOperatorCallExpr* operatorCallExpr) {
  // IF THERE IS A PRINT
  auto decl = llvm::dyn_cast<clang::FunctionDecl>(operatorCallExpr->getCalleeDecl());
  if (!decl) {
    std::cerr << "Unknown function in CXXOperatorCallExpr" << std::endl;
    return true;
  }
  const std::string functionName = decl->getNameInfo().getAsString();
  if (functionName == PRINT_NAME || functionName == READ_NAME) {
    bool isFirst = false;
    if (!iofunctionStarted) {
      isFirst = true;
      iofunctionStarted = true;
    }

    rapidjson::Value arrayValue(rapidjson::kArrayType);
    for (unsigned i = 0; i < operatorCallExpr->getNumArgs(); ++i) {
      TRY_TO(TraverseStmt(operatorCallExpr->getArg(i)));
      if (i == 0) {
        // If sonValue is not an array, is because it reached the begin of
        // call, which is the cout/cerr/stream class
        if (sonValue.IsArray()) {
          arrayValue = sonValue;
        }
      }
      else {
        arrayValue.PushBack(sonValue, allocator);
      }
    }
    
    if (!isFirst) {
      sonValue = arrayValue;
    }
    else {
      iofunctionStarted = false;

      rapidjson::Value functionValue(rapidjson::kObjectType);
      addId(functionValue);
      addPos(functionValue, operatorCallExpr);
      functionValue.AddMember("type", "function-call", allocator);
      if (functionName == PRINT_NAME) 
        functionValue.AddMember("name", "print", allocator);
      else functionValue.AddMember("name", "read", allocator);
      functionValue.AddMember("arguments", arrayValue, allocator);
      sonValue = functionValue;
    }
  }
  else if (functionName == VECTOR_POS_NAME) {
    // Operator []
    TRY_TO(TraverseStmt(operatorCallExpr->getArg(0)));
    rapidjson::Value leftValue(rapidjson::kObjectType);
    leftValue = sonValue;
    TRY_TO(TraverseStmt(operatorCallExpr->getArg(1)));
    rapidjson::Value rightValue(rapidjson::kObjectType);
    rightValue = sonValue;
    sonValue = createBinOpValue("[]", leftValue, rightValue);
  }
  else {
    std::cerr << "Operator call not defined: " << functionName << std::endl;
  }
    return true;
}