# AY-VM

A lightweight register-based virtual machine written in C++.

AY-VM executes custom bytecode instructions using a simple architecture built around:

* Registers
* Stack operations
* Arithmetic instructions
* Bytecode parsing
* Dynamic instruction dispatching

This project was made for learning low-level systems, VM architecture, and programming language internals.

---

# Features

## Register System

Supports dynamically created registers with multiple data types:

* `int`
* `double`
* `char`

Example:

```txt
create R0
set R0 int 10
```

---

## Stack System

Built-in stack manager with support for:

* `push`
* `pop`
* `top`
* `dup`
* `topToReg`

Example:

```txt
push R0 int
dup int
pop int
```

---

## Arithmetic Instructions

Supports register arithmetic:

* `add`
* `sub`
* `mul`
* `div`

Example:

```txt
add R0 R1 R2 int
```

Also supports stack arithmetic:

* `adds`
* `subs`
* `muls`
* `divs`

---

## Data Movement

Move values between registers:

```txt
mov R0 R1 int
```

---

## Output Instructions

Print register values directly:

```txt
print R0 int
```

Supports escaped characters:

* `\n`
* `\t`
* `\sp`

---

## VM Architecture

The VM is built using:

* Register maps
* Stack manager abstraction
* Instruction dispatcher
* Bytecode token parser
* Type-specific execution handlers

---

# Example Program

```txt
create Space
set Space char \sp

create R0
create R1
create R2

set R0 int 28
set R1 int 34

add R0 R1 R2 int

print R0 int
print Space char
print R1 int
print Space char
print R2 int
```

Output:

```txt
28 34 62
```

---

# Why This Project Exists

This VM was built to explore:

* Virtual machine design
* Bytecode execution
* Register-based architectures
* Low-level programming concepts
* Programming language internals

---

# Build

Compile using g++:

```bash
g++ main.cpp stack.o register.o -o vm
```
---

# Example Bytecode Syntax

```txt
create R0
set R0 int 100

create R1
set R1 int 20

div R0 R1 R2 int

print R2 int
```
---

# License

MIT License
