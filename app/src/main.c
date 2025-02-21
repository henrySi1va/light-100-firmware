#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define STACKSIZE 1024
#define PRIORITY 7
#define SLEEPTIME 1

/*
 * @param my_name      thread identification string
 */
void hello_loop(const char *my_name)
{
	while (1) {
		/* Say hello! */
		printk("%s: Hello World from %s!\n", my_name, CONFIG_BOARD);

		/* wait a while, then let other thread have a turn */
		k_sleep(K_SECONDS(SLEEPTIME));
	}
}

/* thread_b is a static thread spawned immediately */
void thread_b_entry_point(void *dummy1, void *dummy2, void *dummy3)
{
	ARG_UNUSED(dummy1);
	ARG_UNUSED(dummy2);
	ARG_UNUSED(dummy3);

	hello_loop("light-100");
}

K_THREAD_DEFINE(thread_b, STACKSIZE,
				thread_b_entry_point, NULL, NULL, NULL,
				PRIORITY, 0, 100);
extern const k_tid_t thread_b;

int main(void)
{
	return 0;
}
