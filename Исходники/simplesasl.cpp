    virtual void tryAgain() {
        // All exits of the method must emit the ready signal
        // so all exits go through a goto ready;
        if(step == 0) {
            out_mech = mechanism_;

#ifdef SIMPLESASL_PLAIN
            // PLAIN
            if (out_mech == "PLAIN") {
                // First, check if we have everything
                if(need.user || need.pass) {
                    qWarning("simplesasl.cpp: Did not receive necessary auth parameters");
                    result_ = Error;
                    goto ready;
                }
                if(!have.user)
                    need.user = true;
                if(!have.pass)
                    need.pass = true;
                if(need.user || need.pass) {
                    result_ = Params;
                    goto ready;
                }

                // Continue with authentication
                QByteArray plain;
                if (!authz.isEmpty())
                    plain += authz.toUtf8();
                plain += '\0' + user.toUtf8() + '\0' + pass.toByteArray();
                out_buf.resize(plain.length());
                memcpy(out_buf.data(), plain.data(), out_buf.size());
            }
#endif
            ++step;
            if (out_mech == "PLAIN")
                result_ = Success;
            else
                result_ = Continue;
        }
        else if(step == 1) {
            // if we still need params, then the app has failed us!
            if(need.user || need.authzid || need.pass || need.realm) {
                qWarning("simplesasl.cpp: Did not receive necessary auth parameters");
                result_ = Error;
                goto ready;
            }
            // see if some params are needed
            if(!have.user)
                need.user = true;
            //if(!have.authzid)
            //	need.authzid = true;
            if(!have.pass)
                need.pass = true;
            if(need.user || need.authzid || need.pass) {
                result_ = Params;
                goto ready;
            }

            // get props
            QByteArray cs(in_buf);
            PropList in;
            if(!in.fromString(cs)) {
                authCondition_ = QCA::SASL::BadProtocol;
                result_ = Error;
                goto ready;
            }
            //qDebug() << (QString("simplesasl.cpp: IN: %1").arg(QString(in.toString())));

            // make a cnonce
            QByteArray a(32,'\0');
            for(int n = 0; n < (int)a.size(); ++n)
                a[n] = (char)(256.0*rand()/(RAND_MAX+1.0));
            QByteArray cnonce = QCA::Base64().arrayToString(a).toLatin1();

            // make other variables
            if (realm.isEmpty())
                realm = QString::fromUtf8(in.get("realm"));
            QByteArray nonce = in.get("nonce");
            QByteArray nc = "00000001";
            QByteArray uri = service.toUtf8() + '/' + host.toUtf8();
            QByteArray qop = "auth";

            // build 'response'
            QByteArray X = user.toUtf8() + ':' + realm.toUtf8() + ':' + pass.toByteArray();
            QByteArray Y = QCA::Hash("md5").hash(X).toByteArray();
            QByteArray tmp = ':' + nonce + ':' + cnonce;
            if (!authz.isEmpty())
                tmp += ':' + authz.toUtf8();
            //qDebug() << (QString(tmp));

            QByteArray A1(Y + tmp);
            QByteArray A2 = QByteArray("AUTHENTICATE:") + uri;
            QByteArray HA1 = QCA::Hash("md5").hashToString(A1).toLatin1();
            QByteArray HA2 = QCA::Hash("md5").hashToString(A2).toLatin1();
            QByteArray KD = HA1 + ':' + nonce + ':' + nc + ':' + cnonce + ':' + qop + ':' + HA2;
            QByteArray Z = QCA::Hash("md5").hashToString(KD).toLatin1();

            //qDebug() << (QString("simplesasl.cpp: A1 = %1").arg(QString(A1)).toAscii());
            //qDebug() << (QString("simplesasl.cpp: A2 = %1").arg(QString(A2)).toAscii());
            //qDebug() << (QString("simplesasl.cpp: KD = %1").arg(QString(KD)).toAscii());

            // build output
            PropList out;
            out.set("username", user.toUtf8());
            if (!realm.isEmpty())
                out.set("realm", realm.toUtf8());
            out.set("nonce", nonce);
            out.set("cnonce", cnonce);
            out.set("nc", nc);
            //out.set("serv-type", service.utf8());
            //out.set("host", host.utf8());
            out.set("digest-uri", uri);
            out.set("qop", qop);
            out.set("response", Z);
            out.set("charset", "utf-8");
            if (!authz.isEmpty())
                out.set("authzid", authz.toUtf8());
            QByteArray s(out.toString());
            //qDebug() << (QString("OUT: %1").arg(QString(out.toString())));

            // done
            out_buf.resize(s.length());
            memcpy(out_buf.data(), s.data(), out_buf.size());
            ++step;
            result_ = Continue;
        }
        /*		else if (step == 2) {
        			out_buf.resize(0);
        			result_ = Continue;
        			++step;
        		}*/
        else {
            out_buf.resize(0);
            result_ = Success;
        }
ready:
        QMetaObject::invokeMethod(this, "resultsReady", Qt::QueuedConnection);
    }