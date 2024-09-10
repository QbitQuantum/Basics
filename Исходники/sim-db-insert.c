/**
 * sim_db_insert_host_service:
 *
 * Insert 'host service' in @databse
 */
void
sim_db_insert_host_service (SimDatabase   *database,
                            SimInet       *inet,
                            gchar         *date,
                            gint           port,
                            gint           protocol,
                            SimInet       *sensor,
                            gchar         *interface,
                            gchar         *service,
                            gchar         *application,
                            SimUuid       *context_id)
{
    gchar           *query;
    gint             plugin_id;
    struct servent  *temp_serv  = NULL;
    struct protoent *temp_proto = NULL;

    g_return_if_fail (SIM_IS_DATABASE (database));
    g_return_if_fail (SIM_IS_INET (inet));
    g_return_if_fail (date);
    g_return_if_fail (port >= 0); /* Needed for ints */
    g_return_if_fail (protocol >= 0);
    g_return_if_fail (sensor);
    g_return_if_fail (service);
    g_return_if_fail (application);


    temp_proto = getprotobynumber (protocol);
    if (temp_proto->p_name == NULL)
        return; /* Since we don't know the proto we wont insert a service without a protocol */

    temp_serv = getservbyport (port, temp_proto->p_name);

    query = g_strdup_printf ("INSERT INTO host_services "
                             "(id, date, port, protocol, service, service_type, version, origin, sensor, interface, ctx) "
                             "SELECT id, '%s', %u, %u, '%s', '%s', '%s', 0, %s, '%s', %s "
                             "FROM host WHERE ip = %s and ctx = %s LIMIT 1",
                             date,
                             port,
                             protocol,
                             (temp_serv != NULL) ? temp_serv->s_name : "unknown",
                             service,
                             application,
                             sim_inet_get_db_string (sensor),
                             interface,
                             sim_uuid_get_db_string (context_id),
                             sim_inet_get_db_string (inet),
                             sim_uuid_get_db_string (context_id));

    sim_db_execute_query (database, query);

    g_free (query);

    plugin_id = SIM_PLUGIN_SERVICE;

    sim_db_insert_host_plugin_sid (database, inet, plugin_id, port, context_id);
}