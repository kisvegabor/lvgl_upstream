.. _renesas:

=======
Renesas
=======

`Renesas <https://renesas.com/>`__ is an official partner of LVGL.
Therefore, LVGL contains built-in support for `Dave2D <https://www.renesas.com/document/mas/tes-dave2d-driver-documentation>`__ (the GPU of Renesas)
and LVGL also hosts ready-to-use Renesas projects.

Dave2D
------

Dave2D is capable of accelerating most of the drawing operations of LVGL:

- Rectangle drawing, even with gradients
- Image drawing, scaling, and rotation
- Letter drawing
- Triangle drawing
- Line drawing

As Dave2D works in the background, the CPU is free for other tasks. In practice, during rendering, Dave2D can reduce the CPU usage by half or to one-third, depending on the application.

GLCDC
-----

GLCDC is a multi-stage graphics output peripheral available in several Renesas MCUs.
It is able to drive LCD panles via a highly configurable RGB interface.

More info can be found at the :ref:`driver's page<renesas_glcdc>`.

Supported boards
----------------

.. list-table::
   :widths: 10 30 30 30

   * -
     - **EK-RA8D1**
     - **EK-RA6M3G**
     - **RX72N Envision Kit**
   * - CPU
     - 480MHz, Arm Cortex-M85 core
     - 120MHz, Arm Cortex-M4 core
     - 240MHz, Renesas RXv3 core
   * - Memory
     -
         | 1MB internal, 64MB external SDRAM
         | 2MB internal, 64MB External Octo-SPI Flash
     -
         | 640kB internal SRAM
         | 2MB internal, 32MB external QSPI Flash
     -
         | 1MB internal SRAM
         | 4MB internal, 32MB external QSPI Flash
   * - Display
     -
         | 4.5”
         | 480x854
         | 2-lane MIPI
     -
         | 4.3”
         | 480x272
         | Parallel RGB565
     -
         | 4.3”
         | 480x272
         | Parallel RGB565
   * - `Certification <https://lvgl.io/certificate>`__ video
     - .. raw:: html

           <iframe width="320" height="180" src="https://www.youtube.com/embed/LHPIqBV_MGA?si=mtW3g-av56bCdR4k" title="YouTube video player" frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" referrerpolicy="strict-origin-when-cross-origin" allowfullscreen></iframe>

     - Coming soon
     - Coming soon
   * - Links
     - `Demo repository for EK-RA8D1 <https://github.com/lvgl/lv_port_renesas_ek-ra8d1>`__
     - `Demo repository for EK-RA6M3G <https://github.com/lvgl/lv_port_renesas_ek-ra6m3g>`__
     - `Demo repository for RX72N Envision Kit <https://github.com/lvgl/lv_port_renesas_rx72n-envision-kit>`__

Get started with the Renesas ecosystem
--------------------------------------

.. |img_debug_btn| image:: /misc/renesas/debug_btn.png
   :alt: Debug button

.. dropdown:: RA Family

   - The official IDE of Renesas is called e² studio. As it's Eclipse-based, it runs on Windows, Linux, and Mac as well. The RA family requires the latest version with FSP 5.3. It can be downloaded from `here <https://www.renesas.com/us/en/software-tool/flexible-software-package-fsp>`__.

   - JLink is used for debugging, it can be downloaded `here <https://www.segger.com/downloads/jlink/>`__.


   - Clone the ready-to-use repository for your selected board:

      .. code-block:: shell

         git clone https://github.com/lvgl/lv_port_renesas_ek-ra8d1.git --recurse-submodules

      Downloading the `.zip` from GitHub doesn't work as it doesn't download the submodules.

   - Open e² studio, go to ``File`` -> ``Import project`` and select ``General`` / ``Existing projects into workspace``

   - Browse the cloned folder and press ``Finish``.

   - Double click on ``configuration.xml``. This will activate the `Configuration Window`.

      Renesas' Flexible Software Package (FSP) includes BSP and HAL layer support extended with multiple RTOS variants and other middleware stacks.
      The components will be available via code generation, including the entry point of *"main.c"*.

      Press ``Generate Project Content`` in the top right corner.

      .. image:: /misc/renesas/generate.png
         :alt: Code generation with FSP

   - Build the project by pressing ``Ctrl`` + ``Alt`` + ``B``

   - Click the Debug button (|img_debug_btn|). If prompted with `Debug Configurations`, on the `Debugger` tab select the ``J-Link ARM`` as `Debug hardware` and the proper IC as `Target Device`:

      - ``R7FA8D1BH`` for EK-RA8D1

         .. image:: /misc/renesas/debug_ra8.png
            :alt: Debugger parameters for RA8

      - ``R7FA6M3AH`` for EK-RA6M3G

         .. image:: /misc/renesas/debug_ra6.png
            :alt: Debugger parameters for RA6

   .. note::
      On EK-RA8D1 boards, the ``SW1`` DIP switch (middle of the board) 7 should be ON, all others are OFF.

