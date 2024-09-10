/**
 * Callback for solver to notify about assignment changes
 *
 * @param cls NULL
 * @param address the address with changes
 */
static void
bandwidth_changed_cb (void *cls,
		      struct ATS_Address *address)
{
  long long diff_out;
  long long diff_in;

  GNUNET_log (GNUNET_ERROR_TYPE_DEBUG,
              "Bandwidth assignment changed for peer %s to %u/%u\n",
              GNUNET_i2s (&address->peer),
              (unsigned int) address->assigned_bw_in,
              (unsigned int) address->assigned_bw_out);
  GAS_reservations_set_bandwidth (&address->peer,
                                  GNUNET_BANDWIDTH_value_init (address->assigned_bw_in));
  /* Notify performance clients about changes to address */
  GAS_performance_notify_all_clients (&address->peer,
				      address->plugin,
				      address->addr,
				      address->addr_len,
				      address->active,
				      &address->properties,
                                      address->local_address_info,
				      GNUNET_BANDWIDTH_value_init (address->assigned_bw_out),
				      GNUNET_BANDWIDTH_value_init (address->assigned_bw_in));

  if ( (0 == address->assigned_bw_in) &&
       (0 == address->assigned_bw_out) )
  {
    GNUNET_log (GNUNET_ERROR_TYPE_DEBUG,
               "Telling transport to disconnect peer `%s'\n",
                GNUNET_i2s (&address->peer));

    /* Notify scheduling clients about suggestion */
    GAS_scheduling_transmit_address_suggestion (&address->peer,
                                                address->session_id,
                                                GNUNET_BANDWIDTH_ZERO,
                                                GNUNET_BANDWIDTH_ZERO);
    return;
  }

  /* Do bandwidth stability check */
  diff_out = llabs ((long long) address->assigned_bw_out -
                    (long long) address->last_notified_bw_out);
  diff_in = llabs ((long long) address->assigned_bw_in -
                   (long long) address->last_notified_bw_in);
  if ( (diff_out < htonl (GNUNET_CONSTANTS_DEFAULT_BW_IN_OUT.value__)) &&
       (diff_in < htonl (GNUNET_CONSTANTS_DEFAULT_BW_IN_OUT.value__)) )
  {
    GNUNET_log (GNUNET_ERROR_TYPE_DEBUG,
                "Bandwidth change too small, not notifying client\n");
    return;
  }

  GNUNET_log (GNUNET_ERROR_TYPE_DEBUG,
              "Sending bandwidth update for peer `%s': %u/%u\n",
              GNUNET_i2s (&address->peer),
              address->assigned_bw_out,
              address->assigned_bw_out);

  /* *Notify scheduling clients about suggestion */
  GAS_scheduling_transmit_address_suggestion (&address->peer,
                                              address->session_id,
                                              GNUNET_BANDWIDTH_value_init (address->assigned_bw_out),
                                              GNUNET_BANDWIDTH_value_init (address->assigned_bw_in));

  address->last_notified_bw_out = address->assigned_bw_out;
  address->last_notified_bw_in = address->assigned_bw_in;
}