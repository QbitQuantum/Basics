MX_EXPORT mx_status_type
mxi_win32com_send_break( MX_RS232 *rs232 )
{
	static const char fname[] = "mxi_win32com_send_break()";

	MX_WIN32COM *win32com;
	BOOL win32_status;
	mx_status_type status;

	MX_DEBUG( 2,("%s invoked.",fname));

	status = mxi_win32com_get_pointers( rs232, &win32com, fname );

	if ( status.code != MXE_SUCCESS )
		return status;

	if ( win32com->handle == INVALID_HANDLE_VALUE ) {
		return mx_error( MXE_ILLEGAL_ARGUMENT, fname,
		"Win32 COM port device '%s' is not open.",
		rs232->record->name );
	}

	/* Turn the break signal on. */

	win32_status = SetCommBreak( win32com->handle );

	if ( win32_status == 0 ) {
		DWORD last_error_code;
		TCHAR message_buffer[MXU_ERROR_MESSAGE_LENGTH - 120];

		last_error_code = GetLastError();

		mx_win32_error_message( last_error_code,
			message_buffer, sizeof(message_buffer) );

		return mx_error( MXE_INTERFACE_IO_ERROR, fname,
		"Attempt to send a Break signal for '%s' failed.  "
			"Win32 error code = %ld, error message = '%s'",
			win32com->filename, last_error_code, message_buffer );
	}

	/* Leave the break signal on for about 0.5 seconds. */

	Sleep(500);

	/* Turn the break signal off. */
		
	win32_status = ClearCommBreak( win32com->handle );

	if ( win32_status == 0 ) {
		DWORD last_error_code;
		TCHAR message_buffer[MXU_ERROR_MESSAGE_LENGTH - 120];

		last_error_code = GetLastError();

		mx_win32_error_message( last_error_code,
			message_buffer, sizeof(message_buffer) );

		return mx_error( MXE_INTERFACE_IO_ERROR, fname,
		"Attempt to stop a Break signal for '%s' failed.  "
			"Win32 error code = %ld, error message = '%s'",
			win32com->filename, last_error_code, message_buffer );
	}

	return MX_SUCCESSFUL_RESULT;
}