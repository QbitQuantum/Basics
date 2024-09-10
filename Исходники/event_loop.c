/* Composes and draws suggestion box. */
static void
display_suggestion_box(const wchar_t input[])
{
	size_t prefix;

	/* Don't do this for ESC because it's prefix for other keys. */
	if(!should_display_suggestion_box() || wcscmp(input, L"\033") == 0)
	{
		return;
	}

	/* Fill completion list with suggestions of keys and marks. */
	vle_compl_reset();
	vle_keys_suggest(input, &process_suggestion, !(cfg.sug.flags & SF_KEYS),
				(cfg.sug.flags & SF_FOLDSUBKEYS));
	/* Completion grouping removes duplicates.  Because user-defined keys are
	 * reported first, this has an effect of leaving only them in the resulting
	 * list, which is correct as they have higher priority. */
	vle_compl_finish_group();

	/* Handle registers suggestions. */
	prefix = wcsspn(input, L"0123456789");
	if((cfg.sug.flags & SF_REGISTERS) &&
			input[prefix] == L'"' && input[prefix + 1U] == L'\0')
	{
		regs_sync_from_shared_memory();

		/* No vle_compl_finish_group() after this to prevent sorting and
		 * deduplication. */
		regs_suggest(&process_suggestion, cfg.sug.maxregfiles);
	}

	if(vle_compl_get_count() != 0)
	{
		draw_suggestion_box();
		suggestions_are_visible = 1;
	}
}