.. dropdown:: RX Family

   - The official IDE of Renesas is called e² studio. As it's Eclipse-based, it runs on Windows, Linux, and Mac as well. It can be downloaded `here <https://www.renesas.com/us/en/software-tool/e-studio>`__.

   - Download and install the required driver for the debugger

       - for Windows: `64 bit here <https://www.renesas.com/us/en/document/uid/usb-driver-renesas-mcu-tools-v27700-64-bit-version-windows-os?r=488806>`__ and `32 bit here <https://www.renesas.com/us/en/document/uid/usb-driver-renesas-mcu-toolse2e2-liteie850ie850apg-fp5-v27700for-32-bit-version-windows-os?r=488806>`__
       - for Linux: `here <https://www.renesas.com/us/en/document/swo/e2-emulator-e2-emulator-lite-linux-driver?r=488806>`__

   - RX72 requires an external compiler for the RXv3 core. A free and open-source version is available `here <https://llvm-gcc-renesas.com/rx-download-toolchains/>`__ after a registration.

      The compiler must be activated in e² studio:

      - Go to go to ``Help`` -> ``Add Renesas Toolchains``
      - Press the ``Add... `` button
      - Browse the installation folder of the toolchain

      |

      .. image:: /misc/renesas/toolchains.png
         :alt: Toolchains

   - Clone the ready-to-use `lv_port_renesas_rx72n-envision-kit <https://github.com/lvgl/lv_port_renesas_rx72n-envision-kit.git>`__ repository:

      .. code-block:: shell

         git clone https://github.com/lvgl/lv_port_renesas_rx72n-envision-kit.git --recurse-submodules

      Downloading the `.zip` from GitHub doesn't work as it doesn't download the submodules.

   - Open e² studio, go to ``File`` -> ``Import project`` and select ``General`` / ``Existing projects into workspace``

   - Select the cloned folder and press ``Finish``.

   - Double click on ``RX72N_EnVision_LVGL.scfg``. This will activate the `Configuration Window`.

      Renesas' Smart Configurator (SMC) includes BSP and HAL layer support extended with multiple RTOS variants and other middleware stacks.
      The components will be available via code generation, including the entry point of the application.

      Press ``Generate Code`` in the top right corner.

      .. image:: /misc/renesas/generate_smc.png
         :alt: Code generation with SMC

   - Build the project by pressing ``Ctrl`` + ``Alt`` + ``B``

   - Click the Debug button (|img_debug_btn|). If prompted with `Debug Configurations`, on the `Debugger` tab select the ``E2 Lite`` as `Debug hardware` and ``R5F572NN`` as `Target Device`:

      .. image:: /misc/renesas/debug_rx72.png
         :alt: Debugger parameters for RX72

   .. note::
      Make sure that both channels of ``SW1`` DIP switch (next to ``ECN1``) are OFF.

Modify the project
------------------

Open a demo
~~~~~~~~~~~

The entry point of the main task is contained in ``src/LVGL_thread_entry.c`` in all 3 projects.

You can disable the LVGL demos (or just comment them out) and call some ``lv_example_...()`` functions, or add your custom code.

Configuration
~~~~~~~~~~~~~

``src/lv_conf.h`` contains the most important settings for LVGL. Namely:

