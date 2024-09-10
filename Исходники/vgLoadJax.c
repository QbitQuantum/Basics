void vgLoadJax(char *visiGeneDir, char *jaxDb, char *outDir)
/* vgLoadJax - Load visiGene database from jackson database. */
{
struct sqlConnection *conn = sqlConnect(jaxDb);
struct sqlConnection *conn2 = sqlConnect(jaxDb);
struct sqlConnection *connSp = sqlConnect("uniProt");

char inFull[PATH_LEN];
char *jaxPath = "inSitu/Mouse/jax";
char inJax[PATH_LEN];

#ifdef UNUSED
/* won't work yet */
char* host = "genome-test";
char* user = cfgOptionEnv("HGDB_USER", "db.user");
char* password = cfgOptionEnv("HGDB_PASSWORD", "db.password");

connSp = sqlConnectRemote(host, user, password, "uniProt");
#endif

safef(inFull, sizeof(inFull), "%s/full", visiGeneDir);
safef(inJax, sizeof(inJax), "%s/%s", inFull, jaxPath);
submitToDir(conn, conn2, connSp, outDir, inJax);
sqlDisconnect(&connSp);
sqlDisconnect(&conn2);
sqlDisconnect(&conn);
}