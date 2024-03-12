# baudrate
Linux filter to simulate baud rates on terminal programs using telnet

This little program is very useful if you are using a telnet
session to connect to a host from within cool-retro-term

Unfortunately cool-retro-term does not allow to simulate a baud
rate if the connection is done with telnet instead of a serial
line. This program adds this feature. It also works together with
the standard terminal (console), and any program producing
output on stdout.

Installation:

    git clone https://github.com/rricharz/baudrate.git
    cd baudrate
    make clean
    make
    make install

Example of usage with telnet:

    telnet <hostname> <port> | baudrate 2400 

Example of usage without telnet:

    cat <filename> | baudrate 1200
    ssh localhost | baudrate 4800

To use it together with cool-retro-term:

    sudo apt install cool-retro-term
    cool-retro-term
    Now you can use any of the examples above

To use cool-retro-term on the PiDP-11, look at
https://github.com/rricharz/pidp11-2.11bsd/blob/master/Cool.pdf
  
  


