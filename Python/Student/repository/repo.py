from exceptii.exceptie import RepoError
class RepoStud:
    def __init__(self):
        self._entitati_student=[]
    
    def adaugaStudent(self, x):
        #date de intrare: x-un obiect de tip Student
        #date de iesire: lista de entitati_student
        if x in self._entitati_student:
            raise RepoError("id student existent!\n")
        self._entitati_student.append(x)
    
    def cautareStudent(self, x):
        #date de intrare: un obiect de tip Student
        #date de iesire: un obiect de tip Student, obiectul gasit cu id-ul dat
        sem=0
        for i in range(len(self._entitati_student)):
            if self._entitati_student[i]==x:
                sem=1               
                salvez_i=i #daca gasesc id-ul cautat in repo, retin indicele la care l-am gasit in lista
        
        if sem==0:
            raise RepoError("id student cautat inexistent!\n")
        else:
            return self._entitati_student[salvez_i]
    
    def delete(self,student):
        #date de intrare: student- obiect al clasei Student
        #functia va seterge din lista de entitati obiectrul student
        sem=0
        for i in range(len(self._entitati_student)):
            if self._entitati_student[i].get_studentID()==student.get_studentID():
                sem=1               
                salvez_i=i
        if sem==0:       
            raise RepoError("id student cautat inexistent!\n")
        else:
            self._entitati_student.remove(self._entitati_student[salvez_i])  
        
    def update_student(self,student):
        #date de intrare: student- obiect al clasei Student
        #functia va updata un student gasit dupa id, cu noile valori din student
        sem=0
        for i in range(len(self._entitati_student)):
            if self._entitati_student[i].get_studentID()==student.get_studentID():
                sem=1               
                salvez_i=i
        if sem==0:       
            raise RepoError("id student cautat inexistent!\n")
        else:
            self._entitati_student[salvez_i].set_nume(student.get_nume())
            self._entitati_student[salvez_i].set_grup(student.get_grup())
                
    def len_entitati_student(self):
        return len(self._entitati_student)
          
    def get_all_studenti(self):
        return self._entitati_student[:]


class RepoPLab:
    def __init__(self):
        self._entitati_probleme=[]

    def adaugaProblema(self, pbLab):
        #date de intrare: pbLab- obiect de tipul PbLab
        #functia va adauga un obect in lista de entitati, daca acesta nu exista deja
        if pbLab in self._entitati_probleme:
            raise RepoError("problma existenta!\n")
        self._entitati_probleme.append(pbLab)
        
    def cautare_nrlab_pb(self,pbLab):
        #date de intrare: pbLab-obiect de tip PbLab
        #voi cauta in functie de nrlab_pb, parametrul lui pbLab, o entitate
        sem=0
        for i in range(len(self._entitati_probleme)):
            if self._entitati_probleme[i].get_nrlab_pb()==pbLab.get_nrlab_pb():
                salvez_i=i
                sem=1
        if sem==0:
            raise RepoError("problema cautata nu exista!\n")
        else:
            return self._entitati_probleme[salvez_i]
    
    def stergere_problema(self,pbLab):
        #date de intrare:pbLab-obiect de tip PbLab
        #voi sterge in functie de nrlab_pb, parametrul lui pbLab
        sem=0
        for i in range(len(self._entitati_probleme)):
            if self._entitati_probleme[i].get_nrlab_pb()==pbLab.get_nrlab_pb():
                salvez_i=i
                sem=1
        if sem==0:
            raise RepoError("problema pe care vreti sa o stergeti nu exista!\n")  
        else:
            self._entitati_probleme.remove(self._entitati_probleme[salvez_i])      
    
    def modific_problema(self,pbLab):
        #date de intrare:pbLab-obiect de tip PbLab
        #voi modifica in functie de nrlab_pb, parametrul lui pbLab
        sem=0
        for i in range(len(self._entitati_probleme)):
            if self._entitati_probleme[i].get_nrlab_pb()==pbLab.get_nrlab_pb():
                salvez_i=i
                sem=1
        if sem==0:
            raise RepoError("problema pe care vreti sa o stergeti nu exista!\n")
        else:
            self._entitati_probleme[salvez_i].set_descriere(pbLab.get_descriere())
            self._entitati_probleme[salvez_i].set_deadline(pbLab.get_deadline())
    def get_all_probleme(self):
        return self._entitati_probleme[:]   



class RepoNote:
    
    def __init__(self):
        self._entitati_note=[]
        
    def adauga_nota(self, nota):
        if nota in self._entitati_note:
            raise RepoError("nota deja existenta!\n")
        self._entitati_note.append(nota)
    
    def get_all_note(self):
        return self._entitati_note[:]

