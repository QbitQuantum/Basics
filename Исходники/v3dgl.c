/*
 *	Sets the given gl resources structure's gl interpritation
 *	legend to the given glinterp.
 *
 *	Returns non-zero on error.
 */
int V3DGLResourceSetInterpritation(
	v3d_glresource_struct *glres,
	const v3d_glinterprite_struct *glinterp
)
{
	unsigned int flags;
	v3d_glinterprite_struct *t_glinterp;


	if((glres == NULL) || (glinterp == NULL))
	    return(-1);

	flags = glinterp->flags;

	/* Get target gl interpritation structure from the given gl
	 * resource structure.
	 */
	t_glinterp = glres->glinterprite;
	if(t_glinterp == NULL)
	    return(-1);

	if(flags & V3D_GLFLAG_COORDINATE_AXIS)
	    t_glinterp->coordinate_axis = glinterp->coordinate_axis;

	if(flags & V3D_GLFLAG_TEXTURE_KEEP)
	    t_glinterp->texture_keep = glinterp->texture_keep;

	if(flags & V3D_GLFLAG_ALLOW_TRANSLATIONS)
	    t_glinterp->allow_translations = glinterp->allow_translations;

	if(flags & V3D_GLFLAG_ALLOW_ROTATIONS)
	    t_glinterp->allow_rotations = glinterp->allow_rotations;


	if(flags & V3D_GLFLAG_FLIP_WINDING)
	    t_glinterp->flip_winding = glinterp->flip_winding;

	if(flags & V3D_GLFLAG_PASS_NORMALS)
	    t_glinterp->pass_normals = glinterp->pass_normals;

	if(flags & V3D_GLFLAG_UNITLIZE_NORMALS)
	    t_glinterp->unitlize_normals = glinterp->unitlize_normals;

	if(flags & V3D_GLFLAG_PASS_TEXCOORDS)
	    t_glinterp->pass_texcoords = glinterp->pass_texcoords;

	if(flags & V3D_GLFLAG_TEXTURE_NAME_CASE_SENSITIVE)
	    t_glinterp->texture_name_case_sensitive =
		glinterp->texture_name_case_sensitive;

	if(flags & V3D_GLFLAG_MATERIAL_PROPERTIES)
	    t_glinterp->material_properties = glinterp->material_properties;

	if(flags & V3D_GLFLAG_FACES)
	    t_glinterp->faces = glinterp->faces;


	if(flags & V3D_GLFLAG_ENABLE_BLENDING)
	    t_glinterp->enable_blending = glinterp->enable_blending;

	if(flags & V3D_GLFLAG_SET_BLEND_FUNC)
	    t_glinterp->set_blend_func = glinterp->set_blend_func;

	if(flags & V3D_GLFLAG_HEIGHTFIELD_BASE_DIR)
	{
	    const char *src_str = glinterp->heightfield_base_dir;

	    free(t_glinterp->heightfield_base_dir);
	    t_glinterp->heightfield_base_dir = STRDUP(src_str);
	}

	if(flags & V3D_GLFLAG_TEXTURE_BASE_DIR)
	{
	    const char *src_str = glinterp->texture_base_dir;

	    free(t_glinterp->texture_base_dir);
	    t_glinterp->texture_base_dir = STRDUP(src_str);
	}


	/* Update flags on the target glinterp. */
	t_glinterp->flags |= flags;

	return(0);
}