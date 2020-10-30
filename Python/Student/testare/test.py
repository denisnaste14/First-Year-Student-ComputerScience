from repository.repo import RepoStud, RepoPLab, RepoNote
from validator.validari import ValidStud, ValidPLab, ValidNote
from domain.entitati import Student, PbLab, Nota
from exceptii.exceptie import RepoError
from services.srv import SrvStud,SrvNote
import unittest
class Teste(unittest.TestCase):
    
    #teste student
    def setUp(self):
        studentID=180
        nume="Andrei"
        grup=219
        student=Student(180,"Andrei",219)
        assert(student.get_studentID()==studentID)
        assert(student.get_nume()==nume)
        assert(student.get_grup()==grup)
        student.set_nume("Alexandru")
        student.set_grup(220)
        assert(student.get_nume()=="Alexandru")
        assert(student.get_grup()==220)
        student2=Student(180,"Mihai",280)
        assert(student==student2)
        self.__student=student
    
    def test_repo_student(self):
        self.__repoStud=RepoStud()
        assert(self.__repoStud.len_entitati_student()==0)
        self.__repoStud.adaugaStudent(self.__student)
        assert(self.__repoStud.len_entitati_student()==1)
        assert(self.__repoStud.get_all_studenti()==[self.__student])
        self.__id_student=Student(180,None,None)
        self.__stud_gasit=self.__repoStud.cautareStudent(self.__id_student)
        assert(self.__stud_gasit.get_nume()==self.__student.get_nume())
        assert(self.__stud_gasit.get_grup()==self.__student.get_grup())
        try:
            self.__repoStud.adaugaStudent(self.__student)
            assert(False)
        except RepoError as re:
            assert(str(re)=="id student existent!\n")
    def test_afiseaza_student(self):
        studentID=199
        nume="Denis"
        grup=215
        student=Student(studentID,nume,grup)
        validStud=ValidStud()
        repoStud=RepoStud()
        self.__srvStud=SrvStud(repoStud,validStud)
        self.__srvStud.adauga_student(studentID,nume,grup)
        assert(self.__srvStud.afiseaza_student(studentID)==student)
        self.__srvStud.sterge_student(studentID)
    def test_update_student(self):
        studentID=180
        nume="Denis"
        grup=215
        student=Student(studentID,nume,grup)
        self.__repoStud=RepoStud()
        self.__repoStud.adaugaStudent(student)
        nume="Andrei"
        grup=200
        student_up=Student(studentID,nume,grup)
        self.__repoStud.update_student(student_up)
        assert(student_up.get_nume()==nume)
        assert(student_up.get_grup()==grup)
    #teste problema
    def test_creaza_problema(self):
        nrlab_pb="17_3"
        descriere="calculeaza"
        deadline="7.11"
        pbLab=PbLab(nrlab_pb,descriere,deadline)
        assert(pbLab.get_nrlab_pb()==nrlab_pb)
        assert(pbLab.get_descriere()==descriere)
        assert(pbLab.get_deadline()==deadline)
        pbLab.set_descriere("dhhfk")
        pbLab.set_deadline("18.19")
        assert(pbLab.get_descriere()=="dhhfk")
        assert(pbLab.get_deadline()=="18.19")
    
    def test_cautare_nrlab_pb(self):
        nrlab_pb="17_3"
        descriere="calculeaza"
        deadline="7.11"
        pbLab=PbLab(nrlab_pb,descriere,deadline)
        pbLab_cautare=PbLab(nrlab_pb,None,None)
        self.__repoPLab=RepoPLab()
        self.__repoPLab.adaugaProblema(pbLab)
        assert(self.__repoPLab.cautare_nrlab_pb(pbLab_cautare).get_nrlab_pb()=="17_3")
        assert(self.__repoPLab.cautare_nrlab_pb(pbLab_cautare).get_descriere()=="calculeaza")
        assert(self.__repoPLab.cautare_nrlab_pb(pbLab_cautare).get_deadline()=="7.11")
    
    def test_stergre_problema(self):
        nrlab_pb="17_3"
        descriere="calculeaza"
        deadline="7.11"
        pbLab=PbLab(nrlab_pb,descriere,deadline)
        pbLab_cautare=PbLab(nrlab_pb,None,None)
        self.__repoPLab=RepoPLab()
        self.__repoPLab.adaugaProblema(pbLab)
        assert(self.__repoPLab.cautare_nrlab_pb(pbLab).get_nrlab_pb()=="17_3")
        self.__repoPLab.stergere_problema(pbLab_cautare)
        try:
            self.__repoPLab.cautare_nrlab_pb(pbLab).get_nrlab_pb()=="17_3"
            assert(False)
        except RepoError as re:
            assert(str(re)=="problema cautata nu exista!\n")
            
    def test_modific_problema(self):
        nrlab_pb="17_3"
        descriere="calculeaza"
        deadline="7.11"
        pbLab=PbLab(nrlab_pb,descriere,deadline)
        pbLab_modificare=PbLab(nrlab_pb,"iiii","12.3")
        self.__repoPLab=RepoPLab()
        self.__repoPLab.adaugaProblema(pbLab)
        self.__repoPLab.modific_problema(pbLab_modificare)
        assert self.__repoPLab.cautare_nrlab_pb(pbLab).get_descriere()=="iiii"
        assert(self.__repoPLab.cautare_nrlab_pb(pbLab).get_deadline()=="12.3")
    
    def test_adauga_nota(self):
        punctaj=18.3
        studentID=129
        nrlab_pb="23_5"
        nota=Nota(punctaj,studentID,nrlab_pb)
        assert(nota.get_punctaj()==punctaj)
        assert(nota.get_studentID()==studentID)
        assert(nota.get_nrlab_pb()==nrlab_pb)
    
    def test_srv_sortare_dupa_nume(self):
        #creare repository de studenti
        studID=18
        nume="denis"
        grup=218
        student1=Student(studID,nume,grup)
        studID=19
        nume="darius"
        grup=239
        student2=Student(studID,nume,grup)
        studID=17
        nume="alex"
        grup=237
        student3=Student(studID,nume,grup)
        self.__repoStud=RepoStud()
        self.__repoStud.adaugaStudent(student1)
        self.__repoStud.adaugaStudent(student2)
        self.__repoStud.adaugaStudent(student3)
        #creare repository de probleme
        nrlab_pb="17_3"
        descriere="calculeaza"
        deadline="7.11"
        pbLab1=PbLab(nrlab_pb,descriere,deadline)
        nrlab_pb="11_5"
        descriere="calculeaza"
        deadline="7.12"
        pbLab2=PbLab(nrlab_pb,descriere,deadline)
        nrlab_pb="16_19"
        descriere="calculeaza"
        deadline="7.16"
        pbLab3=PbLab(nrlab_pb,descriere,deadline)
        self.__repoPLab=RepoPLab()
        self.__repoPLab.adaugaProblema(pbLab1)
        self.__repoPLab.adaugaProblema(pbLab2)
        self.__repoPLab.adaugaProblema(pbLab3)
        #creare repository de note
        self.__repoNote=RepoNote()
        self.__validNote=ValidNote()
        self.__srvNote=SrvNote(self.__repoStud,self.__repoPLab,self.__repoNote,self.__validNote)
        punctaj=92
        studID=18
        nrlab_pb="17_3"
        nota1=Nota(punctaj,studID,nrlab_pb)
        punctaj=85
        studID=19
        nrlab_pb="11_5"
        nota2=Nota(punctaj,studID,nrlab_pb)
        punctaj=99
        studID=17
        nrlab_pb="16_19"
        nota3=Nota(punctaj,studID,nrlab_pb)
        self.__repoNote.adauga_nota(nota1)
        self.__repoNote.adauga_nota(nota2)
        self.__repoNote.adauga_nota(nota3)
        
        assert(self.__srvNote.sortare_dupa_nume()=="1. Studentul cu numele alex si ID-ul 17 are punctajul notei de: 99\n2. Studentul cu numele darius si ID-ul 19 are punctajul notei de: 85\n3. Studentul cu numele denis si ID-ul 18 are punctajul notei de: 92\n")
        
        
    def test_srv_sortare_dupa_nota(self):
        #creare repository de studenti
        studID=18
        nume="denis"
        grup=218
        student1=Student(studID,nume,grup)
        studID=19
        nume="darius"
        grup=239
        student2=Student(studID,nume,grup)
        studID=17
        nume="alex"
        grup=237
        student3=Student(studID,nume,grup)
        self.__repoStud=RepoStud()
        self.__repoStud.adaugaStudent(student1)
        self.__repoStud.adaugaStudent(student2)
        self.__repoStud.adaugaStudent(student3)
        #creare repository de probleme
        nrlab_pb="17_3"
        descriere="calculeaza"
        deadline="7.11"
        pbLab1=PbLab(nrlab_pb,descriere,deadline)
        nrlab_pb="11_5"
        descriere="calculeaza"
        deadline="7.12"
        pbLab2=PbLab(nrlab_pb,descriere,deadline)
        nrlab_pb="16_19"
        descriere="calculeaza"
        deadline="7.16"
        pbLab3=PbLab(nrlab_pb,descriere,deadline)
        self.__repoPLab=RepoPLab()
        self.__repoPLab.adaugaProblema(pbLab1)
        self.__repoPLab.adaugaProblema(pbLab2)
        self.__repoPLab.adaugaProblema(pbLab3)
        #creare repository de note
        self.__repoNote=RepoNote()
        self.__validNote=ValidNote()
        self.__srvNote=SrvNote(self.__repoStud,self.__repoPLab,self.__repoNote,self.__validNote)
        punctaj=92
        studID=18
        nrlab_pb="17_3"
        nota1=Nota(punctaj,studID,nrlab_pb)
        punctaj=85
        studID=19
        nrlab_pb="11_5"
        nota2=Nota(punctaj,studID,nrlab_pb)
        punctaj=99
        studID=17
        nrlab_pb="16_19"
        nota3=Nota(punctaj,studID,nrlab_pb)
        self.__repoNote.adauga_nota(nota1)
        self.__repoNote.adauga_nota(nota2)
        self.__repoNote.adauga_nota(nota3)
    
        assert(self.__srvNote.sortare_dupa_nota()=="1. Studentul cu numele darius si ID-ul 19 are punctajul notei de: 85\n2. Studentul cu numele denis si ID-ul 18 are punctajul notei de: 92\n3. Studentul cu numele alex si ID-ul 17 are punctajul notei de: 99\n")
        
         
    '''def run_all_tests(self):
        self.__testeaza_creeaza_student()
        self.__testeaza_repo_student()
        self.__testeaza_afiseaza_student()
        self.__testeaza_update_student()
        
        self.__testeaza_creaza_problema()
        self.__testeaza_cautare_nrlab_pb()
        self.__testeaza_stergre_problema()
        self.__testeaza_modific_problema()
        
        self.__testeaza_adauga_nota()
        self.__testeaza_srv_sortare_dupa_nume()
        self.__testeaza_srv_sortare_dupa_nota()'''
        
if __name__=='__main__':
    unittest.main() 