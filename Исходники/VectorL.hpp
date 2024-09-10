size_t ArgMax(const VectorL<T>& v)
{
    return v.beginRow_ +
           distance(v.storage_.begin(), max_element(v.storage_.begin(), v.storage_.end()));
}