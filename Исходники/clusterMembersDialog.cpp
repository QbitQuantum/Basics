clusterMembersDialog::clusterMembersDialog(QWidget *parent, FWObject *o)
    : QDialog(parent), table_update(false)
{
    m_dialog = new Ui::clusterMembersDialog_q;
    m_dialog->setupUi(this);
    setWindowModality(Qt::WindowModal);

    // assign clustergroup object
    obj = o;
    FWObject *parent_host = Host::getParentHost(obj);
    host_os = parent_host->getStr("host_OS").c_str();
    platform = parent_host->getStr("platform").c_str();

    // if empty, retry with parent of parent (interface level)
    if (host_os.isEmpty())
    {
        FWObject *parent = NULL;
        parent = obj->getParent();
        if (parent == NULL)
        {
            throw FWException("clusterMembersDialog: parent is NULL!");
        }
        parent = parent->getParent();
        if (parent == NULL)
        {
            throw FWException("clusterMembersDialog: parent is NULL!");
        }
        host_os = parent->getStr("host_OS").c_str();
        platform = parent->getStr("platform").c_str();
    }

    string type = obj->getStr("type");
    enable_master_column = Resources::os_res[host_os.toStdString()]->getResourceBool(
        "/FWBuilderResources/Target/protocols/" + type + "/needs_master");
    if (!enable_master_column) m_dialog->fwSelectedTable->hideColumn(2);

    // prepare lists of firewalls (selected, available)
    getSelectedMembers();
    getPossibleMembers();

    // init views
    updateAvailableTree();
    updateSelectedTable();
}