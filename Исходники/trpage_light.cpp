bool trpgLightTable::Read(trpgReadBuffer &buf)
{
    int32        numLights;
    trpgToken    lightTok;
    int32        len;

    try {
        buf.Get(numLights);
        for (int i=0;i<numLights;i++) {
            buf.GetToken(lightTok,len);
            if (lightTok != TRPGLIGHTATTR) throw 1;
            buf.PushLimit(len);
            trpgLightAttr light;// = lightList[i];
            bool status = light.Read(buf);
            buf.PopLimit();
            if (!status) throw 1;
            AddLightAttr(light);
        }
    }
    catch (...) {
        return false;
    }

    return true;
}