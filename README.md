# PROJECT RTOS - Advanced Computer Systems
A small real-time operating system prototype for the Raspberry Pi Pico (RP2040), written in C with the Pico SDK.

The project explores the core pieces of an RTOS: task creation, task control blocks, context switching, scheduling, timing interrupts, and a serial command shell. It also includes task examples that drive an external MAX7219-compatible seven-segment display.

## Features

- Dynamically allocated task control blocks (TCBs)
- Linked-list task management
- Task creation and removal through `add_Task()` and `remove_Task()`
- SysTick-based timing and periodic context-switch requests
- Round-robin scheduler
- USB serial command shell
- Example LED and seven-segment display tasks
- SPI-based display support through the hardware abstraction layer
- UF2, ELF, BIN, HEX, and disassembly build outputs

## Project Structure
inc/rtos.h       Shared RTOS types, constants, globals, and prototypes
src/main.c       Kernel startup and initial task creation
src/add_task.c   TCB allocation, stack setup, and task-list insertion
src/remove_task.c
				 Task lookup, unlinking, and cleanup
src/scheduler.c  Round-robin task selection
src/systick.c    SysTick configuration and tick handling
src/tasks.c      Example application tasks
src/cmdshell.c  USB serial command shell

## Shell Commands

After connecting to the Pico over USB serial, the shell supports:

```text
pt                         Print the current task list
mm                         Print the main menu
rt <id>                    Remove a task by ID
sd                         Clear the display and stop the RTOS

blink <flashes> <priority> Blink the onboard LED
count <position> <priority>
						   Count from 00 to 99 on two digits
flash <position> <priority>
						   Flash a decimal point
hexer <position> <priority>
						   Display a repeating hexadecimal count
splat <position> <priority>
						   Animate the display segments
```

The shell uses ANSI escape sequences for colored terminal output. A terminal with ANSI/VT100 color support, such as Tera Term, is recommended.


## Current Scope

This is an educational RTOS prototype rather than a production kernel. The scheduler currently uses a simple round-robin policy and does not yet use task priorities for selection. Removing the currently running task is unsafe until task deletion is deferred or otherwise coordinated with the context switch.

