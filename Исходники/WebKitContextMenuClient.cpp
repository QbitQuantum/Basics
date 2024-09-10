    bool getContextMenuFromProposedMenu(WebPageProxy&, const Vector<RefPtr<WebContextMenuItem>>& proposedMenu, Vector<RefPtr<WebContextMenuItem>>&, const WebHitTestResultData& hitTestResultData, API::Object* userData) override
    {
        GRefPtr<GVariant> variant;
        if (userData) {
            ASSERT(userData->type() == API::Object::Type::String);
            CString userDataString = static_cast<API::String*>(userData)->string().utf8();
            variant = adoptGRef(g_variant_parse(nullptr, userDataString.data(), userDataString.data() + userDataString.length(), nullptr, nullptr));
        }

        Vector<WebContextMenuItemData> menuItems;
        menuItems.reserveInitialCapacity(proposedMenu.size());
        for (auto& item : proposedMenu)
            menuItems.uncheckedAppend(*item->data());
        webkitWebViewPopulateContextMenu(m_webView, menuItems, hitTestResultData, variant.get());
        return true;
    }