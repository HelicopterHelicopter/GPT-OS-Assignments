#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>

// Signal handler for SIGCHLD to handle zombie processes
void handle_sigchld(int sig) {
    //waitpid is used to make a process wait for a specific child process to change its state, such as exiting, being stopped, or resuming after being stopped.
    //-1 means to wait for any child process.
    //WNOHANG means to return immediately if no child has changed state.
    while (waitpid(-1, NULL, WNOHANG) > 0);   
    printf("[Parent] Cleaned up a zombie process\n");
}

//Simulated memory segments
char code_segment[256] = "This is a simulated code segment";
char data_segment[256] = "This is a simulated data segment";
char stack_segment[256];

// Function for child process to write to a file
void child_write_file() {
    int fd = open("child_output.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0 ) {
        perror("File open error");  //used to print human-readable error message to the standard error stream.
        exit(1);
    }
    write(fd, "Hello from child 1\n", 19);
    close(fd);
    exit(0);
}

void child_compute_factorial(int num) {
    int factorial = 1;
    for (int i=1; i<=num; i++){
        factorial *= i;
    }

    printf("[Child2] Factorial of %d is %d\n", num, factorial);
    exit(0);
}

// Simulate Stack Operations
void simulate_stack_operations() {
    printf("[Parent] Simulating stack operations...\n");
    asm volatile (              // volatile tells the compiler not to optimize the assembly code. Syntax: asm volatile ("assembly-code" : output-operands : input-operands : clobbered-registers);
        "mov $0x1234, %%rax\n"  //Load value into RAX. Here we are using RAX instead of EAX because the machine is 64-bit
        "push %%rax\n"          //Push RAX onto the stack
        "pop %%rbx\n"           //Pop the value into RBX
        :                       // No outputs
        :                       // No inputs
        : "rax", "rbx"          // Clobbered registers (specifies registers or memory locations that are modified by the assembly code to inform the compiler)
    );
    printf("[Parent] Stack operations simulated\n");
}

//Signal handler for SIGITN
void handle_sigint(int sig) {
    printf("\n[Parent] Caught SIGINT (Keyboard Interrupt)\n");
}

int main(){

    pid_t pid1, pid2; //pid_t is a data type defined in POSIX standard to represent process IDs. Comes from <sys/types.h>

    //Setup signal handlers
    signal(SIGCHLD, handle_sigchld);
    signal(SIGINT, handle_sigint);

    printf("[Parent] Starting simulation... \n");

    //Fork the first child to write to a file
    if((pid1=fork())==0){
        child_write_file();
    }

    //Fork the second child to compute factorial
    if((pid2=fork())==0){
        child_compute_factorial(5);
    }

    // Parent simulates memory segments
    printf("[Parent] Simulating memory segmentation:\n");
    printf("Code segment: %s\n", code_segment);
    printf("Data segment: %s\n", data_segment);
    strcpy(data_segment, "Modified data segment.");
    printf("Modified Data Segment: %s\n", data_segment);

    //Parent simulates stack operations
    simulate_stack_operations();

    while(wait(NULL) > 0);

    printf("[Parent] All child processes completed. Exiting simulation. \n");
    return 0; 

}