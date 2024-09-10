void handler(int r)
{
  DMSG_("Stoping service... ");
  my_global_orb->shutdown(true);
  DMSG("Done");
  exit(1);
}