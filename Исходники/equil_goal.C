void
EquilibriumGoal_A::initialize (const Units& units, const Scope& scope, 
                               Treelog& msg)
{ 
  goal_A_expr->initialize (units, scope, msg);
  min_B_expr->initialize (units, scope, msg);
}