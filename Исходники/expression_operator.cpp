Type
compile(const Node&  l, const UnaryOperator&   op, Context&  ctx)
{
  auto  l_type = l.compile(ctx);

    if(op == Operator('&'))
    {
        if(l_type != TypeKind::reference)
        {
          printf("参照でないオブジェクトのアドレスを取得しようとしました\n");

          throw;
        }


      return I32Type();
    }


    if(l_type == TypeKind::reference)
    {
      l_type = l_type.compile_dereference(ctx);
    }


    switch(op)
    {
      case(Operator('*')):
          if(l_type != TypeKind::pointer)
          {
            printf("ポインタでないオブジェクトを参照しようとしました\n");

            throw;
          }


        return l_type.make_reference();
        break;
      case(Operator('!')): ctx.push("  lnot;\n");break;
      case(Operator('~')): ctx.push("  bnot;\n");break;
      case(Operator('-')): ctx.push("  neg ;\n");break;
    }


  return I32Type();
}