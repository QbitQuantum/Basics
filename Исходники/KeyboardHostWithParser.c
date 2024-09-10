/** Processes a read HID report from an attached keyboard, extracting out elements via the HID parser results
 *  as required and prints pressed characters to the serial port. Each time a key is typed, a board LED is toggled.
 *
 *  \param[in] KeyboardReport  Pointer to a HID report from an attached keyboard device
 */
void ProcessKeyboardReport(uint8_t* KeyboardReport)
{
	/* Check each HID report item in turn, looking for keyboard scan code reports */
	for (uint8_t ReportNumber = 0; ReportNumber < HIDReportInfo.TotalReportItems; ReportNumber++)
	{
		/* Create a temporary item pointer to the next report item */
		HID_ReportItem_t* ReportItem = &HIDReportInfo.ReportItems[ReportNumber];

		/* Check if the current report item is a keyboard scan-code */
		if ((ReportItem->Attributes.Usage.Page      == USAGE_PAGE_KEYBOARD) &&
			(ReportItem->Attributes.BitSize         == 8)                   &&
			(ReportItem->Attributes.Logical.Maximum > 1)                    &&
			(ReportItem->ItemType                   == HID_REPORT_ITEM_In))
		{
			/* Retrieve the keyboard scan-code from the report data retrieved from the device */
			bool FoundData = USB_GetHIDReportItemInfo(KeyboardReport, ReportItem);

			/* For multi-report devices - if the requested data was not in the issued report, continue */
			if (!(FoundData))
			  continue;

			/* Key code is an unsigned char in length, cast to the appropriate type */
			uint8_t KeyCode = (uint8_t)ReportItem->Value;

			/* If scan-code is non-zero, a key is being pressed */
			if (KeyCode)
			{
				/* Toggle status LED to indicate keypress */
				LEDs_ToggleLEDs(LEDS_LED2);

				char PressedKey = 0;

				/* Retrieve pressed key character if alphanumeric */
				if ((KeyCode >= HID_KEYBOARD_SC_A) && (KeyCode <= HID_KEYBOARD_SC_Z))
				{
					PressedKey = (KeyCode - HID_KEYBOARD_SC_A) + 'A';
				}
				else if ((KeyCode >= HID_KEYBOARD_SC_1_AND_EXCLAMATION) &
						 (KeyCode  < HID_KEYBOARD_SC_0_AND_CLOSING_PARENTHESIS))
				{
					PressedKey = (KeyCode - HID_KEYBOARD_SC_1_AND_EXCLAMATION) + '1';
				}
				else if (KeyCode == HID_KEYBOARD_SC_0_AND_CLOSING_PARENTHESIS)
				{
					PressedKey = '0';
				}
				else if (KeyCode == HID_KEYBOARD_SC_SPACE)
				{
					PressedKey = ' ';
				}
				else if (KeyCode == HID_KEYBOARD_SC_ENTER)
				{
					PressedKey = '\n';
				}

				/* Print the pressed key character out through the serial port if valid */
				if (PressedKey)
				  putchar(PressedKey);
			}

			/* Once a scan-code is found, stop scanning through the report items */
			break;
		}
	}
}