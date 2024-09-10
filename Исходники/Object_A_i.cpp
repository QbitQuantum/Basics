void
Object_A_i::shutdown (void)
{
  int argc = 0;
  ACE_TCHAR **argv = 0;
  CORBA::ORB_var orb = CORBA::ORB_init (argc, argv);

  orb->shutdown ();
}