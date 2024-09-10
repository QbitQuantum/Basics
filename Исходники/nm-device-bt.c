static gboolean
complete_connection (NMDevice *device,
                     NMConnection *connection,
                     const char *specific_object,
                     const GSList *existing_connections,
                     GError **error)
{
	NMDeviceBtPrivate *priv = NM_DEVICE_BT_GET_PRIVATE (device);
	NMSettingBluetooth *s_bt;
	const GByteArray *setting_bdaddr;
	struct ether_addr *devaddr = ether_aton (priv->bdaddr);
	const char *ctype;
	gboolean is_dun = FALSE, is_pan = FALSE;
	NMSettingGsm *s_gsm;
	NMSettingCdma *s_cdma;
	NMSettingSerial *s_serial;
	NMSettingPPP *s_ppp;
	const char *format = NULL, *preferred = NULL;

	s_gsm = nm_connection_get_setting_gsm (connection);
	s_cdma = nm_connection_get_setting_cdma (connection);
	s_serial = nm_connection_get_setting_serial (connection);
	s_ppp = nm_connection_get_setting_ppp (connection);

	s_bt = nm_connection_get_setting_bluetooth (connection);
	if (!s_bt) {
		s_bt = (NMSettingBluetooth *) nm_setting_bluetooth_new ();
		nm_connection_add_setting (connection, NM_SETTING (s_bt));
	}

	ctype = nm_setting_bluetooth_get_connection_type (s_bt);
	if (ctype) {
		if (!strcmp (ctype, NM_SETTING_BLUETOOTH_TYPE_DUN))
			is_dun = TRUE;
		else if (!strcmp (ctype, NM_SETTING_BLUETOOTH_TYPE_PANU))
			is_pan = TRUE;
	} else {
		if (s_gsm || s_cdma)
			is_dun = TRUE;
		else if (priv->capabilities & NM_BT_CAPABILITY_NAP)
			is_pan = TRUE;
	}

	if (is_pan) {
		/* Make sure the device supports PAN */
		if (!(priv->capabilities & NM_BT_CAPABILITY_NAP)) {
			g_set_error_literal (error,
			                     NM_SETTING_BLUETOOTH_ERROR,
			                     NM_SETTING_BLUETOOTH_ERROR_INVALID_PROPERTY,
			                     "PAN required but Bluetooth device does not support NAP");
			return FALSE;
		}

		/* PAN can't use any DUN-related settings */
		if (s_gsm || s_cdma || s_serial || s_ppp) {
			g_set_error_literal (error,
			                     NM_SETTING_BLUETOOTH_ERROR,
			                     NM_SETTING_BLUETOOTH_ERROR_INVALID_PROPERTY,
			                     "PAN incompatible with GSM, CDMA, or serial settings");
			return FALSE;
		}

		g_object_set (G_OBJECT (s_bt),
		              NM_SETTING_BLUETOOTH_TYPE, NM_SETTING_BLUETOOTH_TYPE_PANU,
		              NULL);

		format = _("PAN connection %d");
	} else if (is_dun) {
		/* Make sure the device supports PAN */
		if (!(priv->capabilities & NM_BT_CAPABILITY_DUN)) {
			g_set_error_literal (error,
			                     NM_SETTING_BLUETOOTH_ERROR,
			                     NM_SETTING_BLUETOOTH_ERROR_INVALID_PROPERTY,
			                     "DUN required but Bluetooth device does not support DUN");
			return FALSE;
		}

		/* Need at least a GSM or a CDMA setting */
		if (!s_gsm && !s_cdma) {
			g_set_error_literal (error,
			                     NM_SETTING_BLUETOOTH_ERROR,
			                     NM_SETTING_BLUETOOTH_ERROR_INVALID_PROPERTY,
			                     "Setting requires DUN but no GSM or CDMA setting is present");
			return FALSE;
		}

		g_object_set (G_OBJECT (s_bt),
		              NM_SETTING_BLUETOOTH_TYPE, NM_SETTING_BLUETOOTH_TYPE_DUN,
		              NULL);

		if (s_gsm) {
			format = _("GSM connection %d");
			if (!nm_setting_gsm_get_number (s_gsm))
				g_object_set (G_OBJECT (s_gsm), NM_SETTING_GSM_NUMBER, "*99#", NULL);
		} else if (s_cdma) {
			format = _("CDMA connection %d");
			if (!nm_setting_cdma_get_number (s_cdma))
				g_object_set (G_OBJECT (s_cdma), NM_SETTING_GSM_NUMBER, "#777", NULL);
		} else
			format = _("DUN connection %d");
	} else {
		g_set_error_literal (error,
		                     NM_SETTING_BLUETOOTH_ERROR,
		                     NM_SETTING_BLUETOOTH_ERROR_INVALID_PROPERTY,
		                     "Unknown/unhandled Bluetooth connection type");
		return FALSE;
	}

	nm_utils_complete_generic (connection,
	                           NM_SETTING_BLUETOOTH_SETTING_NAME,
	                           existing_connections,
	                           format,
	                           preferred,
	                           is_dun ? FALSE : TRUE); /* No IPv6 yet for DUN */

	setting_bdaddr = nm_setting_bluetooth_get_bdaddr (s_bt);
	if (setting_bdaddr) {
		/* Make sure the setting BT Address (if any) matches the device's */
		if (memcmp (setting_bdaddr->data, devaddr->ether_addr_octet, ETH_ALEN)) {
			g_set_error_literal (error,
			                     NM_SETTING_BLUETOOTH_ERROR,
			                     NM_SETTING_BLUETOOTH_ERROR_INVALID_PROPERTY,
			                     NM_SETTING_BLUETOOTH_BDADDR);
			return FALSE;
		}
	} else {
		GByteArray *bdaddr;
		const guint8 null_mac[ETH_ALEN] = { 0, 0, 0, 0, 0, 0 };

		/* Lock the connection to this device by default */
		if (memcmp (devaddr->ether_addr_octet, null_mac, ETH_ALEN)) {
			bdaddr = g_byte_array_sized_new (ETH_ALEN);
			g_byte_array_append (bdaddr, devaddr->ether_addr_octet, ETH_ALEN);
			g_object_set (G_OBJECT (s_bt), NM_SETTING_BLUETOOTH_BDADDR, bdaddr, NULL);
			g_byte_array_free (bdaddr, TRUE);
		}
	}

	return TRUE;
}