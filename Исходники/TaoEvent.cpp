TaoStatus TaoEvent::getStringData(UtlString& data)
{
        if (!mStringData.isNull())
        {
                data.remove(0);
                data.append(mStringData.data());
        }

        return TAO_SUCCESS;
}