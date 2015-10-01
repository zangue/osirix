/*
 * boot/boot.S
 * 
 * Copyrigth (c) 2015, Armand Zangue <armand@zangue.com>
 */

// To keep this in the first portion of the binary.
.section ".text.boot"
 
.global _start
 
_start:
	// Set the stack pointer, which progresses downwards through memory
	ldr sp, =0x8000
	sub sp, sp, #0x4

	// start the kernel
	b start_kernel

__loop:
	b __loop 
