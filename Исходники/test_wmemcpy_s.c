int test_wmemcpy_s (void)
{
    errno_t rc;
    uint32_t i;
    rsize_t len;
    unsigned int testno = 0;


    printf("\nTesting wmemcpy_s:\n");
/*--------------------------------------------------*/
/* 1  Test for NULL destination check                  */
    printf("Test #%d:\n", ++testno);

    rc = wmemcpy_s(NULL, LEN, mem2, LEN);
    if (rc != ESNULLP) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

/*--------------------------------------------------*/
/* 2  Test for zero length destination                 */

    printf("Test #%d:\n", ++testno);

    rc = wmemcpy_s(mem1, 0, mem2, LEN);
    if (rc != ESZEROL) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

/*--------------------------------------------------*/
/* 3  Test for too large destination size              */
    printf("Test #%d:\n", ++testno);

    rc = wmemcpy_s(mem1, RSIZE_MAX_MEM+1, mem2, LEN);
    if (rc != ESLEMAX) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

/*--------------------------------------------------*/
/* 4  Test for NULL source check                  */
    printf("Test #%d:\n", ++testno);

    rc = wmemcpy_s(mem1, LEN, NULL, LEN);
    if (rc != ESNULLP) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

/*--------------------------------------------------*/
/* 5  Test for zero length source                 */
    printf("Test #%d:\n", ++testno);

    rc = wmemcpy_s(mem1, 10, mem2, 0);
    if (rc != ESZEROL) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

/*--------------------------------------------------*/
/* 6  Test for too large source size              */
    printf("Test #%d:\n", ++testno);

    rc = wmemcpy_s(mem1, LEN, mem2, RSIZE_MAX_MEM+1);
    if (rc != ESLEMAX) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

/*--------------------------------------------------*/
/* 7 Test for destination overlaps into source buffer */
    printf("Test #%d:\n", ++testno);

    rc = wmemcpy_s(mem1, LEN, &mem1[20], 21);
    if (rc != ESOVRLP) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

/*--------------------------------------------------*/
/* 8 Test for source overlaps into dest buffer */
	printf("Test #%d:\n", ++testno);

	rc = wmemcpy_s(&mem1[25], LEN, mem1, 26);
	if (rc != ESOVRLP) {
		printf("%s %u   Error rc=%u \n",
					 __FUNCTION__, __LINE__,  rc);
	}


/*--------------------------------------------------*/
/* 9 Test for just enough room for dest buffer before source & proper copying */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<10; i++) { mem1[i] = 33; }
    mem1[10] = 40;
    for (i=11; i<LEN; i++) { mem1[i] = 44; }

    rc = wmemcpy_s(mem1, 10, &mem1[10], 10);
    if (rc != EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    } else {

    	if ( mem1[0] != 40 && mem1[10] != 40) {
            printf("%d - %d m1[0]=%d  m1[10]=%d should be 40  \n",
                 __LINE__, i, mem1[0], mem1[10]);
    	}
		for (i=1; i<10; i++) {
			if (mem1[i] != 44) {
				printf("%d - %d m1=%d  should be 44  \n",
					 __LINE__, i, mem1[i]);
			}
		}
    }

/*--------------------------------------------------*/
/* 10    */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<LEN+1; i++) { mem1[i] = 33; }
    for (i=0; i<LEN; i++) { mem2[i] = 44; }

    len = LEN;
    rc = wmemcpy_s(mem1, len, mem2, (len+1) );
    if (rc == EOK) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);

    } else {

    for (i=0; i<len; i++) {
        if (mem1[i] != 0) {
            printf("%d - %d m1=%d  m2=%d  \n",
                 __LINE__, i, mem1[i], mem2[i]);
        }
    }

    if (mem1[i] != 33) {
        printf("%d - %lu m1=%d  m2=%d  \n",
                 __LINE__, len, mem1[len], mem2[len]);
    }

    }

/*--------------------------------------------------*/
/* 11    */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<LEN+2; i++) { mem1[i] = 33; }
    for (i=0; i<LEN; i++) { mem2[i] = 44; }

    len = LEN/2;
    rc = wmemcpy_s(mem1, len, mem2, LEN);
    if (rc != ESLEMAX) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);

    } else {

    for (i=0; i<len; i++) {
        if (mem1[i] != 0) {
            printf("%d - %d m1=%d  m2=%d  \n",
                 __LINE__, i, mem1[i], mem2[i]);
        }
    }

    if (mem1[len] != 33) {
            printf("%d - %lu m1=%d  m2=%d  \n",
                 __LINE__, len, mem1[len], mem2[len]);
    }
    }

