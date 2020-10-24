#include "string.h"

void setCapacity(string str, size_t len);
int isSmallString(string str);

string NewString(const char* s) {
   assert(s != NULL);

   string str = (string)calloc(1, sizeof(struct String));
   size_t len = strlen(s);

   if (len < MAX_SMALL_STRING) {
      for (int i = 0; i < len; ++i) {
         str->StringData.SmallStringData[i] = s[i];
      }
      str->StringData.SmallStringData[len] = '\0';
   } else {
      size_t cap = len * 2;
      str->StringData.Data = (char*)calloc(1, cap + 1);
      for (int i = 0; s[i] != '\0'; ++i) {
         str->StringData.Data[i] = s[i];
      }
      str->StringData.Data[len] = '\0';
      setCapacity(str, cap);
   }

   str->Size = len;
   return str;
}

int Len(string str) {
   assert(str != NULL);

   return str->Size;
}

char At(string str, size_t index) {
   assert(str != NULL);
   assert(index < Len(str));

   if (isSmallString(str)) {
      return str->StringData.SmallStringData[index];
   } else {
      return str->StringData.Data[index];
   }
}

void DeleteString(string str) {
   assert(str != NULL);

   if (!isSmallString(str)) {
      free(str->StringData.Data);
   }

   free(str);
}

int Capacity(string str) {
   assert(str != NULL);

   if (isSmallString(str)) {
      return MAX_SMALL_STRING;
   } else {
      return *(int*)(&str->StringData.SmallStringData[0] + sizeof(char*));
   }
}

char* Raw(string str) {
   assert(str != NULL);

   if (isSmallString(str)) {
      return &str->StringData.SmallStringData[0];
   } else {
      return str->StringData.Data;
   }
}

void AppendString(string str, const char* s) {
   assert(str != NULL);
   assert(s != NULL);

   size_t rightLen = strlen(s);
   size_t leftLen = Len(str);
   size_t newLen = leftLen + rightLen;
   int isSmall = isSmallString(str);

   if (isSmall && newLen < MAX_SMALL_STRING) {
      for (int i = Len(str), j = 0; i < newLen && j < rightLen; ++i, ++j) {
         str->StringData.SmallStringData[i] = s[j];
      }
      str->StringData.SmallStringData[newLen] = '\0';
   } else if (isSmall) {
      size_t cap = newLen * 2;
      char* data = (char*)calloc(1, cap + 1);

      for (int i = 0; i < leftLen; ++i) {
         data[i] = At(str, i);
      }

      for (int i = leftLen, j = 0; i < newLen && j < rightLen; ++i, ++j) {
         data[i] = s[j];
      }

      data[newLen] = '\0';
      setCapacity(str, cap);

      str->StringData.Data = data;
      str->Size = newLen;
   } else {
      int cap = Capacity(str);
      if (cap > newLen) {
         for (int i = leftLen, j = 0; i < newLen && j < rightLen; ++i, ++j) {
            str->StringData.Data[i] = s[j];
         }
         str->StringData.Data[newLen] = '\0';
         str->Size = newLen;
      } else {
         char* data = (char*)calloc(1, newLen * 2 + 1);

         for (int i = 0; i < leftLen; ++i) {
            data[i] = At(str, i);
         }

         for (int i = leftLen, j = 0; i < newLen && j < rightLen; ++i, ++j) {
            data[i] = s[j];
         }

         data[newLen] = '\0';
         setCapacity(str, newLen * 2);

         str->StringData.Data = data;
         str->Size = newLen;
      }
   }
}

void Append(string str, string str2) {
   AppendString(str, Raw(str2));
}

int EqualString(string str, const char* s) {
   return CompareString(str, s) == 0;
}

int Equal(string str, string str2) {
   return Compare(str, str2) == 0;
}

int CompareString(string str, const char* s) {
   return strcmp(Raw(str), s);
}

int Compare(string str, string str2) {
   return CompareString(str, Raw(str2));
}

string Slice(string str, int start, int end) {
   assert(str != NULL);
   assert(start >= 0);

   int len = Len(str);

   if (end < 0) {
      end = len + end;
   }

   if (end > len) {
      end = len;
   }

   int sliceLen = end - start;
   if (sliceLen == 0) {
      return NewString("");
   }

   string newStr = (string)calloc(1, sizeof(struct String));
   char* src = Raw(str);
   src += start;

   if (sliceLen < MAX_SMALL_STRING) {
      strncpy(newStr->StringData.SmallStringData, src, sliceLen);
      newStr->StringData.SmallStringData[sliceLen] = '\0';
      newStr->Size = sliceLen;
   } else {
      newStr->StringData.Data = (char*)calloc(1, sliceLen * 2 + 1);
      strncpy(newStr->StringData.Data, src, end - start);
      newStr->Size = sliceLen;
      setCapacity(newStr, sliceLen * 2);
   }

   return newStr;
}

int HasSuffix(string str, string suffix) {
   if (Len(suffix) > Len(str)) {
      return 0;
   }

   for (int i = Len(str) - 1, j = Len(suffix) - 1; i >= 0 && j >= 0; --i, --j) {
      if (At(str, i) != At(suffix, j)) {
         return 0;
      }
   }

   return 1;
}

string TrimSuffix(string str, string suffix) {
   if (!HasSuffix(str, suffix)) {
      return str;
   }

   return Slice(str, 0, Len(str) - Len(suffix));
}

int HasPrefix(string str, string prefix) {
   if (Len(prefix) > Len(str)) {
      return 0;
   }

   for (int i = 0, j = 0; i < Len(str) && j < Len(prefix); ++i, ++j) {
      if (At(str, i) != At(prefix, j)) {
         return 0;
      }
   }

   return 1;
}

string TrimPrefix(string str, string prefix) {
   if (!HasPrefix(str, prefix)) {
      return str;
   }

   return Slice(str, Len(prefix), Len(str));
}

void setCapacity(string str, size_t len) {
   assert(str != NULL);

   *(int*)(&str->StringData.SmallStringData[0] + sizeof(char*)) = len;
}

int isSmallString(string str) {
   assert(str != NULL);

   return str->Size < MAX_SMALL_STRING;
}
