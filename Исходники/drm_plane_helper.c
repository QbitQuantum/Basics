/**
 * drm_primary_helper_update() - Helper for primary plane update
 * @plane: plane object to update
 * @crtc: owning CRTC of owning plane
 * @fb: framebuffer to flip onto plane
 * @crtc_x: x offset of primary plane on crtc
 * @crtc_y: y offset of primary plane on crtc
 * @crtc_w: width of primary plane rectangle on crtc
 * @crtc_h: height of primary plane rectangle on crtc
 * @src_x: x offset of @fb for panning
 * @src_y: y offset of @fb for panning
 * @src_w: width of source rectangle in @fb
 * @src_h: height of source rectangle in @fb
 *
 * Provides a default plane update handler for primary planes.  This is handler
 * is called in response to a userspace SetPlane operation on the plane with a
 * non-NULL framebuffer.  We call the driver's modeset handler to update the
 * framebuffer.
 *
 * SetPlane() on a primary plane of a disabled CRTC is not supported, and will
 * return an error.
 *
 * Note that we make some assumptions about hardware limitations that may not be
 * true for all hardware --
 *   1) Primary plane cannot be repositioned.
 *   2) Primary plane cannot be scaled.
 *   3) Primary plane must cover the entire CRTC.
 *   4) Subpixel positioning is not supported.
 * Drivers for hardware that don't have these restrictions can provide their
 * own implementation rather than using this helper.
 *
 * RETURNS:
 * Zero on success, error code on failure
 */
int drm_primary_helper_update(struct drm_plane *plane, struct drm_crtc *crtc,
			      struct drm_framebuffer *fb,
			      int crtc_x, int crtc_y,
			      unsigned int crtc_w, unsigned int crtc_h,
			      uint32_t src_x, uint32_t src_y,
			      uint32_t src_w, uint32_t src_h)
{
	struct drm_mode_set set = {
		.crtc = crtc,
		.fb = fb,
		.mode = &crtc->mode,
		.x = src_x >> 16,
		.y = src_y >> 16,
	};
	struct drm_rect src = {
		.x1 = src_x,
		.y1 = src_y,
		.x2 = src_x + src_w,
		.y2 = src_y + src_h,
	};
	struct drm_rect dest = {
		.x1 = crtc_x,
		.y1 = crtc_y,
		.x2 = crtc_x + crtc_w,
		.y2 = crtc_y + crtc_h,
	};
	const struct drm_rect clip = {
		.x2 = crtc->mode.hdisplay,
		.y2 = crtc->mode.vdisplay,
	};
	struct drm_connector **connector_list;
	int num_connectors, ret;
	bool visible;

	ret = drm_plane_helper_check_update(plane, crtc, fb,
					    &src, &dest, &clip,
					    DRM_PLANE_HELPER_NO_SCALING,
					    DRM_PLANE_HELPER_NO_SCALING,
					    false, false, &visible);
	if (ret)
		return ret;

	if (!visible)
		/*
		 * Primary plane isn't visible.  Note that unless a driver
		 * provides their own disable function, this will just
		 * wind up returning -EINVAL to userspace.
		 */
		return plane->funcs->disable_plane(plane);

	/* Find current connectors for CRTC */
	num_connectors = get_connectors_for_crtc(crtc, NULL, 0);
	BUG_ON(num_connectors == 0);
	connector_list = kzalloc(num_connectors * sizeof(*connector_list),
				 GFP_KERNEL);
	if (!connector_list)
		return -ENOMEM;
	get_connectors_for_crtc(crtc, connector_list, num_connectors);

	set.connectors = connector_list;
	set.num_connectors = num_connectors;

	/*
	 * We call set_config() directly here rather than using
	 * drm_mode_set_config_internal.  We're reprogramming the same
	 * connectors that were already in use, so we shouldn't need the extra
	 * cross-CRTC fb refcounting to accomodate stealing connectors.
	 * drm_mode_setplane() already handles the basic refcounting for the
	 * framebuffers involved in this operation.
	 */
	ret = crtc->funcs->set_config(&set);

	kfree(connector_list);
	return ret;
}
EXPORT_SYMBOL(drm_primary_helper_update);

/**
 * drm_primary_helper_disable() - Helper for primary plane disable
 * @plane: plane to disable
 *
 * Provides a default plane disable handler for primary planes.  This is handler
 * is called in response to a userspace SetPlane operation on the plane with a
 * NULL framebuffer parameter.  It unconditionally fails the disable call with
 * -EINVAL the only way to disable the primary plane without driver support is
 * to disable the entier CRTC. Which does not match the plane ->disable hook.
 *
 * Note that some hardware may be able to disable the primary plane without
 * disabling the whole CRTC.  Drivers for such hardware should provide their
 * own disable handler that disables just the primary plane (and they'll likely
 * need to provide their own update handler as well to properly re-enable a
 * disabled primary plane).
 *
 * RETURNS:
 * Unconditionally returns -EINVAL.
 */
