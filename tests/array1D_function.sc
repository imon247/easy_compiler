array arr[4];
arr[1] = 6;
func(arr,x){
	arr[x] = 9;
	return 0;
}
x = 1;
i = func(arr,0);
print arr[0];
print arr[1];