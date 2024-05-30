#include "app.h"

#include <stdio.h>
#include <stdlib.h>

// Main function: entry point of the application
int main(int argc, char** argv) {
    if (argc != 6) {
        printf(
            "[ADNSIZE] [SPEED] [ROTATIONSPEED] [NPOP] [PLAYMODE]\n"
            "\n"
            "[RECTSIZE] = 0 : Point, switch the renderer to draw point (faster)\n"
            "\n"
            "[PLAYMODE] = 0 : Step by step, (type space-bar to show next frame)\n"
            "[PLAYMODE] = 1 : Continuous, (type space-bar to pause/play)\n"
            "\n"
        );
        return -1;
    }

    // Initialize application with command-line arguments
    if (!app_init(argv)) {
        fprintf(stderr, "Failed to initialize the application\n");
        return EXIT_FAILURE;
    }

    // Run the application
    app_run();

    // Cleanup and exit
    app_cleanup();
    return EXIT_SUCCESS;
}