void InfoBox::GenerateAbilityString()
{
    f_infoBuffer->insert_at_cursor( "Name: " );
    f_infoBuffer->insert_at_cursor( f_char->name() );
    f_infoBuffer->insert_at_cursor( " " );
    Glib::RefPtr<Gtk::TextChildAnchor> refAnchor = f_infoBuffer->create_child_anchor(f_infoBuffer->end());
    Gtk::Button* editBtn = Gtk::manage( new Gtk::Button("Edit") );
    editBtn->signal_clicked().connect( sigc::mem_fun( *this, &InfoBox::OnEditCharacter ) );
    //editBtn->set_sensitive( true );
    add_child_at_anchor( *editBtn, refAnchor );
    f_infoBuffer->insert_at_cursor( "\n" );
    editBtn->show_all();

    auto statMgr( GetStatMgr().lock() );
    assert(statMgr);

    auto       iter (statMgr->GetStats().begin());
    const auto end  (statMgr->GetStats().end()  );

    while( iter != end )
    {
        Stat::pointer_t stat ( iter->second );
        Value::pointer_t value ( f_char->getStat( stat->id() ) );

        const bool last = (++iter == end);

        if( !stat->ability() ) continue;
#if 0
        if( stat->enabled() )
        {
#endif
            AddAttribute( stat->name(), value->total() );
            AddModifier( Common::StatToMod( value->total() ) );
#if 0
        }
        else
        {
            AddAttribute( stat->name(), "--" );
        }
#endif

        if( last )
        {
            AddCR();
        }
        else
        {
            AddComma();
        }
    }
}