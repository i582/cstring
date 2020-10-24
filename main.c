#include <stdio.h>
#include "src/string.h"

int main() {
   string str = NewString("Hello ");
   string str2 = NewString("World");

   Append(str, str2);

   printf("%s", Raw(str));

   DeleteString(str);
   DeleteString(str2);
}