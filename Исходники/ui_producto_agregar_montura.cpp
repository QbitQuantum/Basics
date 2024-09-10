void ui_producto_agregar_montura::tipoEditar(Montura & montura_editar)
{

    //Recibe la montura nueva y cambia lo campos
    ui->lineEdit_codigo->setText(montura_editar.getCodigo());
    ui->lineEdit_stock->setText(QString::number(montura_editar.getStock()));
    ui->lineEdit_precio_compra->setText(QString::number(montura_editar.getPrecioCompra()));
    ui->lineEdit_precio_venta->setText(QString::number(montura_editar.getPrecioVenta()));
    ui->lineEdit_p_descuento->setText(QString::number(montura_editar.getP_descuento()));
    ui->lineEdit_accesorios->setText(montura_editar.getAccesorios());
    ui->lineEdit_descripcion->setText(montura_editar.getDescripcion());


    int posM=ui->myComboBox_marca->findText(montura_editar.getMarca().getNombre());
    ui->myComboBox_marca->setCurrentIndex(posM);

    int posT=ui->comboBox_tamanio->findText(montura_editar.getTamanio().getNombre());
    ui->comboBox_tamanio->setCurrentIndex(posT);

    int posF=ui->comboBox_forma->findText(montura_editar.getForma().getNombre());
    ui->comboBox_forma->setCurrentIndex(posF);

    int posC=ui->comboBox_calidad->findText(montura_editar.getCalidad().getNombre());
    ui->comboBox_calidad->setCurrentIndex(posC);

    int posCo=ui->comboBox_color->findText(montura_editar.getColor().getNombre());
    ui->comboBox_color->setCurrentIndex(posCo);

    Montura_Editar=montura_editar;
    editar=true;

    ui->pushButton_agregar->setText("Guardar");
    ui->label_tiulo->setText("Editar Montura");
}