void Group::Generate(IdList<Entity,hEntity> *entity,
                     IdList<Param,hParam> *param)
{
    Vector gn = (SS.GW.projRight).Cross(SS.GW.projUp);
    Vector gp = SS.GW.projRight.Plus(SS.GW.projUp);
    Vector gc = (SS.GW.offset).ScaledBy(-1);
    gn = gn.WithMagnitude(200/SS.GW.scale);
    gp = gp.WithMagnitude(200/SS.GW.scale);
    int a, i;
    switch(type) {
        case DRAWING_3D:
            break;

        case DRAWING_WORKPLANE: {
            Quaternion q;
            if(subtype == WORKPLANE_BY_LINE_SEGMENTS) {
                Vector u = SK.GetEntity(predef.entityB)->VectorGetNum();
                Vector v = SK.GetEntity(predef.entityC)->VectorGetNum();
                u = u.WithMagnitude(1);
                Vector n = u.Cross(v);
                v = (n.Cross(u)).WithMagnitude(1);

                if(predef.swapUV) SWAP(Vector, u, v);
                if(predef.negateU) u = u.ScaledBy(-1);
                if(predef.negateV) v = v.ScaledBy(-1);
                q = Quaternion::From(u, v);
            } else if(subtype == WORKPLANE_BY_POINT_ORTHO) {
                // Already given, numerically.
                q = predef.q;
            } else oops();

            Entity normal;
            memset(&normal, 0, sizeof(normal));
            normal.type = Entity::NORMAL_N_COPY;
            normal.numNormal = q;
            normal.point[0] = h.entity(2);
            normal.group = h;
            normal.h = h.entity(1);
            entity->Add(&normal);

            Entity point;
            memset(&point, 0, sizeof(point));
            point.type = Entity::POINT_N_COPY;
            point.numPoint = SK.GetEntity(predef.origin)->PointGetNum();
            point.group = h;
            point.h = h.entity(2);
            entity->Add(&point);

            Entity wp;
            memset(&wp, 0, sizeof(wp));
            wp.type = Entity::WORKPLANE;
            wp.normal = normal.h;
            wp.point[0] = point.h;
            wp.group = h;
            wp.h = h.entity(0);
            entity->Add(&wp);
            break;
        }

        case EXTRUDE: {
            AddParam(param, h.param(0), gn.x);
            AddParam(param, h.param(1), gn.y);
            AddParam(param, h.param(2), gn.z);
            int ai, af;
            if(subtype == ONE_SIDED) {
                ai = 0; af = 2;
            } else if(subtype == TWO_SIDED) {
                ai = -1; af = 1;
            } else oops();

            // Get some arbitrary point in the sketch, that will be used
            // as a reference when defining top and bottom faces.
            hEntity pt = { 0 };
            for(i = 0; i < entity->n; i++) {
                Entity *e = &(entity->elem[i]);
                if(e->group.v != opA.v) continue;

                if(e->IsPoint()) pt = e->h;

                e->CalculateNumerical(false);
                hEntity he = e->h; e = NULL;
                // As soon as I call CopyEntity, e may become invalid! That
                // adds entities, which may cause a realloc.
                CopyEntity(entity, SK.GetEntity(he), ai, REMAP_BOTTOM,
                    h.param(0), h.param(1), h.param(2),
                    NO_PARAM, NO_PARAM, NO_PARAM, NO_PARAM,
                    true, false);
                CopyEntity(entity, SK.GetEntity(he), af, REMAP_TOP,
                    h.param(0), h.param(1), h.param(2),
                    NO_PARAM, NO_PARAM, NO_PARAM, NO_PARAM,
                    true, false);
                MakeExtrusionLines(entity, he);
            }
            // Remapped versions of that arbitrary point will be used to
            // provide points on the plane faces.
            MakeExtrusionTopBottomFaces(entity, pt);
            break;
        }

        case LATHE: {
            break;
        }

        case TRANSLATE: {
            // The translation vector
            AddParam(param, h.param(0), gp.x);
            AddParam(param, h.param(1), gp.y);
            AddParam(param, h.param(2), gp.z);

            int n = (int)valA, a0 = 0;
            if(subtype == ONE_SIDED && skipFirst) {
                a0++; n++;
            }

            for(a = a0; a < n; a++) {
                for(i = 0; i < entity->n; i++) {
                    Entity *e = &(entity->elem[i]);
                    if(e->group.v != opA.v) continue;

                    e->CalculateNumerical(false);
                    CopyEntity(entity, e,
                        a*2 - (subtype == ONE_SIDED ? 0 : (n-1)),
                        (a == (n - 1)) ? REMAP_LAST : a,
                        h.param(0), h.param(1), h.param(2),
                        NO_PARAM, NO_PARAM, NO_PARAM, NO_PARAM,
                        true, false);
                }
            }
            break;
        }
        case ROTATE: {
            // The center of rotation
            AddParam(param, h.param(0), gc.x);
            AddParam(param, h.param(1), gc.y);
            AddParam(param, h.param(2), gc.z);
            // The rotation quaternion
            AddParam(param, h.param(3), 30*PI/180);
            AddParam(param, h.param(4), gn.x);
            AddParam(param, h.param(5), gn.y);
            AddParam(param, h.param(6), gn.z);

            int n = (int)valA, a0 = 0;
            if(subtype == ONE_SIDED && skipFirst) {
                a0++; n++;
            }

            for(a = a0; a < n; a++) {
                for(i = 0; i < entity->n; i++) {
                    Entity *e = &(entity->elem[i]);
                    if(e->group.v != opA.v) continue;

                    e->CalculateNumerical(false);
                    CopyEntity(entity, e,
                        a*2 - (subtype == ONE_SIDED ? 0 : (n-1)),
                        (a == (n - 1)) ? REMAP_LAST : a,
                        h.param(0), h.param(1), h.param(2),
                        h.param(3), h.param(4), h.param(5), h.param(6),
                        false, true);
                }
            }
            break;
        }
        case IMPORTED:
            // The translation vector
            AddParam(param, h.param(0), gp.x);
            AddParam(param, h.param(1), gp.y);
            AddParam(param, h.param(2), gp.z);
            // The rotation quaternion
            AddParam(param, h.param(3), 1);
            AddParam(param, h.param(4), 0);
            AddParam(param, h.param(5), 0);
            AddParam(param, h.param(6), 0);

            for(i = 0; i < impEntity.n; i++) {
                Entity *ie = &(impEntity.elem[i]);
                CopyEntity(entity, ie, 0, 0,
                    h.param(0), h.param(1), h.param(2),
                    h.param(3), h.param(4), h.param(5), h.param(6),
                    false, false);
            }
            break;

        default: oops();
    }
}