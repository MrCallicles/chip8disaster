# Chip8Disaster

My first attempt to make a Chip8 emulator, disassembler and debugger.

From now, only the disassembler work properly but basically.

# Compile

To compile : make. Then ./chip8disaster

To compile the test program : make test. Then ./test\_chip
(there must be a roms/PONG path in the directory)

To clean the directory (delete .o files) : make clean

# Usage

disassemble : ./chip8disaster [PATH TO ROM]

debugger : ./chip8disaster [PATH TO ROM] --debug

emulator : Not working

test : ./test\_chip
(there must be a roms/PONG path in the directory)

# Debugger

Support only few commands today :

- exit or quit : quit the program
- run or r : run the debugger (in step mode)
- step : go to the next instruction
- reg or register : show general registers
- cpu : show registers except general registers
- mem : show memory content
