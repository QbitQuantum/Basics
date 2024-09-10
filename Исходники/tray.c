void tray_update(HWND hWnd, struct th_data *data) {
	struct tray_status *status = &data->status;
	NOTIFYICONDATA *niData = &data->niData;
	HICON oldIcon;
	unsigned int fg, bg, p, d;
	BOOL ret;
	DWORD err;

	if (!data->tray_ok) {
		tray_add(hWnd, data);

		if (!data->tray_ok)
			return;
	}

	odprintf("tray[update]: conn=%d msg=\"%s\" temperature_celsius=%f relative_humidity=%f dew_point=%f",
		status->conn, status->msg, status->temperature_celsius, status->relative_humidity, status->dew_point);

	fg = icon_syscolour(COLOR_BTNTEXT);
	bg = icon_syscolour(COLOR_3DFACE);

	switch (status->conn) {
	case NOT_CONNECTED:
		if (not_connected_width < ICON_WIDTH || not_connected_height < ICON_HEIGHT)
			icon_wipe(bg);

		icon_blit(0, 0, 0, fg, bg, 0, 0, not_connected_width, not_connected_height, not_connected_bits);

		if (status->msg[0] != 0)
			ret = snprintf(niData->szTip, sizeof(niData->szTip), "Not Connected: %s", status->msg);
		else
			ret = snprintf(niData->szTip, sizeof(niData->szTip), "Not Connected");
		if (ret < 0)
			niData->szTip[0] = 0;
		break;

	case CONNECTING:
		if (connecting_width < ICON_WIDTH || connecting_height < ICON_HEIGHT)
			icon_wipe(bg);

		icon_blit(0, 0, 0, fg, bg, 0, 0, connecting_width, connecting_height, connecting_bits);

		if (status->msg[0] != 0)
			ret = snprintf(niData->szTip, sizeof(niData->szTip), "Connecting to %s", status->msg);
		else
			ret = snprintf(niData->szTip, sizeof(niData->szTip), "Connecting");
		if (ret < 0)
			niData->szTip[0] = 0;
		break;

	case CONNECTED:
		if (isnan(status->temperature_celsius)) {
			icon_clear(0, 0, bg, 0, 0, ICON_WIDTH, digits_base_height);
			p = 0;

			icon_blit(0, 0, 0, fg, bg, p, 0, digit_dash_width, digit_dash_height, digit_dash_bits);
			p += digit_dash_width + 1;

			icon_blit(0, 0, 0, fg, bg, p, 0, digit_dash_width, digit_dash_height, digit_dash_bits);
			p += digit_dash_width + 1;

			icon_blit(0, 0, 0, fg, bg, p, 0, digit_dot_width, digit_dot_height, digit_dot_bits);
			p += digit_dot_width + 1;

			icon_blit(0, 0, 0, fg, bg, p, 0, digit_dash_width, digit_dash_height, digit_dash_bits);
		} else {
			unsigned int h_fg, h_bg, h_end, hue;
			int tc = lrint(status->temperature_celsius * 100.0);

			if (tc > 99999)
				tc = 99999;
			if (tc < -9999)
				tc = -9999;

			hue = tray_range_to_hue(MIN_TEMPC, MIN_TEMPC_WARN, status->temperature_celsius, MAX_TEMPC_WARN, MAX_TEMPC);
			h_end = tray_hue_to_width(hue);
			h_fg = tray_hue_to_fg_colour(hue);
			h_bg = tray_hue_to_bg_colour(hue);

			icon_clear(h_bg, h_end, bg, 0, 0, ICON_WIDTH, digits_base_height);

			if (tc >= 9995) {
				/* _NNN 100 to 999 */
				if (tc % 100 >= 50)
					tc += 100 - (tc % 100);
				p = digit_dot_width + 1;

				d = (tc/10000) % 10;
				icon_blit(h_fg, h_bg, h_end, fg, bg, p, 0, digits_width[d], digits_height[d], digits_bits[d]);
				p += digits_width[d] + 1;

				d = (tc/1000) % 10;
				icon_blit(h_fg, h_bg, h_end, fg, bg, p, 0, digits_width[d], digits_height[d], digits_bits[d]);
				p += digits_width[d] + 1;

				d = (tc/100) % 10;
				icon_blit(h_fg, h_bg, h_end, fg, bg, p, 0, digits_width[d], digits_height[d], digits_bits[d]);
			} else if (tc > 999) {
				/* NN.N 10.0 to 99.9 */
				if (tc % 10 >= 5)
					tc += 10 - (tc % 10);
				p = 0;

				d = (tc/1000) % 10;
				icon_blit(h_fg, h_bg, h_end, fg, bg, p, 0, digits_width[d], digits_height[d], digits_bits[d]);
				p += digits_width[d] + 1;

				d = (tc/100) % 10;
				icon_blit(h_fg, h_bg, h_end, fg, bg, p, 0, digits_width[d], digits_height[d], digits_bits[d]);
				p += digits_width[d] + 1;

				icon_blit(h_fg, h_bg, h_end, fg, bg, p, 0, digit_dot_width, digit_dot_height, digit_dot_bits);
				p += digit_dot_width + 1;

				d = (tc/10) % 10;
				icon_blit(h_fg, h_bg, h_end, fg, bg, p, 0, digits_width[d], digits_height[d], digits_bits[d]);
			} else if (tc >= 0) {
				/* N.NN 0.00 to 9.99 */
				p = 0;

				d = (tc/100) % 10;
				icon_blit(h_fg, h_bg, h_end, fg, bg, p, 0, digits_width[d], digits_height[d], digits_bits[d]);
				p += digits_width[d] + 1;

				icon_blit(h_fg, h_bg, h_end, fg, bg, p, 0, digit_dot_width, digit_dot_height, digit_dot_bits);
				p += digit_dot_width + 1;

				d = (tc/10) % 10;
				icon_blit(h_fg, h_bg, h_end, fg, bg, p, 0, digits_width[d], digits_height[d], digits_bits[d]);
				p += digits_width[d] + 1;

				d = tc % 10;
				icon_blit(h_fg, h_bg, h_end, fg, bg, p, 0, digits_width[d], digits_height[d], digits_bits[d]);
			} else if (tc > -995) { 
				/* -N.N -0.1 to -9.9 */
				if (abs(tc) % 10 >= 5)
					tc -= 10 - (abs(tc) % 10);
				p = 0;

				icon_blit(h_fg, h_bg, h_end, fg, bg, p, 0, digit_dash_width, digit_dash_height, digit_dash_bits);
				p += digit_dash_width + 1;

				d = abs(tc/100) % 10;
				icon_blit(h_fg, h_bg, h_end, fg, bg, p, 0, digits_width[d], digits_height[d], digits_bits[d]);
				p += digits_width[d] + 1;

				icon_blit(h_fg, h_bg, h_end, fg, bg, p, 0, digit_dot_width, digit_dot_height, digit_dot_bits);
				p += digit_dot_width + 1;

				d = abs(tc/10) % 10;
				icon_blit(h_fg, h_bg, h_end, fg, bg, p, 0, digits_width[d], digits_height[d], digits_bits[d]);
			} else /* if (tc >= -9999) */ {
				/* _-NN -10 to -99 */
				if (abs(tc) % 100 >= 50)
					tc -= 100 - (abs(tc) % 100);
				p = digit_dot_width + 1;

				icon_blit(h_fg, h_bg, h_end, fg, bg, p, 0, digit_dash_width, digit_dash_height, digit_dash_bits);
				p += digit_dash_width + 1;

				d = abs(tc/1000) % 10;
				icon_blit(h_fg, h_bg, h_end, fg, bg, p, 0, digits_width[d], digits_height[d], digits_bits[d]);
				p += digits_width[d] + 1;

				d = abs(tc/100) % 10;
				icon_blit(h_fg, h_bg, h_end, fg, bg, p, 0, digits_width[d], digits_height[d], digits_bits[d]);
			}
		}

		icon_clear(0, 0, bg, 0, ICON_HEIGHT/2 - (ICON_HEIGHT/2 - digits_base_height), ICON_WIDTH, (ICON_HEIGHT/2 - digits_base_height) * 2);

		if (isnan(status->relative_humidity)) {
			icon_clear(0, 0, bg, 0, ICON_HEIGHT - digits_base_height, ICON_WIDTH, digit_dash_height);
			p = 0;

			icon_blit(0, 0, 0, fg, bg, p, ICON_HEIGHT - digits_base_height, digit_dash_width, digit_dash_height, digit_dash_bits);
			p += digit_dash_width + 1;

			icon_blit(0, 0, 0, fg, bg, p, ICON_HEIGHT - digits_base_height, digit_dash_width, digit_dash_height, digit_dash_bits);
			p += digit_dash_width + 1;

			icon_blit(0, 0, 0, fg, bg, p, ICON_HEIGHT - digits_base_height, digit_dot_width, digit_dot_height, digit_dot_bits);
			p += digit_dot_width + 1;

			icon_blit(0, 0, 0, fg, bg, p, ICON_HEIGHT - digits_base_height, digit_dash_width, digit_dash_height, digit_dash_bits);
		} else {
			unsigned int h_fg, h_bg, h_end, hue;
			int rh = lrint(status->relative_humidity * 10.0);

			if (rh > 999)
				rh = 999;
			if (rh < 0)
				rh = 0;

			hue = tray_range_to_hue(MIN_DEWPC, MIN_DEWPC_WARN, status->dew_point, MAX_DEWPC_WARN, MAX_DEWPC);
			h_end = tray_hue_to_width(hue);
			h_fg = tray_hue_to_fg_colour(hue);
			h_bg = tray_hue_to_bg_colour(hue);

			icon_clear(h_bg, h_end, bg, 0, ICON_HEIGHT - digits_base_height, ICON_WIDTH, digits_base_height);

			/* NN.N 00.0 to 99.9 */
			p = 0;

			d = (rh/100) % 10;
			icon_blit(h_fg, h_bg, h_end, fg, bg, p, ICON_HEIGHT - digits_base_height, digits_width[d], digits_height[d], digits_bits[d]);
			p += digits_width[d] + 1;

			d = (rh/10) % 10;
			icon_blit(h_fg, h_bg, h_end, fg, bg, p, ICON_HEIGHT - digits_base_height, digits_width[d], digits_height[d], digits_bits[d]);
			p += digits_width[d] + 1;

			icon_blit(h_fg, h_bg, h_end, fg, bg, p, ICON_HEIGHT - digits_base_height, digit_dot_width, digit_dot_height, digit_dot_bits);
			p += digit_dot_width + 1;

			d = rh % 10;
			icon_blit(h_fg, h_bg, h_end, fg, bg, p, ICON_HEIGHT - digits_base_height, digits_width[d], digits_height[d], digits_bits[d]);
		}

		snprintf(niData->szTip, sizeof(niData->szTip), "Temperature: %.2fC, Relative Humidity: %.2f%%, Dew Point: %.2fC",
			status->temperature_celsius, status->relative_humidity, status->dew_point);
		break;

	default:
		return;
	}

	oldIcon = niData->hIcon;

	niData->uFlags &= ~NIF_ICON;
	niData->hIcon = icon_create();
	if (niData->hIcon != NULL)
		niData->uFlags |= NIF_ICON;

	SetLastError(0);
	ret = Shell_NotifyIcon(NIM_MODIFY, niData);
	err = GetLastError();
	odprintf("Shell_NotifyIcon[MODIFY]: %s (%ld)", ret == TRUE ? "TRUE" : "FALSE", err);
	if (ret != TRUE)
		tray_remove(hWnd, data);

	if (oldIcon != NULL)
		icon_destroy(niData->hIcon);
}