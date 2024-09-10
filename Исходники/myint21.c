void *install_int21_hook(void)
// Rueckgabe: ptr to allocated realmode mem
{
  if ( GetLogDpmiInfo() )
    LogLine("- Now installing rm hook\n");

  //--- allocatore low memory for the new int21 handler ---
  rm21ptr = (struct rmcode *) dpmi_real_malloc(2048, &Hook21Sel);

  if (rm21ptr != NULL) {

    //--- lock this low memory region ---
    if (!dpmi_lock_region(rm21ptr, 2048)) {  // locking failed?
      dpmi_real_free(Hook21Sel);
      return NULL;
    }

    OrgRmInt21 = ahf_dpmi_get_rmint(0x21);   // get the org int21 vector

    //--- now patch the raw code of my new handler ---
    memcpy(rm21ptr, &rm21code, sizeof(rm21code));
    *(unsigned long*)(rm21ptr->oldintofs) = OrgRmInt21;
    *(unsigned long*)(rm21ptr->LammCallAdr) = FP_OFF(RcvGP2Call);

    //--- now set my new handler ---
    _disable();
    ahf_dpmi_set_rmint(0x21, ((unsigned long)DPMI_real_segment(rm21ptr) << 16) + DPMI_real_offset(rm21ptr));
    _enable();

    //--- make sure it's getting restored at exit ---
    atexit( remove_int21_hook );

  }

  return rm21ptr;

} // install_int21_hook()