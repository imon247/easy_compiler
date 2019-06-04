array arr[3][4][2];
func(arr, y){
	arr[1][0][2] = y;
	return arr[1][0][2]*arr[1][0][2];
}

x = func(arr, 3);
print x;