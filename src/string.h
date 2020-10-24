#ifndef STRING_H
#define STRING_H

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_SMALL_STRING sizeof(char*) + sizeof(int)

typedef struct String {
   union {
      char* Data;
      int  Capacity;
      char SmallStringData[MAX_SMALL_STRING];
   } StringData;

   int Size;
} *string;

string NewString(const char* s);
void   DeleteString(string str);
char*  Raw(string str);
char   At(string str, size_t index);
int    Len(string str);
int    Capacity(string str);
void   Append(string str, string str2);
void   AppendString(string str, const char* s);
int    Compare(string str, string str2);
int    CompareString(string str, const char* s);
int    Equal(string str, string str2);
int    EqualString(string str, const char* s);
string Slice(string str, int start, int end);
int    HasSuffix(string str, string suffix);
string TrimSuffix(string str, string suffix);
int    HasPrefix(string str, string prefix);
string TrimPrefix(string str, string prefix);

#endif