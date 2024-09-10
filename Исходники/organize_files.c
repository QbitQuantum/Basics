void	delete_files(t_group *grp)
{
	t_dir	*file;
	t_dir	*trash;

	file = grp->first_dir;
	while (file != NULL)
	{
		REMOVE(&file->name);
		REMOVE(&file->rights);
		REMOVE(&file->last_stat);
		REMOVE(&file->last_access);
		REMOVE(&file->last_modif);
		REMOVE(&file->uid);
		REMOVE(&file->gid);
		file->slink = 0;
		file->size = 0;
		file->size_min = -1;
		file->blocks = 0;
		trash = file;
		ft_memdel((void *)trash);
		file = file->next;
	}
	grp->first_dir = NULL;
	grp->curr_first_dir = NULL;
}