bool AsignacionModel::insertAsignacion (Asignacion asignacion)
{

    query->prepare("INSERT INTO "+TABLE_ASIGNACION+" ("
                                      "codigo,descripcion,forma,valor,formula,prima,activo,fechacreac) "
                                      "Values (:codigo,:descripcion,:forma,:valor,:formula,:prima,:activo,CURDATE());");

    query->bindValue(":codigo",asignacion.getCodigo());
    query->bindValue(":descripcion",asignacion.getDescripcion());
    query->bindValue(":forma",asignacion.getForma());
    query->bindValue(":valor",asignacion.getValor());
    query->bindValue(":formula",asignacion.getFormula());
    query->bindValue(":prima",asignacion.hasPrima());
    query->bindValue(":activo",asignacion.isActivo());

    if (!query->exec()){
        status = "Error al Insertar Concepto de Asignación: " + query->lastError().text();
        debugMessage(status);
        debugMessage(query->executedQuery());
        return false;
    }else {
        status = "Concepto de Asignación Insertado Exitosamente...";
        debugMessage(status);
        return true;
        }
}