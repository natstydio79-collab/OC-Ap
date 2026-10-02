#include <stdint.h>

static uint16_t* const VGA = (uint16_t*) 0xB8000;
static int cursor = 0;

static void clear(void) {
    for (int i = 0; i < 80 * 25; i++)
        VGA[i] = (0x0F << 8) | ' ';
    cursor = 0;
}

static void putc(char c) {
    if (c == '\n') {
        cursor += 80 - (cursor % 80);
        return;
    }
    VGA[cursor++] = (0x0F << 8) | (uint8_t)c;
}

static void print(const char* s) {
    while (*s) putc(*s++);
}

void kernel_main(void) {
    clear();
    print("================================\n");
    print("   MY OS v0.1 (32-bit x86)\n");
    print("   Svojo jadro s nulya\n");
    print("================================\n\n");
    print("Kernel loaded OK!\n");
    print("Video: VGA text 80x25\n\n");
    print("Gotovo! Sistema rabotaet.\n");

    for (;;) __asm__ volatile ("hlt");
}
