static void
buildChoiceMenu(OCIO::ConstConfigRcPtr config,
                ChoiceParamType* choice,
                bool cascading,
                const std::string& name = "")
{
#ifdef DEBUG
    //printf("%p->resetOptions\n", (void*)choice);
#endif
    choice->resetOptions();
    assert(choice->getNOptions() == 0);
    if (!config) {
        return;
    }
    int def = -1;
    int defaultcs = config->getIndexForColorSpace(OCIO_NAMESPACE::ROLE_DEFAULT);
    int referencecs = config->getIndexForColorSpace(OCIO_NAMESPACE::ROLE_REFERENCE);
    int datacs = config->getIndexForColorSpace(OCIO_NAMESPACE::ROLE_DATA);
    int colorpickingcs = config->getIndexForColorSpace(OCIO_NAMESPACE::ROLE_COLOR_PICKING);
    int scenelinearcs = config->getIndexForColorSpace(OCIO_NAMESPACE::ROLE_SCENE_LINEAR);
    int compositinglogcs = config->getIndexForColorSpace(OCIO_NAMESPACE::ROLE_COMPOSITING_LOG);
    int colortimingcs = config->getIndexForColorSpace(OCIO_NAMESPACE::ROLE_COLOR_TIMING);
    int texturepaintcs = config->getIndexForColorSpace(OCIO_NAMESPACE::ROLE_TEXTURE_PAINT);
    int mattepaintcs = config->getIndexForColorSpace(OCIO_NAMESPACE::ROLE_MATTE_PAINT);
    for (int i = 0; i < config->getNumColorSpaces(); ++i) {
        std::string csname = config->getColorSpaceNameByIndex(i);
        std::string msg;
        // set the default value, in case the GUI uses it
        if (!name.empty() && csname == name) {
            def = i;
        }
        OCIO_NAMESPACE::ConstColorSpaceRcPtr cs = config->getColorSpace(csname.c_str());
        if (cascading) {
            std::string family = config->getColorSpace(csname.c_str())->getFamily();
            if (!family.empty()) {
                csname = family + "/" + csname;
            }
        }
        std::string csdesc = cs ? cs->getDescription() : "(no colorspace)";
        csdesc = whitespacify(trim(csdesc));
        int csdesclen = csdesc.size();
        if ( csdesclen > 0 ) {
            msg += csdesc;
        }
        bool first = true;
        int roles = 0;
        if (i == defaultcs) {
            msg += first ? " (" : ", ";
            msg += OCIO_NAMESPACE::ROLE_DEFAULT;
            first = false;
            ++roles;
        }
        if (i == referencecs) {
            msg += first ? " (" : ", ";
            msg += OCIO_NAMESPACE::ROLE_REFERENCE;
            first = false;
            ++roles;
        }
        if (i == datacs) {
            msg += first ? " (" : ", ";
            msg += OCIO_NAMESPACE::ROLE_DATA;
            first = false;
            ++roles;
        }
        if (i == colorpickingcs) {
            msg += first ? " (" : ", ";
            msg += OCIO_NAMESPACE::ROLE_COLOR_PICKING;
            first = false;
            ++roles;
        }
        if (i == scenelinearcs) {
            msg += first ? " (" : ", ";
            msg += OCIO_NAMESPACE::ROLE_SCENE_LINEAR;
            first = false;
            ++roles;
        }
        if (i == compositinglogcs) {
            msg += first ? " (" : ", ";
            msg += OCIO_NAMESPACE::ROLE_COMPOSITING_LOG;
            first = false;
            ++roles;
        }
        if (i == colortimingcs) {
            msg += first ? " (" : ", ";
            msg += OCIO_NAMESPACE::ROLE_COLOR_TIMING;
            first = false;
            ++roles;
        }
        if (i == texturepaintcs) {
            msg += first ? " (" : ", ";
            msg += OCIO_NAMESPACE::ROLE_TEXTURE_PAINT;
            first = false;
            ++roles;
        }
        if (i == mattepaintcs) {
            msg += first ? " (" : ", ";
            msg += OCIO_NAMESPACE::ROLE_MATTE_PAINT;
            first = false;
            ++roles;
        }
        if (roles > 0) {
            msg += ')';
        }
#ifdef DEBUG
        //printf("%p->appendOption(\"%s\",\"%s\") (%d->%d options)\n", (void*)choice, csname.c_str(), msg.c_str(), i, i+1);
#endif
        assert(choice->getNOptions() == i);
        choice->appendOption(csname, msg);
        assert(choice->getNOptions() == i+1);
    }
    if (def != -1) {
        choice->setDefault(def);
    }
}