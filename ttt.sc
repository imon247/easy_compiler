finish = 0;
player = 1;
i = 0;
array board[3][3];
board[0][0] = 0;
board[0][1] = 0;
board[0][2] = 0;
board[1][0] = 0;
board[1][1] = 0;
board[1][2] = 0;
board[2][0] = 0;
board[2][1] = 0;
board[2][2] = 0;

while(finish==0 && i<9){
	print "enter a pair of integer less than three:";
	read x;
	read y;
	board[x][y] = player;
	print board[x][y];
	if(board[0][0]==1 && board[0][1]==1 && board[0][2]==1){
		finish = 1;
	}
	if(board[1][0]==1 && board[1][1]==1 && board[1][2]==1){
		finish = 1;
	}
	if(board[2][0]==1 && board[2][1]==1 && board[2][2]==1){
		finish = 1;
	}
	if(board[0][0]==1 && board[1][0]==1 && board[2][0]==1){
		finish = 1;
	}
	if(board[0][1]==1 && board[1][1]==1 && board[2][1]==1){
		finish = 1;
	}
	if(board[0][2]==1 && board[1][2]==1 && board[2][2]==1){
		finish = 1;
	}
	if(board[0][0]==1 && board[1][1]==1 && board[2][2]==1){
		finish = 1;
	}
	if(board[0][2]==1 && board[1][1]==1 && board[2][0]==1){
		finish = 1;
	}


	if(board[0][0]==2 && board[0][1]==2 && board[0][2]==2){
		finish = 1;
	}
	if(board[1][0]==2 && board[1][1]==2 && board[1][2]==2){
		finish = 1;
	}
	if(board[2][0]==2 && board[2][1]==2 && board[2][2]==2){
		finish = 1;
	}
	if(board[0][0]==2 && board[1][0]==2 && board[2][0]==2){
		finish = 1;
	}
	if(board[0][1]==2 && board[1][1]==2 && board[2][1]==2){
		finish = 1;
	}
	if(board[0][2]==2 && board[1][2]==2 && board[2][2]==2){
		finish = 1;
	}
	if(board[0][0]==2 && board[1][1]==2 && board[2][2]==2){
		finish = 1;
	}
	if(board[0][2]==2 && board[1][1]==2 && board[2][0]==2){
		finish = 1;
	}

	if(player==1){
		player = 2;
	}
	else{
		player = 1;
	}
	i = i+1;
}

print "finish!";
if(finish==1){
	print "first player wins!";
}
if(finish==2){
	print "second player wins!";
}
if(finish==0){
	print "end in a draw!";
}