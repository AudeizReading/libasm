;	ssize_t	ft_write(int fildes, const void *buffer, int iovcnt);
;
;		ecrit le buffer de taille iovcnt dans le file descriptor fildes
;		inspiré de 
;		
;	author: alellouc@student.42nice.fr
;	date:	2023-06-29 Thursday
section	.data

write_syscall:
	dq	0x2000004					; bien plus comprehensible que seulement 0x2000004 
									; Les numeros des syscalls MacOSX sont tous préfixés d'un 2.
mess: db "Ca me casse les bonbons",10
section .text

extern ___error
global _ft_write

_ft_write:
;epilog
	push	rbp	;
	mov		rbp, rsp	;
	sub		rsp, 32

	mov		qword [rbp - 16], rdi			; fildes 
	mov		qword [rbp - 24], rsi			; buffer
	mov		qword [rbp - 32], rdx			; iovcnt

	mov		rax, [rel write_syscall]		; On doit placer la valeur du syscall dans rax
											; [rel write_syscall] est la syntaxe pour acceder a la valeur d'un
											; label de la section data (nasm tutorial)

	mov		rdi, qword [rbp - 16]			; préparation de fildes pr write syscall
	mov		rsi, qword [rbp - 24]			; préparation de buffer pr write syscall
	mov		rdx, qword [rbp - 32]			; préparation de iovcnt pr write syscall
	syscall									; Appel au syscall write

	mov		[rbp - 8], rax					; Sauvegarde du retour de l'appel système write
											; MacOSX a la particularité de ne pas retourner les erreurs sous
											; forme negative, par contre le flag CF est levé si un syscall
											; rencontre un souci et le code retourné dans rax est le numéro de
											; l'erreur qu'il nous faut pour parametrer errno
	jc		errno_settings					; On checke le flag CF avec l'instruction jc (jump carry...), 
											; si CF est levé alors go pour la gestion de errno
	jmp		prolog							; sinon go la fin

errno_settings:
	call	___error						; call ___error, __errno_location ne semble pas fonctionner sous
											; MacOSX. Cette routine ne prend aucun argument et retourne un int
											; correspondant a errno. errno se trouve alors dans rax
	mov		ecx, dword [rbp - 8]			; On recup le retour du syscall write pour set errno avec
	mov		dword [rax], ecx				; Enfin, errno = retour syscall + ajustement sur 4 bytes

	mov		dword [rbp - 8], -1				; On place -1 sur la stack, a l'endroit qu'on a reservé pr les
											; valeurs de retour, pour le rappeler au prolog
prolog:
;prolog
	mov		eax, dword [rbp - 8]			; On recupere la valeur de retour du syscall write pr la retourner
	add		rsp, 32							; On remet la stack propre
	pop		rbp								; On remet rbp dans son etat anterieur
	ret										;
