int find_linebreak(char *str, int size, int *index) {
  for (int i = 0; i < size; i++) {
    if (str[i] == '\0') {
      *index = i;
      return 0;
    }
  }
  return 1;
}
