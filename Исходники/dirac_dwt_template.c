static int RENAME(ff_spatial_idwt_init)(DWTContext *d, enum dwt_type type)
{
    int level;

    d->temp = (uint8_t *)(((TYPE *)d->temp) + 8);

    for (level = d->decomposition_count - 1; level >= 0; level--){
        int hl = d->height >> level;
        int stride_l = d->stride << level;

        switch(type){
            case DWT_DIRAC_DD9_7:
                RENAME(spatial_compose_dd97i_init)(d->cs+level, d->buffer, hl, stride_l);
                break;
            case DWT_DIRAC_LEGALL5_3:
                RENAME(spatial_compose53i_init)(d->cs+level, d->buffer, hl, stride_l);
                break;
            case DWT_DIRAC_DD13_7:
                RENAME(spatial_compose_dd137i_init)(d->cs+level, d->buffer, hl, stride_l);
                break;
            case DWT_DIRAC_HAAR0:
            case DWT_DIRAC_HAAR1:
                d->cs[level].y = 1;
                break;
            case DWT_DIRAC_DAUB9_7:
                RENAME(spatial_compose97i_init)(d->cs+level, d->buffer, hl, stride_l);
                break;
            default:
                d->cs[level].y = 0;
                break;
        }
    }

    switch (type) {
        case DWT_DIRAC_DD9_7:
            d->spatial_compose = RENAME(spatial_compose_dd97i_dy);
            d->vertical_compose_l0 = (void*)RENAME(vertical_compose53iL0);
            d->vertical_compose_h0 = (void*)RENAME(vertical_compose_dd97iH0);
            d->horizontal_compose = RENAME(horizontal_compose_dd97i);
            d->support = 7;
            break;
        case DWT_DIRAC_LEGALL5_3:
            d->spatial_compose = RENAME(spatial_compose_dirac53i_dy);
            d->vertical_compose_l0 = (void*)RENAME(vertical_compose53iL0);
            d->vertical_compose_h0 = (void*)RENAME(vertical_compose_dirac53iH0);
            d->horizontal_compose = RENAME(horizontal_compose_dirac53i);
            d->support = 3;
            break;
        case DWT_DIRAC_DD13_7:
            d->spatial_compose = RENAME(spatial_compose_dd137i_dy);
            d->vertical_compose_l0 = (void*)RENAME(vertical_compose_dd137iL0);
            d->vertical_compose_h0 = (void*)RENAME(vertical_compose_dd97iH0);
            d->horizontal_compose = RENAME(horizontal_compose_dd137i);
            d->support = 7;
            break;
        case DWT_DIRAC_HAAR0:
        case DWT_DIRAC_HAAR1:
            d->spatial_compose = RENAME(spatial_compose_haari_dy);
            d->vertical_compose = (void*)RENAME(vertical_compose_haar);
            if (type == DWT_DIRAC_HAAR0)
                d->horizontal_compose = RENAME(horizontal_compose_haar0i);
            else
                d->horizontal_compose = RENAME(horizontal_compose_haar1i);
            d->support = 1;
            break;
        case DWT_DIRAC_FIDELITY:
            d->spatial_compose = RENAME(spatial_compose_fidelity);
            d->vertical_compose_l0 = (void*)RENAME(vertical_compose_fidelityiL0);
            d->vertical_compose_h0 = (void*)RENAME(vertical_compose_fidelityiH0);
            d->horizontal_compose = RENAME(horizontal_compose_fidelityi);
            d->support = 0; // not really used
            break;
        case DWT_DIRAC_DAUB9_7:
            d->spatial_compose = RENAME(spatial_compose_daub97i_dy);
            d->vertical_compose_l0 = (void*)RENAME(vertical_compose_daub97iL0);
            d->vertical_compose_h0 = (void*)RENAME(vertical_compose_daub97iH0);
            d->vertical_compose_l1 = (void*)RENAME(vertical_compose_daub97iL1);
            d->vertical_compose_h1 = (void*)RENAME(vertical_compose_daub97iH1);
            d->horizontal_compose = RENAME(horizontal_compose_daub97i);
            d->support = 5;
            break;
        default:
            return AVERROR_INVALIDDATA;
    }

    return 0;
}