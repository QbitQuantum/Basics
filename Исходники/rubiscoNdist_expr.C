  rubiscoNdist_expr (const BlockModel& al)
    : RubiscoNdist (al),
      f_photo (al.number ("f_photo")),
      expr (Librarian::build_item<Number> (al, "value")),
      scope (__FUNCTION__)
  {
    scope.add_item (new ExchangeNumber (LAI_symbol, Attribute::None(),
					"Leaf area index"));
    scope.add_item (new ExchangeNumber (distance_from_top_symbol, "cm",
					"Distance from top of canopy"));
    scope.add_item (new ExchangeNumber (relative_LAI_symbol, Attribute::None(),
					"Relative leaf area index"));
    scope.add_item (new ExchangeNumber (relative_distance_from_top_symbol, Attribute::None(),
					"Relative distance from top of canopy"));
    scope.add_item (new ExchangeNumber (DS_symbol, Attribute::None(),
					"Development stage"));
    scope.done ();
    expr->initialize (al.units (), scope, al.msg());
    if (!expr->check_dim (al.units (), scope, Attribute::Fraction (), al.msg()))
      al.error("Invalid expression of rubisco expr");
  }