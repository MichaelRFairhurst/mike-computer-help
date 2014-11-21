
all:
	C_INCLUDE_PATH="/usr/include/gtk-1.2:/usr/include/glib-1.2:/usr/lib64/glib/include" cc mikehelp.c -o mikehelp -lglib -lgtk -lgdk
