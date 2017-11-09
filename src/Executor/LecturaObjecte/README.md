Lèxic
=====
Aquí explicarem com ha de ser el codi objecte per a que sigui interpretat.

Notació
-------
- () i [] són per fer bucles i explicacions del codi.
- # serveix per a fer comentaris.
- Només llegeix caràcters diferents ' \t\n'

v00
---
Visió general.

- -v[ariable global]:\d+\n
- (definir variables, on \d+ és el total a reservar)
- -f[uncions descriptors]:\d+\n
- [(bucle per funció)
- \<F[unció concreta]:\d+\n	# On \d+ és quina funció vulguis definir.
-  -a[rguments]:\d+\n
-  (definir variables)
-  -v[ariables locals]:\d+\n
-  (definir variables)
-  -c[odi]:\d+\n		# On \d+ és el nombre de frases del codi.
-  (definir codi)
- ]

Definir variables.

- \d+ \d+ \d+	# id de la variable, tipus de la variable, valor.
- \d+ \d+ '%c'	# id de la variable, tipus de la variable, caracter.

Definir codi.

- [(bucle per frase)
- -f[rased]:\d+\n	# Nombre de paraules per aquesta frase.
-  # on{Codi, variables, funció}, relatiu, adicionals.
-  \d+ \d+ [valor]	# Exemple de codi
-  \d+ \d+\n		# Exemple de variables
-  \d+ \d+ \d+		# Exemple de funció, on l'últim és el nombre d'arguments.
- ]
