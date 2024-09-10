// Add the ObjectID:IOR mapping to the IOR table of
// the ORB. Ignore this method if you are not testing for
// the InterOperable Naming Service.
template <class Servant> int
Server<Servant>::test_for_ins (const char *ior)
{
  CORBA::ORB_var orb = this->orb_manager_.orb ();

  if (TAO_debug_level > 0)
    ACE_DEBUG ((LM_DEBUG,
                ACE_TEXT ("Adding (KEY:IOR) %s:%C\n"),
                this->ins_,
                ior));

  try
    {
      CORBA::Object_var table_object =
        orb->resolve_initial_references ("IORTable");

      IORTable::Table_var adapter =
        IORTable::Table::_narrow (table_object.in ());
      if (CORBA::is_nil (adapter.in ()))
        {
          ACE_ERROR_RETURN ((LM_ERROR,
                             ACE_TEXT ("Nil IORTable\n")),
                            -1);
        }

      adapter->bind (ACE_TEXT_ALWAYS_CHAR (this->ins_), ior);
    }
  catch (const CORBA::Exception& ex)
    {
      ex._tao_print_exception ("ERROR: test_for_ins failed\n");
      return -1;
    }

  return 0;
}