// =====================================================================
//  sts3215.scad  --  Bibliothek: Feetech STS3215 (Variante C018)
//
//  Diese Datei zeichnet von sich aus nichts. Sie stellt nur Konstanten
//  und Module bereit, die andere Dateien per include einbinden.
//  Genau wie ein Header in C++: er sagt, was es gibt, aber er ist kein
//  Programm.
//
//  Das Servo-Modell ist kein Detailabbild, sondern die Huellkontur.
//  Fuer eine Halterung ist genau das richtig -- die Tasche muss den
//  groessten Querschnitt aufnehmen, die Kuehlrippen interessieren nicht.
//
//  Koordinaten-Ursprung: Wellenachse, auf Hoehe der Gehaeuseflaeche
//    +Z = Richtung der Abtriebswelle
//    +X = Laengsrichtung, weg vom Getriebe (zum Motorende)
//    +Y = Breite
//
//  Der Ursprung liegt bewusst auf der Wellenachse: das ist die
//  Gelenkachse. Dreht sich ein Bauteil um dieses Gelenk, ist rotate()
//  um Z dann ohne Umrechnerei richtig.
//
//  Quelle: Feetech Datenblatt ST-3215-C018, Edition A/0, 2023-07-20
//          (liegt im Repo unter docs/FT01015.pdf)
// =====================================================================

$fn = 64;

// ---------------------------------------------------------------------
//  Gesichert: im Datenblatt bemasst
// ---------------------------------------------------------------------
SERVO_L      = 45.23;   // Laenge (Waveshare-Blatt: 45.22)
SERVO_W      = 24.73;   // Breite
SERVO_H      = 35.0;    // Hoehe des Gehaeuses
SHAFT_D      = 5.90;    // Verzahnung 25T, Aussendurchmesser
SHAFT_H      = 3.40;    // ragt ueber die Gehaeuseflaeche hinaus
IDLER_D      = 6.00;    // Gegenlager auf der Gegenseite
IDLER_H      = 4.10;    // ragt ueber die Gehaeuseflaeche hinaus

// Abgeleitet: das Datenblatt bemasst 12.5 von der Gehaeusemitte
// zur Wellenachse, nicht von einer Kante.
SHAFT_OFFSET = SERVO_L/2 - 12.5;   // = 10.115; Waveshare bemasst 10.11 direkt

// ---------------------------------------------------------------------
//  Servohorn (die Metallscheibe), Datenblatt Abschnitt 11
// ---------------------------------------------------------------------
HORN_D       = 19.95;   // Aussendurchmesser
HORN_BOHR    = 14.0;    // Lochkreisdurchmesser der 4 Loecher
HORN_LOCH_D  = 3.2;     // Lochdurchmesser, fuer M3
HORN_DICKE   = 2.1;     // Blechstaerke der flachen Variante

// ---------------------------------------------------------------------
//  Montageloecher, aus der Waveshare-Masszeichnung (ST3215-Gehaeuse)
//  Masskette der Draufsicht: 18.41 + 20.7 + 6.11 = 45.22
//  Die beiden inneren Linien laufen durch die Lochreihen.
// ---------------------------------------------------------------------
HOLE_DX       = 20.7;   // Lochabstand laengs (bemasst)
HOLE_DY       = 20.7;   // Lochabstand quer (aus der Zeichnung gemessen)
HOLE_D        = 2.5;    // Kernloch fuer PA3.0 selbstschneidend

// Mitte des Lochbilds, gemessen von der Wellenachse Richtung Motorende:
//   erste Lochreihe  18.41 - 10.11 = 8.30 hinter der Welle
//   Mitte            8.30 + 20.7/2 = 18.65
HOLE_CENTER_X = 18.41 - SHAFT_OFFSET + HOLE_DX/2;

// ---------------------------------------------------------------------
//  Spiel fuer Taschen -- mit passungstest.scad am A1 ermittelt
// ---------------------------------------------------------------------
FIT = 0.15;

// =====================================================================
//  Der Servo als Volumen
// =====================================================================
module sts3215(spiel = 0) {
    l = SERVO_L + 2*spiel;
    w = SERVO_W + 2*spiel;
    h = SERVO_H + 2*spiel;

    translate([-SHAFT_OFFSET - spiel, -w/2, -h])
        cube([l, w, h]);

    cylinder(d = SHAFT_D, h = SHAFT_H);              // Abtriebswelle

    translate([0, 0, -h - IDLER_H])                  // Gegenlager
        cylinder(d = IDLER_D, h = IDLER_H);
}

// =====================================================================
//  Die vier Montageloecher als Bohrwerkzeug (fuer difference())
// =====================================================================
module sts3215_loecher(tiefe = 8, d = HOLE_D) {
    for (sx = [-1, 1], sy = [-1, 1])
        translate([HOLE_CENTER_X + sx*HOLE_DX/2, sy*HOLE_DY/2, -tiefe/2])
            cylinder(d = d, h = tiefe);
}

// =====================================================================
//  Das Lochbild des Servohorns als Bohrwerkzeug
// =====================================================================
module horn_loecher(tiefe = 8, d = HORN_LOCH_D) {
    for (i = [0 : 3])
        rotate([0, 0, i * 90])
            translate([HORN_BOHR/2, 0, -tiefe/2])
                cylinder(d = d, h = tiefe);
}

// ---------------------------------------------------------------------
//  Zum Anschauen: die naechste Zeile voruebergehend einkommentieren.
//  Vor dem Einbinden in andere Teile wieder auskommentieren.
// ---------------------------------------------------------------------
// sts3215();
