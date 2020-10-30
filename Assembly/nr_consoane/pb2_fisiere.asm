bits 32

global start 

extern exit,fopen,fread,printf              
import exit msvcrt.dll    
import fopen msvcrt.dll
import fread msvcrt.dll
import printf msvcrt.dll

segment data use32 class=data
  filename db "pb2.txt", 0      ;numele fisierului care va fi deschis 
  open_mode db "r", 0           ;modul de deschidere al fisierului, in acest caz "r"-doar pentru citire
  
  file_descriptor dd -1         ;variabila in care vom salva descriptorul fisierului - necesar pentru referirea la fisier
  len equ 100                   ;constanta care imi indica nr max de elemente citite din fisier
  text times len db 0           ; sirul in care se va citi textul din fisier
  
  format_afisare db "Numarul de consoane din textul dat este: %d", 0
;2. Se da un fisier text. Sa se citeasca continutul fisierului, sa se contorizeze numarul de consoane si sa se afiseze aceasta valoare. Numele fisierului text este definit in segmentul de date. 
segment code use32 class=code
    start:
        ;urmeaza apel fopen
        ;functia va returna in EAX descriptorul fisierului sau 0 in caz de eroare
        ;FILE *fopen(const char *filename,const char *mode);
        
        push dword open_mode
        push dword filename
        call [fopen] 
        add esp, 4*2        ;refac dimensiunea stivei
        
        cmp eax, 0
        je final            ;daca a aparut o eroare in deschiderea fisierului, se va termia programul
        
        mov [file_descriptor],eax   ;imi salvez in variabile file_descriptor valoarea returnata de fopen
        
        ;citirea din fisier cu apelul fread
        ;size_t fread(void *buffer,size_t size,size_t count,FILE *stream);
        
        push dword [file_descriptor]    ;am nevoie de valoarea de la offsetul lui file_descriptor
        push dword len
        push dword 1
        push dword text
        call [fread]
        add esp, 4*4   
        ;dupa acest apel de functie, in eax voi avea numarul de caractere citite din fisier
        
        mov esi, 0      ;voi folosi esi pentru parcurgerea sirului byte cu byte
        mov ecx, eax    ;in ecx voi avea acum nr de caractere citite din fisier
        mov ebx, 0      ;ebx voi face numararea consoanelor
    repeta:
        cmp byte [text+esi],'a'
        je vocala
        cmp byte [text+esi],'e'
        je vocala
        cmp byte [text+esi],'i'
        je vocala
        cmp byte [text+esi],'o'
        je vocala
        cmp byte [text+esi],'u'
        je vocala
        inc ebx         ;pe acest nivel de cod se va ajunge doar in cazul in care caracterul curent este consoana
    vocala:
        inc esi
        loop repeta
    
    ;afisare numarului de consoane cu printf 
    ;printf(const char *format [,argument]...)
        push dword ebx
        push dword format_afisare
        call [printf]
        add esp, 4*2
    final:
        push    dword 0     
        call    [exit]       
