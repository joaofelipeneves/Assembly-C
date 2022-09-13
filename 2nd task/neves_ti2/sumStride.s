# pseudo-constantes
EXIT = 1
LINUX_SYSCALL = 0x80

.data                   
vetor:  .int  1, -1, 1, 1, 3	# a vector of integers
len = (. - vetor)/4		# the size of the vector
stride: .int 5
total: .int 0

### do not change this line (your code must be placed after this line)

.text           
.global _start  


_start:



### do not change this line and the lines below
	movl total, %ebx  #  put the result in ebx
        movl $EXIT,%eax	# requires exit to the system
        int  $LINUX_SYSCALL	# calls the system
