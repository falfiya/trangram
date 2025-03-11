function longestPalindrome(s: string): number {
   const chars: {[char: string]: number} = {};
   for (const c of s) {
      if (c in chars) {
         chars[c]++;
      } else {
         chars[c] = 1;
      }
   }

   let sum = 0;
   let middle = 0;
   for (const count of Object.values(chars)) {
      if (count % 2 == 1) {
         middle = 1;
      }
      const pair = count / 2 | 0;
      sum += pair * 2;
   }

   return sum + middle;
}
