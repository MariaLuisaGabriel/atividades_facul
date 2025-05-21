#!/usr/bin/env pybricks-micropython
from pybricks.ev3devices import Motor
from pybricks.parameters import Port
from pybricks.tools import wait

motorDir = Motor(Port.B)
motorEsq = Motor(Port.C)

dist_entre_rodas = 13
dia_roda = 5

def curvaEixoMedio(angulo):
    motorDir.reset_angle(0)
    motorEsq.reset_angle(0)

    media_motor = 0

    graus_motor = angulo * (dist_entre_rodas/dia_roda)

    while media_motor<graus_motor:
        motorDir.run(100)
        motorEsq.run(-100)

        media_motor = (abs(motorDir.angle())+abs(motorEsq.angle()))/2

    motorDir.hold()
    motorEsq.hold()

def curvaEixoRoda(angulo,roda):
    motorDir.reset_angle(0)
    motorEsq.reset_angle(0)

    if roda == 'A':
        while abs(motorEsq.angle())<angulo:
            motorEsq.run(100)
        motorEsq.hold()

    if roda == 'B':
        while abs(motorDir.angle())<angulo:
            motorDir.run(100)
        motorDir.hold()

motorDir.run(100)
motorDir.run(100)
wait(1000)
curvaEixoRoda(90)