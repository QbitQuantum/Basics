bool ImplicitList::invoke(typed_list & in, optional_list & /*opt*/, int /*_iRetCount*/, typed_list & out, const ast::Exp & e)
{
    if (in.size() == 0)
    {
        out.push_back(this);
    }
    else
    {
        InternalType * _out = extract(&in);
        if (!_out)
        {
            std::wostringstream os;
            os << _W("Invalid index.\n");
            throw ast::InternalError(os.str(), 999, e.getLocation());
        }
        out.push_back(_out);
    }

    return true;
}