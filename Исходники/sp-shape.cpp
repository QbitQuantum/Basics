Geom::OptRect SPShape::bbox(Geom::Affine const &transform, SPItem::BBoxType bboxtype) const {
    Geom::OptRect bbox;

    if (!this->_curve) {
    	return bbox;
    }

    bbox = bounds_exact_transformed(this->_curve->get_pathvector(), transform);

    if (!bbox) {
    	return bbox;
    }

    if (bboxtype == SPItem::VISUAL_BBOX) {
        // convert the stroke to a path and calculate that path's geometric bbox

        if (!this->style->stroke.isNone()) {
            Geom::PathVector *pathv = item_outline(this, true);  // calculate bbox_only

            if (pathv) {
                bbox |= bounds_exact_transformed(*pathv, transform);
                delete pathv;
            }
        }

        // Union with bboxes of the markers, if any
        if ( this->hasMarkers()  && !this->_curve->get_pathvector().empty() ) {
            /** \todo make code prettier! */
            Geom::PathVector const & pathv = this->_curve->get_pathvector();
            // START marker
            for (unsigned i = 0; i < 2; i++) { // SP_MARKER_LOC and SP_MARKER_LOC_START
                if ( this->_marker[i] ) {
                    SPItem* marker_item = sp_item_first_item_child( _marker[i] );

                    if (marker_item) {
                        Geom::Affine tr(sp_shape_marker_get_transform_at_start(pathv.begin()->front()));

                        if (_marker[i]->orient_mode == MARKER_ORIENT_AUTO_START_REVERSE) {
                            // Reverse start marker if necessary
                            tr = Geom::Rotate::from_degrees( 180.0 ) * tr;
                        } else if (_marker[i]->orient_mode == MARKER_ORIENT_ANGLE) {
                            Geom::Point transl = tr.translation();
                            tr = Geom::Rotate::from_degrees(_marker[i]->orient) * Geom::Translate(transl);
                        }

                        if (_marker[i]->markerUnits == SP_MARKER_UNITS_STROKEWIDTH) {
                            tr = Geom::Scale(this->style->stroke_width.computed) * tr;
                        }

                        // total marker transform
                        tr = marker_item->transform * _marker[i]->c2p * tr * transform;

                        // get bbox of the marker with that transform
                        bbox |= marker_item->visualBounds(tr);
                    }
                }
            }

            // MID marker
            for (unsigned i = 0; i < 3; i += 2) { // SP_MARKER_LOC and SP_MARKER_LOC_MID
                if ( !this->_marker[i] ) {
                	continue;
                }

                SPMarker* marker = _marker[i];
                SPItem* marker_item = sp_item_first_item_child( marker );

                if ( !marker_item ) {
                	continue;
                }

                for(Geom::PathVector::const_iterator path_it = pathv.begin(); path_it != pathv.end(); ++path_it) {
                    // START position
                    if ( path_it != pathv.begin() 
                         && ! ((path_it == (pathv.end()-1)) && (path_it->size_default() == 0)) ) // if this is the last path and it is a moveto-only, there is no mid marker there
                    {
                        Geom::Affine tr(sp_shape_marker_get_transform_at_start(path_it->front()));

                        if (marker->orient_mode == MARKER_ORIENT_ANGLE) {
                            Geom::Point transl = tr.translation();
                            tr = Geom::Rotate::from_degrees(marker->orient) * Geom::Translate(transl);
                        }

                        if (marker->markerUnits == SP_MARKER_UNITS_STROKEWIDTH) {
                            tr = Geom::Scale(this->style->stroke_width.computed) * tr;
                        }

                        tr = marker_item->transform * marker->c2p * tr * transform;
                        bbox |= marker_item->visualBounds(tr);
                    }

                    // MID position
                    if ( path_it->size_default() > 1) {
                        Geom::Path::const_iterator curve_it1 = path_it->begin();      // incoming curve
                        Geom::Path::const_iterator curve_it2 = ++(path_it->begin());  // outgoing curve

                        while (curve_it2 != path_it->end_default())
                        {
                            /* Put marker between curve_it1 and curve_it2.
                             * Loop to end_default (so including closing segment), because when a path is closed,
                             * there should be a midpoint marker between last segment and closing straight line segment */

                            SPMarker* marker = _marker[i];
                            SPItem* marker_item = sp_item_first_item_child( marker );

                            if (marker_item) {
                                Geom::Affine tr(sp_shape_marker_get_transform(*curve_it1, *curve_it2));

                                if (marker->orient_mode == MARKER_ORIENT_ANGLE) {
                                    Geom::Point transl = tr.translation();
                                    tr = Geom::Rotate::from_degrees(marker->orient) * Geom::Translate(transl);
                                }

                                if (marker->markerUnits == SP_MARKER_UNITS_STROKEWIDTH) {
                                    tr = Geom::Scale(this->style->stroke_width.computed) * tr;
                                }

                                tr = marker_item->transform * marker->c2p * tr * transform;
                                bbox |= marker_item->visualBounds(tr);
                            }

                            ++curve_it1;
                            ++curve_it2;
                        }
                    }

                    // END position
                    if ( path_it != (pathv.end()-1) && !path_it->empty()) {
                        Geom::Curve const &lastcurve = path_it->back_default();
                        Geom::Affine tr = sp_shape_marker_get_transform_at_end(lastcurve);

                        if (marker->orient_mode == MARKER_ORIENT_ANGLE) {
                            Geom::Point transl = tr.translation();
                            tr = Geom::Rotate::from_degrees(marker->orient) * Geom::Translate(transl);
                        }

                        if (marker->markerUnits == SP_MARKER_UNITS_STROKEWIDTH) {
                            tr = Geom::Scale(this->style->stroke_width.computed) * tr;
                        }

                        tr = marker_item->transform * marker->c2p * tr * transform;
                        bbox |= marker_item->visualBounds(tr);
                    }
                }
            }

            // END marker
            for (unsigned i = 0; i < 4; i += 3) { // SP_MARKER_LOC and SP_MARKER_LOC_END
                if ( _marker[i] ) {
                    SPMarker* marker = _marker[i];
                    SPItem* marker_item = sp_item_first_item_child( marker );

                    if (marker_item) {
                        /* Get reference to last curve in the path.
                         * For moveto-only path, this returns the "closing line segment". */
                        Geom::Path const &path_last = pathv.back();
                        unsigned int index = path_last.size_default();

                        if (index > 0) {
                            index--;
                        }

                        Geom::Curve const &lastcurve = path_last[index];

                        Geom::Affine tr = sp_shape_marker_get_transform_at_end(lastcurve);

                        if (marker->orient_mode == MARKER_ORIENT_ANGLE) {
                            Geom::Point transl = tr.translation();
                            tr = Geom::Rotate::from_degrees(marker->orient) * Geom::Translate(transl);
                        }

                        if (marker->markerUnits == SP_MARKER_UNITS_STROKEWIDTH) {
                            tr = Geom::Scale(this->style->stroke_width.computed) * tr;
                        }

                        // total marker transform
                        tr = marker_item->transform * marker->c2p * tr * transform;

                        // get bbox of the marker with that transform
                        bbox |= marker_item->visualBounds(tr);
                    }
                }
            }
        }
    }

    return bbox;
}