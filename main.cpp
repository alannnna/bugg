#include <iostream>
#include <unistd.h>
#include <sys/ptrace.h>

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
    if (pid == 0) {
        ret = ptrace(PT_TRACE_ME, 0, 0, 0);
        if (ret < 0) {
            std::cerr << "failed to trace me: " << ret << std::endl;
            return 1;
        }
        ret = execve(argv[1], argc > 2 ? argv + 2 : NULL, argc > 3 ? argv + 3 : NULL);
        if (ret < 0) {
            std::cerr << "failed to execve: " << ret << std::endl;
            return 1;
        }
    }
    ret = waitpid(pid, NULL, 0);
    if (ret < 0) {
        std::cerr << "failed to waitpid: " << ret << std::endl;
        return 1;
    }
    std::cout << "waitpid: " << ret << std::endl;

    return 0;
}