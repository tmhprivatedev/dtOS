cmake_minimum_required(VERSION 3.20)
project(dtOS LANGUAGES C)

set(CMAKE_C_STANDART 11)
set(CMAKE_C_STANDART_REQUIRED ON)
set(CMAKE_C_FLAGS "-ffreestanding -O2 -Wall -Wextra -mno-red-zone -mno-mmx -mno-sse -mno-sse2 -fno-stack-protector -fno-pic -mcmodel=kernel")

file(GLOB_RECURSE KERNEL_SOURCES "kernel/*.c")

add_executable(dtos_kernel.elf ${KERNEL_SOURCES})

set_target_properties(dtos_kernel.elf PROPERTIES
	LINK_FLAGS "-T ${CMAKE_CURRENT_SOURCE_DIR}/linker.ld -nostdlib -static -no-pie"
)
