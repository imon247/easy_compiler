	push	sp
	push	1
	add
	pop	sp
	push	0
	pop	sb[0]
	push	sp
	push	1
	add
	pop	sp
	push	1
	pop	sb[1]
	push	sp
	push	1
	add
	pop	sp
	push	0
	pop	sb[2]
	push	sp
	push	9
	add
	pop	sp
	push	0
	push	0
	push	3
	mul
	push	0
	add
	push	3
	add
	pop	in
	pop	sb[in]
	push	0
	push	0
	push	3
	mul
	push	1
	add
	push	3
	add
	pop	in
	pop	sb[in]
	push	0
	push	0
	push	3
	mul
	push	2
	add
	push	3
	add
	pop	in
	pop	sb[in]
	push	0
	push	1
	push	3
	mul
	push	0
	add
	push	3
	add
	pop	in
	pop	sb[in]
	push	0
	push	1
	push	3
	mul
	push	1
	add
	push	3
	add
	pop	in
	pop	sb[in]
	push	0
	push	1
	push	3
	mul
	push	2
	add
	push	3
	add
	pop	in
	pop	sb[in]
	push	0
	push	2
	push	3
	mul
	push	0
	add
	push	3
	add
	pop	in
	pop	sb[in]
	push	0
	push	2
	push	3
	mul
	push	1
	add
	push	3
	add
	pop	in
	pop	sb[in]
	push	0
	push	2
	push	3
	mul
	push	2
	add
	push	3
	add
	pop	in
	pop	sb[in]
L000:
	push	sb[0]
	push	0
	compEQ
	push	sb[2]
	push	9
	compLT
	and
	j0	L001
	push	"enter a pair of integer less than three:"
	puts
	push	sp
	push	1
	add
	pop	sp
	geti
	pop	sb[40]
	push	sp
	push	1
	add
	pop	sp
	geti
	pop	sb[41]
	push	sb[1]
	push	sb[40]
	push	3
	mul
	push	sb[41]
	add
	push	3
	add
	pop	in
	pop	sb[in]
	push	sb[40]
	push	3
	mul
	push	sb[41]
	add
	push	3
	add
	pop	in
	push	sb[in]
	puti
	push	0
	push	3
	mul
	push	0
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	1
	compEQ
	push	0
	push	3
	mul
	push	1
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	1
	compEQ
	and
	push	0
	push	3
	mul
	push	2
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	1
	compEQ
	and
	j0	L002
	push	sp
	push	1
	add
	pop	sp
	push	1
	pop	sb[0]
L002:
	push	1
	push	3
	mul
	push	0
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	1
	compEQ
	push	1
	push	3
	mul
	push	1
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	1
	compEQ
	and
	push	1
	push	3
	mul
	push	2
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	1
	compEQ
	and
	j0	L003
	push	sp
	push	1
	add
	pop	sp
	push	1
	pop	sb[0]
L003:
	push	2
	push	3
	mul
	push	0
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	1
	compEQ
	push	2
	push	3
	mul
	push	1
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	1
	compEQ
	and
	push	2
	push	3
	mul
	push	2
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	1
	compEQ
	and
	j0	L004
	push	sp
	push	1
	add
	pop	sp
	push	1
	pop	sb[0]
L004:
	push	0
	push	3
	mul
	push	0
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	1
	compEQ
	push	1
	push	3
	mul
	push	0
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	1
	compEQ
	and
	push	2
	push	3
	mul
	push	0
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	1
	compEQ
	and
	j0	L005
	push	sp
	push	1
	add
	pop	sp
	push	1
	pop	sb[0]
L005:
	push	0
	push	3
	mul
	push	1
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	1
	compEQ
	push	1
	push	3
	mul
	push	1
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	1
	compEQ
	and
	push	2
	push	3
	mul
	push	1
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	1
	compEQ
	and
	j0	L006
	push	sp
	push	1
	add
	pop	sp
	push	1
	pop	sb[0]
L006:
	push	0
	push	3
	mul
	push	2
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	1
	compEQ
	push	1
	push	3
	mul
	push	2
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	1
	compEQ
	and
	push	2
	push	3
	mul
	push	2
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	1
	compEQ
	and
	j0	L007
	push	sp
	push	1
	add
	pop	sp
	push	1
	pop	sb[0]
