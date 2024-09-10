TEST_P(TextToBinaryHalfValueTest, Samples) {
  const std::string input =
      "%1 = OpTypeFloat 16\n%2 = OpConstant %1 " + GetParam().first;
  EXPECT_THAT(CompiledInstructions(input),
              Eq(Concatenate({MakeInstruction(SpvOpTypeFloat, {1, 16}),
                              MakeInstruction(SpvOpConstant,
                                              {1, 2, GetParam().second})})));
}