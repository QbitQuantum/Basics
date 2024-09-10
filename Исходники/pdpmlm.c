double pdpmlm_logpcls( pdpm_t * obj, unsigned int cls ) {
    pdpmlm_t * mdl = (pdpmlm_t *) obj->model;
    double logp = 0.0;
    if( obj->gcl[ cls ] == 0 ) { return logp; }
    //compute posterior statistics
    pdpmlm_parm( obj, cls, mdl->s, mdl->m, &mdl->a, &mdl->b, &mdl->d );
    //compute posterior mass
    logp = lgamma( mdl->a / 2 ) - ( mdl->a / 2 ) * log( mdl->b / 2 ) - mdl->d;
    logp += obj->lam * lgamma( obj->gcl[ cls ] );
    return logp;
}