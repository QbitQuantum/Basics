void
TAO::PG_Object_Group_Storable::read (TAO::Storable_Base & stream)
{
  stream.rewind ();

  ACE_CString group_name;
  stream >> group_name;

  PG_Object_Group::set_name(group_name.c_str());

  stream >> this->distribute_;

  stream >> this->role_;

  ///// primary_location_ /////
  read_cdr (stream, this->primary_location_);

  ///// reference_ /////
  ACE_CString reference_ior;
  stream >> reference_ior;
  this->reference_ = this->orb_->string_to_object (reference_ior.c_str ());

  ///// tagged_component_ /////
  read_cdr (stream, this->tagged_component_);

  ///// type_id_ /////
  // special note: A memory leak appears when the type_id_ is read into directly.
  // reading into a temporary string and handing that to the type_id_ does not leak.
  CORBA::String_var tmp;
  read_cdr(stream, tmp);
  this->type_id_ = tmp._retn();

  ///// properties_ /////
  PortableGroup::Criteria properties;
  read_cdr (stream, properties);
  PG_Object_Group::set_properties_dynamically (properties);

  ///// members_ /////
  int num_members;
  stream >> num_members;

  if (num_members == 0)
    this->empty_ = 1;
  else
    this->empty_ = 0;

  this->clear_members_map ();

  for (int i = 0; i < num_members; ++i)
    {
      ///// location used as members_ key /////
      PortableGroup::Location the_location;
      read_cdr (stream, the_location);

      ///// member /////
      ACE_CString member_ior;
      stream >> member_ior;
      CORBA::Object_var member =
        this->orb_->string_to_object (member_ior.c_str ());
      if (CORBA::is_nil (member.in ()))
        {
          if (TAO_debug_level > 0)
            {
              ORBSVCS_DEBUG ((LM_DEBUG,
                              ACE_TEXT ("(%P|%t) PG_Object_Group_Storable::")
                              ACE_TEXT ("string_to_object failed\n")));
            }
          throw CORBA::INV_OBJREF ();
        }

      ///// location /////
      PortableGroup::Location location;
      read_cdr (stream, location);

      ///// factory /////
      ACE_CString factory_ior;
      stream >> factory_ior;
      CORBA::Object_var obj =
        this->orb_->string_to_object (factory_ior.c_str ());
      PortableGroup::GenericFactory_var factory =
        PortableGroup::GenericFactory::_narrow (obj.in());

      ///// factory_id (typedef of CORBA::Any) /////
      PortableGroup::GenericFactory::FactoryCreationId factory_id;
      read_cdr (stream, factory_id);

      ///// is_primary /////
      int is_primary;
      stream >> is_primary;

      MemberInfo * info = 0;
      ACE_NEW_THROW_EX (info, MemberInfo(member.in (),
                                         the_location,
                                         factory.in (),
                                         factory_id),
                        CORBA::NO_MEMORY());

      info->is_primary_ = is_primary;

      if (this->members_.bind (the_location, info) != 0)
        {
          throw CORBA::NO_MEMORY();
        }
    }
}