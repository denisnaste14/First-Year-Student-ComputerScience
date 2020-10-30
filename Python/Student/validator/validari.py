from exceptii.exceptie import ValidError

class ValidStud:
    def validare_parametrii_student(self,student):
        erori=""
        #studentID trebuie sa fie de tipul int
        try:
            student.get_studentID()==int(student.get_studentID())
        except: 
            erori+="Introduceti o valoare intreaga pentru ID-ul studentului!\n"
        #numele studentului trebuie sa fie string 
        try:
            student.get_nume()==str(student.get_nume())
        except:
            erori+="Introduceti un nume valid!\n"
        #grupa studentului trebuie sa fie o valoare intreaga
        try:
            student.get_grup()==int(student.get_grup())
        except: 
            erori+="Introduceti o valoare intreaga pentru grupul studentului!\n"  
        if(student.get_nume()==""):
            erori+="Introduceti un nume valid!\n"
        if(erori!=""):
            raise ValidError(erori)
        
    #validarea unui obiect student 
    def validare_student(self,student):
        erori=""
        if(int(student.get_studentID())<0):
            erori+="id student invalid!\n"
        if(student.get_nume()==""):
            erori+="nume student invalid!\n"
        if(int(student.get_grup())<200 or int(student.get_grup())>299):
            erori+="grup student invalid!\n"
        if(erori!=""):
            raise ValidError(erori)
    
    def validare_studentID(self,student):
        #studentID trebuie sa fie de tipul int
        try:
            student.get_studentID()==int(student.get_studentID())
        except: 
            raise ValidError("Introduceti o valoare intreaga pentru ID-ul studentului!\n")
        
class ValidPLab:
    #validarea unui obiect problema laborator
    def validare_pbLab(self,pbLab):
        erori=""
        nrlab_pb=pbLab.get_nrlab_pb()
        descriere=pbLab.get_descriere()
        deadline=pbLab.get_deadline()
        #verificare nrlab_pb
        valori_nrlab_pb=nrlab_pb.split("_")
        try:
            valori_nrlab_pb[0]==int(valori_nrlab_pb[0])
        except:
            erori+="introduceti un numar intreg pentru numarul laboraorului!\n"
        try:
            valori_nrlab_pb[1]==int(valori_nrlab_pb[1])
        except:
            erori+="introduceti un numar intreg pentru numarul problemei!\n"
        #verificare descriere
        if not descriere.isalpha():
            erori+="introduceti o descriere potrivita!\n"
        #verificare deadline
        valori_deadline=deadline.split(".")
        try:
            valori_deadline[0]==int(valori_deadline[0])
        except:
            erori+="introduceti un numar intrg pentru ziua deadline-ului!\n"
        valori_deadline[0]=int(valori_deadline[0])
        if valori_deadline[0]<1 or valori_deadline[0]>31:
            erori+="introduceti o zi valabila dintr-0 luna!\n"
        try:
            valori_deadline[1]==int(valori_deadline[1])
        except:
            erori+="introduceti un numar intreg pentru luna deadline-ului!\n"
        valori_deadline[1]=int(valori_deadline[1])
        if valori_deadline[1]<1 or valori_deadline[1]>12:
            erori+="introduceti o luna valabila!\n"
        if erori!="":
            raise ValidError(erori)
            
    def validare_nrlab_pb(self,nrlab_pb):
        #nrlab_pb trebuie sa fie de forma int_int
        erori=""
        valori_nrlab_pb=nrlab_pb.split("_")
        try:
            valori_nrlab_pb[0]==int(valori_nrlab_pb[0])
        except:
            erori+="introduceti un numar intreg pentru numarul laboraorului!\n"
        try:
            valori_nrlab_pb[1]==int(valori_nrlab_pb[1])
        except:
            erori+="introduceti un numar intreg pentru numarul problemei!\n"
        if erori!="":
            raise ValidError(erori)
            

class ValidNote(object):
    
    def validare_nota(self,punctaj):
        #punctaj trebuie sa fie float
        try:
            punctaj==float(punctaj)
        except:
            raise ValidError("ati introdus un punctaj invalid!\n")

    def validare_punctaj(self,punctaj):
        #punctajul trebuie sa fie intre 10 si 100
        if int(punctaj)<10 or int(punctaj)>99:
            raise ValidError("ati introdus un punctaj invalid!\n")
