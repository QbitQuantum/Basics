void CmsController::list_operator(const QString &adminID)
{
    //QList<Operators> list_operator();
    Operators form;
    QList<Operators> operator_list = form.list_operator(adminID);
    texport(operator_list);
    //QString adminID = session().value("adminID").toString();
    texport(adminID);
    render("list_operator");

}