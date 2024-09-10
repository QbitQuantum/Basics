static void appendaction(int imenu, const char* prompt, const char* command)
{
	Menuitem *item;
	item = append(imenu);
	item->type = MENU_ACTION;
	item->prompt = (char *)emalloc((unsigned)(strlen(prompt) + 1));
	Strcpy(item->prompt, prompt);
	item->command = (char *)emalloc((unsigned)(strlen(command) + 1));
	Strcpy(item->command, command);
}