void cpp_typecheckt::new_temporary(
  const source_locationt &source_location,
  const typet &type,
  const exprt::operandst &ops,
  exprt &temporary)
{
  // create temporary object
  exprt tmp_object_expr=exprt(ID_side_effect, type);
  tmp_object_expr.set(ID_statement, ID_temporary_object);
  tmp_object_expr.add_source_location()= source_location;

  exprt new_object(ID_new_object);
  new_object.add_source_location()=tmp_object_expr.source_location();
  new_object.set(ID_C_lvalue, true);
  new_object.type()=tmp_object_expr.type();

  already_typechecked(new_object);

  codet new_code =
    cpp_constructor(source_location, new_object, ops);

  if(new_code.is_not_nil())
  {
    if(new_code.get(ID_statement)==ID_assign)
      tmp_object_expr.move_to_operands(new_code.op1());
    else
      tmp_object_expr.add(ID_initializer)=new_code;
  }

  temporary.swap(tmp_object_expr);
}