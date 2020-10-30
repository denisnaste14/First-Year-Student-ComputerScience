from testare.test import Teste 
from repository.repo import RepoStudFile,RepoPLabFile,RepoNoteFile
from services.srv import SrvStud, SrvPLab, SrvNote
from validator.validari import ValidStud, ValidPLab, ValidNote
from interface.console import Console
from domain.entitati import Student, PbLab, Nota
test=Teste()
repoStud=RepoStudFile("Studenti.txt",Student.citeste_student_fisier,Student.tipareste_student_fisier)
repoPLab=RepoPLabFile("Probleme.txt",PbLab.citeste_problema_fisier,PbLab.tipareste_problema_fisier)
repoNote=RepoNoteFile("Note.txt",Nota.citeste_nota_fisier,Nota.tipareste_nota_fisier)
validStud=ValidStud()
validPLab=ValidPLab()
validNote=ValidNote()
srvStud=SrvStud(repoStud,validStud)
srvPLab=SrvPLab(repoPLab,validPLab)
srvNote=SrvNote(repoStud,repoPLab,repoNote,validNote)
ui=Console(srvStud,srvPLab,srvNote)
ui.run()
