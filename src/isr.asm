; ** por compatibilidad se omiten tildes **
; ==============================================================================
; TRABAJO PRACTICO 3 - System Programming - ORGANIZACION DE COMPUTADOR II - FCEN
; ==============================================================================
; definicion de rutinas de atencion de interrupciones

%include "imprimir.mac"

BITS 32

sched_tarea_offset:     dd 0x00
sched_tarea_selector:   dw 0x00

;; PIC
extern fin_intr_pic1

;; Sched
extern sched_proximo_indice

;;Mensajes

error_msg_1 db     'OH NO! Dividiste por cero!'
error_msg_1_len equ    $ - iniciando_mp_msg
imprimir_texto_mp iniciando_mp_msg, iniciando_mp_len, 0x07, 0, 0

;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;

%macro ISR 1
global _isr%1

_isr%1:
    mov eax, %1
    imprimir_texto_mp error_msg_%1, iniciando_mp_len, 0x07, 0, 0
    jmp $


%endmacro


;;
;; Datos
;; -------------------------------------------------------------------------- ;;
; Scheduler
isrnumero:           dd 0x00000000
isrClock:            db '|/-\'

;;
;; Rutina de atención de las EXCEPCIONES
;; -------------------------------------------------------------------------- ;;
ISR 0
error_msg_1 db     'OH NO! Dividiste por cero!'
error_msg_1_len equ    $ - iniciando_mp_msg
imprimir_texto_mp iniciando_mp_msg, iniciando_mp_len, 0x07, 0, 0

ISR 1
iniciando_mp_msg db     'OH NO! Esta Reservado para INTEL!'
iniciando_mp_len equ    $ - iniciando_mp_msg
imprimir_texto_mp iniciando_mp_msg, iniciando_mp_len, 0x07, 0, 0

ISR 2
iniciando_mp_msg db     'OH NO! NMASK'
iniciando_mp_len equ    $ - iniciando_mp_msg
imprimir_texto_mp iniciando_mp_msg, iniciando_mp_len, 0x07, 0, 0

ISR 3
iniciando_mp_msg db     'OH NO! Breakpoint'
iniciando_mp_len equ    $ - iniciando_mp_msg
imprimir_texto_mp iniciando_mp_msg, iniciando_mp_len, 0x07, 0, 0

;;
;; Rutina de atención del RELOJ
;; -------------------------------------------------------------------------- ;;

;;
;; Rutina de atención del TECLADO
;; -------------------------------------------------------------------------- ;;

;;
;; Rutinas de atención de las SYSCALLS
;; -------------------------------------------------------------------------- ;;

%define DONDE  0x124
%define SOY    0xA6A
%define MAPEAR 0xFF3

%define VIRUS_ROJO 0x841
%define VIRUS_AZUL 0x325


;; Funciones Auxiliares
;; -------------------------------------------------------------------------- ;;
proximo_reloj:
        pushad
        inc DWORD [isrnumero]
        mov ebx, [isrnumero]
        cmp ebx, 0x4
        jl .ok
                mov DWORD [isrnumero], 0x0
                mov ebx, 0
        .ok:
                add ebx, isrClock
                imprimir_texto_mp ebx, 1, 0x0f, 49, 79
                popad
        ret
        
        
