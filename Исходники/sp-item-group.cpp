void
sp_item_group_ungroup (SPGroup *group, GSList **children, bool do_done)
{
    g_return_if_fail (group != NULL);
    g_return_if_fail (SP_IS_GROUP (group));

    SPDocument *doc = group->document;
    SPRoot *root = doc->getRoot();
    SPObject *defs = root->defs;

    SPItem *gitem = group;
    Inkscape::XML::Node *grepr = gitem->getRepr();

    g_return_if_fail (!strcmp (grepr->name(), "svg:g") || !strcmp (grepr->name(), "svg:a") || !strcmp (grepr->name(), "svg:switch"));

    // this converts the gradient/pattern fill/stroke on the group, if any, to userSpaceOnUse
    gitem->adjust_paint_recursive (Geom::identity(), Geom::identity(), false);

    SPItem *pitem = SP_ITEM(gitem->parent);
    Inkscape::XML::Node *prepr = pitem->getRepr();

	if (SP_IS_BOX3D(gitem)) {
		group = box3d_convert_to_group(SP_BOX3D(gitem));
		gitem = group;
	}

	sp_lpe_item_remove_all_path_effects(SP_LPE_ITEM(group), false);

    /* Step 1 - generate lists of children objects */
    GSList *items = NULL;
    GSList *objects = NULL;
    for (SPObject *child = group->firstChild() ; child; child = child->getNext() ) {

        if (SP_IS_ITEM (child)) {

            SPItem *citem = SP_ITEM (child);

            /* Merging of style */
            // this converts the gradient/pattern fill/stroke, if any, to userSpaceOnUse; we need to do
            // it here _before_ the new transform is set, so as to use the pre-transform bbox
            citem->adjust_paint_recursive (Geom::identity(), Geom::identity(), false);

            sp_style_merge_from_dying_parent(child->style, gitem->style);
            /*
             * fixme: We currently make no allowance for the case where child is cloned
             * and the group has any style settings.
             *
             * (This should never occur with documents created solely with the current
             * version of inkscape without using the XML editor: we usually apply group
             * style changes to children rather than to the group itself.)
             *
             * If the group has no style settings, then
             * sp_style_merge_from_dying_parent should be a no-op.  Otherwise (i.e. if
             * we change the child's style to compensate for its parent going away)
             * then those changes will typically be reflected in any clones of child,
             * whereas we'd prefer for Ungroup not to affect the visual appearance.
             *
             * The only way of preserving styling appearance in general is for child to
             * be put into a new group -- a somewhat surprising response to an Ungroup
             * command.  We could add a new groupmode:transparent that would mostly
             * hide the existence of such groups from the user (i.e. editing behaves as
             * if the transparent group's children weren't in a group), though that's
             * extra complication & maintenance burden and this case is rare.
             */

            child->updateRepr();

            Inkscape::XML::Node *nrepr = child->getRepr()->duplicate(prepr->document());

            // Merging transform
            Geom::Affine ctrans;
            Geom::Affine const g(gitem->transform);
            if (SP_IS_USE(citem) && sp_use_get_original (SP_USE(citem)) &&
                sp_use_get_original( SP_USE(citem) )->parent == SP_OBJECT(group)) {
                // make sure a clone's effective transform is the same as was under group
                ctrans = g.inverse() * citem->transform * g;
            } else {
                // We should not apply the group's transformation to both a linked offset AND to its source
                if (SP_IS_OFFSET(citem)) { // Do we have an offset at hand (whether it's dynamic or linked)?
                    SPItem *source = sp_offset_get_source(SP_OFFSET(citem));
                    // When dealing with a chain of linked offsets, the transformation of an offset will be
                    // tied to the transformation of the top-most source, not to any of the intermediate
                    // offsets. So let's find the top-most source
                    while (source != NULL && SP_IS_OFFSET(source)) {
                        source = sp_offset_get_source(SP_OFFSET(source));
                    }
                    if (source != NULL && // If true then we must be dealing with a linked offset ...
                        group->isAncestorOf(source) == false) { // ... of which the source is not in the same group
                        ctrans = citem->transform * g; // then we should apply the transformation of the group to the offset
                    } else {
                        ctrans = citem->transform;
                    }
                } else {
                    ctrans = citem->transform * g;
                }
            }

            // FIXME: constructing a transform that would fully preserve the appearance of a
            // textpath if it is ungrouped with its path seems to be impossible in general
            // case. E.g. if the group was squeezed, to keep the ungrouped textpath squeezed
            // as well, we'll need to relink it to some "virtual" path which is inversely
            // stretched relative to the actual path, and then squeeze the textpath back so it
            // would both fit the actual path _and_ be squeezed as before. It's a bummer.

            // This is just a way to temporarily remember the transform in repr. When repr is
            // reattached outside of the group, the transform will be written more properly
            // (i.e. optimized into the object if the corresponding preference is set)
            gchar *affinestr=sp_svg_transform_write(ctrans);
            nrepr->setAttribute("transform", affinestr);
            g_free(affinestr);

            items = g_slist_prepend (items, nrepr);

        } else {
            Inkscape::XML::Node *nrepr = child->getRepr()->duplicate(prepr->document());
            objects = g_slist_prepend (objects, nrepr);
        }
    }

    /* Step 2 - clear group */
    // remember the position of the group
    gint pos = group->getRepr()->position();

    // the group is leaving forever, no heir, clones should take note; its children however are going to reemerge
    group->deleteObject(true, false);

    /* Step 3 - add nonitems */
    if (objects) {
        Inkscape::XML::Node *last_def = defs->getRepr()->lastChild();
        while (objects) {
            Inkscape::XML::Node *repr = (Inkscape::XML::Node *) objects->data;
            if (!sp_repr_is_meta_element(repr)) {
                defs->getRepr()->addChild(repr, last_def);
            }
            Inkscape::GC::release(repr);
            objects = g_slist_remove (objects, objects->data);
        }
    }

    /* Step 4 - add items */
    while (items) {
        Inkscape::XML::Node *repr = (Inkscape::XML::Node *) items->data;
        // add item
        prepr->appendChild(repr);
        // restore position; since the items list was prepended (i.e. reverse), we now add
        // all children at the same pos, which inverts the order once again
        repr->setPosition(pos > 0 ? pos : 0);

        // fill in the children list if non-null
        SPItem *item = static_cast<SPItem *>(doc->getObjectByRepr(repr));

        item->doWriteTransform(repr, item->transform, NULL, false);

        Inkscape::GC::release(repr);
        if (children && SP_IS_ITEM (item))
            *children = g_slist_prepend (*children, item);

        items = g_slist_remove (items, items->data);
    }

    if (do_done) {
        DocumentUndo::done(doc, SP_VERB_NONE, _("Ungroup"));
    }
}