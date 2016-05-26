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

error_msg_0 db     'OH NO! Dividiste por cero!'
error_msg_len_0 equ    $ - error_msg_0

error_msg_1 db     'OH NO! Esta reservado por Intel!'
error_msg_len_1 equ    $ - error_msg_1

error_msg_2 db     'OH NO! Nonmaskable!'
error_msg_len_2 equ    $ - error_msg_2

error_msg_3 db     'OH NO! Breakpoint!'
error_msg_len_3 equ    $ - error_msg_3

error_msg_4 db     'OH NO! Overflow!'
error_msg_len_4 equ    $ - error_msg_4

error_msg_5 db     'OH NO! Bound!'
error_msg_len_5 equ    $ - error_msg_5

error_msg_6 db     'OH NO! Invalid Opcode!'
error_msg_len_6 equ    $ - error_msg_6

error_msg_7 db     'OH NO! Device Not Available!'
error_msg_len_7 equ    $ - error_msg_7

error_msg_8 db     'OH NO! Double Fault!'
error_msg_len_8 equ    $ - error_msg_8

error_msg_9 db     'OH NO! Coprocessor Segment Overrun!'
error_msg_len_9 equ    $ - error_msg_9

error_msg_10 db     'OH NO! Invalid TSS!'
error_msg_len_10 equ    $ - error_msg_10

error_msg_11 db     'OH NO! Segment Not Present!'
error_msg_len_11 equ    $ - error_msg_11

error_msg_12 db     'OH NO! Stack Segment Fault!'
error_msg_len_12 equ    $ - error_msg_12

error_msg_13 db     'OH NO! General Protection!'
error_msg_len_13 equ    $ - error_msg_13

error_msg_14 db     'OH NO! Page Fault!'
error_msg_len_14 equ    $ - error_msg_14

error_msg_15 db     'OH NO! Intel lo reservo!'
error_msg_len_15 equ    $ - error_msg_15

error_msg_16 db     'OH NO! x86 FPU nose que!'
error_msg_len_16 equ    $ - error_msg_16

error_msg_17 db     'OH NO! Alignment Check!'
error_msg_len_17 equ    $ - error_msg_17

error_msg_18 db     'OH NO! Machine Check!'
error_msg_len_18 equ    $ - error_msg_18

error_msg_19 db     'OH NO! SIMD Floating Point Exception!'
error_msg_len_19 equ    $ - error_msg_19
;;
;; Definición de MACROS
;; -------------------------------------------------------------------------- ;;

%macro ISR 1
global _isr%1

_isr%1:
    mov eax, %1
    imprimir_texto_mp error_msg_%1, error_msg_len_%1, 0x04, 0, 0
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
ISR 1
ISR 2
ISR 3
ISR 4
ISR 5
ISR 6
ISR 7
ISR 8
ISR 9
ISR 10
ISR 11
ISR 12
ISR 13
ISR 14
ISR 15
ISR 16
ISR 17
ISR 18
ISR 19

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
        
        
