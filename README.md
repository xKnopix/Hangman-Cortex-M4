# Hangman

1. [Spielablauf](#Spielablauf)
2. [GitHub](#GitHub)

## Spielablauf

1. [Enter] drücken um zu starten
2. Fenstergröße anpassen (Angaben im Spiel)
3. Wort eingeben
    - Hierbei sind folgende Punkte zu beachten:
        - Wortlänge darf maximal 20 Buchstaben lang sein
        - Es können nur Buchstaben eingegeben werden
        - Es können keine Umlaute eingegeben werden
        - Groß- und Kleinschreibung ist irrelevant, wird jedoch mit angezeigt
4. Wort bestätigen
5. Wort kann erraten werden
    - Hierbei sind folgende Punkte zu beachten:
        - Nach ca. 15 Sekunden läuft ein Timer ab. Wenn dies der Fall ist, zählt die abgelaufene Zeit als Falscheingabe und Versuch.
        - Bei Falscheingabe baut sich der Hangman auf. Beim 9. Fehler hat man verloren.
        - Bei richtiger Eingabe, wird das Wort mit restlich fehlenden Buchstaben angezeigt.
        - Wenn ein Buchstabe öfters vorkommt, werden alle Buchstaben bei Eingabe aufgedeckt.
        - Bereits erratene Buchstaben zählen ebenfalls als Fehler.
6. Wenn das Spiel gewonnen oder verloren wurde, wird eine Endstatistik angezeigt. Diese verschwindet automatisch nach cs. 15 Sekunden oder bei eingabe von [Enter]. Es kann hier ebenfalls das Spiel mit [q] beendet werden.


## GitHub

Für das Projekt wurde GitHub zur Versionsverwaltung genutzt.
</br>
Über folgenden Link kann auf das Repository gehen: https://github.com/xKnopix/Hangman-Cortex-M4
