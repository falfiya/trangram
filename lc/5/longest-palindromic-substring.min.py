class Solution:
 def longestPalindrome(self,s):
  l=0;L=len;a=L(s);r=range
  for i in r(0,a):
   for j in r(i+l,a):
    q=s[i:j+1]
    if q[::-1]==q and L(q)>l:l=L(q);I=q
  return I