/*--------------------------------------------------*/
/* 12   */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<LEN+2; i++) { mem1[i] = 33; }
    for (i=0; i<LEN; i++) { mem2[i] = 44; }

    len = LEN;
    rc = wmemcpy_s(mem1, len, mem2, 0);
    if (rc != ESZEROL) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);

    } else {

    /* verify mem1 was zeroed */
    for (i=0; i<len; i++) {
        if (mem1[i] != 0) {
            printf("%d - %d m1=%d  m2=%d  \n",
                 __LINE__, i, mem1[i], mem2[i]);
        }
    }

    if (mem1[len] != 33) {
            printf("%d - %lu m1=%d  m2=%d  \n",
                 __LINE__, len, mem1[len], mem2[len]);
    }

    }

/*--------------------------------------------------*/
/* 13   */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<LEN; i++) { mem1[i] = 33; }
    for (i=0; i<LEN; i++) { mem2[i] = 44; }

    len = LEN;
    rc = wmemcpy_s(mem1, len, mem2, RSIZE_MAX_MEM+1);
    if (rc != ESLEMAX) {
        printf("%s %u   Error rc=%u \n",
                     __FUNCTION__, __LINE__, rc);
    } else {

		/* verify mem1 was zeroed */
		for (i=0; i<len; i++) {
			if (mem1[i] != 0) {
				printf("%d - %d m1=%d  m2=%d  \n",
					 __LINE__, i, mem1[i], mem2[i]);
			}
		}

		if (mem1[len] == 0) {
				printf("%d - %d m1=%d  m2=%d  \n",
					 __LINE__, i, mem1[i], mem2[i]);
		}

    }

/*--------------------------------------------------*/
/* 14   */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<LEN; i++) { mem1[i] = 55; }

    /* same ptr - no move */
    rc = wmemcpy_s(mem1, LEN, mem1, LEN);
    if (rc != EOK) {
        printf("%s %u  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    }

/*--------------------------------------------------*/
/* 15   */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<LEN; i++) { mem1[i] = 55; }
    for (i=0; i<LEN; i++) { mem2[i] = 65; }

    /* overlap */
    len = 100;
    rc = wmemcpy_s(&mem1[0], len, &mem1[10], len);
    if (rc != ESOVRLP) {
        printf("%s %u  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    } else {

    for (i=0; i<len; i++) {
        if (mem1[i] != 0) {
            printf("%d - %d m1=%d  m2=%d  \n",
                 __LINE__, i, mem1[i], mem2[i]);
        }
    }

    if (mem1[len] == 0) {
            printf("%d - %d m1=%d  m2=%d  \n",
                 __LINE__, i, mem1[i], mem2[i]);
    }

    }

/*--------------------------------------------------*/
/* 16  */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<LEN; i++) { mem1[i] = 55; }
    for (i=0; i<LEN; i++) { mem2[i] = 65; }

    /* overlap */
    len = 100;
    rc = wmemcpy_s(&mem1[10], len, &mem1[0], len);
    if (rc != ESOVRLP) {
        printf("%s %u  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    } else {

		for (i=10; i<len+10; i++) {
			if (mem1[i] != 0) {
				printf("%d - %d m1=%d  m2=%d  \n",
					 __LINE__, i, mem1[i], mem2[i]);
			}
		}

    }

/*--------------------------------------------------*/
/* 17   */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<LEN; i++) { mem1[i] = 35; }
    for (i=0; i<LEN; i++) { mem2[i] = 55; }

    len = 5;
    rc = wmemcpy_s(mem1, len, mem2, len);
    if (rc != EOK) {
        printf("%s %u  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    } else {

    for (i=0; i<len; i++) {
        if (mem1[i] != 55) {
            printf("%d - %d m1=%d\n",
                 __LINE__, i, mem1[i]);
        }
    }

    }

/*--------------------------------------------------*/
/* 18   */
    printf("Test #%d:\n", ++testno);

    for (i=0; i<LEN; i++) { mem1[i] = 35; }
    for (i=0; i<LEN; i++) { mem2[i] = 55; }

    rc = wmemcpy_s(mem1, LEN, mem2, LEN/2);
    if (rc != EOK) {
        printf("%s %u  Error rc=%u \n",
                     __FUNCTION__, __LINE__,  rc);
    } else {

    for (i=0; i<LEN/2; i++) {
        if (mem1[i] != 55) {
            printf("%d - %d m1=%d  m2=%d  \n",
                 __LINE__, i, mem1[i], mem2[i]);
        }
    }
    }

/*--------------------------------------------------*/
/*--------------------------------------------------*/

    return (0);
}