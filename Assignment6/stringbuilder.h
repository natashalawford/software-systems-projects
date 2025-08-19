/** Initializes the stringbuilder, allocating an underlying array of the given `capacity`. The
 * initial size of the stringbuilder is zero. */
void sb_init(int capacity);

/** Appends characters from `buf` to the end of the stringbuilder, until either a NUL byte is
 * reached or `len` many characters have been copied. */
void sb_append(char const *buf, int len);

/** Obtains a copy of the current contents of the stringbuilder as a malloc'd, null-terminated
 * string. It becomes the responsibility of the caller to call `free` on that string. */
char * sb_build();

/** Releases the memory held by the stringbuilder.
 * It is possible to call `sb_init` again after this to build another string. */
void sb_destroy();
