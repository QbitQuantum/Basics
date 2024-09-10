int
TAO_Log_Constraint_Visitor::visit_union_pos (
    ETCL_Union_Pos *union_pos)
{
  try
    {
      if (union_pos->union_value ()->accept (this) == 0)
        {
          TAO_ETCL_Literal_Constraint disc_val;
          this->queue_.dequeue_head (disc_val);

          TAO_DynUnion_i dyn_union;
          dyn_union.init (this->current_member_.in ());

          CORBA::TypeCode_var tc = this->current_member_->type ();

          switch (disc_val.expr_type ())
          {
            case ETCL_INTEGER:
            case ETCL_SIGNED:
            case ETCL_UNSIGNED:
              {
                CORBA::Any disc_any;
                CORBA::TypeCode_var disc_tc =
                  tc->discriminator_type ();
                CORBA::TCKind disc_kind =
                  TAO_DynAnyFactory::unalias (disc_tc.in ());

                switch (disc_kind)
                {
                  case CORBA::tk_boolean:
                    disc_any <<= CORBA::Any::from_boolean ((CORBA::Boolean) disc_val);
                    break;
                  case CORBA::tk_short:
                    disc_any <<= (CORBA::Short) ((CORBA::Long) disc_val);
                    break;
                  case CORBA::tk_ushort:
                    disc_any <<= (CORBA::UShort) ((CORBA::ULong) disc_val);
                    break;
                  case CORBA::tk_long:
                    disc_any <<= (CORBA::Long) disc_val;
                    break;
                  case CORBA::tk_ulong:
                    disc_any <<= (CORBA::ULong) disc_val;
                    break;
                  case CORBA::tk_enum:
                    {
                      TAO_OutputCDR cdr;
                      cdr.write_ulong ((CORBA::ULong) disc_val);
                      TAO_InputCDR in_cdr (cdr);
                      TAO::Unknown_IDL_Type *unk = 0;
                      ACE_NEW_RETURN (unk,
                                      TAO::Unknown_IDL_Type (disc_tc.in (),
                                                             in_cdr),
                                      -1);

                      disc_any.replace (unk);
                      break;
                    }
                  // @@@ (JP) I don't think ETCL handles 64-bit
                  // integers at this point, and I also think that
                  // chars and/or wchars will just come out in the
                  // constraint as (w)strings of length 1.
                  case CORBA::tk_longlong:
                  case CORBA::tk_ulonglong:
                  case CORBA::tk_char:
                  case CORBA::tk_wchar:
                  default:
                    return -1;
                }

                DynamicAny::DynAny_var dyn_any =
                  TAO::MakeDynAnyUtils::make_dyn_any_t<const CORBA::Any &> (
                    disc_tc.in (),
                    disc_any);

                dyn_union.set_discriminator (dyn_any.in ());
                DynamicAny::DynAny_var u_member =
                  dyn_union.member ();

                this->current_member_ =
                  u_member->to_any ();

                break;
              }
            case ETCL_STRING:
              {
                const char *name = (const char *) disc_val;
                CORBA::ULong count =
                  tc->member_count ();

                const char *member_name = 0;
                CORBA::ULong i = 0;

                for (i = 0; i < count; ++i)
                  {
                    member_name = tc->member_name (i);

                    if (ACE_OS::strcmp (name, member_name) == 0)
                      {
                        break;
                      }
                  }

                // If there's no match, member_label will throw
                // CORBA::TypeCode::Bounds and the catch block will
                // return -1;
                this->current_member_ = tc->member_label (i);

                break;
              }
            // The TAO_ETCL_Union_Value that was put on the queue
            // shouldn't have any other type.
            default:
              return -1;
          }

          ETCL_Constraint *nested = union_pos->component ();

          // If there's no nested component, then we just want the
          // union member value on the queue. Otherwise, we want
          // the member value in current_member_ while we visit
          // the nested component.
          if (nested == 0)
            {
              TAO_ETCL_Literal_Constraint lit (this->current_member_.ptr ());
              this->queue_.enqueue_head (lit);
              return 0;
            }
          else
            {
              return nested->accept (this);
            }
        }
      else
        {
          return -1;
        }
    }
  catch (const CORBA::Exception&)
    {
      return -1;
    }
}