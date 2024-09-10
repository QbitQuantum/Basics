/**
  * Checks that the arguments to logical operators are all boolean
  *
  * If not, an error message is logged.
  */
void 
ValidCnUnitsValue::checkValidUnits (const Model& m, const ASTNode& node, 
                                                const SBase & sb)
{
  std::string units = node.getUnits();

  if (!units.empty())
  {
    if (!(Unit::isUnitKind(units, m.getLevel(), m.getVersion()))
      && (m.getUnitDefinition(units) == NULL))
    {
      logMathConflict(node, sb);
    }
  }
}