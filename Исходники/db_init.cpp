void database::init_genesis(const genesis_allocation& initial_allocation)
{ try {
   _undo_db.disable();

   fc::ecc::private_key genesis_private_key = fc::ecc::private_key::regenerate(fc::sha256::hash(string("genesis")));
   const key_object& genesis_key =
      create<key_object>( [&genesis_private_key](key_object& k) {
         k.key_data = public_key_type(genesis_private_key.get_public_key());
      });
   const account_statistics_object& genesis_statistics =
      create<account_statistics_object>( [&](account_statistics_object& b){
      });
   create<account_balance_object>( [](account_balance_object& b) {
      b.balance = GRAPHENE_INITIAL_SUPPLY;
   });
   const account_object& genesis_account =
      create<account_object>( [&](account_object& n) {
         n.name = "genesis";
         n.owner.add_authority(genesis_key.get_id(), 1);
         n.owner.weight_threshold = 1;
         n.active = n.owner;
         n.memo_key = genesis_key.id;
         n.statistics = genesis_statistics.id;
      });

   vector<delegate_id_type> init_delegates;
   vector<witness_id_type> init_witnesses;
   flat_set<witness_id_type> init_witness_set;

   auto delegates_and_witnesses = std::max(GRAPHENE_MIN_WITNESS_COUNT, GRAPHENE_MIN_DELEGATE_COUNT);
   for( int i = 0; i < delegates_and_witnesses; ++i )
   {
      const account_statistics_object& stats_obj =
         create<account_statistics_object>( [&](account_statistics_object&){
         });
      const account_object& delegate_account =
         create<account_object>( [&](account_object& a) {
            a.active = a.owner = genesis_account.owner;
            a.name = string("init") + fc::to_string(i);
            a.statistics = stats_obj.id;
         });
      const delegate_object& init_delegate = create<delegate_object>( [&](delegate_object& d) {
         d.delegate_account = delegate_account.id;
         d.vote_id = i * 2;
      });
      init_delegates.push_back(init_delegate.id);

      const witness_object& init_witness = create<witness_object>( [&](witness_object& d) {
            d.witness_account = delegate_account.id;
            d.vote_id = i * 2 + 1;
            secret_hash_type::encoder enc;
            fc::raw::pack( enc, genesis_private_key );
            fc::raw::pack( enc, d.last_secret );
            d.next_secret = secret_hash_type::hash(enc.result());
      });
      init_witnesses.push_back(init_witness.id);
      init_witness_set.insert(init_witness.id);

   }
   create<block_summary_object>( [&](block_summary_object& p) {
   });

   const witness_schedule_object& wso =
   create<witness_schedule_object>( [&]( witness_schedule_object& _wso )
   {
      memset( _wso.rng_seed.begin(), 0, _wso.rng_seed.size() );

      witness_scheduler_rng rng( _wso.rng_seed.begin(), GRAPHENE_NEAR_SCHEDULE_CTR_IV );

      _wso.scheduler = witness_scheduler();
      _wso.scheduler._min_token_count = init_witnesses.size() / 2;
      _wso.scheduler.update( init_witness_set );

      for( int i=0; i<init_witnesses.size(); i++ )
         _wso.scheduler.produce_schedule( rng );

      _wso.last_scheduling_block = 0;
   } ) ;
   assert( wso.id == witness_schedule_id_type() );

   const global_property_object& properties =
      create<global_property_object>( [&](global_property_object& p) {
         p.active_delegates = init_delegates;
         for( const witness_id_type& wit : init_witnesses )
            p.active_witnesses.insert( wit );
         p.next_available_vote_id = delegates_and_witnesses * 2;
         p.chain_id = fc::digest(initial_allocation);
      });
   (void)properties;

   create<dynamic_global_property_object>( [&](dynamic_global_property_object& p) {
      p.time = fc::time_point_sec( GRAPHENE_GENESIS_TIMESTAMP );
      });

   const asset_dynamic_data_object& dyn_asset =
      create<asset_dynamic_data_object>( [&]( asset_dynamic_data_object& a ) {
         a.current_supply = GRAPHENE_INITIAL_SUPPLY;
      });

   const asset_object& core_asset =
     create<asset_object>( [&]( asset_object& a ) {
         a.symbol = GRAPHENE_SYMBOL;
         a.options.max_supply = GRAPHENE_INITIAL_SUPPLY;
         a.precision = GRAPHENE_BLOCKCHAIN_PRECISION_DIGITS;
         a.options.flags = 0;
         a.options.issuer_permissions = 0;
         a.issuer = genesis_account.id;
         a.options.core_exchange_rate.base.amount = 1;
         a.options.core_exchange_rate.base.asset_id = 0;
         a.options.core_exchange_rate.quote.amount = 1;
         a.options.core_exchange_rate.quote.asset_id = 0;
         a.dynamic_asset_data_id = dyn_asset.id;
      });
   assert( asset_id_type(core_asset.id) == asset().asset_id );
   assert( get_balance(account_id_type(), asset_id_type()) == asset(dyn_asset.current_supply) );
   (void)core_asset;

   if( !initial_allocation.empty() )
   {
      share_type total_allocation = 0;
      for( const auto& handout : initial_allocation )
         total_allocation += handout.second;

      auto mangle_to_name = [](const fc::static_variant<public_key_type, address>& key) {
         string addr = string(key.which() == std::decay<decltype(key)>::type::tag<address>::value? key.get<address>()
                                                                                                 : key.get<public_key_type>());
         string result = "bts";
         string key_string = string(addr).substr(sizeof(GRAPHENE_ADDRESS_PREFIX)-1);
         for( char c : key_string )
         {
            if( isupper(c) )
               result += string("-") + char(tolower(c));
            else
               result += c;
         }
         return result;
      };

      fc::time_point start_time = fc::time_point::now();

      for( const auto& handout : initial_allocation )
      {
         asset amount(handout.second);
         amount.amount = ((fc::uint128(amount.amount.value) * GRAPHENE_INITIAL_SUPPLY)/total_allocation.value).to_uint64();
         if( amount.amount == 0 )
         {
            wlog("Skipping zero allocation to ${k}", ("k", handout.first));
            continue;
         }

         signed_transaction trx;
         trx.operations.emplace_back(key_create_operation({asset(), genesis_account.id, handout.first}));
         relative_key_id_type key_id(0);
         authority account_authority(1, key_id, 1);
         account_create_operation cop;
         cop.name = mangle_to_name(handout.first);
         cop.registrar = account_id_type(1);
         cop.active = account_authority;
         cop.owner = account_authority;
         cop.memo_key = key_id;
         trx.operations.push_back(cop);
         trx.validate();
         auto ptrx = apply_transaction(trx, ~0);
         trx = signed_transaction();
         account_id_type account_id(ptrx.operation_results.back().get<object_id_type>());
         trx.operations.emplace_back(transfer_operation({  asset(),
                                                           genesis_account.id,
                                                           account_id,
                                                           amount,
                                                           memo_data()//vector<char>()
                                                        }));
         trx.validate();
         apply_transaction(trx, ~0);
      }

      asset leftovers = get_balance(account_id_type(), asset_id_type());
      if( leftovers.amount > 0 )
      {
         modify(*get_index_type<account_balance_index>().indices().get<by_balance>().find(boost::make_tuple(account_id_type(), asset_id_type())),
                [](account_balance_object& b) {
            b.adjust_balance(-b.get_balance());
         });
         modify(core_asset.dynamic_asset_data_id(*this), [&leftovers](asset_dynamic_data_object& d) {
            d.accumulated_fees += leftovers.amount;
         });
      }

      fc::microseconds duration = fc::time_point::now() - start_time;
      ilog("Finished allocating to ${n} accounts in ${t} milliseconds.",
           ("n", initial_allocation.size())("t", duration.count() / 1000));
   }

   _undo_db.enable();
} FC_LOG_AND_RETHROW() }