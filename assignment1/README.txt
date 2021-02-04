------------------------------------------------------------------------
Driver 1
- in the driver 1 program we allocate memory for 1 million integers
which take up (1000000 * 4 bytes) about 4 million bytes to store. We defined 2 separate pointers, 
where the (regions1) pointer references the mem regions we find before the 1 million integers are
allocated. The second pointer (regions2) references the mem regions we found after the 1 million 
integers were allocated. We would expect the allocated 1 million integers to be stored in the heap 
within the User space mode of the memory layout, as well as both mem region arrays since
all were initialized with malloc. This would would make the heap grow towards the higher memory
addresses

Driver 2
- in the driver 2 program we make a recursive call to a function finding the result of the fibanacci 
sequence of size 30. We defined 2 separate pointers, where the (regions1) pointer references the 
mem regions we find before the recursive function is called. The second pointer (regions2) 
references the mem regions we found after the recursive functin was called. The fibonacci function
would have a moderate recursive depth where we would expect the stack to grow towards the lower memory 
addresses in the User Space, since local function scopes and return addresses would continue to be stored as the 
recursion tree grows. the local function states on the stack would be popped off once that particular function
in the recursive tree had returned a value to its caller.

Driver 3
in the driver 3 program make a call to a function from the C math library where we calculate the
the remainder of 1200 divided by 376 and store the output in a variable called result. We defined 2 separate pointers, where the (regions1) pointer references the 
mem regions we find before the calculation. The second pointer (regions2) 
references the mem regions we found after the calculation. Dunamically loading the C math library would store it in the 
TEXT section of the User Space which is located in the lower addresses of the memory layout. Making tha actual call to the function fmod() would result in
a frame being added to the stack and incrementing the stack pointer unitl the function call returns. the result returnes
from the function call would get stored in a variable that dynamicalled allocated in the heap space



