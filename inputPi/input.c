#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <linux/input.h>
#include <string.h>
#include <stdio.h>
int main(void)
{
    struct input_event ev;
    ssize_t n;
    int file = open("/dev/input/event0", O_RDONLY);
    while(true){
        n = read(file, &ev, sizeof ev);
        if (ev.type == EV_KEY && ev.value >= 0 && ev.value <= 2){
          printf("%i 0x%04x (%d)\n", (int)ev.value, (int)ev.code, (int)ev.code);
        }
    }
}
