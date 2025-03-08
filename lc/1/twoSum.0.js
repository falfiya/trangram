/**
 * @param {number[]} nums
 * @param {number} target
 * @return {number[]}
 *
 * Brute force. O(n^2)
 */
function twoSum(nums, target) {
   for (let i = 0; i < nums.length; i++) {
      for (let j = 0; j < nums.length; j++) {
         if (i === j) {
            continue;
         }
         if (nums[i] + nums[j] === target) {
            return [i, j];
         }
      }
   }
};
