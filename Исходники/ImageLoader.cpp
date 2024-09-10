bool ImageLoader::OverrideByName(const std::string& name, const std::shared_ptr<LunaImage>& img)
{
    // If we're mapping through an HDC, find it for this image name
    {
        auto it = m_NameToHDC.find(name);
        if (it != m_NameToHDC.end()) {
            if (img)
            {
                m_GfxOverride[it->second] = img;
            }
            else
            {
                m_GfxOverride.erase(it->second);
            }

            // Update height/width based on override
            auto categoryIterator = m_HDCToCategoryAndIndex.find(it->second);
            if (categoryIterator != m_HDCToCategoryAndIndex.end())
            {
                const SMBXImageCategory* category = categoryIterator->second.first;
                uint32_t idx = categoryIterator->second.second;

                if (img)
                {
                    category->setHeight(idx, img->getH());
                    category->setWidth(idx, img->getW());
                }
                else
                {
                    auto currentImg = ImageLoader::GetByName(name);
                    if (currentImg)
                    {
                        category->setHeight(idx, currentImg->getH());
                        category->setWidth(idx, currentImg->getW());
                    }
                }
            }

            return true;
        }
    }

    // Otherwise, for "extra gfx" we're mapping directly from name to image, so set the override that way
    if (m_ExtraGfx.find(name) != m_ExtraGfx.end())
    {
        if (img)
        {
            m_ExtraGfxOverride[name] = img;
        }
        else
        {
            m_ExtraGfxOverride.erase(name);
        }

        return true;
    }

    return false;
}