#ifndef TASK_LOGGER_H
#define TASK_LOGGER_H

#include <zephyr/kernel.h>

typedef struct log_message_t {
  char message[32];
} log_message_t;

struct k_msgq *task_logger_get_msgq(void);

#endif
