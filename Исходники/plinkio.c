pio_status_t
pio_transpose(const char *plink_file_prefix, const char *transposed_file_prefix)
{
    struct pio_file_t plink_file;
    if( pio_open( &plink_file, plink_file_prefix ) != PIO_OK )
    {
        return PIO_ERROR;
    }

    char *bed_path = concatenate( plink_file_prefix, ".bed" );
    char *transposed_bed_path = concatenate( transposed_file_prefix, ".bed" );

    pio_status_t status = bed_transpose( bed_path, transposed_bed_path, pio_num_loci( &plink_file ), pio_num_samples( &plink_file ) );
    if( status == PIO_OK )
    {
        char *fam_path = concatenate( plink_file_prefix, ".fam" );
        char *transposed_fam_path = concatenate( transposed_file_prefix, ".fam" );
        file_copy( fam_path, transposed_fam_path );
        free( fam_path );
        free( transposed_fam_path );
        
        char *bim_path = concatenate( plink_file_prefix, ".bim" );
        char *transposed_bim_path = concatenate( transposed_file_prefix, ".bim" );
        file_copy( bim_path, transposed_bim_path );
        free( bim_path );
        free( transposed_bim_path );
    }

    pio_close( &plink_file );

    free( bed_path );
    free( transposed_bed_path );

    return status;
}