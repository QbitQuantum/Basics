 VarScopeType getScopeTypeOfName(InternedString name) override {
     if (isCompilerCreatedName(name))
         return VarScopeType::FAST;
     else if (forced_globals.find(name) != forced_globals.end())
         return VarScopeType::GLOBAL;
     else
         return VarScopeType::NAME;
 }