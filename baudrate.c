// baudrate.c - simulate baud rate in a pipe
// examples:
//     telnet pdp11 23 | baudrate 2400
//     ssh localhost | baudrate 9600
//
// rricharz 2024
//

#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <signal.h>
#include <unistd.h>

struct termios oldt;
int tty_changed = 0;

void restore_terminal(void) {
  if (tty_changed && isatty(STDIN_FILENO)) {
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // apply old settings
    tty_changed = 0;
  }
}

void handle_signal(int sig) {
  restore_terminal();
  exit(0);
}

int getch(void) {
  static struct termios newt;
  static int initialized = 0;
  int ch;

  if (!initialized && isatty(STDIN_FILENO)) {
    tcgetattr(STDIN_FILENO, &oldt); // save original settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    tty_changed = 1;
    initialized = 1;

    atexit(restore_terminal);
    signal(SIGINT, handle_signal);
    signal(SIGTERM, handle_signal);
    signal(SIGPIPE, handle_signal);
  }

  ch = getchar();

  return ch;
}

int main(int argc, char *argv[]) {
  int c;
  if (argc != 2) {
    printf("Usage: baudrate b\n");
    printf("Where b is the baud rate to simulate (e.g. 4800)\n");
    exit(1);
  }

  int baud = atoi(argv[1]);
  if (baud <= 0) {
    printf("Error: baud rate must be positive\n");
    exit(1);
  }

  printf("Simulated baud rate set to %d baud\n", baud);
  while ((c = getch()) != EOF) {
    putchar(c);
    fflush(stdout);
    usleep(10000000/baud);
  }

  return 0;
}
