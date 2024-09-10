ib_status_t ib_field_convert(
    ib_mpool_t        *mp,
    const ib_ftype_t   desired_type,
    const ib_field_t  *in_field,
    ib_field_t       **out_field
)
{
    assert(mp);
    assert(in_field);

    ib_status_t rc;

    /* Holder values for in_field values before being set in out_field. */
    size_t sz;
    const char *str;
    const ib_bytestr_t *bstr;
    ib_num_t num;
    ib_time_t tme;
    ib_float_t flt;
    void *new_field_value;

    if (in_field->type == desired_type) {
        *out_field = NULL;
        return IB_OK;
    }

    switch (in_field->type) {
    case IB_FTYPE_NULSTR:

        /* Extract string.  Note that a zero-length nulstr field can
         * have a NULL value in the union. */
        if ( (in_field->val->u.nulstr == NULL) &&
             (in_field->val->pval == NULL) )
        {
            str = "";
        }
        else {
            rc = ib_field_value(in_field, ib_ftype_nulstr_out(&str));
            if (rc != IB_OK){
                return rc;
            }
        }

        switch (desired_type) {
        case IB_FTYPE_BYTESTR:
            rc = ib_bytestr_dup_nulstr((ib_bytestr_t **)&bstr, mp, str);
            if (rc != IB_OK) {
                return rc;
            }
            new_field_value = ib_ftype_bytestr_in(bstr);
            break;
        case IB_FTYPE_TIME:
            rc = ib_string_to_time(str, &tme);
            if (rc != IB_OK) {
                return rc;
            }
            new_field_value = ib_ftype_time_in(&tme);
            break;
        case IB_FTYPE_NUM:
            rc = ib_string_to_num(str, 0, &num);
            if (rc != IB_OK) {
                return rc;
            }
            new_field_value = ib_ftype_num_in(&num);
            break;
        case IB_FTYPE_FLOAT:
            rc = ib_string_to_float(str, &flt);
            if (rc != IB_OK) {
                return rc;
            }
            new_field_value = ib_ftype_float_in(&flt);
            break;
        default:
            return IB_EINVAL;
        }
        break;

    case IB_FTYPE_BYTESTR:

        /* Extract bytestr. */
        rc = ib_field_value(in_field, ib_ftype_bytestr_out(&bstr));
        if (rc != IB_OK){
            return rc;
        }
        str = (const char *)ib_bytestr_const_ptr(bstr);
        sz = ib_bytestr_length(bstr);

        /* Convert byte str. */
        switch(desired_type) {
        case IB_FTYPE_NULSTR:
            str = ib_mpool_memdup_to_str(mp, str, sz);
            if (!str) {
                return rc;
            }
            new_field_value = ib_ftype_nulstr_in(str);
            break;
        case IB_FTYPE_TIME:
            rc = ib_string_to_time_ex(str, sz, &tme);
            if (rc != IB_OK) {
                return rc;
            }
            new_field_value = ib_ftype_time_in(&tme);
            break;
        case IB_FTYPE_NUM:
            rc = ib_string_to_num_ex(str, sz, 0, &num);
            if (rc != IB_OK) {
                return rc;
            }
            new_field_value = ib_ftype_num_in(&num);
            break;
        case IB_FTYPE_FLOAT:
            rc = ib_string_to_float_ex(str, sz, &flt);
            if (rc != IB_OK) {
                return rc;
            }
            new_field_value = ib_ftype_float_in(&flt);
            break;
        default:
            return IB_EINVAL;
        }
        break;

    case IB_FTYPE_TIME:

        /* Extract time. */
        rc = ib_field_value(in_field, ib_ftype_time_out(&tme));
        if (rc != IB_OK){
            return rc;
        }

        switch (desired_type) {
        case IB_FTYPE_NULSTR:
            str = ib_time_to_string(mp, tme);
            if (! str) {
                return IB_EINVAL;
            }
            new_field_value = ib_ftype_nulstr_in(str);
            break;
        case IB_FTYPE_BYTESTR:
            str = ib_time_to_string(mp, tme);
            if (! str) {
                return IB_EINVAL;
            }
            rc = ib_bytestr_dup_nulstr((ib_bytestr_t **)&bstr, mp, str);
            if (rc != IB_OK){
                return rc;
            }
            new_field_value = ib_ftype_bytestr_in(bstr);
            break;
        case IB_FTYPE_FLOAT:
            flt = (ib_float_t)tme;
            /* Check that our assignment is within error=1, or fail. */
            if (llabs(tme - flt) > 1) {
                return IB_EINVAL;
            }
            new_field_value = ib_ftype_float_in(&flt);
            break;
        default:
            return IB_EINVAL;
        }
        break;

    case IB_FTYPE_NUM:

        /* Extract unum. */
        rc = ib_field_value(in_field, ib_ftype_num_out(&num));
        if (rc != IB_OK){
            return rc;
        }

        switch (desired_type) {
        case IB_FTYPE_NULSTR:
            str = ib_num_to_string(mp, num);
            if (! str) {
                return IB_EINVAL;
            }
            new_field_value = ib_ftype_nulstr_in(str);
            break;
        case IB_FTYPE_BYTESTR:
            str = ib_num_to_string(mp, num);
            if (! str) {
                return IB_EINVAL;
            }
            rc = ib_bytestr_dup_nulstr((ib_bytestr_t **)&bstr, mp, str);
            if (rc != IB_OK){
                return rc;
            }
            new_field_value = ib_ftype_bytestr_in(bstr);
            break;
        case IB_FTYPE_TIME:
            if (num < 0) {
                return IB_EINVAL;
            }
            tme = (ib_time_t)num;
            new_field_value = ib_ftype_time_in(&tme);
            break;
        case IB_FTYPE_FLOAT:
            flt = (ib_float_t)num;
            if (llabs(flt - num) > 1) {
                return IB_EINVAL;
            }
            new_field_value = ib_ftype_float_in(&flt);
            break;
        default:
            return IB_EINVAL;
        }
        break;

    case IB_FTYPE_FLOAT:

        /* Extract unum. */
        rc = ib_field_value(in_field, ib_ftype_float_out(&flt));
        if (rc != IB_OK){
            return rc;
        }

        switch (desired_type) {
        case IB_FTYPE_NULSTR:
            str = ib_float_to_string(mp, flt);
            if (!str) {
                return IB_EINVAL;
            }
            new_field_value = ib_ftype_nulstr_in(str);
            break;
        case IB_FTYPE_BYTESTR:
            str = ib_float_to_string(mp, flt);
            if (!str) {
                return IB_EINVAL;
            }
            rc = ib_bytestr_dup_nulstr((ib_bytestr_t **)&bstr, mp, str);
            if (rc != IB_OK){
                return rc;
            }
            new_field_value = ib_ftype_bytestr_in(bstr);
            break;
        case IB_FTYPE_TIME:
            if (flt < 0) {
                return IB_EINVAL;
            }
            tme = (ib_float_t)flt;
            new_field_value = ib_ftype_time_in(&tme);
            break;
        case IB_FTYPE_NUM:
            num = (ib_float_t)flt;
            new_field_value = ib_ftype_num_in(&num);
            break;
        default:
            return IB_EINVAL;
        }
        break;

    default:
        return IB_EINVAL;
    }

    rc = ib_field_create(
        out_field,
        mp,
        in_field->name,
        in_field->nlen,
        desired_type,
        new_field_value
    );
    return rc;
}