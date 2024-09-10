inline float BB_TABLE_UNMAP(float T) {
    // return powf ((T - BB_DRAPER) / BB_TABLE_SPACING, 1.0f/BB_TABLE_XPOWER);
    float t  = (T - BB_DRAPER) / BB_TABLE_SPACING;
    float ic = cbrtf(t);
    return ic * ic; // ^2/3
}