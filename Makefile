all : memory_simulation


memory_simulation : code_vm_simulation.c
	gcc -o memory_simulation code_vm_simulation.c -lm
clean:
	rm memory_simulation
