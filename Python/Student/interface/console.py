from exceptii.exceptie import ValidError,RepoError
class Console:
    def __ui_afisare(self):
        #studenti
        print("Gestiune lista de studenti:")
        print("    1.Adaugare student: add_student <id> <nume> <grup>")
        print("    2.Stergere student: del_student <id>")
        print("    3.Modificare student: upd_student <id> <nume nou> <grup nou>")
        print("    4.Afisare student dupa id dat: print_student <id>")
        print("    5.Afisarea studentilor: print_all_studenti")
        print("    6.Adaugare n studenti random: add_random_studenti <nr>")
        print("Gestiune lista de probleme:")
        print("    7.Adaugare problema: add_problema <lab_nr> <descriere> <deadline>")
        print("    8.Stergere problema dupa lab_nr: del_problema <lab_nr>")
        print("    9.Modificare problema: upd_problema <lab_nr> <descriere noua> <deadline nou>")
        print("    10.Afisare problema dupa lab_nr: print_problema <lab_nr")
        print("    11.Afisarea problemelor: print_all_probleme")
        print("Gestiune lista de note:")
        print("    12.Adaugare nota: add_nota <punctaj> <studentID> <lab_nr>")
        print("    13.Afisare toate notele: print_all_note")
        print("Statistici:")
        print("    14.Afisare lista de studenti cu notele lor ordonati dupa nume: sortare_dupa_nume")
        print("    15.Afisare lista de studenti cu notele lor ordonati dupa nota: sortare_dupa_nota")
        print("    16.Afisare studenti care au media notelor mai mica decat nota 5 (50 de puncte): media_restantier")
        print("    17.Insertion Sort: afisarea listei de note sortata 0-crescator sau 1-descrescator: insertion_sort <0/1>")
        print("    18.Comb Sort: afisarea listei de note sortata 0-crescator sau 1-descrescator: comb_sort <0/1>")
    def __ui_add_student(self,values):
    #in values retin comanda data ca text impartita pe valori ca si parametrii
        if len(values)!=3:
            raise ValueError("Nu ati introdus un numar bun de parametrii!")
        studentID=values[0]
        nume=values[1]
        grup=values[2]
        self.__srvStud.adauga_student(studentID,nume,grup)
        
    def __ui_print_student(self, value):
    #date de intrare:value-reprezinta id-ul dupa care se va face cautarea si afisarea unui student
        if len(value)!=1:
            raise ValueError("Nu ati introdus un numar bun de parametrii!")
        studentID=value[0]
        print(self.__srvStud.afiseaza_student(studentID))
        
    
    def __ui_delete_student(self, value):
        #date de intrare:value-reprezinta id-ul dupa care se va face stergerea unui student
        if len(value)!=1:
            raise ValueError("Nu ati introdus un numar bun de parametrii!")
        studentID=value[0]
        self.__srvStud.sterge_student(studentID)
    
    def __ui_update_student(self, values):
        #date de intrare: values- reprezinta o lista cu urmatoarele elemente:
            #values[0]-studentID-id-ul dupa care se va cauta studentul care va fi modificat
            #values[1]-nume-numele care va inlocui cel din obiectul studentului gasit
            #values[2]-grup-grupul care va inlocui cel din obiectul studentului gasit
        if len(values)!=3:
            raise ValueError("Nu ati introdus un numar bun de parametrii!")
        studentID=values[0]
        nume_upd=values[1]
        grup_upd=values[2]
        self.__srvStud.update_student(studentID,nume_upd,grup_upd)
        
    def __ui_print_all_studenti(self,values):
        if len(values)!=0:
            raise ValueError("Nu ati introdus un numar bun de parametrii!")
        for x in self.__srvStud.all_studenti():
            print(x)
            
    def __ui_adauga_problema(self,values):
        if len(values)!=3:
            raise ValueError("Nu ati introdus un numar bun de parametrii!")
        nrlab_pb=values[0]
        descriere=values[1]
        deadline=values[2]
        self.__srvPLab.adauga_problema(nrlab_pb,descriere,deadline)
    
    def __ui_print_problema(self, values):
        if len(values)!=1:
            raise ValueError("Nu ati introdus un numar bun de parametrii!")
        nrlab_pb=values[0]
        print(self.__srvPLab.afiseaza_problema(nrlab_pb))
        
    
    def __ui_del_problema(self, values):
        if len(values)!=1:
            raise ValueError("Nu ati introdus un numar bun de parametrii!")
        nrlab_pb=values[0]
        self.__srvPLab.sterge_problema(nrlab_pb)
    
    def __ui_print_all_probleme(self,values):
        if len(values)!=0:
            raise ValueError("Nu ati introdus un numar bun de parametrii!")
        for x in self.__srvPLab.all_probleme():
            print(x)
            
    def __ui_update_problema(self,values):
        if len(values)!=3:
            raise ValueError("Nu ati introdus un numar bun de parametrii!")
        nrlab_pb=values[0]
        descriere=values[1]
        deadline=values[2]
        self.__srvPLab.modificare_problema(nrlab_pb,descriere,deadline)
        

    def __ui_add_random_studenti(self, values):
        if len(values)!=1:
            raise ValueError("Nu ati introdus un numar bun de parametrii!")
        nr=int(values[0])
        self.__srvStud.random_studenti(nr)
        
    def __ui_add_nota(self, values):
        if len(values)!=3:
            raise ValueError("Nu ati introdus un numar bun de parametrii!")
        punctaj=values[0]
        studentID=values[1]
        nrlab_pb=values[2]
        self.__srvNote.adauga_nota(punctaj,studentID,nrlab_pb)
    

    def __ui_print_all_note(self, values):
        if len(values)!=0:
            raise ValueError("Nu ati introdus un numar bun de parametrii!")  
        for x in self.__srvNote.print_all_note():
            print(x)      
    
    def __ui_media_pe_grup(self, values):
        if len(values)!=0:
            raise ValueError("Nu ati introdus un numar bun de parametrii!")
        print(self.__srvNote.media_fiecare_grupa())
        
    def __ui_afisare_sortare_dupa_nume(self,values):
        if len(values)!=0:
            raise ValueError("Nu ati introdus un numar bun de parametrii!")
        print(self.__srvNote.sortare_dupa_nume())
        
    def __ui_afisare_sortare_dupa_nota(self,values):
        if len(values)!=0:
            raise ValueError("Nu ati introdus un numar bun de parametrii!")
        print(self.__srvNote.sortare_dupa_nota())
    
    def __ui_media_restantier(self,values):
        if len(values)!=0:
            raise ValueError("Nu ati introdus un numar bun de parametrii!")
        print(self.__srvNote.studenti_restanti())
    
    def __ui_insertion_sort(self,values):
        if len(values)!=1:
            raise ValueError("Nu ati introdus un numar bun de parametrii!")
        revers=int(values[0])
        lista=self.__srvNote.print_all_note()
        
        self.__srvNote.insertion_sort(lista,key=lambda x:x.get_punctaj(),reverse=revers,cmp=self.__srvNote.cmp)
        for x in lista:
            print(x)
            
    def __ui_comb_sort(self,values):
        if len(values)!=1:
            raise ValueError("Nu ati introdus un numar bun de parametrii!")
        revers=int(values[0])
        lista=self.__srvNote.print_all_note()
        
        self.__srvNote.combSort(lista,key=lambda x:x.get_punctaj(),reverse=revers,cmp=self.__srvNote.cmp)
        for x in lista:
            print(x)

    def __init__(self, srvStud, srvPLab, srvNote):
        self.__srvStud=srvStud 
        self.__srvPLab=srvPLab
        self.__srvNote=srvNote
        self.__comands={
            "add_student": self.__ui_add_student,
            "print_student": self.__ui_print_student,
            "del_student":self.__ui_delete_student,
            "upd_student":self.__ui_update_student,
            "print_all_studenti":self.__ui_print_all_studenti,
            "add_problema":self.__ui_adauga_problema,
            "print_problema":self.__ui_print_problema,
            "del_problema":self.__ui_del_problema,
            "print_all_probleme":self.__ui_print_all_probleme,
            "upd_problema":self.__ui_update_problema,
            "add_random_studenti":self.__ui_add_random_studenti,
            "add_nota":self.__ui_add_nota,
            "print_all_note":self.__ui_print_all_note,
            "media_grupe":self.__ui_media_pe_grup,
            "sortare_dupa_nume":self.__ui_afisare_sortare_dupa_nume,
            "sortare_dupa_nota":self.__ui_afisare_sortare_dupa_nota,
            "media_restantier":self.__ui_media_restantier,
            "insertion_sort":self.__ui_insertion_sort,
            "comb_sort":self.__ui_comb_sort
            }
        
    def run(self):
        self.__ui_afisare()
        while True:
            txt=input("->")
            txt=txt.strip()
            if(txt=="exit" or txt=="iesi" or txt=="end" or txt=="finish"):
                return
            param=txt.split(" ")
            comanda=param[0]
            values=param[1:]
            if comanda in self.__comands:
                try:
                    self.__comands[comanda](values)
                except ValueError as val:
                    print(str(val)+" Va rugam introduceti valori valabile!Reintrodu valori ")
                except ValidError as ve:
                    print("Eroare de validare!:\n"+str(ve))
                except RepoError as re:
                    print("Eroare de repo!\n"+str(re))
            else:
                print("Va rugam introduceti o comanda valida!")
        

