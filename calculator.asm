
.model small
.stack 64
dispm macro msg
mov dx,offset msg
mov ah,09h
int 21h
endm

dispn macro
mov dl,al
mov ah,02h
int 21h
endm

readno macro num
mov ah,01h
int 21h
sub al,30h
mov num,al
endm

.data
msg1 db 0ah,"Calculator 1.Sum 2.Product 3.Subtraction 4.Quotient 5.Exit$"
msg2 db 0ah,"Enter the choice:$"
msg3 db 0ah,"Enter the number(1):$"
msg4 db 0ah,"Enter the number(2):$"
msg5 db 0ah,"The sum is:$"
msg6 db 0ah,"The product is:$"
msg7 db 0ah,"The difference is:$"
msg8 db 0ah,"The quotient is:$"
num1 db ?
num2 db ?
ch1 db ?
rem db ?

.code
start:mov ax,@data
mov ds,ax

dispm msg1
dispm msg2
readno ch1
cmp ch1,05
jz exit

dispm msg3
readno num1
dispm msg4
readno num2
cmp ch1,01
jz addn
cmp ch1,02
jz prod
cmp ch1,03
jz subn
cmp ch1,04
jz divn
exit:mov ah,4ch
int 21h

addn:dispm msg5
mov al,num1
add al,num2
mov ah,00
   mov bl,10
   div bl
   
   mov rem,ah
   mov dl,al
   add dl,30h
   mov ah,02h
   int 21h

   
    mov dl,rem
    add dl,30h
    mov ah,02h
    int 21h
jmp start

prod:dispm msg6
mov al,num1
mul num2
mov ah,00
   mov bl,10
   div bl
   mov rem,ah
   mov dl,al
   add dl,30h
   mov ah,02h
   int 21h
   mov dl,rem
   add dl,30h
   mov ah,02h
   int 21h
jmp start

subn:dispm msg7
mov al,num1
sub al,num2
add al,30h
dispn
jmp start

divn:dispm msg8
mov ah,00h
mov al,num1
div num2
add al,30h
dispn
jmp start
end     