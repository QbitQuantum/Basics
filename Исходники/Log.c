NTSTATUS log_init( void )
{
	UNICODE_STRING name;
	OBJECT_ATTRIBUTES oa;
	IO_STATUS_BLOCK iosb;
	NTSTATUS r;

	pass_count = 0;
	fail_count = 0;

	/* open the event */
	name.Buffer = eventname;
	name.Length = sizeof eventname - 2;
	name.MaximumLength = name.Length;

	oa.Length = sizeof oa;
	oa.RootDirectory = NULL;
	oa.ObjectName = &name;
	oa.Attributes = OBJ_CASE_INSENSITIVE;
	oa.SecurityDescriptor = NULL;
	oa.SecurityQualityOfService = NULL;

	r = NtOpenEvent( &event, EVENT_ALL_ACCESS, &oa );
	if (r != STATUS_SUCCESS)
		return r;

	/* open the mailslot */
	name.Buffer = slotname;
	name.Length = sizeof slotname - 2;
	name.MaximumLength = name.Length;

	oa.Length = sizeof oa;
	oa.RootDirectory = NULL;
	oa.ObjectName = &name;
	oa.Attributes = OBJ_CASE_INSENSITIVE;
	oa.SecurityDescriptor = NULL;
	oa.SecurityQualityOfService = NULL;

	iosb.Status = 0;
	iosb.Information = 0;

	return NtOpenFile( &slot, GENERIC_WRITE, &oa, &iosb, FILE_SHARE_WRITE | FILE_SHARE_READ, 0 );
}