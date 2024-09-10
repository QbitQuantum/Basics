//
// Function: makeCStdLibCallsComplete()
//
// Description:
//  Fills in completeness information for all calls of a given CStdLib function
//  assumed to be of the form:
//
//   pool_X(POOL *p1, ..., POOL *pN, void *a1, ..., void *aN, ..., uint8_t c);
//
//  Specifically, this function assumes that there are as many pointer arguments
//  to check as there are initial pool arguments, and the pointer arguments
//  follow the pool arguments in corresponding order. Also, it is assumed that
//  the final argument to the function is a byte sized bit vector.
//
//  This function fills in this final byte with a constant value whose ith
//  bit is set exactly when the ith pointer argument is complete.
//
// Inputs:
//
//  F            - A pointer to the CStdLib function appearing in the module
//                 (non-null).
//  PoolArgs     - The number of initial pool arguments for which a
//                 corresponding pointer value requires a completeness check
//                 (required to be at most 8).
//
void
CompleteChecks::makeCStdLibCallsComplete(Function *F, unsigned PoolArgs) {
  assert(F != 0 && "Null function argument!");

  assert(PoolArgs <= 8 && \
    "Only up to 8 arguments are supported by CStdLib completeness checks!");

  Value::use_iterator U = F->use_begin();
  Value::use_iterator E = F->use_end();

  //
  // Hold the call instructions that need changing.
  //
  typedef std::pair<CallInst *, uint8_t> VectorReplacement;
  std::set<VectorReplacement> callsToChange;

  Type *int8ty = Type::getInt8Ty(F->getContext());
  FunctionType *F_type = F->getFunctionType();

  //
  // Verify the type of the function is as expected.
  //
  // There should be as many pointer parameters to check for completeness
  // as there are pool parameters. The last parameter should be a byte.
  //
  assert(F_type->getNumParams() >= PoolArgs * 2 && \
    "Not enough arguments to transformed CStdLib function call!");
  for (unsigned arg = PoolArgs; arg < PoolArgs * 2; ++arg)
    assert(isa<PointerType>(F_type->getParamType(arg)) && \
      "Expected pointer argument to function!");

  //
  // This is the position of the vector operand in the call.
  //
  unsigned vect_position = F_type->getNumParams();

  assert(F_type->getParamType(vect_position - 1) == int8ty && \
    "Last parameter to the function should be a byte!");

  //
  // Iterate over all calls of the function in the module, computing the
  // vectors for each call as it is found.
  //
  for (; U != E; ++U) {
    CallInst *CI;
    if ((CI = dyn_cast<CallInst>(*U)) && \
      CI->getCalledValue()->stripPointerCasts() == F) {

      uint8_t vector = 0x0;

      //
      // Get the parent function to which this instruction belongs.
      //
      Function *P = CI->getParent()->getParent();

      //
      // Iterate over the pointer arguments that need completeness checking
      // and build the completeness vector.
      //
      for (unsigned arg = 0; arg < PoolArgs; ++arg) {
        bool complete = true;
        //
        // Go past all the pool arguments to get the pointer to check.
        //
        Value *V = CI->getOperand(1 + PoolArgs + arg);

        //
        // Check for completeness of the pointer using DSA and 
        // set the bit in the vector accordingly.
        //
        DSNode *N;
        if ((N = getDSNodeHandle(V, P).getNode()) &&
              (N->isExternalNode() || N->isIncompleteNode() ||
               N->isUnknownNode()  || N->isIntToPtrNode()   ||
               N->isPtrToIntNode()) ) {
            complete = false;
        }

        if (complete)
          vector |= (1 << arg);
      }

      //
      // Add the instruction and vector to the set of instructions to change.
      //
      callsToChange.insert(VectorReplacement(CI, vector));
    }
  }


  //
  // Iterate over all call instructions that need changing, modifying the
  // final operand of the call to hold the bit vector value.
  //
  std::set<VectorReplacement>::iterator change = callsToChange.begin();
  std::set<VectorReplacement>::iterator change_end = callsToChange.end();

  while (change != change_end) {
    Constant *vect_value = ConstantInt::get(int8ty, change->second);
    change->first->setOperand(vect_position, vect_value);
    ++change;
  }

  return;

}