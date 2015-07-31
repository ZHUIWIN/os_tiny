STACK_SIZE =	0x1000	# Size of heap and stack. 4KB

WHITE	= 0x7			# 白色，用于输出字符，为字符颜色

VGA_START	= 0xb8000

/* ===== code32 =========================== */

.text
	.globl 	start		# GNU default entry point
	.globl 	myMain
.code32
start:
its_ok:
	movl	$ok_message, %esi
	movb	$WHITE, %ah
#	movl	$0, %edx 	# %edx is set above
	call	pm_print_string

	jmp establish_stack

dead:	jmp dead			# Never here


    .globl context_switch
context_switch:
    #movl %ebp,ptr3
    push %ebp
    movl %esp,ptr2 
    #movl stack_esp,%esp
    pop %ebp
    ret
    
    .globl goto_temp   
goto_temp:
    push ptr4
    popf
    movl ptr2,%esp
    movl ptr3,%ebp
    ret
    
    .globl save_temp
save_temp:    
    movl %esp,ptr2
    movl %ebp,ptr3
    pushf
    pop  ptr4
    ret

    .globl off_int
off_int:
    
    .globl on_int
on_int:
# 在调用pm_print_string之前，必须先进行如下赋值
#	movl	string, %esi 
#	movb	color, %ah
#	movl	offset, %edx
pm_print_string:
	movl	$VGA_START, %ebx	
pm_print_string_loop:	
	lodsb
	andb	%al, %al
	jz	pm_print_string_end
	movw	%ax, %es:0(%ebx,%edx,2)
	incl	%edx
	jmp	pm_print_string_loop
pm_print_string_end:
	ret

# Set up the stack
establish_stack:
	movl	$_end, %eax		# eax = end of bss/start of heap
	addl	$STACK_SIZE, %eax	# make room for stack
	andl	$0xffffffc0, %eax	# align it on 16 byte boundary
	
	movl	%eax, %esp		# set stack pointer
	movl	%eax, %ebp		# set base pointer

# Zero out the BSS segment
zero_bss:
	cld				              # make direction flag count up
	movl	$_end, %ecx		    # find end of .bss
	movl	$_bss_start, %edi	# edi = beginning of .bss
	subl	%edi, %ecx		    # ecx = size of .bss in bytes
	shrl	%ecx			        # size of .bss in longs
	shrl	%ecx
	
	xorl	%eax, %eax		    # value to clear out memory
	repne			            	# while ecx != 0
	stosl				            # clear a long in the bss

# Transfer control to main
to_main:
	movl	$to_main_message, %esi 
	movb	$WHITE, %ah
	movl	$(11*80), %edx 	
	call	pm_print_string
	call    setup_idt
	call    init_8259
	call    init_8253
	call    enable_interupt
	call	myMain

shut_down:	
	jmp	shut_down	# Never here

init_8253:
    movb $0x34,%al
    out  %al,$0x43
    movb $0x2e,%al
    out  %al,$0x40
    movb $0x9c,%al
    out  %al,$0x40
    ret
    
init_8259:
    movb $00,%al
    out %al,$0x21
    
    movb $0xff,%al
    out %al,$0xa1
    
    movb $0x11,%al
    out %al,$0x20
    
    movb $0x20,%al
    out %al,$0x21
    
    movb $0x04,%al
    out %al,$0x21
    
    movb $0x03,%al
    out %al,$0x21
    
    movb $0x11,%al
    out %al,$0xa0
    
    movb $0x28,%al
    out %al,$0xa1
    
    movb $0x02,%al
    out %al,$0xa1
    
    movb $0x01,%al
    out %al,$0xa1
    
    ret

setup_idt:
    lidt idtptr
    
	lea ignore_int,%edx
	movl $0x80000,%eax
	movw %dx,%ax		
	movw $0x8E00,%dx	

    movl $idt,%edi
    
	movl $256,%ecx
rp_sidt:
	movl %eax,(%edi)
	movl %edx,4(%edi)
	addl $8,%edi
	dec %ecx
	jne rp_sidt
	
	lea  time_int,%edx
	movw %dx,%ax
	movw $0x8E00,%dx
	movl $(256-32)*8,%ecx
    subl %ecx,%edi
	movl %eax,(%edi)
	movl %edx,4(%edi)
	ret

ignore_int:
	cld
	pushl %eax
	pushl %edx
	pushl %esi
	
	movl	$int_msg, %esi 
	movb	$WHITE, %ah
	movl	$(11*80), %edx 	
	call	pm_print_string
	
	popl %esi
	popl %edx
	popl %eax
	iret

time_int:
	cld
	pusha
	rdtsc
	movl %edx,TSC1_pev
	movl %eax,TSC2_pev
	#pushf
	#movl	$time_msg, %esi 
	#movb	$WHITE, %ah
	#movl	$(11*80), %edx
	#call	pm_print_string
	call    timer
	rdtsc
	mov %edx,TSC1
	mov %eax,TSC2
	call print_tsc
	
	#popf
	popa
	
	iret    
    
    .globl enable_interupt
enable_interupt:
    sti    
    
    .globl disable_interupt
disable_interupt:
    sti    
    
/* ===== data =========================== */
.data
		.globl _stack_size
_stack_size:	.long STACK_SIZE

ok_message:
	.ascii	"O.K.!"
	.byte	0

to_main_message:
	.ascii	"Call myMain..."
	.byte	0
	
int_msg:
    .ascii "UNKNOWN INTERUPT!"
    .byte   0

time_msg:
    .ascii "TIME INTERUPT"
    .byte   0
    
idtptr:
	.word	256*8-1
	.long	idt

# IDT
idt:
	.rept   256 		# idt contains 256 entries
	.word 0,0,0,0
	.endr
	
