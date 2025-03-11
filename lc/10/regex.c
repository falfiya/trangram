#include <stdlib.h>

enum ReType {
   RE_COUNT,
   RE_STAR,
};
typedef enum ReType ReType; // -Wmicrosoft-enum-forward-reference

typedef struct ReCount ReCount;
struct ReCount {
   char letter;
   size_t count;
};

typedef struct ReStar ReStar;
struct ReStar {
   char letter;
};

// linked list of nodes
typedef struct ReCommandNode ReCommandNode;
struct ReCommandNode {
   ReCommandNode *next;
   ReType type;
   union {
      char letter;
      ReCount ReCount;
      ReStar ReStar;
   };
};

char WILDCARD = -1;

ReCommandNode *parseRegex(char *p, size_t p_len) {
   ReCommandNode *buf = malloc(sizeof(*buf) * p_len);
   ReCommandNode *prev = NULL;
   ReCommandNode *curr = buf;
   for (size_t i = 0; i < p_len;) {
      char c = p[i];
      char n = p[i + 1];
      if (n == '*') {
         curr->type = RE_STAR;
         curr->ReStar.letter = c == '.' ? WILDCARD : c;
         curr->next = curr + 1;
         prev = curr;
         curr++;
         i++;
         i++; // and again because of the star
      } else {
         curr->type = RE_COUNT;
         curr->ReCount.letter = c == '.' ? WILDCARD : c;
         curr->ReCount.count = 1;
         curr->next = curr + 1;
         prev = curr;
         curr++;
         i++;
      }
   }

   if (prev != NULL) {
      prev->next = NULL;
   }

   return buf;
};

void normalizeRegex(ReCommandNode *commands) {
   if (commands == NULL) {
      return;
   }

   ReCommandNode *curr = commands;
   while (curr->next != NULL) {
      if (curr->type == curr->next->type && curr->letter == curr->next->letter) {
         if (curr->type == RE_COUNT) {
            curr->ReCount.count += curr->next->ReCount.count;
            curr->next = curr->next->next;
            // skip list element
            // do not move the current pointer
            continue;
         }

         if (curr->type == RE_STAR) {
            curr->next = curr->next->next;
            // do not move the current pointer
            continue;
         }
      }

      // no normalization found
      // move the current pointer
      curr = curr->next;
   }
};

bool recursiveMatcher(ReCommandNode *command, char *s) {
   if (command == NULL) {
      // reached the end of the regexp.
      // require the string to be over
      return *s == '\0';
   }

   if (command->type == RE_COUNT) {
      if (command->letter == WILDCARD) {
         // for wildcard, we only need to check if the string is long enough
         for (size_t i = 0; i < command->ReCount.count; i++, s++) {
            if (*s == '\0') {
               return 0;
            }
         }
      } else {
         for (size_t i = 0; i < command->ReCount.count; i++, s++) {
            if (*s != command->letter) {
               return 0;
            }
         }
      }
      // if we reach here, the match worked.
      return recursiveMatcher(command->next, s);
   }

   if (command->type == RE_STAR) {
      // try matching nothing
      if (recursiveMatcher(command->next, s)) {
         return 1;
      }

      if (command->letter == WILDCARD) {
         while (*s != '\0') {
            if (recursiveMatcher(command->next, s + 1)) {
               return 1;
            } else {
               // guess we need to match more
               s++;
            }
         }
      } else {
         while (*s == command->letter) {
            if (recursiveMatcher(command->next, s + 1)) {
               return 1;
            } else {
               s++;
            }
         }
      }
      // if we've reached here, we couldn't match anything
      return 0;
   }

   __builtin_trap();
}

bool isMatch(char *s, char *p) {
   size_t p_len = 0;
   while (p[p_len] != '\0') {
      p_len++;
   }

   ReCommandNode *commands = parseRegex(p, p_len);
   normalizeRegex(commands);

   return recursiveMatcher(commands, s);
}