- ``LV_COLOR_DEPTH`` to set LVGL's default color depth
- ``LV_MEM_SIZE to`` set the maximum RAM available for LVGL
- ``LV_USE_DAVE2D`` to enable the GPU


Hardware and software components can be modified in a visual way using the `Configuration Window`.

Change compiler
--------------

By default Renesas supports GCC, however it's possible to use other compilers as well.

Ready to use configurations are available in the ``llvm`` and ``ac6`` branches of `lv_port_renesas_ek-ra8d1 <https://github.com/lvgl/lv_port_renesas_ek-ra8d1>`__.

After switching to a new compiler delete the ``ra_gen``, ``ra_cfg``, and ``Debug`` folders, and also ``Generate Project Content`` again in ``configuration.xml``.

LLVM
~~~~

Add the compiler to e² studio
=============================


1. Download LLVM 17 from `here <https://github.com/ARM-software/LLVM-embedded-toolchain-for-Arm/releases/tag/release-17.0.1>`__ . Other versions might work as well, but they are not tested
2. Extract the downloaded file. The target path can be selected freely.
3. In e² studio click ``Help`` -> ``Add Renesas Toolchain``. From the list select ``LLVM Embedded Toolchain for Arm`` and click the ``Add...`` button at the bottom.
4. Browse the extracted LLVM folder then click ok.


Convert the project LLVM
========================

1. Click ``File`` -> ``Properties`` -> ``C/C++ Build`` -> ``Tool Chain Editor``
2. In ``Current Toolachain`` select ``LLVM for Arm``
3. Confirm the change of the Toolchain
4. Still in Project properties select ``C/C++ Build`` -> ``Settings``. On the ``Tool Settings`` tab select `CPU` and as `Arm Family` the core of your MCU, e.g. ``cortex-m85``.
5. In ``Library Generator`` -> ``Settings`` set ``Library type`` to ``Pre-Built``
6. In ``Linker CPP`` -> ``Archives`` in ``Archive search directories`` add ``script`` folder
7. In ``Objcopy`` -> ``General`` set ``OutFormat`` to ``Intel Hex``
8. On the ``Toolchain`` tab be sure that ``LLVM for Arm`` and the correct version is selected, and click ``Apply``.


Ac6 and Arm2D
~~~~~~~~~~~~~

Add the compiler to e² studio
=============================
1. Download and install the Ac6 compiler from `arm's website <https://developer.arm.com/downloads/view/ACOMPE>`__.
2. To register a community license go to ``bin`` folder of the compiler and in a Terminal run ``armlm.exe activate -server https://mdk-preview.keil.arm.com -product KEMDK-COM0``
3. In E2 Studio open ``Window`` -> ``Preferences``. Select ``Toolchains`` on the left, click ``Add...`` and browse the bin folder of the Ac6 compiler.

Convert the project Ac6
=======================
1. Project props, tool chain Ac6
target: arm-arm-none-eabi
mcpu: cortex-m85
linker target: Cortex-M85
linker scatter ${workspace_loc:/${ProjName}}/script/fsp.scat

linker misc: --lto --library_type=standardlib --no_startup --via="${workspace_loc:/${ProjName}/script}/ac6/fsp_keep.via"
asm misc: -x assembler-with-cpp
comp misc: -DUSE_MVE_INTRINSICS  -Omax -mfloat-abi=hard -flto -Wno-int-conversion -Wno-deprecated-non-prototype -Wno-implicit-function-declaration -Wno-unused-but-set-variable -Wfloat-equal -Waggregate-return -Wshadow -Wpointer-arith -Wconversion -Wmissing-declarations -Wuninitialized -Wunused -Wno-license-management -Wextra -Wno-implicit-int-conversion -Wno-sign-conversion -I"/home/kisvegabor/projects/lvgl/e2_studio-workspace/lv_renesas/lv_ek_ra8d1/ra/arm/CMSIS_5/CMSIS/DSP/Include/" -I"/home/kisvegabor/projects/lvgl/e2_studio-workspace/lv_renesas/lv_ek_ra8d1/ra/arm/CMSIS_5/CMSIS/DSP/PrivateInclude/"



Add Arm2D
=========

Support
-------

In case of any problems or questions open an issue in the corresponding repository.
