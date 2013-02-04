# List of the ChibiOS/RT SPC56ELxx port files.
PORTSRC = ${CHIBIOS}/os/ports/GCC/PPC/chcore.c

PORTASM = ${CHIBIOS}/os/ports/GCC/PPC/SPC56ELxx/bam.s \
          ${CHIBIOS}/os/ports/GCC/PPC/crt0.s \
          ${CHIBIOS}/os/ports/GCC/PPC/SPC56ELxx/ivor.s \
          ${CHIBIOS}/os/ports/GCC/PPC/SPC56ELxx/vectors.s

PORTINC = ${CHIBIOS}/os/ports/GCC/PPC \
          ${CHIBIOS}/os/ports/GCC/PPC/SPC56ELxx

PORTLD  = ${CHIBIOS}/os/ports/GCC/PPC/SPC56ELxx/ld
