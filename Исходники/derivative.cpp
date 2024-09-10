 static RCP<const Basic> diff(const ATan2 &self,
         const RCP<const Symbol> &x) {
     return mul(div(pow(self.get_den(), i2), add(pow(self.get_den(), i2),
         pow(self.get_num(), i2))), div(self.get_num(),
         self.get_den())->diff(x));
 }