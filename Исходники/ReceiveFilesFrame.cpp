/** Receive the size of file and devolve your respective string in bytes, Kbytes, MBytes or GBytes.
* @param[in] size. File Size.
* @param[out] label. String containing the size in format described above.
* Private method.
*/
void ReceiveFilesFrame::SizeToSizeLabel(unsigned long size, wxString &label)
{
	// show in GBytes
	if((size/1073741824) > 0)
	{
		label.Printf(wxT("%d.%d GB"), size/1073741824, ((size*100)/1073741824)%100);
		return;
	}

	// show in MBytes
	if((size/1048576) > 0)
	{
		label.Printf(wxT("%d.%d MB"), size/1048576, ((size*100)/1048576)%100);
		return;
	}

	// show in KBytes
	if((size/1024) > 0)
	{
		label.Printf(wxT("%d.%d kB"), size/1024, ((size*10)/1024)%10);
		return;
	}

	// show in bytes
	label.Printf(wxT("%d Bytes"), size);
	return;
}