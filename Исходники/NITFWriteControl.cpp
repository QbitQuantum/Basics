void NITFWriteControl::addUserDefinedSubheader(
        const six::Data& data,
        nitf::DESubheader& subheader) const
{
    // If NITRO doesn't know this TRE (because our plugin path isn't set),
    // we won't actually get an exception in the TRE constructor because it'll
    // use a default handler for the TRE.  Instead, we'll get a no such key
    // exception when it doesn't know what the fields below are.  try/catch
    // this so we can supply a more obvious error message.
    nitf::TRE tre(Constants::DES_USER_DEFINED_SUBHEADER_TAG,
                  Constants::DES_USER_DEFINED_SUBHEADER_ID);

    try
    {
        tre["DESCRC"] = "99999";
        tre["DESSHFT"] = "XML";
        tre["DESSHDT"] = data.getCreationTime().format("%Y-%m-%dT%H:%M:%SZ");
        setField("DESSHRP", mOrganizationId, tre);

        const std::string dataType =
                (data.getDataType() == DataType::COMPLEX) ? "SICD" : "SIDD";
        tre["DESSHSI"] = dataType +
                " Volume 1 Design & Implementation Description Document";

        // This is the publication date and version of the
        // Design and Implementation Description Document 
        // for the specification -- Add to this list as more
        // versions are published
        const std::string version(data.getVersion());
        std::string specVers;
        std::string specDT;
        if (dataType == "SICD")
        {    
            if (version == "1.0.0" || version == "1.0.1")
            {
                specVers = "1.0";
                specDT = "2011-09-28T00:00:00Z";
            }
            else if (version == "1.1.0")
            {
                specVers = "1.1";
                specDT = "2014-07-08T00:00:00Z";
            }
        }
        else if (dataType == "SIDD")
        {
            if (version == "1.0.0")
            {
                specVers = "1.0";
                specDT = "2011-08-01T00:00:00Z";
            }
        }

        // spec version
        if (specVers.empty())
        {
            throw except::Exception(Ctxt(
                "DESSHSV Failure - Unsupported in " + dataType +
                " version: " + version));
        }
        tre["DESSHSV"] = specVers;

        // spec publication Date/Time
        if (specDT.empty())
        {
            throw except::Exception(Ctxt(
                "DESSHSD Failure - Unsupported in " + dataType +
                " version: " + version));
        }
        tre["DESSHSD"] = specDT;

        tre["DESSHTN"] = "urn:" + dataType + ":" + version;
        tre["DESSHLPG"] = toString(data.getImageCorners());

        // Spec specifies leaving this blank
        tre["DESSHLPT"] = "";

        setField("DESSHLI", mLocationId, tre);
        setField("DESSHLIN", mLocationIdNamespace, tre);
        setField("DESSHABS", mAbstract, tre);
    }
    catch (const except::NoSuchKeyException& )
    {
        throw except::NoSuchKeyException(Ctxt(
                "Must have '" +
                std::string(Constants::DES_USER_DEFINED_SUBHEADER_TAG) +
                "' plugin on the plugin path.  Either set the "
                "NITF_PLUGIN_PATH environment variable or use "
                "six::loadPluginDir()"));
    }
    subheader.setSubheaderFields(tre);
}