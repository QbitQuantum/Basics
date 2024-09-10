void BlockchainScanner::scanBlockData(shared_ptr<BlockDataBatch> batch)
{
   //getBlock lambda
   auto getBlock = [&](unsigned height)->BlockData
   {
      auto iter = batch->blocks_.find(height);
      if (iter == batch->blocks_.end())
      {
         //TODO: encapsulate in try block to catch deser errors and signal pull thread
         //termination before exiting scope. cant have the scan thread hanging if this
         //one fails. Also update batch->end_ if we didn't go as far as that block height

         //grab block file map
         BlockHeader* blockheader = nullptr;
         blockheader = &blockchain_->getHeaderByHeight(height);

         auto filenum = blockheader->getBlockFileNum();
         auto mapIter = batch->fileMaps_.find(filenum);
         if (mapIter == batch->fileMaps_.end())
         {
            //we haven't grabbed that file map yet
            auto insertPair = batch->fileMaps_.insert(
               make_pair(filenum, move(blockDataLoader_.get(filenum, true))));

            mapIter = insertPair.first;
         }

         auto filemap = mapIter->second.get();

         //find block and deserialize it
         try
         {
            BlockData bdata;
            bdata.deserialize(
               filemap->getPtr() + blockheader->getOffset(),
               blockheader->getBlockSize(),
               blockheader, false);

            auto insertPair = batch->blocks_.insert(make_pair(height, move(bdata)));
            iter = insertPair.first;
         }
         catch (...)
         {
            LOGERR << "unknown block deser error during scan at height #" << height;
            batch->exceptionPtr_ = current_exception();
            return BlockData();
         }
      }

      return iter->second;
   };

   //parser lambda
   auto blockDataLoop = [&](function<void(const BlockData&)> callback)
   {
      auto currentBlock = batch->start_;

      while (currentBlock <= batch->end_)
      {
         BlockData&& bdata = getBlock(currentBlock);
         if (!bdata.isInitialized())
            return;

         callback(bdata);

         currentBlock += totalThreadCount_;
      }
   };

   //txout lambda
   auto txoutParser = [&](const BlockData& blockdata)->void
   {
      //TODO: flag isMultisig

      const BlockHeader* header = blockdata.header();

      //update processed height
      auto topHeight = header->getBlockHeight();
      batch->highestProcessedHeight_ = topHeight;

      auto& txns = blockdata.getTxns();
      for (unsigned i = 0; i < txns.size(); i++)
      {
         const BCTX& txn = *(txns[i].get());
         for (unsigned y = 0; y < txn.txouts_.size(); y++)
         {
            auto& txout = txn.txouts_[y];

            BinaryRefReader brr(
               txn.data_ + txout.first, txout.second);
            brr.advance(8);
            unsigned scriptSize = (unsigned)brr.get_var_int();
            auto&& scrAddr = BtcUtils::getTxOutScrAddr(
               brr.get_BinaryDataRef(scriptSize));

            if (!scrAddrFilter_->hasScrAddress(scrAddr))
               continue;

            //if we got this far, this txout is ours
            //get tx hash
            auto& txHash = txn.getHash();

            //construct StoredTxOut
            StoredTxOut stxo;
            stxo.dataCopy_ = BinaryData(
               txn.data_ + txout.first, txout.second);
            stxo.parentHash_ = txHash;
            stxo.blockHeight_ = header->getBlockHeight();
            stxo.duplicateID_ = header->getDuplicateID();
            stxo.txIndex_ = i;
            stxo.txOutIndex_ = y;
            stxo.scrAddr_ = scrAddr;
            stxo.spentness_ = TXOUT_UNSPENT;
            stxo.parentTxOutCount_ = txn.txouts_.size();
            stxo.isCoinbase_ = txn.isCoinbase_;
            auto value = stxo.getValue();

            auto&& hgtx = DBUtils::heightAndDupToHgtx(
               stxo.blockHeight_, stxo.duplicateID_);
            
            auto&& txioKey = DBUtils::getBlkDataKeyNoPrefix(
               stxo.blockHeight_, stxo.duplicateID_,
               i, y);

            //update utxos_
            auto& stxoHashMap = batch->utxos_[txHash];
            stxoHashMap.insert(make_pair(y, move(stxo)));

            //update ssh_
            auto& ssh = batch->ssh_[scrAddr];
            auto& subssh = ssh.subHistMap_[hgtx];
            
            //deal with txio count in subssh at serialization
            TxIOPair txio;
            txio.setValue(value);
            txio.setTxOut(txioKey);
            txio.setFromCoinbase(txn.isCoinbase_);
            subssh.txioMap_.insert(make_pair(txioKey, move(txio)));
         }
      }
   };

   //txin lambda
   auto txinParser = [&](const BlockData& blockdata)->void
   {
      const BlockHeader* header = blockdata.header();
      auto& txns = blockdata.getTxns();

      for (unsigned i = 0; i < txns.size(); i++)
      {
         const BCTX& txn = *(txns[i].get());

         for (unsigned y = 0; y < txn.txins_.size(); y++)
         {
            auto& txin = txn.txins_[y];
            BinaryDataRef outHash(
               txn.data_ + txin.first, 32);

            auto utxoIter = utxoMap_.find(outHash);
            if (utxoIter == utxoMap_.end())
               continue;

            unsigned txOutId = READ_UINT32_LE(
               txn.data_ + txin.first + 32);

            auto idIter = utxoIter->second.find(txOutId);
            if (idIter == utxoIter->second.end())
               continue;

            //if we got this far, this txins consumes one of our utxos

            //create spent txout
            auto&& hgtx = DBUtils::getBlkDataKeyNoPrefix(
               header->getBlockHeight(), header->getDuplicateID());

            auto&& txinkey = DBUtils::getBlkDataKeyNoPrefix(
               header->getBlockHeight(), header->getDuplicateID(),
               i, y);

            StoredTxOut stxo = idIter->second;
            stxo.spentness_ = TXOUT_SPENT;
            stxo.spentByTxInKey_ = txinkey;

            //if this tx's hash was never pulled, let's add it to the stxo's
            //parent hash, in order to keep track of this tx in the hint db
            if (txn.txHash_.getSize() == 0)
               stxo.parentHash_ = move(txn.getHash());

            //add to ssh_
            auto& ssh = batch->ssh_[stxo.getScrAddress()];
            auto& subssh = ssh.subHistMap_[hgtx];

            //deal with txio count in subssh at serialization
            TxIOPair txio;
            auto&& txoutkey = stxo.getDBKey(false);
            txio.setTxOut(txoutkey);
            txio.setTxIn(txinkey);
            txio.setValue(stxo.getValue());
            subssh.txioMap_[txoutkey] = move(txio);
            
            //add to spentTxOuts_
            batch->spentTxOuts_.push_back(move(stxo));
         }
      }
   };

   //txout loop
   blockDataLoop(txoutParser);

   //done with txouts, fill the future flag and wait on the mutex 
   //to move to txins processing
   batch->flagUtxoScanDone();
   unique_lock<mutex> txinLock(batch->parseTxinMutex_);

   //txins loop
   blockDataLoop(txinParser);
}