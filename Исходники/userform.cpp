void UserForm:: createTableModels()
{
    QSqlRelationalTableModel* model = new QSqlRelationalTableModel();
    model->setTable("good");
    model->setRelation(Producer, QSqlRelation("company", "companyid", "name"));
    model->setRelation(Catalog, QSqlRelation("catalog", "id", "name"));

    model->setHeaderData(Producer, Qt::Horizontal, "Producer");
    model->setHeaderData(Name, Qt::Horizontal, "Name");
    model->setHeaderData(Price, Qt::Horizontal, "Price, $");
    model->setHeaderData(Description, Qt::Horizontal, "Description");
    model->setHeaderData(Catalog, Qt::Horizontal, "Catalog");
    model->setFilter("catalog_id IS NOT NULL");

//    model->removeColumn(5);
    model->select();
    productsModel = model;

    model = new QSqlRelationalTableModel();
    model->setTable("`order`");
    model->setRelation(goodId, QSqlRelation("good", "goodid", "name"));
    model->setFilter("user_login='******'");
    model->select();   

    model->setEditStrategy(QSqlTableModel::OnRowChange);
    model->removeColumn(3);
    model->removeColumn(2);
    model->setHeaderData(orderId, Qt::Horizontal, "Order #");
    model->setHeaderData(goodId, Qt::Horizontal, "Product");
    model->setHeaderData(date, Qt::Horizontal, "Date");
    model->setHeaderData(address, Qt::Horizontal, "Address to deliver");
    ordersModel = model;
}