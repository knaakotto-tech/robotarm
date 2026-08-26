// =====================================================================
//  sts3215.scad  --  Dummy-Modell des Feetech STS3215 (Variante C018)
//
//  Kein Detailabbild des Servos, sondern seine Huellkontur.
//  Fuer eine Halterung ist genau das richtig: die Tasche muss den
//  groessten Querschnitt aufnehmen, die Kuehlrippen interessieren nicht.
//
//  Koordinaten-Ursprung: Wellenachse, auf Hoehe der Gehaeuseflaeche
//    +Z = Richtung der Abtriebswelle
//    +X = Laengsrichtung, weg vom Getriebe (zum Motorende)
//    +Y = Breite
//
//  Der Ursprung liegt bewusst auf der Wellenachse: das ist die
//  Gelenkachse. Wenn ein Bauteil sich um dieses Gelenk dreht,
//  ist rotate() um Z dann ohne Umrechnerei richtig.
//
//  Quelle: Feetech Datenblatt ST-3215-C018, Edition A/0, 2023-07-20
// =====================================================================

$fn = 64;

// ---------------------------------------------------------------------
//  Gesichert (im Datenblatt bemasst)
// ---------------------------------------------------------------------
SERVO_L      = 45.23;   // Laenge
SERVO_W      = 24.73;   // Breite
SERVO_H      = 35.0;    // Hoehe des Gehaeuses
SHAFT_D      = 5.90;    // Verzahnung 25T, Aussendurchmesser
SHAFT_H      = 3.40;    // ragt ueber die Gehaeuseflaeche hinaus
IDLER_D      = 6.00;    // Gegenlager auf der Gegenseite
IDLER_H      = 4.10;    // ragt ueber die Gehaeuseflaeche hinaus

// Abgeleitet: Datenblatt bemasst 12.5 von der Gehaeusemitte zur Welle
SHAFT_OFFSET = SERVO_L/2 - 12.5;   // = 10.115 mm von der Getriebe-Stirnseite

// ---------------------------------------------------------------------
//  Noch nicht gesichert  --  bitte nachmessen und hier korrigieren
// ---------------------------------------------------------------------
HOLE_DX      = 21.0;    // Lochabstand in Laengsrichtung   <-- SCHAETZUNG
HOLE_DY      = 21.0;    // Lochabstand in Querrichtung     <-- SCHAETZUNG
HOLE_D       = 2.5;     // Kernloch fuer PA3.0 selbstschneidend
HOLE_CENTER_X = 0;      // Mitte des Lochbilds relativ zur Welle  <-- SCHAETZUNG

// ---------------------------------------------------------------------
//  Spiel fuer Taschen (3D-Druck schrumpft und quillt)
// ---------------------------------------------------------------------
FIT = 0.4;              // pro Seite; bei zu strammem Sitz erhoehen

// =====================================================================
//  Der Servo selbst
// =====================================================================
module sts3215(spiel = 0) {
    l = SERVO_L + 2*spiel;
    w = SERVO_W + 2*spiel;
    h = SERVO_H + 2*spiel;

    // Gehaeuse. Der Ursprung liegt auf der Wellenachse, deshalb
    // wird der Quader um SHAFT_OFFSET verschoben.
    translate([-SHAFT_OFFSET - spiel, -w/2, -h])
        cube([l, w, h]);

    // Abtriebswelle
    cylinder(d = SHAFT_D, h = SHAFT_H);

    // Gegenlager, fluchtet mit der Welle
    translate([0, 0, -h - IDLER_H])
        cylinder(d = IDLER_D, h = IDLER_H);
}

// =====================================================================
//  Die vier Montageloecher als Bohrwerkzeug.
//  Wird mit difference() von einem Halterungsteil abgezogen.
// =====================================================================
module sts3215_loecher(tiefe = 8, d = HOLE_D) {
    for (sx = [-1, 1], sy = [-1, 1])
        translate([HOLE_CENTER_X + sx*HOLE_DX/2, sy*HOLE_DY/2, -tiefe/2])
            cylinder(d = d, h = tiefe);
}

// =====================================================================
//  Kontrollansicht  --  nur aktiv, wenn diese Datei direkt geoeffnet ist
// =====================================================================
sts3215();

// Wellenachse sichtbar machen, damit du siehst, wo der Ursprung liegt
color("red", 0.5)
    translate([0, 0, -SERVO_H - 15])
        cylinder(d = 0.6, h = SERVO_H + 30);
