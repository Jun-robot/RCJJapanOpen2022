import pyb,utime

trig = pyb.Pin("P8", pyb.Pin.OUT_PP)
trig.low()
echo = pyb.Pin("P9", pyb.Pin.IN)

print("aaaaaaa")

while(True):
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


    print(L)

    utime.sleep_ms(10)

#from machine import Pin
#import utime
#trigger = Pin('P0', Pin.OUT)
#echo = Pin('P1', Pin.IN)

#def read_distance():
    #trigger.low()
    #utime.sleep_us(2)
    #trigger.high()
    #utime.sleep(0.00001)
    #trigger.low()

    #a = 0
    #while  a < 50:
        #print(echo.value())
        #a += 1
        #utime.sleep(0.01)

    ##while echo.value() == 0:
        ##signaloff = utime.ticks_us()
    ##print("a")
    ##while echo.value() == 1:
        ##signalon = utime.ticks_us()

    ##timepassed = signalon - signaloff
    ##distance = (timepassed * 0.0343) / 2
    ##print("dinstance: ",distance,"cm")

#while True:
   #read_distance()
   #utime.sleep(0.1)



