#ifndef APP_H
#define APP_H

// Function prototypes for the application
int app_init(char** argv);
void app_run();
void app_cleanup();
int app_next_step_control(int run_next_step);

#endif // APP_H