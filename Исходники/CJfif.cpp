void CJfif::WriteFile(const char* fileName)
{
    fopen_s(&fp, fileName, "wb");
    ASSERT(0 != fp);

    WriteWord(SOI_marker);

    WriteWord(APP0.marker);
    WriteWord(APP0.len);
    WriteByte(APP0.JFIF[0]);
    WriteByte(APP0.JFIF[1]);
    WriteByte(APP0.JFIF[2]);
    WriteByte(APP0.JFIF[3]);
    WriteByte(APP0.JFIF[4]);
    WriteWord(APP0.version);
    WriteByte(APP0.density_unit);
    WriteWord(APP0.Xdensity);
    WriteWord(APP0.Ydensity);
    WriteWord(APP0.thumbnail);

    JFIF_DQT *dqt[2];
    dqt[0] = &DQT_Luma;
    dqt[1] = &DQT_Chroma;
    for (int i=0; i<2; i++)
    {
        WriteWord(dqt[i]->marker);
        WriteWord(dqt[i]->len);
        WriteByte(dqt[i]->id);
        for (int j=0; j<64; j++)
        {
            WriteByte(dqt[i]->data[j]);
        }
    }

    WriteWord(SOF0.marker);
    WriteWord(SOF0.len);
    WriteByte(SOF0.precision);
    WriteWord(SOF0.height);
    WriteWord(SOF0.width);
    WriteByte(SOF0.num_comp);
    WriteByte(SOF0.Y.id);
    WriteByte(SOF0.Y.sample);
    WriteByte(SOF0.Y.quant_table_id);
    WriteByte(SOF0.Cb.id);
    WriteByte(SOF0.Cb.sample);
    WriteByte(SOF0.Cb.quant_table_id);
    WriteByte(SOF0.Cr.id);
    WriteByte(SOF0.Cr.sample);
    WriteByte(SOF0.Cr.quant_table_id);

    JFIF_DHT *dht[4];
    dht[0] = &DHT_Luma_dc;
    dht[1] = &DHT_Chroma_dc;
    dht[2] = &DHT_Luma_ac;    
    dht[3] = &DHT_Chroma_ac;
    for (int i=0; i<4; i++)
    {
        WriteWord(dht[i]->marker);
        WriteWord(dht[i]->len);
        WriteByte(dht[i]->id);
        for (int j=0; j<16; j++)
        {
            WriteByte(dht[i]->bits[j]);
        }
        for (int j=0; j<dht[i]->size_var; j++)
        {
            WriteByte(dht[i]->var[j]);
        }
    }

    WriteWord(SOS.marker);
    WriteWord(SOS.len);
    WriteByte(SOS.num_comp);
    WriteWord(SOS.luma);
    WriteWord(SOS.chroma1);
    WriteWord(SOS.chroma2);
    WriteByte(SOS.spectral[0]);
    WriteByte(SOS.spectral[1]);
    WriteByte(SOS.spectral[2]);

    for (int i=0; i<data_size; i++)
    {
        WriteByte(data[i]);
    }

    WriteWord(EOI_marker);
    fclose(fp);
}