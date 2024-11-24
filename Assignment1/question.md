# Assignment Title
"Building a Simplified Operating System Simulator"

# Objective
To simulate a basic operating system environment with:
1. Process Creation and management
2. System call handling
3. Stack and memory management
4. Interrupt handling using software interrups

# Requirements
1. ### Process Management:
    + Write a program that creates multiple child processes using the fork() system call.
    + Each child process should perform a unique task (e.g., print its PID and perform a mathematical computation)
    + Implement logic to handle zombie processes (use SIGCHLD tp reap child processes)
2. ### Memory Segmentation Simulation:
    + Define and manipulate code, data, and stack segments using arrays to simulate the behavior.
    + Use pointers to emulate access to different memory segments.
3. ### System Call Simulation:
    + Implement a basic write system call to write data to a file
    + USe int 0x80 (or equivalent syscall interface) in an inline assembly block to demonstrate software interrupts for system calls
4. ### Interrupt Handling:
    + Use signal handlers to simulate interrupt handling (e.g., a keyboard interrupt using SIGINT )
    + Print appropriate messages when the interrupt occurs
5. ### Stack OPerations:
    + Simulate stack operations (push, pop) for function calls using assembly instructions
    + Demonstrate stack growth/shrinking behavior in memory

# Assignment Deliverables:
1. A single C program with well-documented code.
2. A README file explaining how to compile and run the program.
3. Sample output of your program.

# Suggested Implementation Details:
1. ## File: os_simulation.c
    + Section 1: Process Management
    `// Create a parent process that forks multiple child processes`
    `// Handle zombies using signal(SIGCHLD, handler);`
    + Section 2: Memory Segmentation
    `// Simulate memory segments using arrays`
    `char code_segment[256];   // Read-only`
    `char data_segment[256];   // Writable`
    `char stack_segment[256];  // Simulated stack`
    + Section 3: System Calls
    `// Use write() and demonstrate syscall interface`
    `asm("int $0x80");  // Inline assembly for system call`
    + Section 4: Interrupt Handling
    `// Use signal(SIGINT, handler) to simulate keyboard interrupt`
    + Section 5: Stack Operations
    `// Inline assembly for PUSH/POP`
    `asm("push %eax; pop %ebx");`

2. ## Example Test Case:
    + Parent process forks 2 children.
    + Child 1 writes "Hello from Child 1" to a file.
    + Child 2 computes the factorial of a number and prints the result.
    + Trigger a SIGINT to demonstrate interrupt handling.
