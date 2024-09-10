/***********************************************************************//**
 * @brief Computes atanh of vector elements
 *
 * @param[in] vector Vector.
 * @return Vector containing the atanh of every element.
 ***************************************************************************/
GVector atanh(const GVector& vector)
{
    // Initialise result vector
    GVector result(vector.m_num);

    // Evaluate each vector element
    for (int i = 0; i < vector.m_num; ++i) {
        result.m_data[i] = atanh(vector.m_data[i]);
    }

    // Return vector
    return result;
}