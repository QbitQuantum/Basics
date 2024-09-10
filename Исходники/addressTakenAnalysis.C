// cast can be lvalue
// example :  &((struct _Rep *)((this) -> _M_data()))[-1] expr from stl_list
void SPRAY::ComputeAddressTakenInfo::OperandToVariableId::visit(SgCastExp* sgn)
{
  if(debuglevel > 0) debugPrint(sgn);
  SgNode* operand = sgn->get_operand();
  operand->accept(*this);
}