// =====================================================================
//  passungstest.scad  --  Teil 1
//
//  Zweck: herausfinden, wie viel Spiel dein Drucker braucht, damit der
//  STS3215 saugend in einer Tasche sitzt.
//
//  Drei Taschen mit unterschiedlichem Spiel nebeneinander. Einmal
//  drucken, den Servo in allen dreien probieren. Die Tasche, in die er
//  ohne Werkzeug reingeht und in der er nicht wackelt, gewinnt.
//  Diesen Wert traegst du dann in sts3215.scad bei FIT ein -- ab da
//  passt jede Halterung, die wir daraus bauen.
//
//  Warum ueberhaupt Spiel noetig ist: ein 3D-Drucker legt heissen
//  Kunststoff ab. Beim Abkuehlen schrumpft er, und an Innenecken
//  quillt Material leicht nach innen. Eine Tasche, die im Modell exakt
//  45.23 mm hat, kommt real bei etwa 44.9 raus -- der Servo geht nicht
//  rein. Wie stark der Effekt ausfaellt, haengt an Duese, Material und
//  Temperatur und ist deshalb bei jedem Drucker anders. Man misst es
//  einmal aus, statt zu raten.
// =====================================================================

include <sts3215.scad>

SPIELE  = [0.15, 0.30, 0.45];   // getestete Werte, Spiel pro Seite in mm

WAND    = 3.2;    // Wandstaerke rund um jede Tasche
LABEL   = 9;      // Streifen an der Vorderseite fuer die Beschriftung
HOEHE   = 12;     // Bauteilhoehe; reicht zum Beurteilen und spart Zeit
SCHRIFT = 5;      // Schriftgroesse
GRAVUR  = 0.6;    // Gravurtiefe

// Breite einer Zelle und laufender Versatz
function zell_breite(i) = SERVO_L + 2*SPIELE[i] + 2*WAND;
function versatz(i)     = (i <= 0) ? 0 : versatz(i-1) + zell_breite(i-1);

// ---------------------------------------------------------------------
//  Eine Zelle: Rahmen mit durchgehender Tasche und Beschriftung
// ---------------------------------------------------------------------
module zelle(spiel) {
    tasche_l = SERVO_L + 2*spiel;
    tasche_w = SERVO_W + 2*spiel;
    aussen_l = tasche_l + 2*WAND;
    aussen_w = tasche_w + 2*WAND + LABEL;

    difference() {
        cube([aussen_l, aussen_w, HOEHE]);

        // Tasche geht durch: so kannst du den Servo wieder
        // rausdruecken, statt ihn rauszuhebeln
        translate([WAND, LABEL + WAND, -1])
            cube([tasche_l, tasche_w, HOEHE + 2]);

        // Wert in die Oberseite gravieren
        translate([aussen_l/2, LABEL/2, HOEHE - GRAVUR])
            linear_extrude(GRAVUR + 1)
                text(str(spiel), size = SCHRIFT,
                     halign = "center", valign = "center");
    }
}

for (i = [0 : len(SPIELE) - 1])
    translate([versatz(i), 0, 0])
        zelle(SPIELE[i]);
