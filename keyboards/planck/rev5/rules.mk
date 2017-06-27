MIDI_ENABLE = yes
AUDIO_ENABLE ?= yes           # Audio output on port C6
RGBARRAY_ENABLE ?= yes
BACKLIGHT_ENABLE = no

MCU = at90usb1286

ifndef QUANTUM_DIR
	include ../../../Makefile
endif