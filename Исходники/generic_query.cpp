void GenericQuery::
clearIntegerCategory (SimpleList<int> &int_category)
{
    int item;

    int_category.Rewind ();
    while (int_category.Next (item))
        int_category.DeleteCurrent ();
}