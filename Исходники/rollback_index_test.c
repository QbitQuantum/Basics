/* Adjusts KERNEL_VERSIONS space.
 */
static uint32_t RollbackTest_AdjustKernelVersions(int* wrong_value) {
  uint8_t kdata[KERNEL_SPACE_SIZE];
  int exists;
  uint32_t result;

  result = TlclRead(KERNEL_VERSIONS_NV_INDEX, kdata, sizeof(kdata));
  if (result != TPM_SUCCESS && result != TPM_E_BADINDEX) {
    return result;
  }
  *wrong_value = Memcmp(kdata + sizeof(uint32_t), KERNEL_SPACE_UID,
                        KERNEL_SPACE_UID_SIZE);     /* for later use */
  exists = result == TPM_SUCCESS;
  if (RBTS.KERNEL_VERSIONS_exists && !exists) {
    RETURN_ON_FAILURE(SafeDefineSpace(KERNEL_VERSIONS_NV_INDEX,
                                      TPM_NV_PER_PPWRITE, KERNEL_SPACE_SIZE));
  }
  if (!RBTS.KERNEL_VERSIONS_exists && exists) {
    RETURN_ON_FAILURE(RollbackTest_RemoveSpace(KERNEL_VERSIONS_NV_INDEX));
  }
  return TPM_SUCCESS;
}