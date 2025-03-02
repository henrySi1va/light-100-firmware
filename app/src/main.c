#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define STACKSIZE 1024
#define PRIORITY 7
#define SLEEPTIME 1

void sound_thread_function(void) {
  printk("Hello Sound\n");
  k_sleep(K_SECONDS(5));
}

void logger_thread_function(void) {
  k_sleep(K_SECONDS(5));
  printk("Hello Logger\n");
}

K_THREAD_DEFINE(sound_thread, STACKSIZE, sound_thread_function, NULL, NULL,
                NULL, PRIORITY, 0, 100);
extern const k_tid_t sound_thread;

K_THREAD_DEFINE(logger_thread, STACKSIZE, logger_thread_function, NULL, NULL,
                NULL, PRIORITY, 0, 100);
extern const k_tid_t thread_b;

int main(void) { return 0; }
