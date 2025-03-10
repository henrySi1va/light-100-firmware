#include "task_temp.h"
#include "task_logger.h"
#include "temp_sim.h"
#include <stdio.h>
#include <string.h>
#include <zephyr/kernel.h>

#define STACKSIZE 1024
#define PRIORITY 7

void temp_thread_function(void);

K_THREAD_DEFINE(temp_thread, STACKSIZE, temp_thread_function, NULL, NULL, NULL,
                PRIORITY, 0, 100);
extern const k_tid_t temp_thread;

void temp_thread_function(void) {

  log_message_t msg;

  // Get the message queue for the logger task.
  struct k_msgq *logger_task_msgq = task_logger_get_msgq();

  while (1) {
    // Get the current temperature and store it in the message.
    float temperature = get_current_temperature();
    snprintf(msg.message, sizeof(msg.message), "Temperature: %.2f",
             (double)temperature);

    // Send the message to the logger task.
    k_msgq_put(logger_task_msgq, &msg, K_NO_WAIT);

    // Check the temperature again in 60 seconds.
    k_sleep(K_SECONDS(60));
  }
}
