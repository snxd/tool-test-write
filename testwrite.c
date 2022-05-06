#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <memory.h>
#ifdef _WINDOWS
#include <io.h>
#include <share.h>

#define open _open
#define read _read
#define write _write
#define close _close
#define unlink _unlink
#else
#include <unistd.h>

#define O_BINARY 0
#endif

unsigned int randr(unsigned int min, unsigned int max) {
    double scaled = (double)rand() / RAND_MAX;
    return (unsigned int)((max - min +1) * scaled + min);
}

int main(int argc, char* argv[]) {
    char Data[16384] = { 0 };
    char Compare[16384] = { 0 };

    srand((unsigned)time(NULL));

    for (int z = 0;; ++z) {
        printf("Pass %d\n", z);
        for (int x = 0; x < 16384; ++x) {
            Data[x] = (char)randr(0, 255);
        }

        unlink("test.bin");

        int file = open("test.bin", O_RDWR | O_CREAT | O_BINARY, S_IREAD | S_IWRITE | S_IEXEC);
        for (int x = 0; x < 30000; ++x) {
            if (write(file, Data, 16384) != 16384) {
                printf("Bad Write\n");
            }
        }

        close(file);

        file = open("test.bin", O_RDONLY | O_BINARY, S_IREAD | S_IWRITE | S_IEXEC);
        for (int x = 0; x < 30000; ++x) {
            memset(Compare, 0, 16384);
            if (read(file, Compare, 16384) != 16384) {
                printf("Bad Read\n");
            }

            for (int y = 0; y < 16384; ++y) {
                if (Compare[y] != Data[y]) {
                    printf("Bad Data\n");
                    break;
                }
            }
        }

        close(file);
    }

    return 0;
}
