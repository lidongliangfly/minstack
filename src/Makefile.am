## Process this file with automake to produce Makefile.in

lib_LTLIBRARIES = libminstack.la

libminstack_la_SOURCES= \
	list.c \
	list.h \
	tools.c \
	private.c \
	private.h \
	tcp.c \
	minstack_debug.c \
	udp.c

libminstack_la_CPPFLAGS= -D_GNU_SOURCE
libminstack_la_CFLAGS= -Wall -I$(top_srcdir)/include $(CONFIG_CFLAGS)
libminstack_la_LDFLAGS= -release ${VERSION}

INCLUDE = -I$(top_srcdir)/include
AM_CFLAGS=$(STRICT_OPTIONS) $(CONFIG_CFLAGS)
