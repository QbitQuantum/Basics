static struct pipe_texture *
nv50_miptree_create(struct pipe_screen *pscreen, const struct pipe_texture *tmp)
{
	struct nouveau_device *dev = nouveau_screen(pscreen)->device;
	struct nv50_miptree *mt = CALLOC_STRUCT(nv50_miptree);
	struct pipe_texture *pt = &mt->base.base;
	unsigned width = tmp->width0, height = tmp->height0;
	unsigned depth = tmp->depth0, image_alignment;
	uint32_t tile_flags;
	int ret, i, l;

	*pt = *tmp;
	pipe_reference_init(&pt->reference, 1);
	pt->screen = pscreen;

	switch (pt->format) {
	case PIPE_FORMAT_Z32_FLOAT:
		tile_flags = 0x4800;
		break;
	case PIPE_FORMAT_S8Z24_UNORM:
		tile_flags = 0x1800;
		break;
	case PIPE_FORMAT_Z16_UNORM:
		tile_flags = 0x6c00;
		break;
	case PIPE_FORMAT_Z24X8_UNORM:
	case PIPE_FORMAT_Z24S8_UNORM:
		tile_flags = 0x2800;
		break;
	case PIPE_FORMAT_R32G32B32A32_FLOAT:
	case PIPE_FORMAT_R32G32B32_FLOAT:
		tile_flags = 0x7400;
		break;
	default:
		if ((pt->tex_usage & PIPE_TEXTURE_USAGE_PRIMARY) &&
		    util_format_get_blocksizebits(pt->format) == 32)
			tile_flags = 0x7a00;
		else
			tile_flags = 0x7000;
		break;
	}

	/* XXX: texture arrays */
	mt->image_nr = (pt->target == PIPE_TEXTURE_CUBE) ? 6 : 1;

	for (l = 0; l <= pt->last_level; l++) {
		struct nv50_miptree_level *lvl = &mt->level[l];
		unsigned nblocksy = util_format_get_nblocksy(pt->format, height);

		lvl->image_offset = CALLOC(mt->image_nr, sizeof(int));
		lvl->pitch = align(util_format_get_stride(pt->format, width), 64);
		lvl->tile_mode = get_tile_mode(nblocksy, depth);

		width = u_minify(width, 1);
		height = u_minify(height, 1);
		depth = u_minify(depth, 1);
	}

	image_alignment  = get_tile_height(mt->level[0].tile_mode) * 64;
	image_alignment *= get_tile_depth(mt->level[0].tile_mode);

	/* NOTE the distinction between arrays of mip-mapped 2D textures and
	 * mip-mapped 3D textures. We can't use image_nr == depth for 3D mip.
	 */
	for (i = 0; i < mt->image_nr; i++) {
		for (l = 0; l <= pt->last_level; l++) {
			struct nv50_miptree_level *lvl = &mt->level[l];
			int size;
			unsigned tile_h = get_tile_height(lvl->tile_mode);
			unsigned tile_d = get_tile_depth(lvl->tile_mode);

			size  = lvl->pitch;
			size *= align(util_format_get_nblocksy(pt->format, u_minify(pt->height0, l)), tile_h);
			size *= align(u_minify(pt->depth0, l), tile_d);

			lvl->image_offset[i] = mt->total_size;

			mt->total_size += size;
		}
		mt->total_size = align(mt->total_size, image_alignment);
	}

	ret = nouveau_bo_new_tile(dev, NOUVEAU_BO_VRAM, 256, mt->total_size,
				  mt->level[0].tile_mode, tile_flags,
				  &mt->base.bo);
	if (ret) {
		for (l = 0; l <= pt->last_level; ++l)
			FREE(mt->level[l].image_offset);
		FREE(mt);
		return NULL;
	}

	return pt;
}