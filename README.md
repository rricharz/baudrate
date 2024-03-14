# baudrate
Linux filter to simulate baud rates on terminal programs such
as cool-retro-term.

This little program is very useful if you are connecting to a
host from within cool-retro-term using tcp/ip (ssh or telnet).

Unfortunately cool-retro-term does not allow to simulate a baud
rate if the connection is done with ssh or telnet instead of
a serial line. This program adds this feature. It also works
together with any other program producing output on stdout.

Video showing baudrate used together with cool-retro-term, connecting to
a simulated PDP-11 running 2.11 BSD:

https://www.youtube.com/watch?v=RUKjzGCJkUs

Installation:

    git clone https://github.com/rricharz/baudrate.git
    cd baudrate
    make clean
    make
    make install

Examples of usage:

    telnet <hostname> <port> | baudrate 2400
    ssh localhost | baudrate 4800
    cat <filename> | baudrate 1200
    vi <filename> | baudrate 9600

If it is used with a command such as vi or cat, the baud rate
is just limited for the output of this command. If it is used
with ssh or telnet, the baud rate of the subsequent output
in the new login shell is limited.

Use it with cool-retro-term:

    sudo apt install cool-retro-term
    cool-retro-term
    Now you can use any of the examples in cool-retro-term

To use cool-retro-term on the PiDP-11, look at
https://github.com/rricharz/pidp11-2.11bsd/blob/master/Cool.pdf

If cool-retro-term is used with SimH, there is also another
solution available to limit the baud rate. But limiting the
baud rate at the terminal side with baudrate is typically
less choppy.

    Using 2.11 BSD:
    "stty" shows the current baud rate
    "stty 4800" for example, sets the baudrate

    Using RSX:
    "SET /SPEED=T1:9600:9600" (MCR)
    "SET TERM/SPEED=9600" (DCL)

  
  


