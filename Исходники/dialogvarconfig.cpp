void DialogVarConfig::eliminar()
{
    datos.removeAt(index);
    QFile f;
    f.setFileName("scriptsconfig");
    f.remove();
    f.open(QIODevice::WriteOnly);
    f.write(datos.join("\n").toLatin1());
    f.waitForBytesWritten(0);
    f.close();
    cargarDatos();
}