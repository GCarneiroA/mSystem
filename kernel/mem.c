#include <system.h>

uint16 *memcpyw(uint16 *dest, const uint16 *src, uint32 count)
{
    const uint16 *sp = (const uint16 *)src;
    uint16 *dp = (uint16 *)dest;
    for (; count != 0; count--) *dp++ = *sp++;
    return dest;
}

uint8 *memset(uint8 *dest, uint8 val, uint32 count)
{
    uint8 *temp = (uint8 *)dest;
    for (; count != 0; count--) *temp++ = val;
    return dest;
}

uint16 *memsetw(uint16 *dest, uint16 val, uint32 count)
{
    uint16 *temp = (uint16 *)dest;
    for (; count != 0; count--) *temp++ = val;
    return dest;
}