void Sys_DebugVPrintf( const char *fmt, va_list arg ) {
	tty_Hide();
	vprintf( fmt, arg );
	tty_Show();
}