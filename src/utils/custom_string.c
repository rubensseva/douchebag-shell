

char **alloc_string_arr(size_t str_size, arr_size) {
  char **strs = (char **) malloc(arr_size);
  for (int i = 0; i < arr_size; i++) {
    strs[i] = (char *) malloc(str_size);
  }
  return strs;
}
