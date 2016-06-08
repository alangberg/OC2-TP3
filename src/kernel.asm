; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "imprimir.mac"
extern GDT_DESC
extern IDT_DESC
extern idt_inicializar
extern imprimirJuego
extern systemClock
extern mmu_inicializar_dir_kernel
extern mmu_mapear_pagina
extern mmu_unmapear_pagina
extern resetear_pic
extern habilitar_pic

%define PAGE_DIRECTORY_KERNEL   0x27000
%define PAGE_TABLE_KERNEL		0x28000

global start


;; Saltear seccion de datos
jmp start

;;
;; Seccion de datos.
;; -------------------------------------------------------------------------- ;;
iniciando_mr_msg db     'Iniciando kernel (Modo Real)...'
iniciando_mr_len equ    $ - iniciando_mr_msg

iniciando_mp_msg db     'Iniciando kernel (Modo Protegido)...'
iniciando_mp_len equ    $ - iniciando_mp_msg

;;
;; Seccion de código.
;; -------------------------------------------------------------------------- ;;

;; Punto de entrada del kernel.
BITS 16
start:
    ; Deshabilitar interrupciones
    cli

    ; Cambiar modo de video a   
    mov ax, 0003h
    int 10h ; set mode 03h
    xor bx, bx
    mov ax, 1112h
    int 10h ; load 8x8 font

    ; Imprimir mensaje de bienvenida
    imprimir_texto_mr iniciando_mr_msg, iniciando_mr_len, 0x07, 0, 0
    

    ; Habilitar A20
    call habilitar_A20 

    ; Cargar la GDT
    cli
    LGDT [GDT_DESC]

    ; Setear el bit PE del registro CR0
    MOV eax,cr0
    OR eax,1
    MOV cr0, eax
            
    ; Saltar a modo protegido
    ;xchg bx, bx
    JMP 0x20:mProtegido  ;codigo primera tabla lvl 0 0X20 es VERDURITA     
BITS 32
mProtegido:

    ;Establecer selectores de segmentos
    xor ax, ax
    mov ax, 0x28   ;datos primera tabla lvl 0
    mov ds, ax ;VERDURITA
    mov ss, ax ;VERDURITA
    mov es, ax ;VERDURITA
    mov gs, ax ;VERDURITA
    xor ax, ax
    mov ax, 0x40
    mov fs, ax ;VERDURITA Pongo la entrada de Video


    ; Establecer la base de la pila
    mov esp, 0x27000 ;VERDURITA
    mov ebp, esp ;Hace falta algo mas para la pila ?

    
    ; Imprimir mensaje de bienvenida
    imprimir_texto_mp iniciando_mp_msg, iniciando_mp_len, 0x07, 2, 0

    ; Inicializar pantalla  ;ALTA VERDURA
    
 ;    xor ecx, ecx
 ;    mov ecx, 0xdc0
 ;    sub ecx, 160
 ;    xor esi, esi
 ;    add esi, 160
	; .ciclo:
 ;    	mov word [fs:esi], 0xF700
 ;        add esi, 2
 ;    loop .ciclo

    mov edi, 10
    mov esi, 10

    push edi
    push esi

    .gameLoop:
        call imprimirJuego
        ; add systemClock, 1
    ; jmp .gameLoop

    add esp, 2*4

    ; Inicializar el manejador de memoria
 	 
    ; Inicializar el directorio de paginas
    call mmu_inicializar_dir_kernel
    ; Cargar directorio de paginas
	mov eax, PAGE_DIRECTORY_KERNEL
	mov cr3, eax

    ; Habilitar paginacion
 	mov eax, cr0
	or eax, 0x80000000
	mov cr0, eax ;Verdurita

    mov edi, 0x00400000
    mov esi, cr3
    mov edx, 0x00400000
    push edx
    push esi
    push edi
    call mmu_mapear_pagina
;    xchg bx, bx    

    add esp, 3*4

    mov edi, 0x00400000
    mov esi, cr3
    push esi
    push edi
    call mmu_unmapear_pagina

    ;xchg bx, bx    
    ; Inicializar tss

    ; Inicializar tss de la tarea Idle

    ; Inicializar el scheduler

    ; Inicializar la IDT

    call idt_inicializar
    
    ; Cargar IDT
 	
    LIDT [IDT_DESC]
    ;xchg bx, bx

    ; Configurar controlador de interrupciones

    call resetear_pic
    call habilitar_pic

    ; Cargar tarea inicial

    ; Habilitar interrupciones

    sti

    ; Saltar a la primera tarea: Idle

    ; Ciclar infinitamente (por si algo sale mal...)
    mov eax, 0xFFFF
    mov ebx, 0xFFFF
    mov ecx, 0xFFFF
    mov edx, 0xFFFF
    jmp $
    jmp $

;; -------------------------------------------------------------------------- ;;

%include "a20.asm"
