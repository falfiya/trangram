// #pragma GCC target "arch=native"

/**
 * Note: The returned array must be malloced, assume caller calls free().
 * The stupid leetcode problem labeled that last parameter as "returnSize" but
 * it was actually the number of combinations, not the size of the output array.
 */
__attribute__((no_sanitize("address")))
char **letterCombinations(char const *restrict digits, int *restrict out_combinations) {
   size_t digits_len = 0;
   size_t combinations = 1;

   for (;;) {
      char c = digits[digits_len];
      if (c == 0) {
         break;
      }

      static char lookup_table[] = {
      // 1, 2, 3
            3, 3,
      // 4, 5, 6
         3, 3, 3,
      // 7, 8, 9
         4, 3, 4,
      };

      combinations *= lookup_table[c - '2'];
      digits_len++;
   }

   if (digits_len == 0) {
      *out_combinations = 0;
      return 0;
   }

   size_t combination_sz = digits_len + 1;

   size_t combinations_buf_sz = sizeof(void *) * combinations;
   size_t char_buf_sz = combination_sz * combinations;

   // Allocate in one block
   void *buf = malloc(combinations_buf_sz + char_buf_sz);

   // Split the block into two.
   // The combinations buffer will contain a bunch of pointers into the char
   // buffer. It's easy to calculate their offset.
   char **combinations_buf = buf;
   char *char_buf = buf + combinations_buf_sz;

   // Initialize the combinations buffer
   for (size_t i = 0; i < combinations; i++) {
      // set the pointer in the output table
      char *this_combination = char_buf + i * combination_sz;
      this_combination[digits_len] = 0;
      combinations_buf[i] = this_combination;

      // Compute the actual combination using a stringification algo reminiscent
      // of integer to string.
      // It turns out that computing all possible combinations can be thought of
      // as counting upwards with a weird notation.
      size_t working_i = i;
      for (size_t j = 0; j < digits_len; j++) {
         // Each row represents a number on the phone.
         // 7 and 8 annoyingly have 4 possible letters, so we have to devote the
         // first byte to the number of possible letters. The remaining bytes
         // are the letters themselves, padded by the null byte if it's less
         // than 4.
         static char lookup_table2[] =
            "\3abc\0" // 2
            "\3def\0" // 3
            "\3ghi\0" // 4
            "\3jkl\0" // 5
            "\3mno\0" // 6
            "\4pqrs"  // 7
            "\3tuv\0" // 8
            "\4wxyz"  // 9
         ;
         size_t table_index = (digits[j] - '2') * 5;
         // each column has a different base
         char base = lookup_table2[table_index];
         size_t value = working_i % base;
         working_i /= base;
         char symbol = lookup_table2[table_index + 1 + value];
         this_combination[j] = symbol;
      }
   }

   *out_combinations = combinations;
   return combinations_buf;
}
