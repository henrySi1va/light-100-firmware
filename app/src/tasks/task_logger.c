#include "task_logger.h"
#include <zephyr/kernel.h>

#define STACKSIZE 1024
#define PRIORITY 7
#define MSGQ_MAX_MSGS 10

void logger_thread_function(void);

K_THREAD_DEFINE(logger_thread, STACKSIZE, logger_thread_function, NULL, NULL,
                NULL, PRIORITY, 0, 100);
extern const k_tid_t logger_thread;

K_MSGQ_DEFINE(logger_task_msgq, sizeof(log_message_t), MSGQ_MAX_MSGS, 4);

void logger_thread_function(void) {
  log_message_t msg;

  while (1) {
    // Wait for the next message in the message queue.
    k_msgq_get(&logger_task_msgq, &msg, K_FOREVER);

    // Print the message to the console.
    printk("%s\n", msg.message);
  }
}

/**
 * @brief Retrieves the message queue for the logger task.
 *
 * This function returns a pointer to the message queue used by the logger task.
 *
 * @return A pointer to the message queue.
 */
struct k_msgq *task_logger_get_msgq(void) {
  return &logger_task_msgq;
}