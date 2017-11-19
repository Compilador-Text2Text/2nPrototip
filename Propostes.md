# Lèxic
## No vull fer anar whiles.
Amb fors, queda més curt i simple el codi. Sent el codi molt més coherent i
lògic.
## Errors
### Trobo que són poc descriptius.
Entre altres, estaria bé que donessin molta més informació de quin estat ha
petat.
- Quina funció (1era, 2ona, nom si és té)
- Quina frase (1, 2, …)
- Quina paraula.
- Quina variable (1, 2, nom si en té)
- Quina línia ha petat (Necessito un comptador de '\n'.

### Necessitaria variables globals.
- Saber en quina funció vaig.	(i\_fu)	i de funció.
- Saber en quina frase vaig.	(i\_fr) i de frase.
- Saber en quina paraula vaig.	(i\_p)	i de paraula.
- Saber en quina variable vaig. (i\_v)	i de variable.
- Saber en quina línia vaig.	(c\_l)	comptador de línia.

### Més descriptius.
Al cridar una funció, aquesta necessitarà certa informació.
- variables
  - Saber si és argument o local.
  - Saber si és de la funció 2 o de cap (-1).
- frase
  - Saber de quina funció prové.
- paraula
  - Saber de quina funció prové.
  - Saber de quina frase ve.


# GNUmakefile
Usar un vocabulari més fàcil d'entendre.
- Nom dels fitxers \*\_[CHO]\_
- Nom de les dependències només d'aquell document \*\_[CH]\_D
- Només té sentit generar variables noves pels objectes.
- Tots els includes, se faran amb l'ajuda de les variables \*\_D
Així obtindrem el GNUmakefile simple:
```
$(FITXER_O_): $(FITXER_C_D)
	gcc $(FITXER_C_) $(GLIBS) -o $(FITXER_O_)
```
Aquest model per a tots els objectes!

# main.c
Estaria bé que al tenir tantes condicions, fer com si fos un switch gran.
Subdividir-ho amb funcions per tal de facilitar la lectura del document.
