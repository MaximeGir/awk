#
#  @author : Maxime Girard 
#  @CodePermanent : GIRM30058500
#

# variables

cc=gcc
options=-std=c99 -Wall
bin=filtre
objets=affichage.o fonctions.o filtre.o argument.o  

#cible : dépendance 

filtre: $(objets)
	$(cc) $(options) $(objets) -o $(bin)

argument.o: argument.h argument.c
	$(cc) $(options) -c argument.c -o argument.o

affichage.o: affichage.h affichage.c
	$(cc) $(options) -c affichage.c -o affichage.o

fonctions.o: fonctions.h fonctions.c
	$(cc) $(options) -c fonctions.c -o fonctions.o

filtre.o: filtre.c
	$(cc) $(options) -c filtre.c -o filtre.o

#cible : nettoyage
	
clean:
	\rm -f *.o
	\rm -f $(bin)
	\rm -f *~

#cible : archivage

archive:
	tar cvf filtre.tar *
	gzip filtre.tar
