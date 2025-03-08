/**
 * @param {number[]} nums
 * @param {number} target
 * @return {number[]}
 *
 * O(n*object_lookup(n))
 */
function twoSum(nums, target) {
   const index = Object.create(null);
   for (let i = 0; i < nums.length; i++) {
      const curr = nums[i];
      index[curr] = i;
   }

   for (let i = 0; i < nums.length; i++) {
      const curr = nums[i];
      const needed = target - curr;
      const j = index[needed];
      if (j == null) continue;
      if (j === i) continue;
      return [i, j];
   }
};
