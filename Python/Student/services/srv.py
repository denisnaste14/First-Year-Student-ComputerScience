from domain.entitati import Student, PbLab, Nota
import random
import string
from exceptii.exceptie import RepoError

class SrvStud:
    def __init__(self,repoStud, validStud):
        self.__repoStud=repoStud
        self.__validStud=validStud
    
    def adauga_student(self, studentID, nume, grup):
        #date de intrare: studentID- nr intreg, nume-string, grup- nr intreg din [200,299]
        student=Student(studentID, nume, grup)
        #self.__validStud.validare_parametrii_student(student)
        self.__validStud.validare_student(student) 
        self.__repoStud.adaugaStudent(student)
    
    def afiseaza_student(self,studentID):
        #date de intrare: studentID- nr intreg
        #voi afisa studentul cerut prin ID-ul sau unic 
        student=Student(studentID,None,None)
        self.__validStud.validare_studentID(student)
        return self.__repoStud.cautareStudent(student)
    
    def sterge_student(self,studentID):
        #date de intrare: studentID-nr intreg
        #voi cauta studentul cu id-ul dat si il voi elimina din lista de entitati
        student=Student(studentID,None,None)
        self.__validStud.validare_studentID(student)
        self.__repoStud.delete(student)
        
    def update_student(self,studentID,nume_upd,grup_upd):
        #date de intrare:
            #studentID-id-ul dupa care se va cauta studentul care va fi modificat
            #nume_upd-numele care va inlocui cel din obiectul studentului gasit
            #grup_upd-grupul care va inlocui cel din obiectul studentului gasit
        student=Student(studentID,nume_upd,grup_upd)
        self.__validStud.validare_parametrii_student(student)
        self.__repoStud.update_student(student)
        
    def all_studenti(self):
        return self.__repoStud.get_all_studenti()
    
    
    
    def random_studenti_recursiv(self,nr):
        if nr==0:
            return 
        studentID=random.randint(1,9999)
        #string random
        letters = string.ascii_lowercase
        strlen=random.randint(4,8)
        nume=''.join(random.choice(letters) for i in range(strlen))
        grup=random.randint(200,299)
        student=Student(studentID,nume,grup)
        try:
            self.__repoStud.adaugaStudent(student)
            
            self.random_studenti_recursiv(nr-1)
        except:
            self.random_studenti_recursiv(nr)
            
            
    def random_studenti(self,nr):
        #date de intrare: nr-u numar intreg care indica cati studenti se vor adauga random
        while nr:
            studentID=random.randint(1,9999)
            #string random
            letters = string.ascii_lowercase
            strlen=random.randint(4,8)
            nume=''.join(random.choice(letters) for i in range(strlen))
            #
            grup=random.randint(200,299)
            student=Student(studentID,nume,grup)
            try:
                self.__repoStud.adaugaStudent(student)
            except:
                continue
            nr-=1
  
    
class SrvPLab:
    def __init__(self,repoPLab, validPLab):
        self.__repoPLab=repoPLab
        self.__validPLab=validPLab
    
    def adauga_problema(self,nrlab_pb,descriere,deadline):
        #date de intrare:
            #nrlab_pb=string format din numarLaborator_numarProblema
            #descriere=string
            #deadline=string format din nrZi_nrLuna
        pbLab=PbLab(nrlab_pb,descriere,deadline)
        self.__validPLab.validare_pbLab(pbLab)
        self.__repoPLab.adaugaProblema(pbLab)
    
    def afiseaza_problema(self,nrlab_pb):
        #date de intrare:
            #nrlab_pb=numarul problemei, dupa acesta se va face cautarea
        pbLab=PbLab(nrlab_pb,None,None)
        self.__validPLab.validare_nrlab_pb(nrlab_pb)
        return self.__repoPLab.cautare_nrlab_pb(pbLab)
    
    def sterge_problema(self,nrlab_pb):
        #date de intrare:
            #nrlab_pb=numarul problemei, dupa care se va face stergerea
        pbLab=PbLab(nrlab_pb,None,None)
        self.__validPLab.validare_nrlab_pb(nrlab_pb)
        self.__repoPLab.stergere_problema(pbLab)
    
    def modificare_problema(self,nrlab_pb,descriere,deadline):
        #date de intrare:
            #nrlab_pb=numarul problemei, dupa care se va face modificarea
        pbLab=PbLab(nrlab_pb,descriere,deadline)
        self.__validPLab.validare_pbLab(pbLab)
        self.__repoPLab.modific_problema(pbLab)
        
    def all_probleme(self):
        return self.__repoPLab.get_all_probleme()



