import java.util.*;
import java.util.stream.Collectors;

class Node {
   public int val;
   public List<Node> neighbors;
   public Node() {
      val = 0;
      neighbors = new ArrayList<Node>();
   }
   public Node(int _val) {
      val = _val;
      neighbors = new ArrayList<Node>();
   }
   public Node(int _val, ArrayList<Node> _neighbors) {
      val = _val;
      neighbors = _neighbors;
   }
}

class Solution {
   Hashtable<Node, Node> memoize = new Hashtable<>();
   public Node cloneGraph(Node x) {
      if (x == null) {
         return x;
      }
      if (memoize.containsKey(x)) {
         return memoize.get(x);
      }

      var y = new Node();
      y.val = x.val;
      memoize.put(x, y);

      y.neighbors = x.neighbors
         .stream()
         .map(this::cloneGraph)
         .collect(Collectors.toCollection(ArrayList::new));

      return y;
   }
}
