CBNet* ConvertFromDSLNet(const std::string& filename)
{
    DSL_network dslNet;

    if( dslNet.ReadFile(const_cast<char*>(dslFilename(filename).c_str()))
        != DSL_OKAY )
    {
        std::cout << " can't read DSL model file named "
            << dslFilename(filename).c_str() << std::endl;

        return NULL;
    }

    // Convert DSL to PNL
    DSLPNLConverter DPConverter;

    CBNet* pnlNet;

    pnlNet = DPConverter.CreateBNet(dslNet);

    if( pnlNet == NULL )
    {
        std::cout << " Conversion DSL->PNL failed. " << std::endl;

        return NULL;
    }

    return pnlNet;
}