// ------------------------------------------------------------------------------------------------
Texture2D* TextureManager::allocTexture2D(GLsizei levels, GLenum internalformat, GLsizei width, GLsizei height)
{
    Texture2DContainer* memArray = nullptr;

    auto texType = std::make_tuple(levels, internalformat, width, height);
    auto arrayIt = mTexArrays2D.find(texType);
    if (arrayIt == mTexArrays2D.end()) {
        mTexArrays2D[texType] = std::vector<Texture2DContainer*>();
        arrayIt = mTexArrays2D.find(texType);
        assert(arrayIt != mTexArrays2D.end());
    }

    for (auto it = arrayIt->second.begin(); it != arrayIt->second.end(); ++it) {
        if ((*it)->hasRoom()) {
            memArray = (*it);
            break;
        }
    }

    if (memArray == nullptr) {
        memArray = new Texture2DContainer(mSparse, levels, internalformat, width, height, mMaxTextureArrayLevels);
        arrayIt->second.push_back(memArray);
    }

    assert(memArray);
    return new Texture2D(memArray, memArray->virtualAlloc());
}