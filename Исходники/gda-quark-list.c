static void
protected_value_xor (ProtectedValue *pvalue, gboolean to_clear)
{
	if (to_clear) {
		if (! pvalue->cvalue) {
			guint i, l;
			ensure_static_blob_filled ();
			l = protected_get_length (pvalue->pvalue, pvalue->offset);
			pvalue->cvalue = malloc (sizeof (gchar) * (l + 1));
			for (i = 0; i < l; i++)
				pvalue->cvalue [i] = pvalue->pvalue [i] ^ random_blob [pvalue->offset + i];
			pvalue->cvalue [l] = 0;
#ifdef G_OS_WIN32
			VirtualLock (pvalue->cvalue, sizeof (gchar) * (l + 1));
#else
#ifdef USE_MLOCK
			mlock (pvalue->cvalue, sizeof (gchar) * (l + 1));
#endif
#endif
			/*g_print ("Unmangled [%s]\n", pvalue->cvalue);*/
		}
	}
	else {
		if (pvalue->cvalue) {
			/*g_print ("Mangled [%s]\n", pvalue->cvalue);*/
			guint i;
			for (i = 0; ; i++) {
				gchar c;
				c = pvalue->cvalue[i];
				pvalue->cvalue[i] = g_random_int_range (1, 255);
				if (!c)
					break;
			}
#ifdef G_OS_WIN32
			VirtualUnlock (pvalue->cvalue, sizeof (gchar) * (i + 1));
#else
#ifdef USE_MLOCK
			munlock (pvalue->cvalue, sizeof (gchar) * (i + 1));
#endif
#endif
			free (pvalue->cvalue);
			pvalue->cvalue = NULL;
		}
	}
}