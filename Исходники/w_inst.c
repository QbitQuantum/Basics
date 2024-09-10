/* Remove installed service from servicecontrolmanager */
void
wsvc_remove(FILE* out)
{
        SC_HANDLE scm;
        SC_HANDLE sv;
        if(out) fprintf(out, "removing unbound service\n");
        scm = OpenSCManager(NULL, NULL, (int)SC_MANAGER_ALL_ACCESS);
        if(!scm) fatal_win(out, "could not OpenSCManager");
        sv = OpenService(scm, SERVICE_NAME, DELETE);
        if(!sv) {
                CloseServiceHandle(scm);
                fatal_win(out, "could not OpenService");
        }
        if(!DeleteService(sv)) {
		CloseServiceHandle(sv);
		CloseServiceHandle(scm);
                fatal_win(out, "could not DeleteService");
        }
        CloseServiceHandle(sv);
        CloseServiceHandle(scm);
	event_reg_remove(out);
        if(out) fprintf(out, "unbound service removed\n");
}