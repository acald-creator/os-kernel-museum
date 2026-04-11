ENTRY(_start)
SECTIONS
{
    . = 1M;
    .text : ALIGN(4K)
    {
        *(.multiboot)
        *(.text)
    }
    .rodata : ALIGN(4K)
    {
        *(.data)
        *(.bootstrap_stack)
    }
    .bss : ALIGN(4K)
    {
        *(COMMON)
        *(.bss)
    }
    /DISCARD/ :
    {
        *(.note*)
        *(.iplt*)
        *(.igot*)
        *(.rel*)
        *(.comment)
    }
}