static unsigned int ray_color(const point3 e, double t,
        const point3 d,
        idx_stack *stk,
        const rectangular_node rectangulars,
        const sphere_node spheres,
        const light_node lights,
        color object_color, int bounces_left)
{
    rectangular_node hit_rec = NULL, light_hit_rec = NULL;
    sphere_node hit_sphere = NULL, light_hit_sphere = NULL;
    double diffuse, specular;
    point3 l, _l, r, rr;
    object_fill fill;

    color reflection_part;
    color refraction_part;
    /* might be a reflection ray, so check how many times we've bounced */
    if (bounces_left == 0) {
        SET_COLOR(object_color, 0.0, 0.0, 0.0);
        return 0;
    }

    /* check for intersection with a sphere or a rectangular */
    intersection ip= ray_hit_object(e, d, t, MAX_DISTANCE, rectangulars,
            &hit_rec, spheres, &hit_sphere);
    if (!hit_rec && !hit_sphere)
        return 0;

    /* pick the fill of the object that was hit */
    fill = hit_rec ?
        hit_rec->element.rectangular_fill :
        hit_sphere->element.sphere_fill;

    void *hit_obj = hit_rec ? (void *) hit_rec : (void *) hit_sphere;

    /* assume it is a shadow */
    SET_COLOR(object_color, 0.0, 0.0, 0.0);

    for (light_node light = lights; light; light = light->next) {
        /* calculate the intersection vector pointing at the light */
        subtract_vector(ip.point, light->element.position, l);
        multiply_vector(l, -1, _l);
        normalize(_l);
        /* check for intersection with an object. use ignore_me
         * because we don't care about this normal
         */
        ray_hit_object(ip.point, _l, MIN_DISTANCE, length(l),
                rectangulars, &light_hit_rec,
                spheres, &light_hit_sphere);
        /* the light was not block by itself(lit object) */
        if (light_hit_rec || light_hit_sphere)
            continue;

        compute_specular_diffuse(&diffuse, &specular, d, l,
                ip.normal, fill.phong_power);

        localColor(object_color, light->element.light_color,
                diffuse, specular, &fill);
    }

    reflection(r, d, ip.normal);
    double idx = idx_stack_top(stk).idx, idx_pass = fill.index_of_refraction;
    if (idx_stack_top(stk).obj == hit_obj) {
        idx_stack_pop(stk);
        idx_pass = idx_stack_top(stk).idx;
    } else {
        idx_stack_element e = { .obj = hit_obj,
            .idx = fill.index_of_refraction
        };
        idx_stack_push(stk, e);
    }

    refraction(rr, d, ip.normal, idx, idx_pass);
    double R = (fill.T > 0.1) ?
        fresnel(d, rr, ip.normal, idx, idx_pass) :
        1.0;

    /* totalColor = localColor +
       mix((1-fill.Kd) * fill.R * reflection, T * refraction, R)
       */
    if (fill.R > 0) {
        /* if we hit something, add the color */
        int old_top = stk->top;
        if (ray_color(ip.point, MIN_DISTANCE, r, stk, rectangulars, spheres,
                    lights, reflection_part,
                    bounces_left - 1)) {
            multiply_vector(reflection_part, R * (1.0 - fill.Kd) * fill.R,
                    reflection_part);
            add_vector(object_color, reflection_part,
                    object_color);
        }
        stk->top = old_top;
    }
    /* calculate refraction ray */
    if ((length(rr) > 0.0) && (fill.T > 0.0) &&
            (fill.index_of_refraction > 0.0)) {
        normalize(rr);
        if (ray_color(ip.point, MIN_DISTANCE, rr, stk,rectangulars, spheres,
                    lights, refraction_part,
                    bounces_left - 1)) {
            multiply_vector(refraction_part, (1 - R) * fill.T,
                    refraction_part);
            add_vector(object_color, refraction_part,
                    object_color);
        }
    }

    protect_color_overflow(object_color);
    return 1;
}

/* @param background_color this is not ambient light */
static void *parallel (void* para)
{
    Threadinside *inside = (Threadinside *)para;

    point3 d;
    idx_stack stk;
    color object_color = { 0.0, 0.0, 0.0 };

    for (int j = inside->h1; j < inside->h2; j++) {
        for (int i = 0; i < inside->p->width; i++) {
            double r = 0, g = 0, b = 0;
            /* MSAA */
            for (int s = 0; s < SAMPLES; s++) {
                idx_stack_init(&stk);
                rayConstruction(d, inside->p->u,
                        inside->p->v, inside->p->w,
                        i * inside->p->factor + s / inside->p->factor,
                        j * inside->p->factor + s % inside->p->factor,
                        inside->p->view,
                        inside->p->width * inside->p->factor, 
                        inside->p->height * inside->p->factor);
                if (ray_color(inside->p->view->vrp, 0.0, d,
                            &(stk), inside->p->rectangulars,
                            inside->p->spheres,
                            inside->p->lights, object_color,
                            MAX_REFLECTION_BOUNCES)) {
                    r += object_color[0];
                    g += object_color[1];
                    b += object_color[2];
                } else {
                    r += inside->p->background_color[0];
                    g += inside->p->background_color[1];
                    b += inside->p->background_color[2];
                }
                inside->p->pixels[((i + (j * inside->p->width)) * 3) + 0] = r * 255 / SAMPLES;
                inside->p->pixels[((i + (j * inside->p->width)) * 3) + 1] = g * 255 / SAMPLES;
                inside->p->pixels[((i + (j * inside->p->width)) * 3) + 2] = b * 255 / SAMPLES;
            }
        }
    }
    return NULL;
}