class SrvNote:
    
    def __init__(self,repoStud,repoPLab,repoNote,validNote):
        self.__repoStud=repoStud
        self.__repoPLab=repoPLab
        self.__repoNote=repoNote
        self.__validNote=validNote
        
    def adauga_nota(self,punctaj,studentID,nrlab_pb):
        self.__validNote.validare_nota(punctaj)
        self.__validNote.validare_punctaj(punctaj)
        student=Student(studentID,None,None)
        pbLab=PbLab(nrlab_pb,None,None)
        if not self.__repoStud.cautareStudent(student)==student:
            raise RepoError("studentul caruia vreti sa-i atribuiti nota nu exista!\n")
        if not self.__repoPLab.cautare_nrlab_pb(pbLab)==pbLab:
            raise RepoError("studentul caruia vreti sa-i atribuiti nota nu exista!\n")
        nota=Nota(punctaj,studentID,nrlab_pb)
        self.__repoNote.adauga_nota(nota)
        
    
    def media_fiecare_grupa(self):
        i=200
        s=""
        while i<300:
            ct=0
            suma=0
            for x in self.__repoNote.get_all_note(): 
                student=Student(x.get_studentID(),None,None)
                if self.__repoStud.cautareStudent(student).get_grup()==str(i):
                    ct+=1
                    suma+=int(x.get_punctaj())
            if ct!=0:
                s+="Media grupei "+str(i)+" este: "+str(suma/ct)+"\n"
            i+=1
        return s
            
    def print_all_note(self):
        return self.__repoNote.get_all_note()
    
    
    def sortare_dupa_nume(self):
        #functia preia toate elementele din lista de entitati de tip nota si le sorteaza in functie de nume 
        lista=self.__repoNote.get_all_note()
        len_lista=len(lista)
        for i in range(len_lista):
            for j in range(0,len_lista-i-1):
                student_j=Student(lista[j].get_studentID(),None,None)
                student_jplus1=Student(lista[j+1].get_studentID(),None,None)#am nevoie de aceste obiecte pentru a cauta studentii cu aceste id-uri
                if self.__repoStud.cautareStudent(student_j).get_nume()>self.__repoStud.cautareStudent(student_jplus1).get_nume(): #de la studentii gasiti dupa id-ul cautat am nevoie de nume
                    aux=lista[j]
                    lista[j]=lista[j+1]
                    lista[j+1]=aux #switch
        s=""
        for i in range(len_lista):
            studentID=lista[i].get_studentID()
            student=Student(studentID,None,None)
            nume=self.__repoStud.cautareStudent(student).get_nume()
            nota=lista[i].get_punctaj()
            s+=str(i+1)+". Studentul cu numele "+nume+" si ID-ul "+str(studentID)+" are punctajul notei de: "+str(nota)+"\n"
        
        return s 
    
    def sortare_dupa_nota(self):
        #functia preia toate elementele din lista de entitati de tip nota si le sorteaza in functie de punctaj
        lista=self.__repoNote.get_all_note()
        len_lista=len(lista)
        for i in range(len_lista):
            for j in range(0,len_lista-i-1):
                if lista[j].get_punctaj()>lista[j+1].get_punctaj():
                    aux=lista[j]
                    lista[j]=lista[j+1]
                    lista[j+1]=aux #switch
        s=""
        for i in range(len_lista):
            studentID=lista[i].get_studentID()
            student=Student(studentID,None,None)
            nume=self.__repoStud.cautareStudent(student).get_nume()
            nota=lista[i].get_punctaj()
            s+=str(i+1)+". Studentul cu numele "+nume+" si ID-ul "+str(studentID)+" are punctajul notei de: "+str(nota)+"\n"
        return s
    
    def studenti_restanti(self):
    #functia transmite toti studentii din lista de entitati de tip nota care au punctajul notei mai mic decat 50
        lista=self.__repoNote.get_all_note()
        l_id_verificat=[]
        s=""
        for i in range(len(lista)):
            ct=1
            media=0
            for j in range(i,len(lista)):
                if lista[j].get_studentID() not in l_id_verificat and lista[i].get_studentID()==lista[j].get_studentID():
                    l_id_verificat.append(lista[j].get_studentID())
                    ct+=1
                    media+=int(lista[j].get_punctaj())
                
            media+=int(lista[i].get_punctaj())
            media=media//ct
            if media<50:
                student=Student(lista[i].get_studentID(),None,None)
                s+=str(self.__repoStud.cautareStudent(student).get_nume())+"cu media notelor "+str(media)
        return s
        
    #pentru laboratorul 12-sortari(insertion sort, comb sort)
    def cmp(self,x,y,reverse):
        if x>y and reverse:
            return 1
        if x==y and reverse:
            return 0
        if x<y and reverse:
            return -1
    #pentru cazul in care se vrea sortre descrescatoare
        if x>y and not reverse:
            return -1
        if x==y and not reverse:
            return 0
        if x<y and not reverse:
            return 1
      
    def insertion_sort(self,lista,*, key=lambda x:x,reverse,cmp):
        for i in range(1, len(lista)): 
            x = lista[i]
            j = i-1
            while j >= 0 and cmp(key(x),key(lista[j]),reverse)>=0: 
                lista[j + 1] = lista[j] 
                j -= 1
            lista[j + 1] = x
    
    #comb sort
    def GetNextGap(self,gap):
        gap=(gap*10)//13
        
        if gap<1:
            return 1
        return gap
    
    def combSort(self,lista,*,key= lambda x:x,reverse,cmp):   
        n=len(lista)
        gap=n
        swapped=True
        
        while gap!=1 or swapped==True:
            gap=self.GetNextGap(gap)
            swapped=False
            
            for i in range(0,n-gap):
                if cmp(key(lista[i]),key(lista[i+gap]),reverse)==1:
                    lista[i], lista[i+gap]=lista[i+gap], lista[i]    
                    swapped=True
        