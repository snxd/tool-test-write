#include <io.h>
#include <sys/stat.h>
#include <share.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <memory.h>

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

        _unlink("test.bin");

        int file = _sopen("test.bin", _O_RDWR | _O_CREAT |_O_BINARY, _SH_DENYNO, S_IREAD | S_IWRITE | S_IEXEC);
        for (int x = 0; x < 30000; ++x) {
            if (_write(file, Data, 16384) != 16384) {
                printf("Bad Write\n");
            }
        }

        _close(file);

        file = _sopen("test.bin", _O_RDONLY | _O_BINARY, _SH_DENYNO, S_IREAD | S_IWRITE | S_IEXEC);
        for (int x = 0; x < 30000; ++x) {
            memset(Compare, 0, 16384);
            if (_read(file, Compare, 16384) != 16384) {
                printf("Bad Read\n");
            }

            for (int y = 0; y < 16384; ++y) {
                if (Compare[y] != Data[y]) {
                    printf("Bad Data\n");
                    break;
                }
            }
        }

        _close(file);
    }

    return 0;
}
