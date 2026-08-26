// =====================================================================
//  servo_ansicht.scad  --  nur zum Anschauen
//
//  sts3215.scad ist eine Bibliothek und zeichnet absichtlich nichts.
//  Diese Datei bindet sie ein und ruft die Module auf, damit du das
//  Modell sehen kannst. Sie geht nie in ein Bauteil ein.
// =====================================================================

include <sts3215.scad>

// Der Servo
sts3215();

// Wellenachse: der Ursprung des Koordinatensystems
color("red")
    translate([0, 0, -SERVO_H - 12])
        cylinder(d = 1.0, h = SERVO_H + 26);

// Die vier Montageloecher an ihrer berechneten Position
color("blue")
    sts3215_loecher(tiefe = SERVO_H + 20, d = HOLE_D);

// Das Lochbild des Servohorns, auf der Wellenseite
color("green")
    translate([0, 0, SHAFT_H])
        horn_loecher(tiefe = 6);
