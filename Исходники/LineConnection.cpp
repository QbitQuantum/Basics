float LineConnection::Distance(const XMVECTOR& vector1,const XMVECTOR& vector2)
{
    XMVECTOR vectorSub = XMVectorSubtract(vector1,vector2);
    XMVECTOR length = XMVector3Length(vectorSub);

    float distance = 0.0f;
    XMStoreFloat(&distance,length);
    return distance;
}