// Convert sf::Transform to float array
inline void createTransform(const sf::Transform& transform, float* converted)
{
    const float* m = transform.getMatrix();
    converted[0] = m[0];
    converted[1] = m[4];
    converted[2] = m[12];
    converted[3] = m[1];
    converted[4] = m[5];
    converted[5] = m[13];
    converted[6] = m[3];
    converted[7] = m[7];
    converted[8] = m[15];
    
}