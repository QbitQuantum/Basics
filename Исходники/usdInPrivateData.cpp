PXR_NAMESPACE_OPEN_SCOPE


PxrUsdKatanaUsdInPrivateData::PxrUsdKatanaUsdInPrivateData(
        const UsdPrim& prim,
        PxrUsdKatanaUsdInArgsRefPtr usdInArgs,
        const PxrUsdKatanaUsdInPrivateData* parentData)
    : _prim(prim), _usdInArgs(usdInArgs), _extGb(0)
{
    // XXX: manually track instance and master path for possible
    //      relationship re-retargeting. This approach does not yet
    //      support nested instances -- which is expected to be handled
    //      via the forthcoming GetMasterWithContext.
    //
    if (prim.IsInstance())
    {
        if (prim.IsInMaster() && parentData)
        {
            SdfPath descendentPrimPath = 
                prim.GetPath().ReplacePrefix(
                    prim.GetPath().GetPrefixes()[0], 
                    SdfPath::ReflexiveRelativePath());

            _instancePath = parentData->GetInstancePath().AppendPath(
                descendentPrimPath);
        }
        else
        {
            _instancePath = prim.GetPath();
        }

        const UsdPrim& masterPrim = prim.GetMaster();            
        if (masterPrim)
        {
            _masterPath = masterPrim.GetPath();
        }
    }
    else if (parentData)
    {
        // Pass along instance and master paths to children.
        //
        if (!parentData->GetInstancePath().IsEmpty())
        {
            _instancePath = parentData->GetInstancePath();
        }

        if (!parentData->GetMasterPath().IsEmpty())
        {
            _masterPath = parentData->GetMasterPath();
        }
    }

    //
    // Apply session overrides for motion.
    //

    const std::string primPath = prim.GetPrimPath().GetString();
    const std::string isolatePath = usdInArgs->GetIsolatePath();
    const std::string sessionPath = usdInArgs->GetSessionLocationPath();
    FnKat::GroupAttribute sessionAttr = usdInArgs->GetSessionAttr();

    // XXX: If an isolatePath has been specified, it means the PxrUsdIn is
    // probably loading USD contents below the USD root. This can prevent
    // overrides from trickling down the hierarchy, e.g. the overrides for /A/B
    // won't get applied to children if the isolatePath is /A/B/C/D.
    //
    // So, if the usdInArgs suggest that an isolatePath has been specified and
    // we don't have any parentData, we'll need to check if there are overrides
    // for the prim and any of its parents.
    //
    std::vector<std::string> pathsToCheck;
    if (!parentData and !isolatePath.empty() and
        pystring::startswith(primPath, isolatePath+"/"))
    {
        std::vector<std::string> parentLocs;
        Foundry::Katana::Util::Path::GetLocationStack(parentLocs, primPath);
        std::reverse(std::begin(parentLocs), std::end(parentLocs));
        for (size_t i = 0; i < parentLocs.size(); ++i)
        {
            pathsToCheck.push_back(FnKat::DelimiterEncode(
                    sessionPath + parentLocs[i]));
        }
    }
    else
    {
        pathsToCheck.push_back(FnKat::DelimiterEncode(sessionPath + primPath));
    }

    //
    // If a session override is specified, use its value. If no override exists,
    // try asking the parent data for its value. Otherwise, fall back on the
    // usdInArgs value.
    //

    bool overrideFound;

    // Current time.
    //
    overrideFound = false;
    for (size_t i = 0; i < pathsToCheck.size(); ++i)
    {
        FnKat::FloatAttribute currentTimeAttr =
            sessionAttr.getChildByName(
                "overrides."+pathsToCheck[i]+".currentTime");
        if (currentTimeAttr.isValid())
        {
            _currentTime = currentTimeAttr.getValue();
            overrideFound = true;
            break;
        }
    }
    if (!overrideFound)
    {
        if (parentData)
        {
            _currentTime = parentData->GetCurrentTime();
        }
        else
        {
            _currentTime = usdInArgs->GetCurrentTime();
        }
    }

    // Shutter open.
    //
    overrideFound = false;
    for (size_t i = 0; i < pathsToCheck.size(); ++i)
    {
        FnKat::FloatAttribute shutterOpenAttr =
                sessionAttr.getChildByName(
                    "overrides."+pathsToCheck[i]+".shutterOpen");
        if (shutterOpenAttr.isValid())
        {
            _shutterOpen = shutterOpenAttr.getValue();
            overrideFound = true;
            break;
        }
    }
    if (!overrideFound)
    {
        if (parentData)
        {
            _shutterOpen = parentData->GetShutterOpen();
        }
        else
        {
            _shutterOpen = usdInArgs->GetShutterOpen();
        }
    }

    // Shutter close.
    //
    overrideFound = false;
    for (size_t i = 0; i < pathsToCheck.size(); ++i)
    {
        FnKat::FloatAttribute shutterCloseAttr =
                sessionAttr.getChildByName(
                    "overrides."+pathsToCheck[i]+".shutterClose");
        if (shutterCloseAttr.isValid())
        {
            _shutterClose = shutterCloseAttr.getValue();
            overrideFound = true;
            break;
        }
    }
    if (!overrideFound)
    {
        if (parentData)
        {
            _shutterClose = parentData->GetShutterClose();
        }
        else
        {
            _shutterClose = usdInArgs->GetShutterClose();
        }
    }

    // Motion sample times.
    //
    // Fallback logic is a little more complicated for motion sample times, as
    // they can vary per attribute, so store both the overridden and the
    // fallback motion sample times for use inside GetMotionSampleTimes.
    //
    for (size_t i = 0; i < pathsToCheck.size(); ++i)
    {
        FnKat::Attribute motionSampleTimesAttr =
                sessionAttr.getChildByName(
                    "overrides."+pathsToCheck[i]+".motionSampleTimes");
        if (motionSampleTimesAttr.isValid())
        {
            // Interpret an IntAttribute as "use usdInArgs defaults"
            //
            if (motionSampleTimesAttr.getType() == kFnKatAttributeTypeInt)
            {
                _motionSampleTimesOverride = usdInArgs->GetMotionSampleTimes();
                break;
            }
            // Interpret a FloatAttribute as an explicit value override
            //
            if (motionSampleTimesAttr.getType() == kFnKatAttributeTypeFloat)
            {
                const auto& sampleTimes = FnKat::FloatAttribute(
                        motionSampleTimesAttr).getNearestSample(0);
                if (!sampleTimes.empty())
                {
                    for (float sampleTime : sampleTimes)
                        _motionSampleTimesOverride.push_back(
                            (double)sampleTime);
                    break;
                }
            }
        }
    }
    if (parentData)
    {
        _motionSampleTimesFallback = parentData->GetMotionSampleTimes();
    }
    else
    {
        _motionSampleTimesFallback = usdInArgs->GetMotionSampleTimes();
    }
}