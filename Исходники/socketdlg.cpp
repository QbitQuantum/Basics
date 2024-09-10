/*
============================================================================
This routine applies the current settings in the dialog box and calls the
remote API functions to setup and teardown the socket interface.  It is
called by the OK button also.
============================================================================
*/
static void cb_sockdlg_apply(Fl_Widget* w, void*)
{
	int		port_num = 0, listen_port;
	int		telnet;
	int		enabled;

	// ==============================================
	// Get Port Number & telnet flag
	// ==============================================
	if (sockdlg_ctrl.pPortNumber->value() != NULL)
		port_num = atoi(sockdlg_ctrl.pPortNumber->value());
	telnet = sockdlg_ctrl.pTelnet->value();
	enabled = sockdlg_ctrl.pEnable->value();

	// Test if the socket is enabled but the port is invalid
	if (enabled && ((port_num <= 0) || (port_num >= 65536)))
	{
		fl_alert("Please provide a port number between 1 and 65535");
		return;
	}

	// Get the remote socket status
	listen_port = get_remote_listen_port();

	// Test if the socket is enabled and the user want's it disabled
	if (!enabled)
	{
		// Check if the socket is currently active and shutdown if it is
		if (listen_port != 0)
			deinit_remote();
	}

	// Test if we are enabling the socket for a different port number
	if (enabled && listen_port && (listen_port != port_num))
		deinit_remote();

	// Set the new port parameters
	set_remote_telnet(telnet);
	if (enabled)
		set_remote_port(port_num);
	else
		set_remote_port(0);
	enable_remote(enabled);

	// Update preferences
	virtualt_prefs.set("SocketPort", port_num);
	virtualt_prefs.set("SocketTelnetMode", telnet);
	virtualt_prefs.set("SocketEnabled", enabled);

	// Now enable the socket if the socket number is different
	if (enabled && (listen_port != port_num))
	{
		init_remote();
	}
	
	// If the apply button was pressed, then wait a bit for the port
	// status to change in the remote thread, then update the 
	// port status
	if (w == sockdlg_ctrl.pApply)
	{
		SLEEP(500);
		update_port_status();
	}
}