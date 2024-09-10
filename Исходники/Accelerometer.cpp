static inline uint8_t closest_index(const vector<float>& values, float key) {
    vector<float> differences;
    differences.resize(values.size());

    transform(values.begin(), values.end(), differences.begin(), [key](const float val) {
        return fabs(val - key);
    });
    return distance(differences.begin(), min_element(differences.begin(), differences.end()));
}