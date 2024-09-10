 void Operation(const std::string& op) override
 {
   const std::size_t usedVals = Operator(op).Parameters();
   CheckAvailableParameters(usedVals, Position);
   Position = Position - usedVals + 1;
   Delegate.Operation(op);
 }