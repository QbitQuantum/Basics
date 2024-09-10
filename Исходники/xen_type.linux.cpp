bool
VirshType::findCkptConfigAndSuspendFile(MyString &vmconfig, MyString &suspendfile)
{
	if( m_transfer_intermediate_files.isEmpty() ) {
		return false;
	}

	vmconfig = "";
	suspendfile = "";

	MyString tmpconfig;
	MyString tmpsuspendfile;

	if( filelist_contains_file( XEN_CONFIG_FILE_NAME,
				&m_transfer_intermediate_files, true) ) {
		// There is a vm config file for checkpointed files
		tmpconfig.formatstr("%s%c%s",m_workingpath.Value(),
				DIR_DELIM_CHAR, XEN_CONFIG_FILE_NAME);
	}

	MyString tmp_name;
	makeNameofSuspendfile(tmp_name);

	if( filelist_contains_file(tmp_name.Value(),
				&m_transfer_intermediate_files, true) ) {
		// There is a suspend file that was created during vacate
		tmpsuspendfile = tmp_name;
		if( check_vm_read_access_file(tmpsuspendfile.Value(), true) == false) {
			return false;
		}
	}

	if( (tmpconfig.Length() > 0) &&
			(tmpsuspendfile.Length() > 0 )) {
		// check if the timestamp of suspend file is same to
		// that of writable disk files
		// If timestamp differs between suspend file and writable disk file,
		// it means that there was a crash.
		// So we need to restart this VM job from the beginning.
		if( checkCkptSuspendFile(tmpsuspendfile.Value()) ) {
			vmconfig = tmpconfig;
			suspendfile = tmpsuspendfile;
			return true;
		}
	}
	return false;
}