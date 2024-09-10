/*
 * Verify the device info
 */
void VerifyDevInfo(void) {
   if (!ignore_dev_info && !cpci_reprog) {
      /* Read the device info from the board */
      nf2_read_info(&nf2);

      /* Print the device information */
      printf(getDeviceInfoStr(&nf2));

      /* Check the CPCI version info */
      if (getDeviceID(&nf2) == -1) {
         fprintf(log_file, "WARNING: NetFPGA device info not found. Cannot verify that the CPCI version matches.\n");
      }
      else {
         if (getCPCIVersion(&nf2) != getDeviceCPCIVersion(&nf2)) {// ||
            // Commented out so the script will not give an error on revision number changes.  Revisions should be small changes that do not need users to upgrade the CPCI.  The users should only be forced to change the CPCI on a major release.
            // cpci_revision != nf2_cpci_revision) {
            fprintf(stderr, "Error: Virtex design compiled against a different CPCI version\n");
            fprintf(stderr, "  Active CPCI version : %d (rev %d)\n", getCPCIVersion(&nf2), getCPCIRevision(&nf2));
            fprintf(stderr, "  Device built against: %d (rev %d)\n", getDeviceCPCIVersion(&nf2), getDeviceCPCIRevision(&nf2));
            exit(1);
         }
         else {
            fprintf(stderr,"Virtex design compiled against active CPCI version\n");
         }
      }
   }
}