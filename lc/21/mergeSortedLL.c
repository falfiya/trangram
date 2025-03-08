struct ListNode {
   int val;
   struct ListNode *next;
};

struct ListNode *mergeTwoLists(struct ListNode *a, struct ListNode *b) {
   struct ListNode start;
   struct ListNode *c = &start;

   while (1) {
      if (a == 0) {
         c->next = b;
         c = b;
         break;
      }
      if (b == 0) {
         c->next = a;
         c = a;
         break;
      }

      if (b->val < a->val) {
         c->next = b;
         c = b;
         b = b->next;
      } else {
         c->next = a;
         c = a;
         a = a->next;
      }
   }

   return start.next;
}
