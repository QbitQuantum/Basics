void getx_responder::pool_tx(const std::error_code& code,
    const transaction_type& tx, const hash_digest& tx_hash, channel_ptr node)
{
    if (code)
    {
        chain_.fetch_transaction(tx_hash,
            std::bind(&getx_responder::chain_tx,
                this, _1, _2, node));
    }
    else
    {
        BITCOIN_ASSERT(node);
        node->send(tx, [](const std::error_code&) {});
    }
}