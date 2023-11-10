#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>
#include <string>

auto main() -> int {
    int memoryd;
    memoryd = open("memory.txt", O_RDWR | O_CREAT | O_TRUNC, 0666);

    ftruncate(memoryd, 1024);
    char* buffer = (char*)mmap(NULL, 4096, PROT_WRITE, MAP_SHARED, memoryd, 0);

    // Forking the process
    int id = fork();

    if (id == -1) {  // fork error
        return 2;
    } else if (id == 0) {  // child process

        execlp("./calculator", "./calculator", NULL);

        return 3;
    } else {  // parent process
        char c;
        c = getchar();
        size_t i = 0;

        while (c != EOF) {
            buffer[i++] = c;
            c = getchar();
        }

        std::cout << "Test";
        int status;
        waitpid(0, &status, 0);  // waiting for child process to finish

        return status;
    }
}
