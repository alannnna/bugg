#include <iostream>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    if (argc == 1) {
        std::cout << "pass a program to debug!" << std::endl;
        return 1;
    }
    std::cout << argv[1] << std::endl;

    // A process can initiate a trace by calling fork(2) and having the
    // resulting child do a PTRACE_TRACEME, followed (typically) by an
    // execve(2).

    pid_t pid = fork();
    int ret;
    int status;
    if (pid == -1) {
        std::cout << "fork failed" << std::endl;
        return 1;
    } else if (pid == 0) {
        // Child process
        // ret = ptrace(PT_TRACE_ME, 0, 0, 0);
        // std::cout << "ptrace: " << ret << std::endl;
        ret = execve(argv[1], NULL, NULL);
        // execve will not return if successful
        std::cout << "execve returned, oh no: " << ret << std::endl;
    } else {
        do {
            ret = waitpid(pid, &status, 0);
            if (ret == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
            }

           if (WIFEXITED(status)) {
                printf("exited, status=%d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("killed by signal %d\n", WTERMSIG(status));
            } else if (WIFSTOPPED(status)) {
                printf("stopped by signal %d\n", WSTOPSIG(status));
            } else if (WIFCONTINUED(status)) {
                printf("continued\n");
            }
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        std::cout << "waitpid: " << ret << " " << status << std::endl;
    }

    return 0;
}
