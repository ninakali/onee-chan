#include <stdint.h>
#include <stdio.h>

extern void exec86 (int execloops);
extern void reset86();
extern void file_init ();

void	portout (uint16_t portnum, uint8_t value) {}
void	portout16 (uint16_t portnum, uint16_t value) {}
uint8_t	portin (uint16_t portnum) {
  return 0;
}
uint16_t portin16 (uint16_t portnum) {
  return 0;
}


int main() {
  file_init();
  reset86();
  printf("Starting 8086...\n");
  while (1) exec86(1);
}
