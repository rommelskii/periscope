#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define TMP_FILE "/tmp/log.ps"

int main()
{
  FILE* pFile = fopen("/tmp/log.ps", "r");
  char buf[1024];
  memset(buf, 0, sizeof(buf));
  
  while (fgets(buf, sizeof(buf), pFile) != NULL)  
  {
    printf("%s", buf);
  }

  return 0;
}
