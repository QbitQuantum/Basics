    void SpriteBatcher3D::pushSprite(const Vector3 position, const Vector3 &normal, const Vector2 &size, const TextureRegion *region)
  {
    //画像の上方向を表すベクトル(これがそのまま上方向になる訳ではない)
    Vector3 up;
    //通常はy軸が画像の上, 画像が上か下を向いている時はz軸が画像の上
    if( normal.x == 0 && normal.z == 0)
      up.set(0,0,1);
    else
      up.set(0,1,0);  

    //X軸
    Vector3 axis1 = up.cross(normal);
    axis1.normalize();

    //Y軸
    Vector3 axis2 = normal.cross(axis1);
    axis2.normalize();

    axis1 *= size.x/2;
    axis2 *= size.y/2;
    const Vector3 leftBottom  = position - axis1 - axis2;
    const Vector3 rightBottom = position + axis1 - axis2;
    const Vector3 rightTop    = position + axis1 + axis2;
    const Vector3 leftTop     = position - axis1 + axis2;

    verticesBuffer[bufferIndex++] = leftBottom.x;
    verticesBuffer[bufferIndex++] = leftBottom.y;
    verticesBuffer[bufferIndex++] = leftBottom.z;
    verticesBuffer[bufferIndex++] = region->u1;
    verticesBuffer[bufferIndex++] = region->v2;

    verticesBuffer[bufferIndex++] = rightBottom.x;
    verticesBuffer[bufferIndex++] = rightBottom.y;
    verticesBuffer[bufferIndex++] = rightBottom.z;
    verticesBuffer[bufferIndex++] = region->u2;
    verticesBuffer[bufferIndex++] = region->v2;

    verticesBuffer[bufferIndex++] = rightTop.x;
    verticesBuffer[bufferIndex++] = rightTop.y;
    verticesBuffer[bufferIndex++] = rightTop.z;
    verticesBuffer[bufferIndex++] = region->u2;
    verticesBuffer[bufferIndex++] = region->v1;

    verticesBuffer[bufferIndex++] = leftTop.x;
    verticesBuffer[bufferIndex++] = leftTop.y;
    verticesBuffer[bufferIndex++] = leftTop.z;  
    verticesBuffer[bufferIndex++] = region->u1;
    verticesBuffer[bufferIndex++] = region->v1;
    numSprite++;  
  }