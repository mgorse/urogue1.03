#
#   UltraRogue
#   Copyright (C) 1984, 1985, 1986, 1987, 1990 Herb Chong
#   All rights reserved.
#    
#   Based on "Advanced Rogue"
#   Copyright (C) 1983, 1984 Michael Morgan, Ken Dalka and AT&T
#   All rights reserved.
#
#   Based on "Super-Rogue"
#   Copyright (C) 1982, 1983 Robert D. Kindelberger
#   All rights reserved.
#
#   Based on "Rogue: Exploring the Dungeons of Doom"
#   Copyright (C) 1980, 1981 Michael Toy, Ken Arnold and Glenn Wichman
#   All rights reserved.
#    
#   See the file LICENSE.TXT for full copyright and licensing information.


HDRS=	rogue.h 
SRCS=	armor.c artifact.c bag.c chase.c command.c daemon.c daemons.c encumb.c\
	fight.c getplay.c ident.c init.c io.c list.c magic.c magicitm.c main.c\
	maze.c misc.c monsdata.c monsters.c move.c newlvl.c options.c\
	pack.c passages.c player.c potions.c random.c rings.c rip.c rooms.c\
	save.c scrolls.c state.c status.c sticks.c things.c trader.c vers.c\
	weapons.c wizard.c
OBJS=	armor.o artifact.o bag.o chase.o command.o daemon.o daemons.o encumb.o\
	fight.o getplay.o ident.o init.o io.o list.o magic.o magicitm.o main.o\
	maze.o misc.o monsdata.o monsters.o move.o newlvl.o options.o\
	pack.o passages.o player.o potions.o random.o rings.o rip.o rooms.o\
	save.o scrolls.o state.o status.o sticks.o things.o trader.o vers.o\
	weapons.o wizard.o

CC = gcc
CFLAGS=	-g

urogue: $(OBJS)
	cc -g -o urogue $(OBJS) -lncurses -lcrypt

urprint: urprint.o magicitm.o monsdata.o
	cc -o urprint urprint.o magicitm.o monsdata.o

%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c -o $@ $<
