/* calculate request-digest/response-digest as per HTTP Digest spec */
static QByteArray digestMd5ResponseHelper(
    const QByteArray &alg,
    const QByteArray &userName,
    const QByteArray &realm,
    const QByteArray &password,
    const QByteArray &nonce,       /* nonce from server */
    const QByteArray &nonceCount,  /* 8 hex digits */
    const QByteArray &cNonce,      /* client nonce */
    const QByteArray &qop,         /* qop-value: "", "auth", "auth-int" */
    const QByteArray &method,      /* method from the request */
    const QByteArray &digestUri,   /* requested URL */
    const QByteArray &hEntity       /* H(entity body) if qop="auth-int" */
    )
{
    QCryptographicHash hash(QCryptographicHash::Md5);
    hash.addData(userName);
    hash.addData(":", 1);
    hash.addData(realm);
    hash.addData(":", 1);
    hash.addData(password);
    QByteArray ha1 = hash.result();
    if (alg.toLower() == "md5-sess") {
        hash.reset();
        // RFC 2617 contains an error, it was:
        // hash.addData(ha1);
        // but according to the errata page at http://www.rfc-editor.org/errata_list.php, ID 1649, it
        // must be the following line:
        hash.addData(ha1.toHex());
        hash.addData(":", 1);
        hash.addData(nonce);
        hash.addData(":", 1);
        hash.addData(cNonce);
        ha1 = hash.result();
    };
    ha1 = ha1.toHex();

    // calculate H(A2)
    hash.reset();
    hash.addData(method);
    hash.addData(":", 1);
    hash.addData(digestUri);
    if (qop.toLower() == "auth-int") {
        hash.addData(":", 1);
        hash.addData(hEntity);
    }
    QByteArray ha2hex = hash.result().toHex();

    // calculate response
    hash.reset();
    hash.addData(ha1);
    hash.addData(":", 1);
    hash.addData(nonce);
    hash.addData(":", 1);
    if (!qop.isNull()) {
        hash.addData(nonceCount);
        hash.addData(":", 1);
        hash.addData(cNonce);
        hash.addData(":", 1);
        hash.addData(qop);
        hash.addData(":", 1);
    }
    hash.addData(ha2hex);
    return hash.result().toHex();
}