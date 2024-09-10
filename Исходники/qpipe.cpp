// returns the number of keypress events in the console input queue,
//   or -1 if there is an error (don't forget this!!)
static int pipe_read_avail_console(Q_PIPE_ID pipe)
{
	DWORD count, i;
	INPUT_RECORD *rec;
	int n, icount, total;

	// how many events are there?
	if(!GetNumberOfConsoleInputEvents(pipe, &count))
		return -1;

	// peek them all
	rec = (INPUT_RECORD *)malloc(count * sizeof(INPUT_RECORD));
	BOOL ret;
#if QT_VERSION >= 0x050000
	ret = PeekConsoleInputW(pipe, rec, count, &i);
#else
	QT_WA(
		ret = PeekConsoleInputW(pipe, rec, count, &i);
	,