class RepoStudFile(RepoStud):
    
    def __init__(self,nume_fisier,citeste_student_fisier,tipareste_student_fisier):
        RepoStud.__init__(self)
        self.__nume_fisier=nume_fisier
        self.__citeste_student_fisier=citeste_student_fisier
        self.__tipareste_student_fisier=tipareste_student_fisier
    
    def __citeste_tot_fisierul(self):
        #aceasta functie citeste din fisier liniile si le transforma in entitati de tip student pe care le adauga la lista de studenti
        self._entitati_student=[]
        with open(self.__nume_fisier,"r") as f:
            linii=f.readlines()
            for linie in linii:
                student=self.__citeste_student_fisier(linie)
                RepoStud.adaugaStudent(self,student)
    
    def __tipareste_tot_in_fisier(self):
        #aceasta functie tipareste toata lista de studetni in fisier 
        with open(self.__nume_fisier,"w") as f:
            for stud in self._entitati_student:
                linie=self.__tipareste_student_fisier(stud)
                f.write(linie+"\n")         
                
    def adaugaStudent(self, x):
        self.__citeste_tot_fisierul()
        RepoStud.adaugaStudent(self, x)
        self.__tipareste_tot_in_fisier()
        
    def cautareStudent(self, x):
        self.__citeste_tot_fisierul()
        return RepoStud.cautareStudent(self, x)
    
    def delete(self, student):
        self.__citeste_tot_fisierul()
        RepoStud.delete(self, student)
        self.__tipareste_tot_in_fisier()
    
    def len_entitati_student(self):
        self.__citeste_tot_fisierul()
        return RepoStud.len_entitati_student(self)
    
    def get_all_studenti(self):
        self.__citeste_tot_fisierul()
        return RepoStud.get_all_studenti(self)
    
class RepoPLabFile(RepoPLab):
    
    def __init__(self,nume_fisier,citeste_problema_fisier,tipareste_problema_fisier):
        RepoPLab.__init__(self)
        self.__nume_fisier=nume_fisier
        self.__citeste_problema_fisier=citeste_problema_fisier
        self.__tipareste_problema_fisier=tipareste_problema_fisier
        
    def __citeste_tot_fisierul(self):
        #aceasta functie citeste din fisier liniile si le transforma in entitati de tip PLab pe care le adauga la lista de probleme
        self._entitati_probleme=[]
        with open(self.__nume_fisier,"r") as f:
            linii=f.readlines()
            for linie in linii:
                pbLab=self.__citeste_problema_fisier(linie)
                RepoPLab.adaugaProblema(self, pbLab)
                
    def __tipareste_tot_in_fisier(self):
        #aceasta functie tipareste toata lista de probleme in fisier
        with open(self.__nume_fisier,"w") as f:
            for pbLab in self._entitati_probleme:
                linie=self.__tipareste_problema_fisier(pbLab)
                f.write(linie+"\n")
                
    def adaugaProblema(self, pbLab):
        self.__citeste_tot_fisierul()
        RepoPLab.adaugaProblema(self, pbLab)
        self.__tipareste_tot_in_fisier()
        
    def cautare_nrlab_pb(self, pbLab):
        self.__citeste_tot_fisierul()
        return RepoPLab.cautare_nrlab_pb(self, pbLab)
    
    def stergere_problema(self, pbLab):
        self.__citeste_tot_fisierul()
        RepoPLab.stergere_problema(self, pbLab)
        self.__tipareste_tot_in_fisier()
    
    def modific_problema(self, pbLab):
        self.__citeste_tot_fisierul()
        RepoPLab.modific_problema(self, pbLab)
        self.__tipareste_tot_in_fisier()
        
    def get_all_probleme(self):
        self.__citeste_tot_fisierul()
        return RepoPLab.get_all_probleme(self)
    

class RepoNoteFile(RepoNote):
    
    def __init__(self,nume_fisier,citeste_nota_fisier,tipareste_nota_fisier):
        RepoNote.__init__(self)
        self.__nume_fisier=nume_fisier
        self.__citeste_nota_fisier=citeste_nota_fisier
        self.__tipareste_nota_fisier=tipareste_nota_fisier
    
    def __citeste_tot_fisierul(self):
        #aceasta functie citeste din fisier liniile si le transforma in entitati de tip Nota pe care le adauga la lista de note
        self._entitati_note=[]
        with open(self.__nume_fisier,"r") as f:
            linii=f.readlines()
            for linie in linii:
                nota=self.__citeste_nota_fisier(linie)
                RepoNote.adauga_nota(self, nota)
    
    def __tipareste_tot_in_fisier(self):
        #aceasta functie tipareste toata lista de note in fisier
        with open(self.__nume_fisier,"w") as f:
            for nota in self._entitati_note:
                linie=self.__tipareste_nota_fisier(nota)
                f.write(linie+"\n")

    def adauga_nota(self, nota):
        self.__citeste_tot_fisierul()
        RepoNote.adauga_nota(self, nota)
        self.__tipareste_tot_in_fisier()

    def get_all_note(self):
        self.__citeste_tot_fisierul()
        return RepoNote.get_all_note(self)