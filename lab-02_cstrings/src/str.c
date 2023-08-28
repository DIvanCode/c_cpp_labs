#include "str.h"

char *my_strcpy(char * restrict str1, const char * restrict str2) {
  char *str = str1;
  while (*str2 != '\0') {
    *str1 = *str2;
    ++str1, ++str2;
  }
  *str1 = '\0';
  return str;
}

char *my_strcat(char * restrict str1, const char * restrict str2) {
  char *str = str1;
  while (*str1 != '\0') {
    ++str1;
  }
  while (*str2 != '\0') {
    *str1 = *str2;
    ++str1, ++str2;
  }
  *str1 = '\0';
  return str;
}

int my_strcmp(const char *str1, const char *str2) {
  while (*str1 != '\0' && *str2 != '\0') {
    if (*str1 < *str2) {
      return -1;
    }
    if (*str1 > *str2) {
      return 1;
    }
    ++str1, ++str2;
  }
  if (*str1 == '\0' && *str2 == '\0') {
    return 0;
  }
  if (*str1 == '\0') {
    return -1;
  }
  return 1;
}

size_t my_strlen(const char *str) {
  const char *str1 = str;
  while (*str != '\0') {
    ++str;
  }
  return str - str1;
}
