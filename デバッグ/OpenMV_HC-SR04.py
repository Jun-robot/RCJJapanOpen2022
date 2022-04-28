import pyb,utime, ustruct
from pyb import UART

trigA = pyb.Pin("P0", pyb.Pin.OUT_PP)
trigA.low()
echoA = pyb.Pin("P1", pyb.Pin.IN)
trigB = pyb.Pin("P2", pyb.Pin.OUT_PP)
trigB.low()
echoB = pyb.Pin("P3", pyb.Pin.IN)
trigC = pyb.Pin("P8", pyb.Pin.OUT_PP)
trigC.low()
echoC = pyb.Pin("P9", pyb.Pin.IN)


uart = UART(3, 19200)


def ultrasonic(myid):
    if myid == 0 :
        trig = trigA
        echo = echoA
    elif myid == 1:
        trig = trigB
        echo = echoB
    elif myid == 2:
        trig = trigC
        echo = echoC


    trig.high()
    utime.sleep_us(10)
    trig.low()

    while echo.value() == 0:
         utime.sleep_us(1)
    t1 = utime.ticks_us()
    while echo.value() == 1:
         utime.sleep_us(1)
    t2 = utime.ticks_us()
    t = utime.ticks_diff(t2, t1)
    L = int(t * 340.00 / 20000)

    if L > 500:
        L = 500


    return L


force_time = 0

while True:
    right = ultrasonic(0)
    back = ultrasonic(1)
    left = ultrasonic(2)

    print("",left,back,right)

    degree = 0

    if right + left > 160 and (right < 35 or left < 35):
        if back > 55:
            degree = 180
        else:
            degree = 0
    elif right + left > 160 and (right >= 35 or left >= 35):
        if back > 45:
            degree = 180
        else:
            degree = 0
    else:
        if back > 60:
            degree = 180
        else:
            degree = 0

    #if back < 35:
        #force_time = utime.ticks_ms() + 3000
        ##print("AA")

    #if force_time > utime.ticks_ms():
        #degree = 360
        ##print("aaa")
    print(degree)


    degree = degree /1.5

    try:
        uart.write(ustruct.pack('B',int(degree)))
    except OSError as err:
        pass
