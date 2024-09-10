/*!
*  \brief      Translate an AABB with the passed transformations.
*  \details    The new AABB has a larger size as the original and the AABB is no more tight!
*  \author     Sascha Kaden
*  \param[in]  original aabb
*  \param[in]  pair with rotation and transformation
*  \param[out] transformed aabb
*  \date       2017-06-21
*/
static AABB translateAABB(const AABB &a, const Transform &T) {
    AABB result(a);
    result.translate(T.translation());
    return result;
}