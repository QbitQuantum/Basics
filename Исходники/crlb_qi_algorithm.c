crlb_qi_run(const vector2 *anchor, const size_t count, const vector2 *location)
{
    const float pi = (float) M_PI;
    // speed of light in su / s, assumes su = 1dm
    const float c = 299792458.0f / crlb_qi_su;
    // Constant alpha of the paper
    const float alpha =
         (c * c) / (8.0f * pi * pi * crlb_qi_beta * crlb_qi_beta);

    // Calculate the CRLB
    float numer = 0.0f;
    float denom = 0.0f;
    for (size_t i = 0; i < count; i++) {
	numer += distance_v(&(anchor[i]), location);
	for (size_t j = 0; j < i; j++) {
	    float phi_i = atanf((location->y - anchor[i].y) / (location->x - anchor[i].x));
	    float phi_j = atanf((location->y - anchor[j].y) / (location->x - anchor[j].x));
	    float a = sinf(phi_i - phi_j);
	    denom += distance_v(location, &(anchor[i])) *
                       distance_v(location, &(anchor[j])) * a * a;
	}
    }
    return crlb_qi_scale * alpha * numer / denom;
}