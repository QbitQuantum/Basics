void XDG_FreeParsedFile(XDG_PARSED_FILE *parsed)
{
    PARSED_GROUP *group, *next;
    if (!parsed)
        return;
    free_entries_list(parsed->head_comments);
    
    group = parsed->groups;
    while (group)
    {
        next = group->next;
        free_entries_list(group->entries);
        SHFree(group);
        group = next;
    }
    SHFree(parsed->contents);
    SHFree(parsed);
}