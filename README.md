# 0x16. C - Simple Shell

## Introduction
This repository contains the source code for a simple shell program written in C. This shell is a command-line interpreter that allows users to interact with the operating system by executing commands and managing processes.

## Table of Contents
- [Who designed and implemented the original Unix operating system](#who-designed-and-implemented-the-original-unix-operating-system)
- [Who wrote the first version of the UNIX shell](#who-wrote-the-first-version-of-the-unix-shell)
- [Who invented the B programming language](#who-invented-the-b-programming-language)
- [Who is Ken Thompson](#who-is-ken-thompson)
- [How does a shell work](#how-does-a-shell-work)
- [What is a pid and a ppid](#what-is-a-pid-and-a-ppid)
- [How to manipulate the environment of the current process](#how-to-manipulate-the-environment-of-the-current-process)
- [What is the difference between a function and a system call](#what-is-the-difference-between-a-function-and-a-system-call)
- [How to create processes](#how-to-create-processes)
- [What are the three prototypes of `main`](#what-are-the-three-prototypes-of-main)
- [How does the shell use the `PATH` to find the programs](#how-does-the-shell-use-the-path-to-find-the-programs)
- [How to execute another program with the `execve` system call](#how-to-execute-another-program-with-the-execve-system-call)
- [How to suspend the execution of a process until one of its children terminates](#how-to-suspend-the-execution-of-a-process-until-one-of-its-children-terminates)
- [What is `EOF` / "end-of-file"](#what-is-eof--end-of-file)

## Who designed and implemented the original Unix operating system
The original Unix operating system was designed and implemented by Ken Thompson, Dennis Ritchie, and other colleagues at Bell Labs in the early 1970s. 

## Who wrote the first version of the UNIX shell
The first version of the UNIX shell, known as the "Thompson shell" or "sh", was written by Ken Thompson himself. It was one of the fundamental components of the Unix operating system and provided a command-line interface for users to interact with the system.

## Who invented the B programming language
The B programming language, which directly influenced the development of the C programming language, was invented by Ken Thompson and Dennis Ritchie at Bell Labs in the late 1960s. B was a precursor to C and served as an intermediate step in the evolution of programming languages.

## Who is Ken Thompson
Ken Thompson is an American computer scientist and co-creator of the Unix operating system. He played a significant role in the development of many foundational technologies, including the creation of the B programming language and the implementation of the original Unix shell. Thompson also contributed to the development of the C programming language and was one of the key designers of the Plan 9 and Inferno operating systems.

## How does a shell work
A shell is a command-line interpreter that acts as a user interface to an operating system. It reads user commands, interprets them, and executes the corresponding programs or system functions. The basic workflow of a shell involves reading input from the user, parsing the input into commands and arguments, executing the commands, and displaying the output to the user. Shells can also provide features like environment variable management, input/output redirection, and process control.

## What is a pid and a ppid
In an operating system, a PID (Process IDentifier) is a unique numerical identifier assigned to each running process. It is used by the system to track and manage processes. The PPID (Parent Process IDentifier) represents the PID of the parent process that spawned a particular process. The PPID is useful for hierarchical process management, as it allows the system to maintain the relationship between parent and child processes.

## How to manipulate the environment of the current process
The environment of a process consists of a set of variables that define its working environment. In C, the environment variables are accessed through the `environ` variable, which is an array of strings. To manipulate the environment of the current process, you can use functions like `getenv` to retrieve the value of a specific environment variable, `setenv` to set the value of an environment variable, and `unsetenv` to remove an environment variable.

## What is the difference between a function and a system call
In programming, a function is a block of code that performs a specific task and can be called from other parts of a program. Functions are usually provided by libraries or written by the programmer.

A system call, on the other hand, is a request made by a program to the operating system kernel to perform privileged operations, such as creating processes, accessing hardware, or performing file I/O. System calls provide an interface for user programs to interact with the operating system's services and resources.

The main difference between a function and a system call is that functions execute within the user space of a program, while system calls involve a context switch to the kernel space to access protected resources.

## How to create processes
In C, you can create a new process using the `fork` system call. The `fork` call creates a new process by duplicating the existing process. After forking, the original process becomes the parent process, and the newly created process becomes the child process. The `fork` system call returns different values in the parent and child processes, allowing them to distinguish between each other.

## What are the three prototypes of `main`
In C, the `main` function can have three different prototypes:

1. `int main(void)`: This is the most basic form of `main` and is used when the program doesn't take any command-line arguments or environment variables. The return value represents the exit status of the program.

2. `int main(int argc, char *argv[])`: This form of `main` is used when the program accepts command-line arguments. `argc` is the argument count, indicating the number of command-line arguments, and `argv` is an array of strings containing the arguments.

3. `int main(int argc, char *argv[], char *envp[])`: This form of `main` is used when the program needs access to the environment variables. In addition to `argc` and `argv`, it also receives the `envp` argument, which is an array of strings containing the environment variables.

## How does the shell use the `PATH` to find the programs
The shell uses the `PATH` environment variable to locate executable programs. `PATH` is a colon-separated list of directories. When a command is entered in the shell, it searches each directory specified in `PATH`, in order, to find the corresponding executable file. If the executable is found, the shell executes it. If the executable is not found in any of the directories listed in `PATH`, the shell displays an error indicating that the command is not found.

## How to execute another program with the `execve` system call
The `execve` system call is used to execute another program from within a C program. It replaces the current process image with a new process image specified by the given program file path. The `execve` call requires the

 full path to the executable, the command-line arguments as an array of strings, and the environment variables as an array of strings. After the `execve` call, the new program takes over the control flow from the current process.

## How to suspend the execution of a process until one of its children terminates
To suspend the execution of a process until one of its children terminates, you can use the `wait` system call. The `wait` call causes the calling process to block until one of its child processes exits or a specific child process is terminated. When a child process terminates, the `wait` call returns the child's process ID and status. By using the `wait` call, a parent process can synchronize its execution with the termination of its child processes.

## What is `EOF` / "end-of-file"
In C, `EOF` is a symbolic constant defined in the `<stdio.h>` header file. It represents the end-of-file condition when reading from or writing to a file or input stream. The value of `EOF` is typically -1. When reading from a file or input stream, encountering `EOF` indicates that there is no more data to be read. When writing to a file or output stream, a return value of `EOF` indicates an error condition.
