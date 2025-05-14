# gdbinit

# set Commmand Line Arguements
set args -i 10.1.1.48 -p 502 -s 5 1

# allow for "printf "%d\n", var" style "pretty printing"
set print pretty on

# direct stdout to a specifical alternate terminal window.
# - run 'tty' in a open terminal to see the device path.
# tty /dev/pts/2

# load all the saved breakpoints.
source gdb-breakpoints.txt

