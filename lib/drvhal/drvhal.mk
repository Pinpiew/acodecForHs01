# List of all the usb related files.
DRVPATH = $(LIBPATH)/drvhal

LIBSRC += $(DRVPATH)/drvhal.c

LIBINC += ${DRVPATH}

include $(DRVPATH)/audio/audio.mk

