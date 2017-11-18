# Algoritme principal
Farem anar el _Shuting Yard Algortim_. Aquest simplement canviarà l'ordre de les paraules.
No té poder sobre les frases!

# Responsabilitats
- Comptar el nombre d'arguments de cada element.
- Comptar la correcta relació de parèntesis. (Té una pila i comprova que tot encaixa)
- Vull fer responsable dels salts lògics __for while if__.

## Salts lògics
Quan llegiex un '{', reserva memòria a una pila, on indica on està el seu 'pare'.
O farà amb un punter cap al mateix.

D'aquesta forma, un cop que llegeixi '}', podrem veure on està el pare i acte seguit saber de quant és el salt lògic.

# Memòria que necessita
- Enumerador
  - Valor
  - Funció
  - Obert
  - Tancat
  - Operador associatiu per la dreta
  - Operador associatiu per l'esquerra
- Presedència
