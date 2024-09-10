//
// Count the number of objects for a lightweight monitor. The hobj
// parameter is object that owns the monitor so this routine will
// count the number of times the same object was locked by frames
// in java_thread.
//
jint
JvmtiEnvBase::count_locked_objects(JavaThread *java_thread, Handle hobj) {
  jint ret = 0;
  if (!java_thread->has_last_Java_frame()) {
    return ret;  // no Java frames so no monitors
  }

  ResourceMark rm;
  HandleMark   hm;
  RegisterMap  reg_map(java_thread);

  for(javaVFrame *jvf=java_thread->last_java_vframe(&reg_map); jvf != NULL;
                                                 jvf = jvf->java_sender()) {
    GrowableArray<MonitorInfo*>* mons = jvf->monitors();
    if (!mons->is_empty()) {
      for (int i = 0; i < mons->length(); i++) {
        MonitorInfo *mi = mons->at(i);
        if (mi->owner_is_scalar_replaced()) continue;

        // see if owner of the monitor is our object
        if (mi->owner() != NULL && mi->owner() == hobj()) {
          ret++;
        }
      }
    }
  }
  return ret;
}