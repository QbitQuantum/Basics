parent_info& parent_info::operator=(parent_info other) {
    using std::swap;
    swap(*this, other);
    return *this;
}