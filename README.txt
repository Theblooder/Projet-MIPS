Version 1.0

Permet de récupérer les instructions d'un fichier texte pour pouvoir les traduire en héxadécimal avant de les écrires dans un autre fichier texte

Le programme s'executer de la manière suivante :

./emul-mips <input_file>.txt <output_file>.txt


Adresse virutelle de 1000. Pas plus de 250 instructions sinon les data et instructions se touchent.

dossier tests pour les fichiers assembleurs et dossier hexified pour les fichiers .hex et .state (registres) OBLIGATOIRE


execution :

./emul-mips          -mode interactif

./emul-mips <input_file>.txt [<output_file>.txt] [-pas]         --pour le mode normale (avec option -pas) dans cette ordre

./emul-mips <input_file>.txt <output_file>.txt <outputRegister_file>.state          --pas de mode pas à pas ici