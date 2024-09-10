// VFALCO TODO This function should take a reference to the params, modify it
//             as needed, and then there should be a separate function to
//             submit the transaction
//
Json::Value transactionSign (
    Json::Value params, bool bSubmit, bool bFailHard,
    Application::ScopedLockType& mlh, NetworkOPs& netOps, int role)
{
    Json::Value jvResult;

    WriteLog (lsDEBUG, RPCHandler) << "transactionSign: " << params;

    if (! params.isMember ("secret"))
        return RPC::missing_field_error ("secret");

    if (! params.isMember ("tx_json"))
        return RPC::missing_field_error ("tx_json");

    RippleAddress naSeed;

    if (! naSeed.setSeedGeneric (params["secret"].asString ()))
        return RPC::make_error (rpcBAD_SEED,
            RPC::invalid_field_message ("secret"));

    Json::Value& tx_json (params ["tx_json"]);

    if (! tx_json.isObject ())
        return RPC::object_field_error ("tx_json");

    if (! tx_json.isMember ("TransactionType"))
        return RPC::missing_field_error ("tx_json.TransactionType");

    std::string const sType = tx_json ["TransactionType"].asString ();

    if (! tx_json.isMember ("Account"))
        return RPC::make_error (rpcSRC_ACT_MISSING,
            RPC::missing_field_message ("tx_json.Account"));

    RippleAddress raSrcAddressID;

    if (! raSrcAddressID.setAccountID (tx_json["Account"].asString ()))
        return RPC::make_error (rpcSRC_ACT_MALFORMED,
            RPC::invalid_field_message ("tx_json.Account"));

    bool const verify = !(params.isMember ("offline")
                          && params["offline"].asBool ());

    if (!tx_json.isMember ("Sequence") && !verify)
        return RPC::missing_field_error ("tx_json.Sequence");

    // Check for current ledger
    if (verify && !getConfig ().RUN_STANDALONE &&
        (getApp().getLedgerMaster().getValidatedLedgerAge() > 120))
        return rpcError (rpcNO_CURRENT);

    // Check for load
    if (getApp().getFeeTrack().isLoadedCluster() && (role != Config::ADMIN))
        return rpcError(rpcTOO_BUSY);

    Ledger::pointer lSnapshot = netOps.getCurrentLedger ();
    AccountState::pointer asSrc;
    if (verify) {
        asSrc = netOps.getAccountState (lSnapshot, raSrcAddressID);

        if (!asSrc)
        {
            // If not offline and did not find account, error.
            WriteLog (lsDEBUG, RPCHandler)
                    << "transactionSign: Failed to find source account in current ledger: "
                    << raSrcAddressID.humanAccountID ();

            return rpcError (rpcSRC_ACT_NOT_FOUND);
        }
    }

    autofill_fee (params, lSnapshot, jvResult, role == Config::ADMIN);
    if (RPC::contains_error (jvResult))
        return jvResult;

    if ("Payment" == sType)
    {
        auto e = signPayment(params, tx_json, raSrcAddressID, lSnapshot, role);
        if (contains_error(e))
            return e;
    }


    if ("Genesis" == sType)
    {
        auto e = signGenesis(params, tx_json, raSrcAddressID, lSnapshot, role);
        if (contains_error(e))
           return e;
    }

    if ("Transfer" == sType)
    {
        auto e = signTransfer(params, tx_json, raSrcAddressID, lSnapshot, role);
        if (contains_error(e))
           return e;
    }

    if ("AccountCreate" == sType)
    {
        auto e = signAccountCreate(params, tx_json, raSrcAddressID, lSnapshot, role);
        if (contains_error(e))
           return e;
    }


    if (!tx_json.isMember ("Fee")) {
        auto const& transactionType = tx_json["TransactionType"].asString ();
        if ("AccountSet" == transactionType
            || "OfferCreate" == transactionType
            || "OfferCancel" == transactionType
            || "TrustSet" == transactionType)
        {
            tx_json["Fee"] = (int) getConfig ().FEE_DEFAULT;
        }
    }

    if (!tx_json.isMember ("Sequence"))
        tx_json["Sequence"] = asSrc->getSeq ();

    if (!tx_json.isMember ("Flags"))
        tx_json["Flags"] = tfFullyCanonicalSig;

    if (verify)
    {
        SLE::pointer sleAccountRoot = netOps.getSLEi (lSnapshot,
            Ledger::getAccountRootIndex (raSrcAddressID.getAccountID ()));

        if (!sleAccountRoot)
            // XXX Ignore transactions for accounts not created.
            return rpcError (rpcSRC_ACT_NOT_FOUND);
    }

    RippleAddress   naSecret = RippleAddress::createSeedGeneric (params["secret"].asString ());
  
	RippleAddress masterAccountPublic = RippleAddress::createAccountPublic(naSecret);

    if (verify)
    {
        auto account = masterAccountPublic.getAccountID();
        auto const& sle = asSrc->peekSLE();

        WriteLog (lsWARNING, RPCHandler) <<
                "verify: " << masterAccountPublic.humanAccountID () <<
                " : " << raSrcAddressID.humanAccountID ();
        if (raSrcAddressID.getAccountID () == account)
        {
			if (sle.isFlag(lsfDisableMaster) && "Inflation" != sType)
                return rpcError (rpcMASTER_DISABLED);
        }
        else if (!sle.isFieldPresent(sfRegularKey) ||
                 account != sle.getFieldAccount160 (sfRegularKey))
        {
            return rpcError (rpcBAD_SECRET);
        }
    }

    STParsedJSON parsed ("tx_json", tx_json);
    if (!parsed.object.get())
    {
        jvResult ["error"] = parsed.error ["error"];
        jvResult ["error_code"] = parsed.error ["error_code"];
        jvResult ["error_message"] = parsed.error ["error_message"];
        return jvResult;
    }
    std::unique_ptr<STObject> sopTrans = std::move(parsed.object);
    sopTrans->setFieldVL (sfSigningPubKey, masterAccountPublic.getAccountPublic ());

    SerializedTransaction::pointer stpTrans;

    try
    {
        stpTrans = boost::make_shared<SerializedTransaction> (*sopTrans);
    }
    catch (std::exception&)
    {
        return RPC::make_error (rpcINTERNAL,
            "Exception occurred during transaction");
    }

    std::string reason;
    if (!passesLocalChecks (*stpTrans, reason))
        return RPC::make_error (rpcINVALID_PARAMS, reason);

    if (params.isMember ("debug_signing"))
    {
        jvResult["tx_unsigned"] = strHex (
            stpTrans->getSerializer ().peekData ());
        jvResult["tx_signing_hash"] = to_string (stpTrans->getSigningHash ());
    }

    // FIXME: For performance, transactions should not be signed in this code path.
    RippleAddress naAccountPrivate = RippleAddress::createAccountPrivate (naSecret);

    stpTrans->sign (naAccountPrivate);

    Transaction::pointer tpTrans;

    tpTrans = getApp().getMasterTransaction().fetch(stpTrans->getTransactionID(), false);

    if (tpTrans)
    {
        TER res = tpTrans->getResult();
        if (!(isTelLocal(res) || isTemMalformed(res) || isTefFailure(res)))
        {
            tpTrans = Transaction::pointer();
        }
    }

    if (!tpTrans)
    {
        try
        {
            tpTrans     = boost::make_shared<Transaction> (stpTrans, false);
        }
        catch (std::exception&)
        {
            return RPC::make_error (rpcINTERNAL,
                "Exception occurred during transaction");
        }

        try
        {
            // FIXME: For performance, should use asynch interface
            tpTrans = netOps.submitTransactionSync (tpTrans,
                role == Config::ADMIN, true, bFailHard, bSubmit);

            if (!tpTrans)
            {
                return RPC::make_error (rpcINTERNAL,
                    "Unable to sterilize transaction.");
            }
        }
        catch (std::exception&)
        {
            return RPC::make_error (rpcINTERNAL,
                "Exception occurred during transaction submission.");
        }
    }

    try
    {
        jvResult["tx_json"] = tpTrans->getJson (0);
        jvResult["tx_blob"] = strHex (
            tpTrans->getSTransaction ()->getSerializer ().peekData ());

        if (temUNCERTAIN != tpTrans->getResult ())
        {
            std::string sToken;
            std::string sHuman;

            transResultInfo (tpTrans->getResult (), sToken, sHuman);

            jvResult["engine_result"]           = sToken;
            jvResult["engine_result_code"]      = tpTrans->getResult ();
            jvResult["engine_result_message"]   = sHuman;
        }

        return jvResult;
    }
    catch (std::exception&)
    {
        return RPC::make_error (rpcINTERNAL,
            "Exception occurred during JSON handling.");
    }
}