#include "../include/string.hpp"

#include <iostream>

#define UPPER_CASE 1
#define LOWER_CASE 0

namespace string {
// 1 ------> upper case 0 --------> lowercase
void vChangeCasePc(char* str, int caseType);
// int iStringLengthPc(char* str);

void vToUpperPc(char* str) { vChangeCasePc(str, UPPER_CASE); }
void vToLowerPc(char* str) { vChangeCasePc(str, LOWER_CASE); }
// case helper function
void vChangeCasePc(char* str, int caseType) {
  signed char delta;
  char startA, endZ;
  int counter = 0;
  if (caseType == UPPER_CASE) {
    delta = 'A' - 'a';
    startA = 'a';
    endZ = 'z';
  } else {
    delta = 'a' - 'A';
    startA = 'A';
    endZ = 'Z';
  }
  while (str[counter] != '\0') {
    if (str[counter] > startA && str[counter] < endZ) {
      str[counter] += delta;
    }
    counter++;
  }
}
int iCompareStringPcPc(char* str1, char* str2) {
  // compare based on length ----> retrun 1
  // compare based on word ------> return 2
  // compare based on word & length ----> return 3
  int len1 = iStringLengthPc(str1);
  int len2 = iStringLengthPc(str2);
  int flag = 0;
  if (len1 == len2) {
    while (len1 && !flag) {
      if (str1[len1] != str2[len1]) {
        flag = 1;
      }
      len1--;
    }
  } else if (len1 > len2) {
    flag = 2;
    for (int i = 0; i < len1 && flag != 4; i++) {
      if (str1[i] != str2[i]) {
        flag = 4;
      }
    }

  } else {
    flag = 3;
    for (int i = 0; i < len1 && flag != 4; i++) {
      if (str1[i] != str2[i]) {
        flag = 4;
      }
    }
  }

  return flag;
}

void iCopyStringPcPc(char* src, char* des) {
  int lenSrc = iStringLengthPc(src);
  int lenDes = iStringLengthPc(des);
  int cnt = 0;
  if (lenDes == lenSrc) {
    while (src[cnt] != '\0') {
      des[cnt] = src[cnt];
      cnt++;
    }
  } else if (lenDes > lenSrc) {
    while (src[cnt] != '\0') {
      des[cnt] = src[cnt];
      cnt++;
      lenDes--;
    }
    while (lenDes--) {
      des[cnt + lenDes] = '\0';
    }

  } else {
    while (lenDes--) {
      des[lenDes] = src[lenDes];
    }
  }
}

void iCopyStaticStringWithSameLength(char* src, char* des) {
  int srcLen = iStringLengthPc(src);
  std::fill(des, des + srcLen, '\0');
  int cnt = 0;
  while (src[cnt] != '\0') {
    des[cnt] = src[cnt];
    cnt++;
  }
}

int iStringLengthPc(char* str) {
  if (str[0] == '\0') {
    return 0;
  }
  int cnt = 1;
  while (str[cnt] != '\0') {
    cnt++;
  }
  return cnt;
}

}  // namespace string