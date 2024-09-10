// Returns all flat address expressions in function F. The elements are
// If V is an unvisited flat address expression, appends V to PostorderStack
// and marks it as visited.
void InferAddressSpaces::appendsFlatAddressExpressionToPostorderStack(
    Value *V, std::vector<std::pair<Value *, bool>> &PostorderStack,
    DenseSet<Value *> &Visited) const {
  assert(V->getType()->isPointerTy());

  // Generic addressing expressions may be hidden in nested constant
  // expressions.
  if (ConstantExpr *CE = dyn_cast<ConstantExpr>(V)) {
    // TODO: Look in non-address parts, like icmp operands.
    if (isAddressExpression(*CE) && Visited.insert(CE).second)
      PostorderStack.push_back(std::make_pair(CE, false));

    return;
  }

  if (isAddressExpression(*V) &&
      V->getType()->getPointerAddressSpace() == FlatAddrSpace) {
    if (Visited.insert(V).second) {
      PostorderStack.push_back(std::make_pair(V, false));

      Operator *Op = cast<Operator>(V);
      for (unsigned I = 0, E = Op->getNumOperands(); I != E; ++I) {
        if (ConstantExpr *CE = dyn_cast<ConstantExpr>(Op->getOperand(I))) {
          if (isAddressExpression(*CE) && Visited.insert(CE).second)
            PostorderStack.emplace_back(CE, false);
        }
      }
    }
  }
}