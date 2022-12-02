Le point de départ: 
https://gieseanw.wordpress.com/2012/10/21/a-comprehensive-step-by-step-tutorial-to-computing-dubins-paths/
Andy Gease a le mérite inestimable de proposer une méthode de calcul.

https://fr.wikipedia.org/wiki/Odom%C3%A9trie
Sybillin, mais essentiel. Il faut le lire.

Pour une bonne compréhension des atmega :
https://fr.wikiversity.org/wiki/Micro_contr%C3%B4leurs_AVR
de Jean Michel Gérard, GEII de Troyes 

courbesDubins
-------------
courbesDubins calcule seulement la courbe depuis la position de départ jusqu'à la position d'arrivée.

Le rôle de courbesDubins est d'illustrer la construction des courbes, et de valider les calculs. Il n'y a pas de version .ino

Pour faciliter la mise au point, le développement a été écrit (en C++) avec Qt(4). Il y a un exécutable pour les linuxiens (installer Linux et ses applications est facile, même pour quelqu'un ayant une culture informatique aussi médiocre que la mienne, et c'est gratuit)
Si les classes de calcul et celles d'affichage sont distinctes, c'est que l'objectif est de calculer la trajectoire d'un robot à partir des courbes de Dubins avec un ATMEGA. De cette façon, la transition est simplifiée. Les classes d'affichage ne sont là que pour contrôler la bonne exécution des calculs.

L'interface est minimaliste. Le menu ne sert à rien, il est bien plus pratique de passer par le clavier :
- et + => zoom.
1, 2, 3, 4, 5, et 6  affichent les courbes RSR, RSL, LSR, LSL, RLR ou LRL.
0 choisit et affiche la courbe la plus courte
les chiffres 0..7 peuvent être remplacés par un click dans la toolbar.

les touches :
A Active/Désactive l'affichage de la construction

pour déplacer les positions :
shift est la position départ de la courbe
ctrl est la position à l'arrivée de la courbe
Combiner ces touches avec les flèches déplace, ou tourne, la position choisie. Une courbe invalide ne s'affiche pas.

La barre de status affiche la distance en pixels de la courbe choisie.

La phase de départ, est en bleu, la phase de tangence en vert, la phase d'arrivée en rouge. L'angle important pour la construction
de la courbe est l'angle délimité en noir au centre du cercle de courbure du départ.

tpsCalcTheorique
----------------
Donne une idée des temps de calcul
En général, le setup prend environ 10ms pour calculer la courbe la plus courte, la fonction calcTheorique demande environ 350µs avec des pointes à 600 µs. (Arduino nano). Démonstration dans tpsCalcTheorique.ino (qui s'arrête assez vite, pourquoi ?)

robotTheorique
--------------
robotTheorique a une version Qt et AVR, qui tourne sur un atmega328p.

robotTheorique fait parcourir la courbe par un robot ayant simplement deux roues. Il y a 2 variables supplémentaires dans la toolbar, vitesse et rayon. robotThéorique calcule la vitesse de chaque roue en fonction de la courbe choisie, du diamètre des roues, de l'entraxe, de la vitesse et du rayon de courbure, puis en déduit la PWM théorique applicable à chaque roue, et le nombre de tics que les encodeurs de chaque roue devraient mesurer.
La touche <T>héorique lance la simulation, la touche <Espace> arrête/ redémarre. Le robot calcule sa position théorique toutes les secondes, en utilisant la méthode inverse du pdf "Odométrie". La méthode choisie tente d'être aussi proche que possible de celle des microcontrôleurs ATMEGA. 
Dans la version Qt, la position théorique est affichée dans une fenêtre de calculs.

Dans l'IDE Arduino, la position théorique est affichée dans la fenêtre du port série. Son dossier "courbes" doit être glissé et déposé (en le copiant) dans le dossier "libraries" de l'IDE Arduino (pour moi, /opt/arduino-1.8.19/libraries). 
Dans robotTheorique.ino, le timer ne fait pas de calcul dans son ISR, mais les délègue à la boucle loop grâce à 2 variables bool : calcTheorique et stopRobot. La lenteur de l'affichage suffit à en démontrer la raison, la boucle loop affiche pendant que le timer continue de compter.
timer1.h règle le TCNT1 en mode CTC, et implémente l'ISR(TIMER1_COMPA_vect)
pwm.h règle les timers TCNT0 et TCNT2 en mode fast PWM.
robotTheorique.ino endosse le rôle de mainwindow.cpp, en ce qui concerne le setup et le lancement des timers.















 