int drm_primary_helper_disable(struct drm_plane *plane)
{
	return -EINVAL;
}
EXPORT_SYMBOL(drm_primary_helper_disable);

/**
 * drm_primary_helper_destroy() - Helper for primary plane destruction
 * @plane: plane to destroy
 *
 * Provides a default plane destroy handler for primary planes.  This handler
 * is called during CRTC destruction.  We disable the primary plane, remove
 * it from the DRM plane list, and deallocate the plane structure.
 */
void drm_primary_helper_destroy(struct drm_plane *plane)
{
	drm_plane_cleanup(plane);
	kfree(plane);
}
EXPORT_SYMBOL(drm_primary_helper_destroy);

const struct drm_plane_funcs drm_primary_helper_funcs = {
	.update_plane = drm_primary_helper_update,
	.disable_plane = drm_primary_helper_disable,
	.destroy = drm_primary_helper_destroy,
};
EXPORT_SYMBOL(drm_primary_helper_funcs);

static struct drm_plane *create_primary_plane(struct drm_device *dev)
{
	struct drm_plane *primary;
	int ret;

	primary = kzalloc(sizeof(*primary), GFP_KERNEL);
	if (primary == NULL) {
		DRM_DEBUG_KMS("Failed to allocate primary plane\n");
		return NULL;
	}

	/*
	 * Remove the format_default field from drm_plane when dropping
	 * this helper.
	 */
	primary->format_default = true;

	/* possible_crtc's will be filled in later by crtc_init */
	ret = drm_universal_plane_init(dev, primary, 0,
				       &drm_primary_helper_funcs,
				       safe_modeset_formats,
				       ARRAY_SIZE(safe_modeset_formats),
				       DRM_PLANE_TYPE_PRIMARY, NULL);
	if (ret) {
		kfree(primary);
		primary = NULL;
	}

	return primary;
}

/**
 * drm_crtc_init - Legacy CRTC initialization function
 * @dev: DRM device
 * @crtc: CRTC object to init
 * @funcs: callbacks for the new CRTC
 *
 * Initialize a CRTC object with a default helper-provided primary plane and no
 * cursor plane.
 *
 * Returns:
 * Zero on success, error code on failure.
 */
int drm_crtc_init(struct drm_device *dev, struct drm_crtc *crtc,
		  const struct drm_crtc_funcs *funcs)
{
	struct drm_plane *primary;

	primary = create_primary_plane(dev);
	return drm_crtc_init_with_planes(dev, crtc, primary, NULL, funcs,
					 NULL);
}
EXPORT_SYMBOL(drm_crtc_init);

int drm_plane_helper_commit(struct drm_plane *plane,
			    struct drm_plane_state *plane_state,
			    struct drm_framebuffer *old_fb)
{
	const struct drm_plane_helper_funcs *plane_funcs;
	struct drm_crtc *crtc[2];
	const struct drm_crtc_helper_funcs *crtc_funcs[2];
	int i, ret = 0;

	plane_funcs = plane->helper_private;

	/* Since this is a transitional helper we can't assume that plane->state
	 * is always valid. Hence we need to use plane->crtc instead of
	 * plane->state->crtc as the old crtc. */
	crtc[0] = plane->crtc;
	crtc[1] = crtc[0] != plane_state->crtc ? plane_state->crtc : NULL;

	for (i = 0; i < 2; i++)
		crtc_funcs[i] = crtc[i] ? crtc[i]->helper_private : NULL;

	if (plane_funcs->atomic_check) {
		ret = plane_funcs->atomic_check(plane, plane_state);
		if (ret)
			goto out;
	}

	if (plane_funcs->prepare_fb && plane_state->fb &&
	    plane_state->fb != old_fb) {
		ret = plane_funcs->prepare_fb(plane,
					      plane_state);
		if (ret)
			goto out;
	}

	/* Point of no return, commit sw state. */
	swap(plane->state, plane_state);

	for (i = 0; i < 2; i++) {
		if (crtc_funcs[i] && crtc_funcs[i]->atomic_begin)
			crtc_funcs[i]->atomic_begin(crtc[i], crtc[i]->state);
	}

	/*
	 * Drivers may optionally implement the ->atomic_disable callback, so
	 * special-case that here.
	 */
	if (drm_atomic_plane_disabling(plane, plane_state) &&
	    plane_funcs->atomic_disable)
		plane_funcs->atomic_disable(plane, plane_state);
	else
		plane_funcs->atomic_update(plane, plane_state);

