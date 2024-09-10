float CameraParameters::getFloat(const char *key) const
{
    const char *v = get(key);
    if (v == 0) return -1;
    return strtof(v, 0);
}