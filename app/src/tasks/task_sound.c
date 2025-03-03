#include "task_sound.h"
#include "task_logger.h"
#include <string.h>
#include <zephyr/kernel.h>

#define STACKSIZE 1024
#define PRIORITY 7

void sound_thread_function(void);

K_THREAD_DEFINE(sound_thread, STACKSIZE, sound_thread_function, NULL, NULL,
                NULL, PRIORITY, 0, 100);
extern const k_tid_t sound_thread;

void sound_thread_function(void) {

  log_message_t msg;

  strcpy(msg.message, "Hello from sound thread!");

  struct k_msgq *logger_task_msgq = task_logger_get_msgq();

  while (1) {
    k_msgq_put(logger_task_msgq, &msg, K_NO_WAIT);
    k_sleep(K_SECONDS(1));
  }
}
