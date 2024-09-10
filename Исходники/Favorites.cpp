static void AppendFavMenuItems(HMENU m, DisplayState* f, UINT& idx, bool combined, bool isCurrent) {
    for (size_t i = 0; i < f->favorites->size(); i++) {
        if (i >= MAX_FAV_MENUS) {
            return;
        }
        Favorite* fn = f->favorites->at(i);
        fn->menuId = idx++;
        AutoFreeW s;
        if (combined) {
            s.Set(FavCompactReadableName(f, fn, isCurrent));
        } else {
            s.Set(FavReadableName(fn));
        }
        auto str = win::menu::ToSafeString(s);
        AppendMenuW(m, MF_STRING, (UINT_PTR)fn->menuId, str);
    }
}