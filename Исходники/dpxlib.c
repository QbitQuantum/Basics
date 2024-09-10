static void
dumpDpxOriginationInfo(DpxOriginationInformation* originInfo) {
	d_printf("\n--Origination Information--\n");
	d_printf("X offset %ld\n", (intptr_t)ntohl(originInfo->x_offset));
	d_printf("Y offset %ld\n", (intptr_t)ntohl(originInfo->y_offset));
	d_printf("X centre %f\n", ntohf(originInfo->x_centre));
	d_printf("Y centre %f\n", ntohf(originInfo->y_centre));
	d_printf("Original X %ld\n", (intptr_t)ntohl(originInfo->x_original_size));
	d_printf("Original Y %ld\n", (intptr_t)ntohl(originInfo->y_original_size));
	d_printf("File name \"%s\"\n", originInfo->file_name);
	d_printf("Creation time \"%s\"\n", originInfo->creation_time);
	d_printf("Input device \"%s\"\n", originInfo->input_device);
	d_printf("Serial number \"%s\"\n", originInfo->input_serial_number);
}