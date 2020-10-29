# cstring

Мое небольшое баловство на тему строк в Си с поддержкой оптимизации маленькой строки (`small string optimization`), когда для строки размером меньше `sizeof(char*) + sizeof(int)` не происходит выделения памяти в куче.

Реализованы следующие функции:

1. `string NewString(const char* s);`
2. `void   DeleteString(string str);`
3. `char*  Raw(string str);`
4. `char   At(string str, size_t index);`
5. `int    Len(string str);`
6. `int    Capacity(string str);`
7. `void   Append(string str, string str2);`
8. `void   AppendString(string str, const char* s);`
9. `int    Compare(string str, string str2);`
10. `int    CompareString(string str, const char* s);`
11. `int    Equal(string str, string str2);`
12. `int    EqualString(string str, const char* s);`
13. `string Slice(string str, int start, int end);`
14. `int    HasSuffix(string str, string suffix);`
15. `string TrimSuffix(string str, string suffix);`
16. `int    HasPrefix(string str, string prefix);`
17. `string TrimPrefix(string str, string prefix);`

