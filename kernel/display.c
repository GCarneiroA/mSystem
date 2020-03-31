#include <system.h>

#define VIDEO_SEGMENT       0xB8000

uint16 *textmemptr;
uint8 attrib = 0x07;
uint8 csr_x = 0;
uint8 csr_y = 0;

void scroll()
{
    uint16 blank;
    uint16 temp;

    blank = 0x20 | (attrib << 8);

    if (csr_y >= 25)
    {
        temp = csr_y - 25 + 1;
        memcpyw(textmemptr, textmemptr + temp * 80, (25 - temp) * 80 * 2);
        memsetw(textmemptr + (25 - temp) * 80, blank, 80);
        csr_y = 25 - 1;
    }
}

void move_csr(void)
{
    uint16 offset;
    
    offset = csr_y * 80 + csr_x;

    outportb(0x3D4, 14);
    outportb(0x3D5, offset >> 8);
    outportb(0x3D4, 15);
    outportb(0x3D5, offset);
}

void cls()
{
    uint16 blank = 0x20 | (attrib << 8);
    memsetw((uint16*) textmemptr, blank, 80 * 25);

    csr_x = 0;
    csr_y = 0;
    move_csr();
}

void putch(char c)
{
    uint16 *where;
    uint16 att = attrib << 8;

    if (c == 0x08)
    {
        if (csr_x != 0) csr_x--;
    }
    else if (c == 0x09)
    {
        csr_x = (csr_x + 8) & ~(8 - 1);
    }
    else if (c == '\r')
    {
        csr_x = 0;
    }
    else if (c == '\n')
    {
        csr_x = 0;
        csr_y++;
    }
    else if (c >= ' ')
    {
        where = textmemptr + (csr_y * 80 + csr_x);
        *where = c | att;
        csr_x++;
    }

    if (csr_x >= 80)
    {
        csr_x = 0;
        csr_y++;
    }

    scroll();
    move_csr();
}

void puts(char *text)
{
    uint32 len = strlen(text);
    uint32 i;

    for (i = 0; i < len; i++)
    {
        putch(text[i]);
    }
}

void settextcolor(uint8 forecolor, uint8 backcolor)
{
    attrib = (backcolor << 4) | (forecolor & 0x0F);
}

void init_video()
{
    textmemptr = (uint16*) VIDEO_SEGMENT;

    cls();
    puts("Hello System");
}