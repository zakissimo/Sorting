NAME = algo
CFLAGS =  -X -Ofast -X -w 
VALAFLAGS = --disable-assert  
PKG= --pkg=posix

all:
	valac main.vala $(PKG) $(CFLAGS) -o $(NAME)

run: all
	./$(NAME)
