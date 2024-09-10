/** Any pulses received on the Looper's IPC port are
 * passed to this virtual method. 
 *
 * \warning Do not delete the Pulse parameter that you are given. It does 
 * 		    not belong to you either.
 *
 * \param pulse A pointer to the received Pulse. 
 */
void Looper::PulseReceived( Pulse* pulse )
{
	switch ((*pulse)[0])
	{
		case QUIT_REQUESTED:
			QuitRequested();
			Terminate();
			break;
	}
}