; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================

%include "imprimir.mac"
extern GDT_DESC


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

    ; Cambiar modo de video a 80 X 50
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
    xchg bx, bx
    JMP 0x20:mProtegido  ;codigo primera tabla lvl 0 0X20 es VERDURITA     

mProtegido:

    ;Establecer selectores de segmentos
    xor ax, ax
    mov ax, 0x28   ;datos primera tabla lvl 0
    mov ds, ax ;VERDURITA
    mov es, ax ;VERDURITA
    mov gs, ax ;VERDURITA
    mov ss, ax ;VERDURITA
    mov fs, ax ;VERDURITA


    ; Establecer la base de la pila
    mov esp, 0x27000 ;VERDURITA
    mov ebp, esp

    
    ; Imprimir mensaje de bienvenida
    imprimir_texto_mp iniciando_mp_msg, iniciando_mp_len, 0x07, 0, 0 ;Que es cada campo?


    ; Inicializar pantalla
    
    ; Inicializar el manejador de memoria
 
    ; Inicializar el directorio de paginas
    
    ; Cargar directorio de paginas

    ; Habilitar paginacion
    
    ; Inicializar tss

    ; Inicializar tss de la tarea Idle

    ; Inicializar el scheduler

    ; Inicializar la IDT
    
    ; Cargar IDT
 
    ; Configurar controlador de interrupciones

    ; Cargar tarea inicial

    ; Habilitar interrupciones

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
