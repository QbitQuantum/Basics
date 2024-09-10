static void notify_back(struct datawindow_priv *datawindow, int param1, int param2)
{
    switch (datawindow->currentSearchState)
    {
    case attr_country_name:
    break;
    case attr_town_name:
    {
        datawindow->currentSearchState = attr_country_name;
    }
    break;
    case attr_street_name:
    {
        datawindow->currentSearchState = attr_town_name;
    }
    break;
    default:
        break;

    }

    setlayout(datawindow);
}