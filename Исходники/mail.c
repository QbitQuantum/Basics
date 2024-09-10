/*
 * char *read_delete(long #1)
 * #1 - The id number of the person we're checking mail for.
 * Returns the message text of the mail received.
 *
 * Retrieves one messsage for a player. The mail is then discarded from
 * the file and the mail index.
 */
char *
read_delete (long recipient)
{
	header_block_type header;
	data_block_type data;
	mail_index_type *mail_pointer, *prev_mail;
	position_list_type *position_pointer;
	long mail_address, following_block;
	char *message, *tmstr, buf[200];
	char *from, *to;
	size_t string_size;

	if (recipient < 0)
	{
		log ("SYSERR: Mail system -- non-fatal error #6. (recipient: %ld)",
			 recipient);
		return (NULL);
	}
	if (!(mail_pointer = find_char_in_index (recipient)))
	{
		log
			("SYSERR: Mail system -- post office spec_proc error?  Error #7. (invalid character in index)");
		return (NULL);
	}
	if (!(position_pointer = mail_pointer->list_start))
	{
		log
			("SYSERR: Mail system -- non-fatal error #8. (invalid position pointer %p)",
			 position_pointer);
		return (NULL);
	}
	if (!(position_pointer->next))
	{							/* just 1 entry in list. */
		mail_address = position_pointer->position;
		free (position_pointer);

		/* now free up the actual name entry */
		if (mail_index == mail_pointer)
		{						/* name is 1st in list */
			mail_index = mail_pointer->next;
			free (mail_pointer);
		}
		else
		{
			/* find entry before the one we're going to del */
			for (prev_mail = mail_index;
				 prev_mail->next != mail_pointer;
				 prev_mail = prev_mail->next);
			prev_mail->next = mail_pointer->next;
			free (mail_pointer);
		}
	}
	else
	{
		/* move to next-to-last record */
		while (position_pointer->next->next)
			position_pointer = position_pointer->next;
		mail_address = position_pointer->next->position;
		free (position_pointer->next);
		position_pointer->next = NULL;
	}

	/* ok, now lets do some readin'! */
	read_from_file (&header, BLOCK_SIZE, mail_address);

	if (header.block_type != HEADER_BLOCK)
	{
		log ("SYSERR: Oh dear. (Header block %ld != %d)", header.block_type,
			 HEADER_BLOCK);
		no_mail = TRUE;
		log
			("SYSERR: Mail system disabled!  -- Error #9. (Invalid header block.)");
		return (NULL);
	}
	tmstr = asctime (localtime (&header.header_data.mail_time));
	*(tmstr + strlen (tmstr) - 1) = '\0';

	from = get_name_by_id (header.header_data.from);
	to = get_name_by_id (recipient);

	sprintf (buf, " ---==* McLandia Email Service *==--- \r\n"
			 "Date: %s\r\n"
			 "  To: %s\r\n"
			 "From: %s\r\n\r\n", tmstr, to ? to : "Unknown",
			 from ? from : "Unknown");

	string_size = (sizeof (char) * (strlen (buf) + strlen (header.txt) + 1));
	CREATE (message, char, string_size);
	strcpy (message, buf);
	strcat (message, header.txt);
	message[string_size - 1] = '\0';
	following_block = header.header_data.next_block;

	/* mark the block as deleted */
	header.block_type = DELETED_BLOCK;
	write_to_file (&header, BLOCK_SIZE, mail_address);
	push_free_list (mail_address);

	while (following_block != LAST_BLOCK)
	{
		read_from_file (&data, BLOCK_SIZE, following_block);

		string_size =
			(sizeof (char) * (strlen (message) + strlen (data.txt) + 1));
		RECREATE (message, char, string_size);
		strcat (message, data.txt);
		message[string_size - 1] = '\0';
		mail_address = following_block;
		following_block = data.block_type;
		data.block_type = DELETED_BLOCK;
		write_to_file (&data, BLOCK_SIZE, mail_address);
		push_free_list (mail_address);
	}

	return (message);
}