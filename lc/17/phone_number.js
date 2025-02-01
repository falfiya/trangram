/**
 * @param {number} digit
 * @returns {string}
 */
function getDigitNumbers(digit) {
   return ["abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"][digit - 2];
}

/**
 * @param {string} digits
 * @returns {string[]}
 */
function letterCombinations(digits) {
   if (digits.length === 0)
      return [];

   const [head, ...tail] = digits;
   const fst = [...getDigitNumbers(+head)];
   if (tail.length === 0)
      return fst;

   const rest = letterCombinations(tail);
   return fst.flatMap(a => rest.map(b => a + b));
};
