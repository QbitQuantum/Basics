void Particionador::particionarDatos()
{

    int cantidad_entrenamiento = floor(_cantidad_datos * _porcentaje_entrenamiento );
    int cantidad_validacion = floor( cantidad_entrenamiento * _porcentaje_validacion );
    int cantidad_prueba = _cantidad_datos - cantidad_entrenamiento;
    cantidad_entrenamiento-=cantidad_validacion;

    for( int p=0; p<_cant_particiones; p++ ) {
        Particionador::particion part;

        QVector<int> temporal;
        for( int i=0; i<_cantidad_datos; i++ ) {
            temporal.append( i );
        }

        for( int j=0; j<cantidad_entrenamiento; j++ ) {
            int pos = valor_random( 0, temporal.size() );
            part.entrenamiento.append( temporal.at( pos ) );
            temporal.remove( pos );
        }

        for( int j=0; j<cantidad_validacion; j++ ) {
            int pos = valor_random( 0, temporal.size() );
            part.validacion.append( temporal.at( pos ) );
            temporal.remove( pos );
        }


        for( int j=0; j<cantidad_prueba; j++ ) {
            int pos = valor_random( 0, temporal.size() );
            part.prueba.append( temporal.at( pos ) );
            temporal.remove( pos );
        }

        _particiones.append( part );
    }
}