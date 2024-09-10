static void
close_output_file()
{
	if (rdef_err == B_OK || (flags & RDEF_MERGE_RESOURCES) != 0)
		rsrc.Sync();
	else
		entry.Remove();  // throw away output file

	file.Unset();
	entry.Unset();
}