L007:
	push	0
	push	3
	mul
	push	0
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	1
	compEQ
	push	1
	push	3
	mul
	push	1
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	1
	compEQ
	and
	push	2
	push	3
	mul
	push	2
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	1
	compEQ
	and
	j0	L008
	push	sp
	push	1
	add
	pop	sp
	push	1
	pop	sb[0]
L008:
	push	0
	push	3
	mul
	push	2
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	1
	compEQ
	push	1
	push	3
	mul
	push	1
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	1
	compEQ
	and
	push	2
	push	3
	mul
	push	0
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	1
	compEQ
	and
	j0	L009
	push	sp
	push	1
	add
	pop	sp
	push	1
	pop	sb[0]
L009:
	push	0
	push	3
	mul
	push	0
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	2
	compEQ
	push	0
	push	3
	mul
	push	1
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	2
	compEQ
	and
	push	0
	push	3
	mul
	push	2
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	2
	compEQ
	and
	j0	L010
	push	sp
	push	1
	add
	pop	sp
	push	1
	pop	sb[0]
L010:
	push	1
	push	3
	mul
	push	0
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	2
	compEQ
	push	1
	push	3
	mul
	push	1
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	2
	compEQ
	and
	push	1
	push	3
	mul
	push	2
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	2
	compEQ
	and
	j0	L011
	push	sp
	push	1
	add
	pop	sp
	push	1
	pop	sb[0]
L011:
	push	2
	push	3
	mul
	push	0
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	2
	compEQ
	push	2
	push	3
	mul
	push	1
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	2
	compEQ
	and
	push	2
	push	3
	mul
	push	2
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	2
	compEQ
	and
	j0	L012
	push	sp
	push	1
	add
	pop	sp
	push	1
	pop	sb[0]
L012:
	push	0
	push	3
	mul
	push	0
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	2
	compEQ
	push	1
	push	3
	mul
	push	0
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	2
	compEQ
	and
	push	2
	push	3
	mul
	push	0
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	2
	compEQ
	and
	j0	L013
	push	sp
	push	1
	add
	pop	sp
	push	1
	pop	sb[0]
L013:
	push	0
	push	3
	mul
	push	1
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	2
	compEQ
	push	1
	push	3
	mul
	push	1
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	2
	compEQ
	and
	push	2
	push	3
	mul
	push	1
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	2
	compEQ
	and
	j0	L014
	push	sp
	push	1
	add
	pop	sp
	push	1
	pop	sb[0]
L014:
	push	0
	push	3
	mul
	push	2
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	2
	compEQ
	push	1
	push	3
	mul
	push	2
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	2
	compEQ
	and
	push	2
	push	3
	mul
	push	2
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	2
	compEQ
	and
	j0	L015
	push	sp
	push	1
	add
	pop	sp
	push	1
	pop	sb[0]
L015:
	push	0
	push	3
	mul
	push	0
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	2
	compEQ
	push	1
	push	3
	mul
	push	1
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	2
	compEQ
	and
	push	2
	push	3
	mul
	push	2
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	2
	compEQ
	and
	j0	L016
	push	sp
	push	1
	add
	pop	sp
	push	1
	pop	sb[0]
L016:
	push	0
	push	3
	mul
	push	2
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	2
	compEQ
	push	1
	push	3
	mul
	push	1
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	2
	compEQ
	and
	push	2
	push	3
	mul
	push	0
	add
	push	3
	add
	pop	in
	push	sb[in]
	push	2
	compEQ
	and
	j0	L017
	push	sp
	push	1
	add
	pop	sp
	push	1
	pop	sb[0]
L017:
	push	sb[1]
	push	1
	compEQ
	j0	L018
	push	sp
	push	1
	add
	pop	sp
	push	2
	pop	sb[1]
	jmp	L019
L018:
	push	sp
	push	1
	add
	pop	sp
	push	1
	pop	sb[1]
L019:
	push	sp
	push	1
	add
	pop	sp
	push	sb[2]
	push	1
	add
	pop	sb[2]
	jmp	L000
L001:
	push	"finish!"
	puts
	push	sb[0]
	push	1
	compEQ
	j0	L020
	push	"first player wins!"
	puts
L020:
	push	sb[0]
	push	2
	compEQ
	j0	L021
	push	"second player wins!"
	puts
L021:
	push	sb[0]
	push	0
	compEQ
	j0	L022
	push	"end in a draw!"
	puts
L022:
	end
