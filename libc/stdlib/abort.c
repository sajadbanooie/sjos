#include <stdio.h>
#include <stdlib.h>
#include <kernel/tty.h>
__attribute__((__noreturn__))
void abort(void)
{
	// TODO: Add proper kernel panic.
	printf("panic kernel abort");
	while ( 1 ) { }
	__builtin_unreachable();
}