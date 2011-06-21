#include <clib.h>
#include <screen.h>
#include <gdt.h>

void kernel_main()
{
  gdt_install();
  
  settextcolor(GREEN, BLACK);

  puts("Hello from the kernel!\n");
}
