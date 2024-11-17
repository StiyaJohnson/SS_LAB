.model small 
.stack 64
.data

string dw ?
msg1 db "enter the string:$"
string1 db 0ah,"the string is palindrome:$"
string2 db 0ah,"the string is not palindrome:$"

read macro msg
mov dx,offset msg
mov ah,3Fh
int 21h
endm

print macro msg
mov dx,offset msg
mov ah,09h
int 21h
endm

.code

mov ax,@data
mov ds,ax

print msg1
read string
mov si,offset string

loop1:
mov al,[si]
cmp al,'$'
je l1
inc si
jmp loop1


l1:
mov di,offset string
dec si

loop2:
cmp si,di
jl out1
mov al,[si]
mov bl,[di]
cmp al,bl
jne out2
dec si
inc di
jmp loop2



out1:
print string1
jmp exit

out2:
print string2

exit:
mov ah,4ch
int 21h
end
