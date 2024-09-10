void BlobMesh::update()
{
    float curSeconds =  ofGetElapsedTimef();
    //move the blobs
    for( vector<Weight>::iterator cIt = mWeights.begin(); cIt != mWeights.end(); ++cIt )
    {
        cIt->move(ofVec2f(mMeshWidth,
                        mMeshHeight));
    }
    
//    gl::VboMesh::VertexIter iter = mVboMesh->mapVertexBuffer();
    vector<uint32_t> indices;

    for( int x = 0; x < mMeshWidth; ++x )
    {
        for( int y = 0; y < mMeshHeight; ++y )
        {
            mVertexVals[x][y] *= .5;
            for( vector<Weight>::iterator cIt = mWeights.begin(); cIt != mWeights.end(); ++cIt )
            {
                float val = (cIt->pos - ofVec2f(x,y)).length();
                val = 10/(val*val);
                mVertexVals[x][y] += val;
            }
            mVertColors[x+y*mMeshWidth] = ofFloatColor((sin(curSeconds*8+sqrt(mVertexVals[x][y])*100)+1)/2,
                                                       (sin(curSeconds + x/100.f)+1)/2,
                                                       (sin(curSeconds - y/8.f)+1)/2,
                                                       (sin((mVertexVals[x][y])*100)+1)/2);
//            ++iter;
        }
    }
    mVboMesh.updateColorData(mVertColors, mMeshWidth*mMeshHeight);
    float threshhold = .025f;
    for( int x = 0; x < mMeshWidth; ++x )
    {
        for( int y = 0; y < mMeshHeight; ++y )
        {
            if(cos(curSeconds+x/5.4 + 10*sin(y/12.1) ) > (-1.5*(sin(curSeconds/15.1))-.7))
            if(x+1 < mMeshWidth && y+1 < mMeshHeight )
            {
                if(mVertexVals[x][y] > threshhold && mVertexVals[x+1][y] > threshhold && mVertexVals[x][y+1] > threshhold)
                {
//                    //indices.push_back(y*mMeshWidth+x);
//                    //indices.push_back(y*mMeshWidth+x+1);
//                    //indices.push_back((y+1)*mMeshWidth+x+1);
//                    indices.push_back(x*mMeshHeight+y);
//                    indices.push_back((x+1)*mMeshHeight+y+1);
//                    indices.push_back((x+1)*mMeshHeight+y);
                }
                if(mVertexVals[x][y] > threshhold && mVertexVals[x+1][y+1] > threshhold && mVertexVals[x][y+1] > threshhold)
                {
//                    indices.push_back(x*mMeshHeight+y);
//                    indices.push_back(x*mMeshHeight+y+1);
//                    indices.push_back((x+1)*mMeshHeight+y+1);
//                    //indices.push_back(y*mMeshWidth+x);
//                    //indices.push_back((y+1)*mMeshWidth+x+1);
//                    //indices.push_back((y+1)*mMeshWidth+x);
                }
            }
            // the texture coordinates are mapped to [0,1.0)
            //                texCoords.push_back( Vec2f( x / (float)VERTICES_X, y / (float)VERTICES_Z ) );
        }
    }
//    mVboMesh->bufferIndices(indices);
}