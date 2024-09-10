/**
 * Close a serial port.
 *
 * @param hPort handle to a native serial port
 *
 * @exception  IOException  if an I/O error occurs
 */
KNIEXPORT KNI_RETURNTYPE_VOID
    Java_com_sun_midp_io_j2me_comm_Protocol_native_1close() {

    int hPort = (int)KNI_GetParameterAsInt(1);

    closePort(hPort);
    KNI_ReturnVoid();
}