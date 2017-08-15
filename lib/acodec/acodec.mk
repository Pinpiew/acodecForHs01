# List of all the usb related files.
ACODECPATH = $(LIBPATH)/acodec

LIBSRC += $(ACODECPATH)/lpc.c \
          $(ACODECPATH)/nlp.c \
          $(ACODECPATH)/postfilter.c \
          $(ACODECPATH)/sine.c \
          $(ACODECPATH)/codec2.c \
          $(ACODECPATH)/kiss_fft.c \
          $(ACODECPATH)/interp.c \
          $(ACODECPATH)/lsp.c \
          $(ACODECPATH)/phase.c \
          $(ACODECPATH)/quantise.c \
          $(ACODECPATH)/pack.c \
          $(ACODECPATH)/codebook.c \
          $(ACODECPATH)/codebookd.c \
          $(ACODECPATH)/codebookjvm.c \
          $(ACODECPATH)/codebookge.c \
          $(ACODECPATH)/dump.c \
          $(ACODECPATH)/fdmdv.c \
          $(ACODECPATH)/freedv_api.c \
          $(ACODECPATH)/varicode.c \
          $(ACODECPATH)/golay23.c
          
LIBINC += ${ACODECPATH}


