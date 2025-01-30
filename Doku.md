## Ideen
Die Frage die sich mir als erstes stellt, ist welche Features für das Spiel wichtig sind, bzw. welche Features ich gerne einbauen würde. Diese sind:

- Manuelles hinzufügen und entfernen von Feldern
- Das Spiel im Zyklus pausieren und modifizieren
- Das Spiel jederzeit beenden

## Features
Die nächste Frage ist natürlich was brauche ich und wie plane ich diese Features zu implementieren:

- Die Möglichkeit das Feld darzustellen.

- Key Inputs verarbeiten.
	-> hier habe ich im Endeffekt viel rumprobiert und mich zwischen SDL2 und ncurses für letzteres entschieden.

- Wie möchte ich das Feld Codeseitig verarbeiten?
	-> ich habe es zuerst mit einem Array von "structs" probiert, in dem nur die aktiven Zellen gespeichert, hat beim verarbeiten von toten Zellen, leider zu Problemen geführt
	-> weshalb die Entscheidung dann doch auf ein 2D Array gefallen ist um das Feld darzustellen.

- Ich brauche einen GameLoop, in dem ich die einzelnen Zellen durchgehe und checke wie viele Nachbarn diese jeweils haben

- Danach muss ich das neue Feld bzw. die nächste Generation anhand von dem Ergebnis definieren und das Feld überschreiben.
	-> Als ich angefangen habe die Main Funktion zu schreiben mit den Key Inputs, kam mit die Idee Main und Game Loop zu trennen, da so das Pausen feature zumindest wie ich mir das
		 vorgestellt habe einfacher einzubauen ist. Hat mich am Ende doch recht viel Zeit gekostet aber funktioniert soweit.
	-> Während ich den Game Loop dann gecoded habe ist mir aufgefallen, dass es ziemlich nervig ist, dass das Game nicht abbricht, wenn sich am Pattern nichts mehr verändert, also
	   habe ich eine flag in den loop eingebaut, um zu checken, ob Änderungen zwischen den Generationen vorgenommen wurden

- Das Spiel pausieren
	-> Das Feature zum pausieren hat mir ein paar Probleme bereitet, wegen der Art wie die "getch()" funktion der ncurses Library arbeitet. Die Funktion wartet auf einen Input,
	was dazu führt, dass mein Game-Loop nicht durchläuft, bzw man sich durch die Iterations klicken muss
	-> Ich habe zwar ein ziemlich simplen Weg gefunden das Problem zu beheben, trotzdem recht lange gebraucht bis ich auf die Lösung kam. Man kann das blockieren togglen, das führt aber
	dazu, dass der Main-Loop nicht mehr funktioniert, wie erwartet. Ich habe die funktion einmal vor dem Game-Loop "ausgeschaltet" und danach wieder "eingeschaltet"

- Das beenden des Spiels
	-> implementieren, war quasi das selbe wie das pausieren, als ich wusste dass man das warten auf getch() verhindern kann, kein Problem ( einfach nur ein Key mit dem man 
	 das Programm beendet)

- Das Fenster resizen
	-> Ziel war ein Neues Board mit der maximalen Breite und Höhe des Terminals zu erstellen, wenn die Größe von diesem geändert wird. Die Felder (die die reinpassen zumindest), sollen
	dann vom alten Board in das neue Board kopiert werden, um auch während das Game läuft die Position der Zellen beizubehalten
	-> Es gab einen kurzen Moment des Erfolges, in dem ich das resizen einigermaßen funktioniert hat, zu dem Status bin ich leider kein zweites mal mehr gekommen
	-> Ich hatte an Ende Probleme mit dem Memory Management und habe es leider nicht bis zur Deadline geschafft das Feature einzubauen aber habe trotzdem was mitnehmen können

	statt das Board als "char**" zu definieren habe ich hier z.B. online den Ansatz gesehen ein "struct Board" mit den Werten width, height und Board. Ich denke mit diesem Ansatz 
	könnte man die gewünschte Funktionalität ein bisschen einfacher bzw. deutlich einfacher nachvollziehbar implementieren, so zumindest die Theorie.
