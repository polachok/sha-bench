all: test

test: sha1_glue.o sha1.o sha1_avx2_x86_64_asm.o sha1_ni_asm.o sha1_ssse3_asm.o
	gcc -O3 -static $^ -o $@

asm: sha1_avx2_x86_64_asm.o sha1_ni_asm.o sha1_ssse3_asm.o

%.o: %.S
	gcc -I. -c -DCONFIG_AS_AVX -D__ASSEMBLY__ $< -o $@

%.o: %.c
	gcc -O3 -DCONFIG_X86 -I. -c $< -o $@

clean: 
	rm -f test *.o
