# README

# Informations indispensables

Dossier `tests` pour les fichiers assembleurs et dossier `output` pour les fichiers .hex et .state (registres). **Les dossiers doivent être présents pour un bon fonctionnement !**

Le programme s’execute de la manière suivante

- `./emul-mips`	(mode interactif)
- `./emul-mips <input_file>.txt [<output_file>.hex] [-pas]`	(mode pas à pas, dans cet ordre si tous les arguments sont mis)
- `./emul-mips <input_file>.txt	<output_file>.hex <outputRegister_file>.state`	(mode non interactif avec sortie registres)

Nous avons mis une adresse virtuelle statique de 1000. Ainsi il n’est pas possible de mettre plus de 250 instructions (sinon il peut y avoir des conflits dans la mémoire).

# Information complémentaire

Instruction BEQ et ses semblables:

`BEQ $2, $3, 3` compare les 2 registres et si égalité alors le programme sauteras **3** instructions.

Instruction J et ses semblables :

`J 24` sautera à l’adresse 24 de la mémoire (6 ème instruction)

Nous ne prenons pas en compte le **delay slot** ainsi l’instruction située juste après une instruction de saut ne sera pas exécuté avant de faire le saut.

Nous avons fourni 2 fichiers de tests

- Le premier contient toutes les instructions
- Le deuxième contient un petit programme en C mis en commentaire au début du fichier.

Les instructions fausses sont ignorées, mais une précision sur la nature de l’erreur est précisée dans le terminal.

Nous ne prenons pas en compte les étiquettes.