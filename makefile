c4i: lex.yy.c y.tab.c c4i.c
	gcc -o c4i lex.yy.c y.tab.c c4i.c

c6c: lex.yy.c y.tab.c c6c.c
	gcc -o c6c lex.yy.c y.tab.c c6c.c

lex.yy.c: c6.l
	flex c6.l

y.tab.c: c6.y
	bison -y -d c6.y

sas: sas.c sas.tab.c
	gcc -o sas sas.c sas.tab.c

sas.c: sas.l
	flex -o sas.c sas.l

sas.tab.c: sas.y
	bison -d sas.y

cal: cal.c cal.tab.c
	gcc -o cal cal.c cal.tab.c

cal.c: cal.l
	flex -o cal.c cal.l

cal.tab.c: cal.y
	bison -d cal.y

calx: calx.c calx.tab.c
	gcc -o calx calx.c calx.tab.c

calx.c: calx.l
	flex -o calx.c calx.l

calx.tab.c: calx.y
	bison -d calx.y

cleanc6:
	$(RM) lex.yy.c y.tab.c y.tab.h c4i c6c

cleansas:
	$(RM) sas.c sas.tab.c sas.tab.h sas

cleancal:
	$(RM) cal.c cal.tab.c cal.tab.h cal calx.c calx.tab.c calx.tab.h calx
