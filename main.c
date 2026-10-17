#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <spawn.h>
#include <signal.h>
#include <string.h>
#include <stdarg.h>

#define DEBUG_BUILD 0

void debug(char *format, ...) {
    if (!DEBUG_BUILD) return;
    va_list args;
    va_start(args, format);
    printf("[DEBUG] ");
    vprintf(format, args);
    va_end(args);
    return;
}

extern void pthread_jit_write_protect_np(int enabled);

void fixprot(int sig, siginfo_t *info, void *ucontext) {
	debug("SIGBUS handler activated, fixing JIT...\n");
	pthread_jit_write_protect_np(0);
	debug("Permissions fixed, continuing execution.\n");
}

extern void** environ;

__attribute__((constructor))
static void initializer() {
	struct sigaction sig;
	sig.sa_sigaction = fixprot;
	sig.sa_flags = SA_RESTART;
	sigemptyset(&sig.sa_mask);

	int ret = sigaction(SIGBUS, &sig, NULL);
	if (ret != 0) {
		printf("[!] Failed to set signal handler to sigbus ret %i.\n", ret);
		printf("[!] If you have amfi_get_out_of_my_way=1 it will crash.\n");
	}
}
