int
TAO_CosNotify_Service::fini (void)
{
  if (TAO_Notify_PROPERTIES::instance()->separate_dispatching_orb())
    {
      if (!CORBA::is_nil (TAO_Notify_PROPERTIES::instance()->dispatching_orb()))
        {
          CORBA::ORB_var dispatcher =
            TAO_Notify_PROPERTIES::instance()->dispatching_orb();
          dispatcher->shutdown ();
          dispatcher->destroy ();
        }
    }

  TAO_Notify_Properties::instance()->close ();
  return 0;
}