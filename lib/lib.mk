LIBPATH = $(CHIBIOS)/lib

LIBSRC = 
LIBASM = 
LIBINC = $(LIBPATH) 

LIBOPEN = 

include $(LIBPATH)/include/inc.mk
include $(LIBPATH)/fatfs/fatfs.mk
include $(LIBPATH)/shell/shell.mk
include $(LIBPATH)/mem/mem.mk
include $(LIBPATH)/oshal/oshal.mk
include $(LIBPATH)/drvhal/drvhal.mk
include $(LIBPATH)/acodec/acodec.mk
