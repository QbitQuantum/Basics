/* remove all pollfunctions and close socket */
static void udpreceive_tilde_closesocket(t_udpreceive_tilde* x)
{
    sys_rmpollfn(x->x_socket);
    outlet_float(x->x_outlet1, 0);
    CLOSESOCKET(x->x_socket);
    x->x_socket = -1;
}