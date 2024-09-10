/**
 * gnome_vfs_address_get_ipv4:
 * @address: A #GnomeVFSAddress.
 * 
 * Returns: The associated IPv4 address in network byte order.
 *
 * Note that you should avoid using this function because newly written
 * code should be protocol independent.
 *
 * Since: 2.8
 **/
guint32
gnome_vfs_address_get_ipv4 (GnomeVFSAddress *address)
{
	g_return_val_if_fail (address != NULL, 0);
	g_return_val_if_fail (address->sa != NULL, 0);

	if (address->sa->sa_family != AF_INET)
		return 0;

	return (guint32) SIN (address->sa)->sin_addr.s_addr;
}