void simplify_byte_expr(exprt &dest,
                        const namespacet &ns)
{

  /*
   * byte_update(byte_update(e, i, v, t), i, v', t)
   *             -----------------------
   *                    root
   *  =>
   * byte_update(e, i, v', t)
   */
  if(dest.id()==ID_byte_update_little_endian
  || dest.id()==ID_byte_update_big_endian)
  {

    exprt &root=dest.op0();
    exprt &offset=dest.op1();
    const typet &type=root.type();

    if(root.id()==ID_byte_update_little_endian
    || root.id()==ID_byte_update_big_endian)
    {
      exprt &nested_root=root.op0();
      exprt &nested_offset=root.op1();
      const typet &nested_type=root.type();


      if(offset == nested_offset
      && type == nested_type)
      {

        #ifdef DEBUG
        std::cout << "simplify_byte_expr " << from_expr(dest) << std::endl;
        #endif

        root.swap(nested_root);

        #ifdef DEBUG
        std::cout << "  ==> " << from_expr(dest) << std::endl;
        #endif
      }
    }
  }

  /*
   * byte_extract(byte_update(e, i, v, t), i, t)
   *  =>
   * v
   */
  else
  if(dest.id()==ID_byte_extract_little_endian
  || dest.id()==ID_byte_extract_big_endian)
  {
    exprt &root=dest.op0();
    exprt &offset=dest.op1();
    const typet &type=dest.type();

    if(root.id()==ID_byte_update_little_endian
    || root.id()==ID_byte_update_big_endian)
    {
      exprt &nested_offset=root.op1();
      exprt &nested_with=root.op2();
      const typet &nested_type=root.type();


      if(offset == nested_offset
      && type == nested_type)
      {
        #ifdef DEBUG
        std::cout << "simplify_byte_expr " << from_expr(dest) << std::endl;
        #endif

        dest.swap(nested_with);

        //#ifdef DEBUG
        std::cout << "  ==> " << from_expr(dest) << std::endl;
        //#endif
      }
    }
  }

  if(dest.has_operands())
    Forall_operands(it, dest)
      simplify_byte_expr(*it, ns);
}