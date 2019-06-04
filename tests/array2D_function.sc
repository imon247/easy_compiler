array arr[3][4];
func(arr){
	arr[2][2] = 3;
	return arr[2][2]*arr[2][2];
}

x = func(arr);
print x;