static TRI_aql_node_t* OptimiseBinaryArithmeticOperation (TRI_aql_context_t* const context,
                                                          TRI_aql_node_t* node) {
  TRI_aql_node_t* lhs = TRI_AQL_NODE_MEMBER(node, 0);
  TRI_aql_node_t* rhs = TRI_AQL_NODE_MEMBER(node, 1);
  bool isEligibleLhs;
  bool isEligibleRhs;
  double value;
  
  if (!lhs || !rhs) {
    return node;
  } 

  isEligibleLhs = TRI_IsConstantValueNodeAql(lhs);
  isEligibleRhs = TRI_IsConstantValueNodeAql(rhs);

  if (isEligibleLhs && !TRI_IsNumericValueNodeAql(lhs)) {
    // node is not a numeric value => error
    TRI_SetErrorContextAql(context, TRI_ERROR_QUERY_INVALID_ARITHMETIC_VALUE, NULL);
    return node;
  }

  
  if (isEligibleRhs && !TRI_IsNumericValueNodeAql(rhs)) {
    // node is not a numeric value => error
    TRI_SetErrorContextAql(context, TRI_ERROR_QUERY_INVALID_ARITHMETIC_VALUE, NULL);
    return node;
  }
  

  if (!isEligibleLhs || !isEligibleRhs) {
    return node;
  }
  
  assert(node->_type == TRI_AQL_NODE_OPERATOR_BINARY_PLUS ||
         node->_type == TRI_AQL_NODE_OPERATOR_BINARY_MINUS ||
         node->_type == TRI_AQL_NODE_OPERATOR_BINARY_TIMES ||
         node->_type == TRI_AQL_NODE_OPERATOR_BINARY_DIV ||
         node->_type == TRI_AQL_NODE_OPERATOR_BINARY_MOD);

  if (node->_type == TRI_AQL_NODE_OPERATOR_BINARY_PLUS) {
    value = TRI_GetNumericNodeValueAql(lhs) + TRI_GetNumericNodeValueAql(rhs);
  }
  else if (node->_type == TRI_AQL_NODE_OPERATOR_BINARY_MINUS) {
    value = TRI_GetNumericNodeValueAql(lhs) - TRI_GetNumericNodeValueAql(rhs);
  }
  else if (node->_type == TRI_AQL_NODE_OPERATOR_BINARY_TIMES) {
    value = TRI_GetNumericNodeValueAql(lhs) * TRI_GetNumericNodeValueAql(rhs);
  }
  else if (node->_type == TRI_AQL_NODE_OPERATOR_BINARY_DIV) {
    if (TRI_GetNumericNodeValueAql(rhs) == 0.0) {
      // division by zero
      TRI_SetErrorContextAql(context, TRI_ERROR_QUERY_DIVISION_BY_ZERO, NULL);
      return node;
    }
    value = TRI_GetNumericNodeValueAql(lhs) / TRI_GetNumericNodeValueAql(rhs);
  }
  else if (node->_type == TRI_AQL_NODE_OPERATOR_BINARY_MOD) {
    if (TRI_GetNumericNodeValueAql(rhs) == 0.0) {
      // division by zero
      TRI_SetErrorContextAql(context, TRI_ERROR_QUERY_DIVISION_BY_ZERO, NULL);
      return node;
    }
    value = fmod(TRI_GetNumericNodeValueAql(lhs), TRI_GetNumericNodeValueAql(rhs));
  }
  else {
    value = 0.0;
  }
  
  node = TRI_CreateNodeValueDoubleAql(context, value);

  if (!node) {
    TRI_SetErrorContextAql(context, TRI_ERROR_OUT_OF_MEMORY, NULL);
    return NULL;
  }
  
  LOG_TRACE("optimised away binary arithmetic operation");

  return node;
}