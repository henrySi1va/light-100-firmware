#include "temp_sim.h"
#include "zephyr/sys_clock.h"
#include <math.h>
#include <zephyr/kernel.h>

#define PI 3.14159265358979323846
#define BASE_TEMPERATURE 70.0

/**
 * @brief Retrieves the current temperature.
 *
 * This function returns the current temperature as a floating-point value.
 *
 * @return The current temperature.
 */
float get_current_temperature() {
  // Get the current tick count in milliseconds.
  uint32_t current_ticks_ms = k_uptime_get();

  // Calculate the fluctuation based on a sine wave.
  // This will fluctuate the temperature up and down 10 degrees over 10 minutes.
  float fluctuation =
      10.0 * sin((2 * PI) * ((double)(current_ticks_ms % 600000) / 600000));

  return (float)BASE_TEMPERATURE + fluctuation;
}
