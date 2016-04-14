#include <linux/linkage.h>
#include <sys/types.h>
#include <sys/time.h>
#include <limits.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

#define u32 uint32_t
#define __u32 uint32_t

typedef void (sha1_transform_fn)(u32 *digest, const char *data,
				unsigned int rounds);

asmlinkage void sha1_transform_ssse3(u32 *digest, const char *data,
				     unsigned int rounds);
asmlinkage void sha1_transform_avx(u32 *digest, const char *data,
				   unsigned int rounds);
asmlinkage void sha1_transform_avx2(u32 *digest, const char *data,
				    unsigned int rounds);
asmlinkage void sha1_ni_transform(u32 *digest, const char *data,
				   unsigned int rounds);

void dump_digest(u32 *digest) {
    int i;

	printf(" Result: ");
    for(i = 0; i < 32; i++) {
        printf("%u", digest[i]);
    }
    printf("\n");
}

struct impl {
	const char name[10];
	sha1_transform_fn *f;
};

static inline void sha1_transform_generic(u32 *digest, const char *data,
				   unsigned int rounds) {

	u32 temp[16] = {};
	sha_transform(digest, data, temp);
}

static struct impl versions[] = {
	{
		.name = "native",
		.f = sha1_transform_generic,
	},
	{
		.name = "ssse3",
		.f = sha1_transform_ssse3,
	},
	{
		.name = "avx",
		.f = sha1_transform_avx,
	},
	{
		.name = "avx2",
		.f = sha1_transform_avx2,
	},
	{
		.name = "ni",
		.f = sha1_ni_transform,
	},
};

void handler(int sig) {
	printf("unsupported\n");
	exit(1);
}

int main() {
	int i;

	signal(SIGILL, &handler);

	for(i = 0; i < sizeof(versions)/sizeof(versions[0]); i++) {
		struct timeval tval_before, tval_after, tval_result;
		unsigned int j;
		printf("Implementation: %s\n", versions[i].name);
		gettimeofday(&tval_before, NULL);
		u32 digest[256] = {};
		char data[64] = "fdsjflsjfklsjklfjwoieroiwejfslkdjioruwoeirflfjskdjoiwurweirweoiw";
		for(j = 0; j < 1000000; j++) {
			memset(digest, 0, 256);
			versions[i].f(digest, data, 1);
		}
		dump_digest(digest);
		gettimeofday(&tval_after, NULL);
		timersub(&tval_after, &tval_before, &tval_result);
		printf(" Time elapsed: %ld.%06ld for 1000000 rounds\n", (long int)tval_result.tv_sec, (long int)tval_result.tv_usec);
	}
}
