/**
 * Sensing a movement of the original, this function attempts to compensate for it in such a way
 * that the clone stays unmoved or moves in parallel (depending on user setting) regardless of the
 * clone's transform.
 */
void SPUse::move_compensate(Geom::Affine const *mp) {
    // the clone is orphaned; or this is not a real use, but a clone of another use;
    // we skip it, otherwise duplicate compensation will occur
    if (this->cloned) {
        return;
    }

    // never compensate uses which are used in flowtext
    if (parent && dynamic_cast<SPFlowregion *>(parent)) {
        return;
    }

    Inkscape::Preferences *prefs = Inkscape::Preferences::get();
    guint mode = prefs->getInt("/options/clonecompensation/value", SP_CLONE_COMPENSATION_PARALLEL);
    // user wants no compensation
    if (mode == SP_CLONE_COMPENSATION_NONE)
        return;

    Geom::Affine m(*mp);
    Geom::Affine t = this->get_parent_transform();
    Geom::Affine clone_move = t.inverse() * m * t;

    // this is not a simple move, do not try to compensate
    if (!(m.isTranslation())){
    	//BUT move clippaths accordingly.
        //if clone has a clippath, move it accordingly
        if(clip_ref->getObject()){
            SPObject *clip = clip_ref->getObject()->firstChild() ;
            while(clip){
            	SPItem *item = (SPItem*) clip;
            	if(item){
                    item->transform *= m;
                    Geom::Affine identity;
                    item->doWriteTransform(clip->getRepr(),item->transform, &identity);
            	}
                clip = clip->getNext();
            }
        }
        if(mask_ref->getObject()){
            SPObject *mask = mask_ref->getObject()->firstChild() ;
            while(mask){
            	SPItem *item = (SPItem*) mask;
            	if(item){
                    item->transform *= m;
                    Geom::Affine identity;
                    item->doWriteTransform(mask->getRepr(),item->transform, &identity);
            	}
                mask = mask->getNext();
            }
        }
        return;
    }

    // restore item->transform field from the repr, in case it was changed by seltrans
    this->readAttr ("transform");


    // calculate the compensation matrix and the advertized movement matrix
    Geom::Affine advertized_move;
    if (mode == SP_CLONE_COMPENSATION_PARALLEL) {
        clone_move = clone_move.inverse() * m;
        advertized_move = m;
    } else if (mode == SP_CLONE_COMPENSATION_UNMOVED) {
        clone_move = clone_move.inverse();
        advertized_move.setIdentity();
    } else {
        g_assert_not_reached();
    }

    //if clone has a clippath, move it accordingly
    if(clip_ref->getObject()){
        SPObject *clip = clip_ref->getObject()->firstChild() ;
        while(clip){
        	SPItem *item = (SPItem*) clip;
        	if(item){
                item->transform *= clone_move.inverse();
                Geom::Affine identity;
                item->doWriteTransform(clip->getRepr(),item->transform, &identity);
        	}
            clip = clip->getNext();
        }
    }
    if(mask_ref->getObject()){
        SPObject *mask = mask_ref->getObject()->firstChild() ;
        while(mask){
        	SPItem *item = (SPItem*) mask;
        	if(item){
                item->transform *= clone_move.inverse();
                Geom::Affine identity;
                item->doWriteTransform(mask->getRepr(),item->transform, &identity);
        	}
            mask = mask->getNext();
        }
    }


    // commit the compensation
    this->transform *= clone_move;
    this->doWriteTransform(this->getRepr(), this->transform, &advertized_move);
    this->requestDisplayUpdate(SP_OBJECT_MODIFIED_FLAG);
}