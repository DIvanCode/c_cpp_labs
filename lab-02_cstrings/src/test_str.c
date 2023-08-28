#include "test_str.h"
#include "str.h"
#include "string.h"
#include "assert.h"
#include "stdio.h"

void test_strcpy() {
  printf("\ttest_strcpy\n");
  {
    printf("test_strcpy 1\n");

    char str[80], my_str[80];
    strcpy(str, "hello");
    char *str1 = my_strcpy(my_str, "hello");

    printf("%s\n%s\n", str, my_str);

    assert(my_str == str1);
    assert(strcmp(str, my_str) == 0);

    printf("OK\n");
  }

  {
    printf("test_strcpy 2\n");

    char str[6], my_str[7];
    strcpy(str, "hello");
    char *str1 = my_strcpy(my_str, "hello");

    printf("%s\n%s\n", str, my_str);

    assert(my_str == str1);
    assert(strcmp(str, my_str) == 0);

    printf("OK\n");
  }
  printf("\n");
}

void test_strcat() {
  printf("\ttest_strcat\n");
  {
    printf("test_strcat 1\n");

    char str[80];
    str[0] = '\0';

    char *str1 = my_strcat(str, "Hello");
    assert(str == str1);
    str1 = my_strcat(str, ", World!");
    assert(str == str1);
    
    printf("%s\n", str);

    assert(strcmp(str, "Hello, World!") == 0);

    printf("OK\n");
  }
  {
    printf("test_strcat 2\n");
    
    char str[80], my_str[80];
    str[0] = '\0'; my_str[0] = '\0';
    
    char *str1 = strcat(str, "hello");
    assert(str1 == str);
    str1 = strcat(str, "");
    assert(str1 == str);
    
    my_strcat(my_str, "hello");
    my_strcat(my_str, "");

    printf("%s\n%s\n", str, my_str);

    assert(strcmp(str, my_str) == 0);
    printf("OK\n");
  }
  printf("\n");
}

void test_strcmp() {
  printf("\ttest_strcmp\n");
  {
    printf("test_strcmp 1\n");
    
    assert(strcmp("hello", "hello") == my_strcmp("hello", "hello"));
    
    printf("OK\n");
  }
  {
    printf("test_strcmp 2\n");
    
    assert(strcmp("hello", "hell") == my_strcmp("hello", "hell"));

    printf("OK\n");
  }
  {
    printf("test_strcmp 3\n");
    
    assert(strcmp("hell", "hello") == my_strcmp("hell", "hello"));

    printf("OK\n");
  }
  {
    printf("test_strcmp 4\n");

    assert(strcmp("hell", "fell") == my_strcmp("hell", "fell"));

    printf("OK\n");
  }
  {
    printf("test_strcmp 5\n");

    assert(strcmp("fell", "hell") == my_strcmp("fell", "hell"));
    
    printf("OK\n");
  }
  printf("\n");
}

void test_strlen() {
  printf("\ttest_strlen\n");
  {
    printf("test_strlen 1\n");

    assert(strlen("hello") == my_strlen("hello"));
    
    printf("OK\n");
  }
  {
    printf("test_strlen 2\n");
    
    assert(strlen("") == my_strlen(""));
    
    printf("OK\n");
  }
  printf("\n");
}
