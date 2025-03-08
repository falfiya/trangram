/**
 * Pushdown automata version
 */
function isValid(s: string): boolean {
   const stack: ("(" | "{" | "[")[] = [];
   for (const c of s) {
      switch (c) {
      case "(":
      case "{":
      case "[":
         stack.push(c);
         break;
      case ")":
         if (stack.pop() !== "(")
            return false;
         break;
      case "}":
         if (stack.pop() !== "{")
            return false;
         break;
      case "]":
         if (stack.pop() !== "[")
            return false;
         break;
      default:
         return false;
      }
   }
   return stack.length === 0;
}
