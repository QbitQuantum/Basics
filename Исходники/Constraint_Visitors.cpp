int
TAO_Constraint_Evaluator::visit_max (TAO_Unary_Constraint* unary_max)
{
  TAO_Constraint* operand = unary_max->operand ();
  return operand->accept (this);
}