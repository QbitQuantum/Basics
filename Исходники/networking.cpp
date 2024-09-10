//////////////////////////////////////////////////////////////////////////////
///  private SSHExecSyncCommand
///  Passes the command off to PlinkConnect after appending a boolean test to
///     know if the command completely successfully.
///
///  @param  command wxString   command to execute
///  @param  output  wxString & output from the command.
///
///  @return bool    Whether the call succeeded or not.
///
///  @author David Czechowski @date 04-22-2004
//////////////////////////////////////////////////////////////////////////////
//Private:
bool Networking::SSHExecSyncCommand(wxString command, wxString &output) {
	command += " && echo Su_CC_ess-CMD";

	output = m_plinks->executeSyncCommand(command);

	int tokenPos = output.Find("Su_CC_ess-CMD");
	if(tokenPos != -1) {
		output.Remove(tokenPos);
		return true;
	}
	// else
		return false;
}