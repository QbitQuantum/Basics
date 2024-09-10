CosNaming::NamingContext_ptr
TAO_Hash_Naming_Context::get_context (const CosNaming::Name &name)
{
  CosNaming::NamingContext_var result =
    CosNaming::NamingContext::_nil ();

  // Create compound name to be resolved, i.e.,
  // (<name> - last component).  To avoid copying, we can just reuse
  // <name>'s buffer, since we will not be modifying it.
  CORBA::ULong name_len = name.length ();
  CosNaming::Name comp_name (name.maximum (),
                             name_len - 1,
                             const_cast<CosNaming::NameComponent*> (name.get_buffer ()));
  try
    {
      CORBA::Object_var context = this->resolve (comp_name);

      // Try narrowing object reference to the NamingContext type.
      result = CosNaming::NamingContext::_narrow (context.in ());
    }
  catch (CosNaming::NamingContext::NotFound& ex)
    {
      // Add the last component of the name, which was stripped before
      // the call to resolve.
      CORBA::ULong const rest_len = ex.rest_of_name.length () + 1;
      ex.rest_of_name.length (rest_len);
      ex.rest_of_name[rest_len - 1] = name[name_len - 1];

      throw;
    }

  if (CORBA::is_nil (result.in ()))
    {
      CosNaming::Name rest;
      rest.length (2);
      rest[0] = name[name_len - 2];
      rest[1] = name[name_len - 1];
      throw CosNaming::NamingContext::NotFound(
        CosNaming::NamingContext::not_context,
        rest);
    }
  // Finally, if everything went smoothly, just return the resolved
  // context.
  return result._retn ();
}