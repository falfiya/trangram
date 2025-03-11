int longestPalindrome(char *s) {
   size_t dict[255] = {};
   while (*s != 0) {
      dict[*s++]++;
   }

   size_t sum = 0;
   size_t middle = 0;

   for (size_t i = 0; i < 255; i++) {
      if (dict[i] % 2 == 1) {
         middle = 1;
      }

      sum += 2 * (dict[i] / 2);
   }

   return sum + middle;
}
