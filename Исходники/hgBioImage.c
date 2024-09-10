void cartMain(struct cart *theCart)
/* We got the persistent/CGI variable cart.  Now
 * set up the globals and make a web page. */
{
cart = theCart;

/* Break out new block after have set cart */
    {
    int id = cartUsualInt(cart, hgbiId, 1);
    struct sqlConnection *conn = sqlConnect("bioImage");
    char *geneName = bioImageGeneName(conn, id);
    if (cartVarExists(cart, hgbiDoFullSize))
	{
	htmStart(stdout, "BioImage Full Sized Image");
	printf("<IMG SRC=\"/%s\"><BR>\n", bioImageFullSizePath(conn, id));
	printCaption(conn, id, geneName);
	htmlEnd();
	}
    else  /* Default case - start fancy web page. */
	{
	mainPage(conn, id, geneName);
	}

    cartRemovePrefix(cart, hgbiDoPrefix);
    sqlDisconnect(&conn);
    }
}