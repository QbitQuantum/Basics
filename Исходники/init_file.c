int add_init_section(InitFile *inif, InitSection *inis)
{
    int i;
    InitSection *oinis;
    if ((i = find_init_section(inif, inis->section_name)) >= 0) {
	oinis = inif->sections[i];
	inif->sections[i] = inis;
	free_init_section(oinis);
	return INIT_FILE_PRESENT;
    } 
    if (inif->num_sections == inif->size_sections) {
	inif->size_sections += 10;
	inif->sections = REALLOC(inif->sections, 
				 sizeof(InitSection *) * inif->size_sections);
    }
    inif->sections[inif->num_sections] = inis;
    ++(inif->num_sections);
    return INIT_FILE_NOT_PRESENT;
}