/**
 * Handle fatal errors
 *
 * @v fmt	Error message format string
 * @v ...	Arguments
 */
void die ( const char *fmt, ... ) {
	EFI_BOOT_SERVICES *bs;
	EFI_RUNTIME_SERVICES *rs;
	va_list args;

	/* Print message */
	va_start ( args, fmt );
	vprintf ( fmt, args );
	va_end ( args );

	/* Reboot or exit as applicable */
	if ( efi_systab ) {

		/* Exit */
		bs = efi_systab->BootServices;
		bs->Exit ( efi_image_handle, EFI_LOAD_ERROR, 0, NULL );
		printf ( "Failed to exit\n" );
		rs = efi_systab->RuntimeServices;
		rs->ResetSystem ( EfiResetWarm, 0, 0, NULL );
		printf ( "Failed to reboot\n" );

	} else {

		/* Wait for keypress */
		printf ( "Press a key to reboot..." );
		getchar();
		printf ( "\n" );

		/* Reboot system */
		reboot();
	}

	/* Should be impossible to reach this */
	__builtin_unreachable();
}