static __inline int
inccl(const struct ccl *ccl, wint_t wi)
{

	if (ccl->compl) {
		return (wmemchr(ccl->start, wi, ccl->end - ccl->start)
		    == NULL);
	} else {
		return (wmemchr(ccl->start, wi, ccl->end - ccl->start) != NULL);
	}
}