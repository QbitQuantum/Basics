void c_typecastt::do_typecast(exprt &expr, const typet &type)
{
  // special case: array -> pointer is actually
  // something like address_of
  
  const typet &expr_type=ns.follow(expr.type());

  if(expr_type.id()==ID_array)
  {
    index_exprt index;
    index.array()=expr;
    index.index()=gen_zero(index_type());
    index.type()=expr_type.subtype();
    expr=address_of_exprt(index);
    if(ns.follow(expr.type())!=ns.follow(type))
      expr.make_typecast(type);
    return;
  }

  if(expr_type!=type)
  {
    // C booleans are special: we compile to ?0:1
    
    if(type.get(ID_C_c_type)==ID_bool)
    {
      if(expr_type.id()==ID_bool) // bool -> _Bool
      {
        exprt result=if_exprt(expr, gen_one(type), gen_zero(type));
        expr.swap(result);
      }
      else // * -> _Bool
      {
        equal_exprt equal_zero(expr, gen_zero(expr_type));
        exprt result=if_exprt(equal_zero, gen_zero(type), gen_one(type));
        expr.swap(result);
      }
    }
    else
    {    
      expr.make_typecast(type);
    }
  }
}