	for (i = 0; i < 2; i++) {
		if (crtc_funcs[i] && crtc_funcs[i]->atomic_flush)
			crtc_funcs[i]->atomic_flush(crtc[i], crtc[i]->state);
	}

	/*
	 * If we only moved the plane and didn't change fb's, there's no need to
	 * wait for vblank.
	 */
	if (plane->state->fb == old_fb)
		goto out;

	for (i = 0; i < 2; i++) {
		if (!crtc[i])
			continue;

		if (crtc[i]->cursor == plane)
			continue;

		/* There's no other way to figure out whether the crtc is running. */
		ret = drm_crtc_vblank_get(crtc[i]);
		if (ret == 0) {
			drm_crtc_wait_one_vblank(crtc[i]);
			drm_crtc_vblank_put(crtc[i]);
		}

		ret = 0;
	}

	if (plane_funcs->cleanup_fb)
		plane_funcs->cleanup_fb(plane, plane_state);
out:
	if (plane_state) {
		if (plane->funcs->atomic_destroy_state)
			plane->funcs->atomic_destroy_state(plane, plane_state);
		else
			drm_atomic_helper_plane_destroy_state(plane, plane_state);
	}

	return ret;
}

/**
 * drm_plane_helper_update() - Transitional helper for plane update
 * @plane: plane object to update
 * @crtc: owning CRTC of owning plane
 * @fb: framebuffer to flip onto plane
 * @crtc_x: x offset of primary plane on crtc
 * @crtc_y: y offset of primary plane on crtc
 * @crtc_w: width of primary plane rectangle on crtc
 * @crtc_h: height of primary plane rectangle on crtc
 * @src_x: x offset of @fb for panning
 * @src_y: y offset of @fb for panning
 * @src_w: width of source rectangle in @fb
 * @src_h: height of source rectangle in @fb
 *
 * Provides a default plane update handler using the atomic plane update
 * functions. It is fully left to the driver to check plane constraints and
 * handle corner-cases like a fully occluded or otherwise invisible plane.
 *
 * This is useful for piecewise transitioning of a driver to the atomic helpers.
 *
 * RETURNS:
 * Zero on success, error code on failure
 */
int drm_plane_helper_update(struct drm_plane *plane, struct drm_crtc *crtc,
			    struct drm_framebuffer *fb,
			    int crtc_x, int crtc_y,
			    unsigned int crtc_w, unsigned int crtc_h,
			    uint32_t src_x, uint32_t src_y,
			    uint32_t src_w, uint32_t src_h)
{
	struct drm_plane_state *plane_state;

	if (plane->funcs->atomic_duplicate_state)
		plane_state = plane->funcs->atomic_duplicate_state(plane);
	else {
		if (!plane->state)
			drm_atomic_helper_plane_reset(plane);

		plane_state = drm_atomic_helper_plane_duplicate_state(plane);
	}
	if (!plane_state)
		return -ENOMEM;
	plane_state->plane = plane;

	plane_state->crtc = crtc;
	drm_atomic_set_fb_for_plane(plane_state, fb);
	plane_state->crtc_x = crtc_x;
	plane_state->crtc_y = crtc_y;
	plane_state->crtc_h = crtc_h;
	plane_state->crtc_w = crtc_w;
	plane_state->src_x = src_x;
	plane_state->src_y = src_y;
	plane_state->src_h = src_h;
	plane_state->src_w = src_w;

	return drm_plane_helper_commit(plane, plane_state, plane->fb);
}
EXPORT_SYMBOL(drm_plane_helper_update);

/**
 * drm_plane_helper_disable() - Transitional helper for plane disable
 * @plane: plane to disable
 *
 * Provides a default plane disable handler using the atomic plane update
 * functions. It is fully left to the driver to check plane constraints and
 * handle corner-cases like a fully occluded or otherwise invisible plane.
 *
 * This is useful for piecewise transitioning of a driver to the atomic helpers.
 *
 * RETURNS:
 * Zero on success, error code on failure
 */
int drm_plane_helper_disable(struct drm_plane *plane)
{
	struct drm_plane_state *plane_state;

	/* crtc helpers love to call disable functions for already disabled hw
	 * functions. So cope with that. */
	if (!plane->crtc)
		return 0;

	if (plane->funcs->atomic_duplicate_state)
		plane_state = plane->funcs->atomic_duplicate_state(plane);
	else {
		if (!plane->state)
			drm_atomic_helper_plane_reset(plane);

		plane_state = drm_atomic_helper_plane_duplicate_state(plane);
	}
	if (!plane_state)
		return -ENOMEM;
	plane_state->plane = plane;

	plane_state->crtc = NULL;
	drm_atomic_set_fb_for_plane(plane_state, NULL);

	return drm_plane_helper_commit(plane, plane_state, plane->fb);
}
EXPORT_SYMBOL(drm_plane_helper_disable);