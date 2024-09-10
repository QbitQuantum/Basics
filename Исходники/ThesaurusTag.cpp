void ThesaurusTag::Save_SQL(OFormatter &out, const SQL_Production &sql_version) const
{
    out.printf("INSERT INTO sg_tag( id, name ) VALUES ( %d, %us'%us' );\n"
        , id, sql_version.GetNPrefix(), sql_version.SqlStr(name).c_str());

    for (lem::Container::size_type i = 0; i < values.size(); ++i)
    {
        out.printf("INSERT INTO sg_tag_value( id_tag, ivalue, name ) VALUES ( %d, %d, %us'%us' );\n",
            id, ivalues[i], sql_version.GetNPrefix(), sql_version.SqlStr(values[i]).c_str());
    }

    return;
}