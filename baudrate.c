// baudrate.c - simulate baud rate in a pipe
// example: telnet pdp11 23 | baudrate 2400
//
// rricharz 2024
//

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

int getch(void) {
  int ch;
  struct termios oldt;
  struct termios newt;
  
  tcgetattr(STDIN_FILENO, &oldt); // save old settings
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);  
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  
  ch = getchar();
  
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // apply old settings
  
  return ch;
}


int main(int argc, char *argv[]) {
  char c;
  if (argc != 2) {
    printf("Usage baudrate b\n");
    printf("Where b is the baud rate to simulate (e.g. 4800)\n");
    exit(1);
  }

  int baud = atoi(argv[1]);

  printf("Simulated baud rate set to %d baud\n",baud);
  while ((c = getch()) != (EOF & 0xff)) {
    putchar(c);
    fflush(stdout);
    usleep(10000000/baud);
  }
  return 0;
}
