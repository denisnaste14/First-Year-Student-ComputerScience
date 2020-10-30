bits 32

global start 

extern exit,scanf,fopen,fwrite,printf             
import exit msvcrt.dll 
import scanf msvcrt.dll
import fopen msvcrt.dll
import fwrite msvcrt.dll  
import printf msvcrt.dll 
                          
segment data use32 class=data
    mod_acces db 'w', 0
    filename db 'ex17.txt', 0
    file_descriptor dd 0
    
    format db '%d', 0
    n dd 1
    
    mesaj_citire db 'Numar= ', 0
    
    divizor7 dw 7
  
;17. Se da un nume de fisier (definit in segmentul de date). Sa se creeze un fisier cu numele dat, apoi sa se citeasca de la tastatura numere si sa se scrie din valorile citite in fisier numerele divizibile cu 7, pana cand se citeste de la tastatura valoarea 0. 
segment code use32 class=code
    start:
    
        ;fopen(const char* nume_fisier, const char * mod_acces)
        push dword mod_acces
        push dword filename
        call [fopen]
        add esp, 4*2
        
        mov [file_descriptor], eax
        
    bucla:
        cmp [n], dword 0
        je dupa_bucla
        
        ;printf-mesaj pentru citire
        push dword mesaj_citire
        call [printf]
        add esp, 4*1
       
        ;scanf(const char * format, adresa_variabila_1, ...)
        push dword n
        push dword format
        call [scanf]
        add esp, 4*2
        cmp [n], dword 0
        je dupa_bucla
        
        mov eax, [n]
        mov dx, 0
        div word [divizor7]     ;voi avea restul in dx si catul in ax
        
        cmp dx, word 0          ;verifica daca numarul citit este divizibil cu 7 (daca restul este 0)
        jne peste
        ;in aceasta parte se va intra doar in cazul in care dx=0
        
        ;fwrite(fwrite(void buffer, int size, int count, FILE stream )
        
        push dword [file_descriptor]
        push 1
        push 4
        push dword n
        call [fwrite]
        add esp, 4*4
             
    peste:
        jmp bucla
    dupa_bucla:
        push    dword 0     
        call    [exit]       
