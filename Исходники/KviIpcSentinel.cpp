static void kvi_ipcLoadAtoms()
{
	if(g_bIpcAtomsLoaded)
		return;
	g_bIpcAtomsLoaded = true;
	g_uLocalInstanceId = (kvi_u64_t)::getpid();
	kvi_sentinel_id.sprintf("pane tonno e mistero - %d", getuid());
	kvi_atom_ipc_sentinel_window = XInternAtom(kvi_ipc_get_xdisplay(), "XA_KVI4_IPC_SENTINEL_WINDOW", False);
	kvi_atom_ipc_remote_command = XInternAtom(kvi_ipc_get_xdisplay(), "XA_KVI4_IPC_REMOTE_COMMAND", False);
	kvi_atom_ipc_remote_message = XInternAtom(kvi_ipc_get_xdisplay(), "XA_KVI4_IPC_REMOTE_MESSAGE", False);
}