# Chip8Disaster

My first attempt to make a Chip8 emulator, disassembler and debugger.

For now, only the disassembler works, in a simple but effective way.

# Compile

To compile : 
```bash
make 
```

To Run:
```bash
./chip8disaster
```

To compile the test program :
```bash
make test
```

To run the test program: (there must be a roms/PONG path in the directory)
```bash
./test_chip
```

To clean the directory (delete .o files and executables) :
```bash
make clean
```

# Usage

disassemble : 
```bash 
./chip8disaster [PATH TO ROM]
```

debugger :
```bash 
./chip8disaster [PATH TO ROM] --debug
```

emulator : Not working

test : (there must be a roms/PONG path in the directory)
```bash 
 ./test_chip
```

# Debugger

Support only few commands today :

- exit or quit : quit the program
- run or r : run the debugger (in step mode)
- step : go to the next instruction
- reg or register : show general registers
- cpu : show registers except general registers
- stack : show stack (nested call) content

