# STM32G071RB_NUCLEO_AZ2 TBS

The TBS is based on the NUCLEO-G071RB and the display module X-NUCLEO-GFX01M2 AZ2. The default IDE is set to STM32CubeIDE, to change IDE open the STM32G071RB_NUCLEO_AZ2.ioc with STM32CubeMX and select from the supported IDEs.

This TBS is configured for 240 x 320 pixels 16bpp screen resolution.

Performance testing can be done using the GPIO pins designated with the following signals:
 - VSYNC_FREQ  - Pin PD9(CN10 - PIN 38)
 - RENDER_TIME - Pin PD8(CN10 - PIN 36)
 - FRAME_RATE  - Pin PC5(CN10 - PIN 37)
 - MCU_ACTIVE  - Pin PC4(CN10 - PIN 35)
