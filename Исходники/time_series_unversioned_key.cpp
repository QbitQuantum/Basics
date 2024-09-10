time_series_unversioned_key& time_series_unversioned_key::operator=(time_series_unversioned_key other) {
    using std::swap;
    swap(*this, other);
    return *this;
}