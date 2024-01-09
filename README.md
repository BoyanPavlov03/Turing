# Turing Machine Simulator #

This is a C++ implementation of a Turing Machine simulator, capable of running and composing Turing Machines based on provided input files. The simulator also supports running a Turing Machine in a loop while a specified predicate Turing Machine accepts the input.

## Usage ##
To use the Turing Machine simulator, compile the provided C++ code and run the executable. The program will prompt the user to enter commands. The supported commands are:

**run <machine_file> <tape_file>**: Run a Turing Machine with the specified machine description file and tape file.

**runWhile <predicate_file> <machine_file> <tape_file>**: Run a Turing Machine in a loop while the specified predicate machine accepts the input.

**runMachineDependingOn <recognizer_file> <acceptor_file> <rejector_file> <tape_file>**: Run one of two machines based on the recognition result of the recognizer machine.

**composition <first_machine_file> <second_machine_file> <tape_file>**: Compose two Turing Machines and run the resulting machine with the provided tape.

**exit**: Exit the program.

## File Formats ##

**Tape**: Tapes should start with *$* each symbol should be seperated by a space.

**Turing Machine**: Machines have the following format:

first line - all states

second line - alphabet

third line - start state

fourth line - stop state

rest - all transitions which are as follows: <state> <read> <newState> <write> <command> <helperMachine>(optional)

The helper machine role is if that particular transition needs to be executed by another machine.

**Example**

This is an example of a machine that swaps the digits of a binary number.

```
s q halt
_ 0 1
s
halt
q $ q $ R
s $ s $ R
s 0 q 1 S
s 1 q 0 S
s _ halt _ S
q 0 s 0 R
q 1 s 1 R
q _ s _ R
```
