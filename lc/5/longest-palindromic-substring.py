class Solution:
   def longestPalindrome(self, s: str) -> str:
      long_len = 0
      long_pal = ""

      for i in range(0, len(s)):
         for j in range(i + long_len, len(s)):
            subtr = s[i:j + 1]
            if subtr[::-1] == subtr:
               if len(subtr) > long_len:
                  long_len = len(subtr)
                  long_pal = subtr

      return long_pal
