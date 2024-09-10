static void	parsing_options2(char **tab, t_env *rt, int i)
{
	if (!ft_strcmp(tab[0], "angle"))
		rt->object[i].angle = new_vector(ATOF(2), ATOF(3), ATOF(4));
	else if (!ft_strcmp(tab[0], "a"))
		rt->object[i].a = new_vector(ATOF(2), ATOF(3), ATOF(4));
	else if (!ft_strcmp(tab[0], "b"))
		rt->object[i].b = new_vector(ATOF(2), ATOF(3), ATOF(4));
	else if (!ft_strcmp(tab[0], "c"))
		rt->object[i].c = new_vector(ATOF(2), ATOF(3), ATOF(4));
	else if (!ft_strcmp(tab[0], "material"))
		parsing_material(rt, &rt->object[i].material, tab[2]);
	else if (!ft_strcmp(tab[0], "separation"))
		rt->object[i].separation = ATOF(2);
}