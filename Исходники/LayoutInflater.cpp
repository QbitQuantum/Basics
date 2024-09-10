    /* [in] */ IViewGroup* root,
    /* [in] */ Boolean attachToRoot,
    /* [out] */ IView** view)
{
    VALIDATE_NOT_NULL(view)

    if (DEBUG) {
        Slogger::D(TAG, "Inflate from resource: %08x", resource);
    }

    AutoPtr<IContext> ctx;
    GetContext((IContext**)&ctx);
    AutoPtr<IResources> res;
    ASSERT_SUCCEEDED(ctx->GetResources((IResources**)&res));
    AutoPtr<IXmlResourceParser> parser;
    ASSERT_SUCCEEDED(res->GetLayout(resource, (IXmlResourceParser**)&parser));
    ECode ec = Inflate(IXmlPullParser::Probe(parser), root, attachToRoot, view);
    parser->Close();
    return ec;
}

ECode LayoutInflater::Inflate(
    /* [in] */ IXmlPullParser* parser,
    /* [in] */ IViewGroup* root,
    /* [in] */ Boolean attachToRoot,
    /* [out] */ IView** view)
{
    VALIDATE_NOT_NULL(view)

    AutoLock lock(mConstructorArgsLock);
    AutoPtr<IAttributeSet> attrs = Xml::AsAttributeSet(parser);