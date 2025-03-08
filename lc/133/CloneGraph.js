function _Node(val, neighbors) {
   this.val = val === undefined ? 0 : val;
   this.neighbors = neighbors === undefined ? [] : neighbors;
};

function cloneGraph(n, a = []) {
   if (n == null) {
      return null;
   }

   const key = n.val;

   if (key in a) {
      return a[n.val];
   }

   const m = new _Node(key);
   a[key] = m;

   m.neighbors = n.neighbors.map(x => cloneGraph(x, a));

   return m;
}
