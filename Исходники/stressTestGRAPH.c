static void gid_location(long gid, long *cylID, long *ringID)
{
  ldiv_t result;
  result = ldiv(gid, cylSize);
  *cylID = result.quot;  /* cylinder ID */
  *ringID = result.rem;  /* ring ID */
}