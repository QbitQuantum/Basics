void ossimVpfAnnotationCoverageInfo::buildCoverage(const ossimString& feature)
{
    deleteAllFeatures();
    if(theLibrary)
    {
        ossimVpfCoverage coverage;

        if(theLibrary->getCoverage(theName, coverage))
        {
            ossimVpfFeatureClassSchema schema;
            if(coverage.openFeatureClassSchema(schema))
            {
                std::vector<ossimString> featureClassArray;
                schema.getFeatureClasses(featureClassArray);
                schema.closeTable();
                for(ossim_uint32  idx = 0; idx < featureClassArray.size(); ++idx)
                {
                    ossimString s1 = feature;
                    ossimString s2 = featureClassArray[idx];
                    s1.downcase();
                    s2.downcase();
                    if (! feature.length() || (s1 == s2) )
                    {
                        ossimVpfAnnotationFeatureInfo* featureInfo =
                            new ossimVpfAnnotationFeatureInfo;
                        featureInfo->setName(featureClassArray[idx]);
                        featureInfo->setCoverage(coverage);
                        theFeatureInfoArray.push_back(featureInfo);
                        featureInfo->buildFeature();
                    }
                }
            }
        }
    }
}