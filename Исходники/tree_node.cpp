void Tree_Node::Print(OFormatter &txtfile, SynGram &gram, int offset, bool detailed) const
{
    int Offset = offset;

    if (offset > 0)
        txtfile.printf("%H ", offset);

    ilink.Print(txtfile, gram);

    if (node.IsNull())
        txtfile.printf("%vfC(null)%vn");
    else
        node->Print(txtfile, &gram, detailed);

    if (!child.Empty())
    {
        if (detailed)
        {
            txtfile.printf('.');

            if (child.size() != 1)
                txtfile.printf('{');
        }

        if (Offset != -1)
        {
            txtfile.eol();
            Offset++;
        }

        for (Container::size_type i = 0; i < child.size(); i++)
        {
            if (Offset == -1 && i)
                txtfile.printf(' ');

            if (Offset != -1)
                txtfile.printf("%H ", Offset);

            child[i].Print(txtfile, gram, Offset, detailed);
        }

        if (detailed)
        {
            if (offset != -1)
                txtfile.printf("%H ", Offset - 1);

            if (child.size() != 1)
                txtfile.printf('}');
        }
    }

    if (!dims.empty())
    {
        for (lem::Container::size_type i = 0; i < dims.size(); ++i)
        {
            const TreeDimension &d = *dims[i];
            txtfile.printf(' ');
            d.Print(gram.GetDict(), txtfile, detailed);
        }
    }

    if (detailed && !marks.empty())
    {
        txtfile.printf(" %vf6marks={%vn");

        for (lem::Container::size_type i = 0; i < marks.size(); ++i)
        {
            txtfile.printf(' ');
            marks[i]->Print(gram.GetDict(), txtfile);
        }

        txtfile.printf(" %vf6}%vn");
    }

    if (Offset != -1)
        txtfile.eol();

    return;
}