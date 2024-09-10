bool gui_filterbar_c::update_filter(const ts::wstr_c & e)
{
    ts::wstrings_c ospl( found_stuff.fsplit );
    found_stuff.fsplit.split<ts::wchar>(e, ' ');
    found_stuff.fsplit.trim();
    found_stuff.fsplit.kill_empty_fast();
    found_stuff.fsplit.case_down();

    // kill dups
    for(int i = found_stuff.fsplit.size() - 1;i>=0;--i)
    {
        for(int j = i-1;j>=0;--j)
            if ( found_stuff.fsplit.get(j).equals( found_stuff.fsplit.get(i) ) )
            {
                found_stuff.fsplit.remove_fast(i);
                break;
            }
    }

    // sort by length
    found_stuff.fsplit.sort([](const ts::wstr_c &s1,const ts::wstr_c &s2)->bool { return s1.get_length() == s2.get_length() ? (ts::wstr_c::compare(s1,s2) > 0) : s1.get_length() > s2.get_length(); });

    if (!tagschanged && found_stuff.fsplit == ospl)
        return true;

    if (current_search)
    {
        current_search->no_need = true;
        current_search = nullptr;
    }

    show_options(0 != found_stuff.fsplit.size());

    if (!tagschanged && is_all())
    {
        found_stuff.items.clear();
        gui_contactlist_c &cl = HOLD(getparent()).as<gui_contactlist_c>();
        cl.on_filter_deactivate(RID(),nullptr);
        return true;
    }

    if (search_in_messages && found_stuff.fsplit.size())
    {
        current_search = TSNEW( full_search_s, prf().get_db(), this, found_stuff.fsplit );
        found_stuff.items.clear();
        g_app->add_task( current_search );
    } else
        found_stuff.items.clear();


    active = g_app->active_contact_item ? &g_app->active_contact_item->getengine() : nullptr;

    if (!active)
    {
        gui_contactlist_c &cl = HOLD(getparent()).as<gui_contactlist_c>();
        active = cl.get_first_contact_item();
    }

    tagschanged = false;
    contact_index = 1;
    do_contact_check(RID(),nullptr);
    return true;
}