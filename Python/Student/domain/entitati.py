class Student:
    
    def __init__(self,studentID,nume,grup):
        self.__studentID=studentID
        self.__nume=nume
        self.__grup=grup
        
    def get_studentID(self):
        return self.__studentID
    
    def get_nume(self):
        return self.__nume
    
    def get_grup(self):
        return self.__grup
    
    def set_nume(self, x):
        self.__nume=x 
    
    def set_grup(self, x):
        self.__grup=x 
    
    def __eq__(self,other):
        return int(self.__studentID)==int(other.__studentID)
    
    def __str__(self):
        return str(self.__studentID)+" "+self.__nume+" "+str(self.__grup)
    
    @staticmethod
    def citeste_student_fisier(linie_fisier):
        elem=linie_fisier.split("*")
        return Student(int(elem[0].strip()),elem[1].strip(),int(elem[2].strip()))
    
    @staticmethod
    def tipareste_student_fisier(student):
        return str(student.__studentID)+"*"+student.__nume+"*"+str(student.__grup)

class PbLab:
    def __init__(self,nrlab_pb,descriere,deadline):
        self.__nrlab_pb=nrlab_pb
        self.__descriere=descriere
        self.__deadline=deadline
    
    def get_nrlab_pb(self):
        return self.__nrlab_pb
    
    def get_descriere(self):
        return self.__descriere
    
    def get_deadline(self):
        return self.__deadline
    
    def set_descriere(self,text):
        self.__descriere=text
        
    def set_deadline(self,text):
        self.__deadline=text
        
    def __eq__(self,other):
        return self.__nrlab_pb==other.__nrlab_pb
    
    def __str__(self):
        return self.__nrlab_pb+" "+self.__descriere+" "+self.__deadline
    
    @staticmethod
    def citeste_problema_fisier(linie_fisier):
        elem=linie_fisier.split("*")
        return PbLab(elem[0].strip(),elem[1].strip(),elem[2].strip())
    
    @staticmethod
    def tipareste_problema_fisier(pbLab):
        return pbLab.get_nrlab_pb()+"*"+pbLab.get_descriere()+"*"+pbLab.get_deadline()

class Nota:
    
    def __init__(self,punctaj,studentID,nrlab_pb):
        self.__punctaj = punctaj
        self.__studentID = studentID
        self.__nrlab_pb=nrlab_pb
        
    def get_punctaj(self):
        return self.__punctaj
    
    def get_studentID(self):
        return self.__studentID
    
    def get_nrlab_pb(self):
        return self.__nrlab_pb
    
    def __eq__(self,other):
        return self.__punctaj==other.__punctaj or self.__studentID==other.__studentID or self.__nrlab_pb==other.__nrlab_pb
    
    def __str__(self):
        return str(self.__punctaj)+" "+str(self.__studentID)+" "+str(self.__nrlab_pb)
        
    @staticmethod
    def citeste_nota_fisier(linie_fisier):
        elem=linie_fisier.split("*")
        return Nota(elem[0].split()[0],elem[1].split()[0],elem[2].split()[0])
    
    @staticmethod 
    def tipareste_nota_fisier(nota):
        return str(nota.get_punctaj())+"*"+str(nota.get_studentID())+"*"+nota.get_nrlab_pb()
    
    