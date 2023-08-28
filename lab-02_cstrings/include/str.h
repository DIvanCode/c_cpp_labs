#pragma once

#include "stdio.h"

char *my_strcpy(char * restrict str1, const char * restrict str2);

char *my_strcat(char * restrict str1, const char * restrict str2);

int my_strcmp(const char *str1, const char *str2);

size_t my_strlen(const char *str);
