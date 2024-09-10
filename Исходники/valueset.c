/*
 * Remove an array of values from a value set.
 * The removed values are passed back in an array.
 *
 * Flags
 *  SLAPI_VALUE_FLAG_PRESERVECSNSET - csnset in the value set is duplicated and
 *                                    preserved in the matched element of the
 *                                    array of values.
 *  SLAPI_VALUE_FLAG_IGNOREERROR - ignore an error: Couldn't find the value to
 *                                 be deleted.
 *  SLAPI_VALUE_FLAG_USENEWVALUE - replace the value between the value set and
 *                                 the matched element of the array of values
 *                                 (used by entry_add_present_values_wsi).
 *
 * Returns
 *  LDAP_SUCCESS - OK.
 *  LDAP_NO_SUCH_ATTRIBUTE - A value to be deleted was not in the value set.
 *  LDAP_OPERATIONS_ERROR - Something very bad happened.
 */
int
valueset_remove_valuearray(Slapi_ValueSet *vs, const Slapi_Attr *a, Slapi_Value **valuestodelete, int flags, Slapi_Value ***va_out)
{
	int rc= LDAP_SUCCESS;
	if(!valuearray_isempty(vs->va))
	{
		int numberofvaluestodelete= valuearray_count(valuestodelete);
		struct valuearrayfast vaf_out;
		if ( va_out )
		{
			valuearrayfast_init(&vaf_out,*va_out);
		}

		/*
		 * If there are more then one values, build an AVL tree to check
		 * the duplicated values.
		 */
		if ( numberofvaluestodelete > 1 )
		{
			/*
			 * Several values to delete: first build an AVL tree that
			 * holds all of the existing values and use that to find
			 * the values we want to delete.
			 */
			Avlnode	*vtree = NULL;
			int numberofexistingvalues= slapi_valueset_count(vs);
			rc= valuetree_add_valuearray( a, vs->va, &vtree, NULL );
			if ( rc!=LDAP_SUCCESS )
			{
				/*
				 * failed while constructing AVL tree of existing
				 * values... something bad happened.
				 */
				rc= LDAP_OPERATIONS_ERROR;
			}
			else
			{
				int i;
				/*
				 * find and mark all the values that are to be deleted
				 */
				for ( i = 0; rc == LDAP_SUCCESS && valuestodelete[i] != NULL; ++i )
				{
					int index= 0;
					rc = valuetree_find( a, valuestodelete[i], vtree, &index );
					if(rc==LDAP_SUCCESS)
					{
						if(vs->va[index]!=NULL)
						{
							/* Move the value to be removed to the out array */
							if ( va_out )
							{
								if (vs->va[index]->v_csnset &&
									(flags & (SLAPI_VALUE_FLAG_PRESERVECSNSET|
                                              SLAPI_VALUE_FLAG_USENEWVALUE)))
								{
									valuestodelete[i]->v_csnset = csnset_dup (vs->va[index]->v_csnset);
								}
								if (flags & SLAPI_VALUE_FLAG_USENEWVALUE)
								{
									valuearrayfast_add_value_passin(&vaf_out,valuestodelete[i]);
									valuestodelete[i] = vs->va[index];
									vs->va[index] = NULL;
								}
								else
								{
									valuearrayfast_add_value_passin(&vaf_out,vs->va[index]);
									vs->va[index] = NULL;
								}
							}
							else
							{
								if (flags & SLAPI_VALUE_FLAG_PRESERVECSNSET)
								{
									valuestodelete[i]->v_csnset = vs->va[index]->v_csnset;
									vs->va[index]->v_csnset = NULL;
								}
								slapi_value_free ( & vs->va[index] );
							}
						}
						else
						{
							/* We already deleted this value... */
							if((flags & SLAPI_VALUE_FLAG_IGNOREERROR) == 0)
							{
								/* ...that's an error. */
								rc= LDAP_NO_SUCH_ATTRIBUTE;
							}
						}
					}
					else
					{
						/* Couldn't find the value to be deleted */
						if(rc==LDAP_NO_SUCH_ATTRIBUTE && (flags & SLAPI_VALUE_FLAG_IGNOREERROR ))
						{
							rc= LDAP_SUCCESS;
						}
					}
				}
				valuetree_free( &vtree );

				if ( rc != LDAP_SUCCESS )
				{
					LDAPDebug( LDAP_DEBUG_ANY,"could not find value %d for attr %s (%s)\n", i-1, a->a_type, ldap_err2string( rc ));
				}
				else
				{
					/* Shunt up all the remaining values to cover the deleted ones. */
					valuearray_compress(vs->va,numberofexistingvalues);
				}
			}
		}
		else
		{
			/* We delete one or no value, so we use brute force. */
			int i;
			for ( i = 0; rc==LDAP_SUCCESS && valuestodelete[i] != NULL; ++i )
			{
				Slapi_Value *found= valueset_remove_value(a, vs, valuestodelete[i]);
				if(found!=NULL)
				{
					if ( va_out )
					{
						if (found->v_csnset &&
							(flags & (SLAPI_VALUE_FLAG_PRESERVECSNSET|
                                      SLAPI_VALUE_FLAG_USENEWVALUE)))
						{
							valuestodelete[i]->v_csnset = csnset_dup (found->v_csnset);
						}
						if (flags & SLAPI_VALUE_FLAG_USENEWVALUE)
						{
							valuearrayfast_add_value_passin(&vaf_out,valuestodelete[i]);
							valuestodelete[i] = found;
						}
						else
						{
							valuearrayfast_add_value_passin(&vaf_out,found);
						}
					}
					else
					{
						if (flags & SLAPI_VALUE_FLAG_PRESERVECSNSET)
						{
							valuestodelete[i]->v_csnset = found->v_csnset;
							found->v_csnset = NULL;
						}
						slapi_value_free ( & found );
					}
				}
				else
				{
					if((flags & SLAPI_VALUE_FLAG_IGNOREERROR) == 0)
					{
						LDAPDebug( LDAP_DEBUG_ARGS,"could not find value %d for attr %s\n", i-1, a->a_type, 0 );
						rc= LDAP_NO_SUCH_ATTRIBUTE;
					}
				}
			}
		}
		if ( va_out )
		{
			*va_out= vaf_out.va;
			if(rc!=LDAP_SUCCESS)
			{
				valuearray_free(va_out);
			}
		}
	}
	return rc;
}