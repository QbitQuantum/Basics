static int op_capi_get_by_subject(X509_LOOKUP *_lu,int _type,X509_NAME *_name,
                                  X509_OBJECT *_ret) {
    HCERTSTORE h_store;
    if(_name==NULL)return 0;
    if(_name->bytes==NULL||_name->bytes->length<=0||_name->modified) {
        if(i2d_X509_NAME(_name,NULL)<0)return 0;
        OP_ASSERT(_name->bytes->length>0);
    }
    h_store=(HCERTSTORE)_lu->method_data;
    switch(_type) {
    case X509_LU_X509: {
        CERT_NAME_BLOB  find_para;
        PCCERT_CONTEXT  cert;
        X509           *x;
        int             ret;
        /*Although X509_NAME contains a canon_enc field, that "canonical" [1]
           encoding was just made up by OpenSSL.
          It doesn't correspond to any actual standard, and since it drops the
           initial sequence header, won't be recognized by the Crypto API.
          The assumption here is that CertFindCertificateInStore() will allow any
           appropriate variations in the encoding when it does its comparison.
          This is, however, emphatically not true under Wine, which just compares
           the encodings with memcmp().
          Most of the time things work anyway, though, and there isn't really
           anything we can do to make the situation better.

          [1] A "canonical form" is defined as the one where, if you locked 10
           mathematicians in a room and asked them to come up with a
           representation for something, it's the answer that 9 of them would
           give you back.
          I don't think OpenSSL's encoding qualifies.*/
        find_para.cbData=_name->bytes->length;
        find_para.pbData=(unsigned char *)_name->bytes->data;
        cert=CertFindCertificateInStore(h_store,X509_ASN_ENCODING,0,
                                        CERT_FIND_SUBJECT_NAME,&find_para,NULL);
        if(cert==NULL)return 0;
        x=d2i_X509(NULL,(const unsigned char **)&cert->pbCertEncoded,
                   cert->cbCertEncoded);
        CertFreeCertificateContext(cert);
        if(x==NULL)return 0;
        ret=X509_STORE_add_cert(_lu->store_ctx,x);
        X509_free(x);
        if(ret)return op_capi_retrieve_by_subject(_lu,_type,_name,_ret);
    }
    break;
    case X509_LU_CRL: {
        CERT_INFO      cert_info;
        CERT_CONTEXT   find_para;
        PCCRL_CONTEXT  crl;
        X509_CRL      *x;
        int            ret;
        ret=op_capi_retrieve_by_subject(_lu,_type,_name,_ret);
        if(ret>0)return ret;
        memset(&cert_info,0,sizeof(cert_info));
        cert_info.Issuer.cbData=_name->bytes->length;
        cert_info.Issuer.pbData=(unsigned char *)_name->bytes->data;
        memset(&find_para,0,sizeof(find_para));
        find_para.pCertInfo=&cert_info;
        crl=CertFindCRLInStore(h_store,0,0,CRL_FIND_ISSUED_BY,&find_para,NULL);
        if(crl==NULL)return 0;
        x=d2i_X509_CRL(NULL,(const unsigned char **)&crl->pbCrlEncoded,
                       crl->cbCrlEncoded);
        CertFreeCRLContext(crl);
        if(x==NULL)return 0;
        ret=X509_STORE_add_crl(_lu->store_ctx,x);
        X509_CRL_free(x);
        if(ret)return op_capi_retrieve_by_subject(_lu,_type,_name,_ret);
    }
    break;
    }
    return 0;
}