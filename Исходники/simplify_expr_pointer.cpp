bool simplify_exprt::simplify_address_of_arg(exprt &expr)
{
    if(expr.id()==ID_index)
    {
        if(expr.operands().size()==2)
        {
            bool result=true;
            if(!simplify_address_of_arg(expr.op0())) result=false;
            if(!simplify_rec(expr.op1())) result=false;

            // rewrite (*(type *)int) [index] by
            // pushing the index inside

            mp_integer address;
            if(is_dereference_integer_object(expr.op0(), address))
            {
                // push index into address

                mp_integer step_size, index;

                step_size=pointer_offset_size(expr.type(), ns);

                if(!to_integer(expr.op1(), index) &&
                        step_size!=-1)
                {
                    unsignedbv_typet int_type(config.ansi_c.pointer_width);
                    pointer_typet pointer_type;
                    pointer_type.subtype()=expr.type();
                    typecast_exprt typecast_expr(
                        from_integer(step_size*index+address, int_type), pointer_type);
                    exprt new_expr=dereference_exprt(typecast_expr, expr.type());
                    expr=new_expr;
                    result=true;
                }
            }

            return result;
        }
    }
    else if(expr.id()==ID_member)
    {
        if(expr.operands().size()==1)
        {
            bool result=true;
            if(!simplify_address_of_arg(expr.op0())) result=false;

            const typet &op_type=ns.follow(expr.op0().type());

            if(op_type.id()==ID_struct)
            {
                // rewrite NULL -> member by
                // pushing the member inside

                mp_integer address;
                if(is_dereference_integer_object(expr.op0(), address))
                {
                    const struct_typet &struct_type=to_struct_type(op_type);
                    const irep_idt &member=to_member_expr(expr).get_component_name();
                    mp_integer offset=member_offset(struct_type, member, ns);
                    if(offset!=-1)
                    {
                        unsignedbv_typet int_type(config.ansi_c.pointer_width);
                        pointer_typet pointer_type;
                        pointer_type.subtype()=expr.type();
                        typecast_exprt typecast_expr(
                            from_integer(address+offset, int_type), pointer_type);
                        exprt new_expr=dereference_exprt(typecast_expr, expr.type());
                        expr=new_expr;
                        result=true;
                    }
                }
            }

            return result;
        }
    }
    else if(expr.id()==ID_dereference)
    {
        if(expr.operands().size()==1)
            return simplify_rec(expr.op0());
    }
    else if(expr.id()==ID_if)
    {
        if(expr.operands().size()==3)
        {
            bool result=true;
            if(!simplify_rec(expr.op0())) result=false;
            if(!simplify_address_of_arg(expr.op1())) result=false;
            if(!simplify_address_of_arg(expr.op2())) result=false;

            // op0 is a constant?
            if(expr.op0().is_true())
            {
                result=false;
                exprt tmp;
                tmp.swap(expr.op1());
                expr.swap(tmp);
            }
            else if(expr.op0().is_false())
            {
                result=false;
                exprt tmp;
                tmp.swap(expr.op2());
                expr.swap(tmp);
            }

            return result;
        }
    }

    return true;
}